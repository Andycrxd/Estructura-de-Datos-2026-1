#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <iostring.h>
#include <arbol.h>
#include "variable.h"
#include "expresion.h"
#include <pila.h>





void abortar(void);
void ordenIterativo(NodoA *raiz,void (*imprimir)(void*));
void imprimirDoubleDouble(void *);
int  Menuopc();

void ingresarInfix(char *cadena);
void convertirPostFix(char  infix [],char postfix[],Pila *pila);
NodoA* crearArbolDesdePostfix(char postfix[]);
int procedencia(char c);

int main(void)
{
	Arbol arbol;
	arbol.raiz = NULL;
	arbol.imprimir = &imprimirVariable;
	arbol.comparar = &compararVariable;
	arbol.liberar = &free;
	Pila pila = {NULL,0,-1,NULL,NULL};

	char infix[100];
	char postfix[100];
	
	int opc =0;
	
	do{
    opc = Menuopc();
    
    switch(opc){
        case 0:
            ingresarInfix(infix);
            convertirPostFix(infix, postfix, &pila);
            arbol.raiz = crearArbolDesdePostfix(postfix); 
			arbol.cantidad = strlen(postfix);
            break;

        case 1:
            if(arbol.raiz != NULL){
                imprimirArbol(arbol);
				printf("\n");
            }else{
                printf("No hay arbol\n");
			}
            break;

        case 2:
            if(arbol.raiz != NULL)
                evaluar(arbol);
            else
                printf("No hay expresion\n");
            break;

        case 3:
				printf("Saliendo...\n");
            break;

        default:
            printf("Error ingresa otro valor\n");
    }

	}while(opc != 3);
	/*
	//NOTA
	arbol.cantidad = 7; // <<-- ACTUALIZAR ESTE VALOR SI SE CREA MANUALMENTE EL ARBOL	
	arbol.raiz = crearNodoA(crearVariable('^'));	
	arbol.raiz->izq = crearNodoA(crearVariable('X'));	
	arbol.raiz->dch = crearNodoA(crearVariable('^'));	
	arbol.raiz->dch->izq = crearNodoA(crearVariable('X'));	
	arbol.raiz->dch->dch = crearNodoA(crearVariable('^'));	
	arbol.raiz->dch->dch->izq = crearNodoA(crearVariable('X'));	
	arbol.raiz->dch->dch->dch = crearNodoA(crearVariable('Y'));	
	
	printf("\n ARBOL\n");
	imprimirArbol(arbol);
	evaluar(arbol);
	*/
	
	
	eliminarArbol(&arbol);

	printf("\n\n FIN DE PROGRAMA\n");
	
	
	return 0;
}


void imprimirDoubleDouble(void *ptr)
{
	double **ptrdouble= ptr;	
	if(!ptrdouble)	
	{		
		printf("null ") ;
		return;
	}
	printf("%lf ",**ptrdouble); 
}

void ordenIterativo(NodoA *raiz,void (*imprimir)(void*))
{
	Pila pila = {NULL,0,-1,imprimir,NULL};
	if(!raiz)
		return;
	NodoA* aux = raiz;
	while( aux || !pilaVacia(pila))
	{			
		while(aux)
		{
			pushDato(&pila,aux);	
			aux = aux->izq;
		}		
		aux = popDato(&pila);
		imprimir(aux);		
		printf(" ");		
		aux= aux->dch;
	}	
	vaciarPila(&pila);
}

void abortar(void)
{
	char c = 'e';
	if( (c=getchar()) == 'e')
		exit(0);
}


int  Menuopc()
{
	int opc=0;
	printf("=================Menu=================\n");
	printf("0. CAPTURAR EXPRESION\n");
	printf("1. IMPRIMIR ARBOL DE EXPRESION\n");
	printf("2. EVALUAR EXPRESION\n");
	printf("3. TERMINAR PROGRAMA\n");
	printf("Ingresa la opcion: ");
	scanf("%d",&opc);
	
	return opc;
	
}

void ingresarInfix(char  infix []){
	printf("Ingesa el valor de infix: ");
	scanf("%s", infix );
}

void convertirPostFix(char infix[], char postfix[], Pila *pila)
{
    int j = 0;

    for(int i = 0; infix[i] != '\0'; i++)
    {
        char c = infix[i];

        // OPERANDO
        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            postfix[j++] = c;
        }

        // PARÉNTESIS IZQ
        else if(c == '(')
        {
            char *dato = malloc(sizeof(char));
            *dato = c;
            pushDato(pila, dato);
        }

        // PARÉNTESIS DER
        else if(c == ')')
        {
            while(!pilaVacia(*pila))
            {
                char *top = (char*)peekPila(*pila);

                if(*top == '(')
                {
                    free(popDato(pila));
                    break;
                }

                top = (char*)popDato(pila);
                postfix[j++] = *top;
                free(top);
            }
        }

        // OPERADORES
        else if(procedencia(c) > 0)
        {
            while(!pilaVacia(*pila))
            {
                char *top = (char*)peekPila(*pila);

                if(procedencia(*top) >= procedencia(c))
                {
                    top = (char*)popDato(pila);
                    postfix[j++] = *top;
                    free(top);
                }
                else break;
            }

            char *dato = malloc(sizeof(char));
            *dato = c;
            pushDato(pila, dato);
        }
    }

    // VACIAR PILA
    while(!pilaVacia(*pila))
    {
        char *dato = (char*)popDato(pila);
        postfix[j++] = *dato;
        free(dato);
    }

    postfix[j] = '\0';
}
NodoA* crearArbolDesdePostfix(char postfix[])
{
    Pila pila = {NULL,0,-1,NULL,NULL};

    for(int i = 0; postfix[i] != '\0'; i++)
    {
        char c = postfix[i];

        // OPERANDO
        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            NodoA* nodo = crearNodoA(crearVariable(c));
            pushDato(&pila, nodo);
        }

        // OPERADOR
        else if(precedencia(crearVariable(c)) > 0)
        {
            NodoA* nodo = crearNodoA(crearVariable(c));

            NodoA* derecho = (NodoA*)popDato(&pila);
            NodoA* izquierdo = (NodoA*)popDato(&pila);

            nodo->izq = izquierdo;
            nodo->dch = derecho;

            pushDato(&pila, nodo);
        }
    }

    // RAÍZ DEL ÁRBOL
    NodoA* raiz = (NodoA*)popDato(&pila);
    return raiz;
}
int procedencia(char c){
	switch(c){
	case '+':
	case '-':
	return 1;
	case '*':case'/':
	return 2;
	case '^':
	return 3;
	case '(':
	return -1;	
	}
	return 0;
}
	
