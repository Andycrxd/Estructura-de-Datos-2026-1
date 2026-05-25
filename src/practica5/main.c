#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <stdarg.h>
#include <time.h>
#include <iostring.h>
#include <arbol.h>

int* crearEntero(int);
int compararEntero(void*,void*);
void imprimirEntero(void*);
void imprimirResultado(Resultado resultado);
void invertir_Ramas(NodoA *nodo);
int invertir_arbol(Arbol *arbol);



int ValorNuevo();
int  Menuopc();
void compararArboles(Arbol a1, Arbol a2, int (*comparar)(void*, void*));
void extraerMitades(int *arr1,int *arr2,int longitud,int *i);

void myprintf(char *msg,char *formato,...);
int igualesSoloDatos(NodoA *n1, NodoA *n2, int (*comparar)(void*, void*));
int existeEnArbol(NodoA *raiz, void *dato, int (*comparar)(void*, void*));


NodoA* eliminar(NodoA* raiz, void* dato, int (*comparar)(void*, void*));
int NumeroEliminar();
NodoA* minimo(NodoA* raiz);
int altura(NodoA *raiz) ;

void guardarInorden(NodoA *raiz, int *arr, int *i);
void equilibrar(Arbol *arbol);

int main(void)
{
	
	Arbol arbol;
	arbol.raiz = NULL;
	arbol.cantidad = 0;
	arbol.imprimir = &imprimirEntero;
	arbol.comparar = &compararEntero;
	arbol.liberar = &free;
	
	
	Arbol arbol2;
	arbol2.raiz = NULL;
	arbol2.cantidad = 0;
	arbol2.imprimir = &imprimirEntero;
	arbol2.comparar = &compararEntero;
	arbol2.liberar = &free;
	
	
	
	int opc=0;
	int datonuevo=0;
	int numeliminar=0;
	insertarArbol(&arbol, crearEntero(8));
		insertarArbol(&arbol, crearEntero(7));
		insertarArbol(&arbol, crearEntero(6));
		insertarArbol(&arbol, crearEntero(4));
		insertarArbol(&arbol, crearEntero(5));;
		insertarArbol(&arbol, crearEntero(1));
		insertarArbol(&arbol, crearEntero(10));
		insertarArbol(&arbol, crearEntero(9));
		insertarArbol(&arbol, crearEntero(11));
	
	insertarArbol(&arbol2, crearEntero(7));
	insertarArbol(&arbol2, crearEntero(5));
	insertarArbol(&arbol2, crearEntero(4));
	insertarArbol(&arbol2, crearEntero(1));
	insertarArbol(&arbol2, crearEntero(6));
	insertarArbol(&arbol2, crearEntero(10));
	insertarArbol(&arbol2, crearEntero(9));
	insertarArbol(&arbol2, crearEntero(8));
	insertarArbol(&arbol2, crearEntero(11));
	
	//int n=0;
	do{
		
		
		opc=Menuopc();
		switch(opc){
			case 1:	
				datonuevo =ValorNuevo();
				insertarArbol(&arbol, crearEntero(datonuevo));
			break;
			case 2:
				datonuevo =ValorNuevo();
				insertarArbol(&arbol2, crearEntero(datonuevo));
			break;
			case 3:
				compararArboles(arbol, arbol2, compararEntero);
			break;
			case 4:
				numeliminar = NumeroEliminar();
				arbol.raiz = eliminar(arbol.raiz, &numeliminar, compararEntero);
			break;
			case 5:
				numeliminar = NumeroEliminar();
				arbol2.raiz =eliminar(arbol2.raiz, &numeliminar,compararEntero);
			break;
			case 6:
					printf("Altura Arbol A: %d\n", altura(arbol.raiz));
					printf("Altura Arbol B: %d\n", altura(arbol2.raiz));
			break;
			case 7:
				    equilibrar(&arbol);
					equilibrar(&arbol2);
					printf("Ambos arboles equilibrados\n");
				
			break;
			case 8:	
				imprimirArbol(arbol);
				printf("\n");
				printf("\n");
				printf("\n");
				imprimirArbol(arbol2);
				printf("\n");
			break;
			case 9:
			
			break;
			default:
				printf("Error al elegir a opcion");
		}
		
		
	}while(opc!=9);
	
	eliminarArbol(&arbol);
	eliminarArbol(&arbol2);
	printf("\n\n FIN DE PROGRAMA\n");
	
	return 0;
	
}

NodoA* eliminar(NodoA* raiz, void* dato, int (*comparar)(void*, void*)) {

    if(raiz == NULL)
        return NULL;

    if(comparar(dato, raiz->dato) < 0)
        raiz->izq = eliminar(raiz->izq, dato, comparar);

    else if(comparar(dato, raiz->dato) > 0)
        raiz->dch = eliminar(raiz->dch, dato, comparar);

    else {
        // caso 1 y 2
        if(raiz->izq == NULL) {
            NodoA* temp = raiz->dch;
            free(raiz);
            return temp;
        }
        else if(raiz->dch == NULL) {
            NodoA* temp = raiz->izq;
            free(raiz);
            return temp;
        }

        // caso 3
        NodoA* temp = minimo(raiz->dch);
        raiz->dato = temp->dato;
        raiz->dch = eliminar(raiz->dch, temp->dato, comparar);
    }

    return raiz;
}

NodoA* minimo(NodoA* raiz) {
    while(raiz->izq != NULL)
        raiz = raiz->izq;
    return raiz;
}





void compararArboles(Arbol a1, Arbol a2, int (*comparar)(void*, void*)) {

    if(igualesEstructuraDatos(a1.raiz, a2.raiz, comparar)) {
        printf("Iguales en estructura y datos\n");
    }
    else if(igualesSoloDatos(a1.raiz, a2.raiz, comparar) &&
            igualesSoloDatos(a2.raiz, a1.raiz, comparar)) {

        printf("Solo iguales en datos\n");
    }
    else {
        printf("Diferentes\n");
    }
}

int igualesSoloDatos(NodoA *n1, NodoA *n2, int (*comparar)(void*, void*)) {

    if(n1 == NULL)
        return 1;

    if(!existeEnArbol(n2, n1->dato, comparar))
        return 0;

    return igualesSoloDatos(n1->izq, n2, comparar) &&
           igualesSoloDatos(n1->dch, n2, comparar);
}

int existeEnArbol(NodoA *raiz, void *dato, int (*comparar)(void*, void*)) {

    if(raiz == NULL)
        return 0;

    if(comparar(raiz->dato, dato) == 0)
        return 1;

    return existeEnArbol(raiz->izq, dato, comparar) ||
           existeEnArbol(raiz->dch, dato, comparar);
}



int  Menuopc()
{
	
	
	int opc=0;
	printf("=================Menu=================\n");
	printf("1. Insertar en Árbol A \n");
	printf("2. Insetar en Arbol B \n");
	printf("3. Comparar Arboles \n");
	printf("4. Eliminar dato en Árbol A\n");
	printf("5. Eliminar dato en Árbol B\n");
	printf("6. Profundidades\n");
	printf("7. Equilibrar arboles\n");
	printf("8. Mostrar arboles\n");
	printf("9. Salir del programa\n");
	printf("Ingresa la opcion: ");
	scanf("%d",&opc);
	
	
	return opc;
	
}

int altura(NodoA *raiz) {

    if(raiz == NULL)
        return 0;

    int izq = altura(raiz->izq);
    int der = altura(raiz->dch);

    return 1 + (izq > der ? izq : der);
}


int ValorNuevo()
{
	
	int datonuevo=0;
	
	printf("Ingresa el nuevo valor : ");
	scanf("%d",&datonuevo);
	
	return datonuevo;
	
	
}


int NumeroEliminar(){
	
	int datonuevo=0;
	
	printf("Ingresa el valor para eliminar : ");
	scanf("%d",&datonuevo);
	
	return datonuevo;
	
}



//3,13,20,1
void invertir_Ramas(NodoA *nodo)
{
	
	
	if(nodo == NULL)
		return;

	NodoA *temp = nodo->izq;
	nodo->izq = nodo->dch;
	nodo->dch = temp;

	invertir_Ramas(nodo->izq);
	invertir_Ramas(nodo->dch);
	
	
}

int invertir_arbol(Arbol *arbol)
{
	if(arbol != NULL)
		invertir_Ramas(arbol->raiz);

	return 1;
}






void imprimirResultado(Resultado resultado)
{
	
	if(resultado.nodo)
	{
		if(resultado.padre)
		{
			printf("\n PADRE: ");
			imprimirEntero(resultado.padre->dato);
			printf("\n RAMA: %s",
			(resultado.rama) ? "DERECHA":"IZQUIERDA");
		}
		printf("\n Nodo: ");
		imprimirEntero(resultado.nodo->dato);
	}
	else
		printf("\n NODO NO ENCONTRADO");
	
}


int* crearEntero(int dato)
{
	
	int *nuevo = malloc(sizeof(int));
	*nuevo = dato;
	return nuevo;
	
}

int compararEntero(void*a,void*b)
{
	
	int *aa = a,*bb=b;
	if(*aa==*bb)return 0;
	else if(*aa<*bb)return -1;
	else return 1;
	
}

void imprimirEntero(void *a)
{
	int *aa=a;
	printf("%d",*aa);
	
}


void myprintf(char* msg,char *formato,...)
{
	
	va_list args;
    va_start(args, formato);
	printf("\n %s ",msg);
	char *ptr = formato;
	while(*ptr!='\0')
	{
		switch(*ptr)
		{
			case 'd':
				printf("%d ",va_arg(args, int));
				break;
			case 'c':
				printf("%c ",va_arg(args, int));				
				break;
			case 'f':
				printf("%f ",va_arg(args, double));				
				break;
			case 'x':
				printf("%p ",va_arg(args, Arbol*));				
				break;
		}
		ptr++;
	}
	va_end(args);
	
	
}


void guardarInorden(NodoA *raiz, int *arr, int *i) {
    if(raiz == NULL)
        return;

    guardarInorden(raiz->izq, arr, i);

    arr[*i] = *(int*)raiz->dato;
    (*i)++;

    guardarInorden(raiz->dch, arr, i);
}

void equilibrar(Arbol *arbol) {

    int n = arbol->cantidad;

    int *arr1 = malloc(n * sizeof(int));
    int *arr2 = malloc(n * sizeof(int));

    int i = 0;
    guardarInorden(arbol->raiz, arr1, &i);

    i = 0;
    extraerMitades(arr1, arr2, n, &i);

    arbol->raiz = NULL;
    arbol->cantidad = 0;

    for(int j = 0; j < n; j++) {
        insertarArbol(arbol, crearEntero(arr2[j]));
    }

    free(arr1);
    free(arr2);
}
void extraerMitades(int *arr1,int *arr2,int longitud,int *i)
{
	
	if(longitud <= 0)
		return;
	int mitad = longitud/2;
	//EXTRAER MITAD
	arr2[*i] = arr1[mitad];
	(*i)++;
	//IZQUIERDA
	extraerMitades(arr1,arr2,mitad,i);
	//DERECHA
	extraerMitades(arr1+mitad+1,arr2,longitud-1-mitad,i);	
	
}