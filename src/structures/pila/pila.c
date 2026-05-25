#include "pila.h"
#include <string.h>
#include <ctype.h>

//VERIFICIACION
int pilaVacia(Pila pila)
{
	return pila.cima == NULL && pila.cantidad==0;
}

int pilaVacia2(Pila pila)
{
	return pila.cima == NULL ;
}

int pilaLlena(Pila pila)
{
	return pila.cantidad == pila.capacidad;
}

//DATOS
void pushDato(Pila *pila,void *dato)
{
	if(pilaLlena(*pila))
	{
		printf("\nOVERFLOW");
		return;
	}
	Nodo *nuevaCima = crearNodo(dato);
	nuevaCima->sig = pila->cima;	
	pila->cima = nuevaCima; 
	pila->cantidad++;
}


void* popDato(Pila *pila)
{
	void *dato = NULL;
	if(pilaVacia(*pila))
	{
		printf("\nUNDERFLOW");
		return dato;	
	}
	Nodo *cimaVieja = pila->cima;
	pila->cima = pila->cima->sig;	
	dato = cimaVieja->dato;
	free(cimaVieja);
	pila->cantidad--;	
	return dato;
}

void* peekPila(Pila pila)
{
	void  *dato = NULL;
	if(pilaVacia(pila))
	{
		printf("\nUNDERFLOW");
		return dato;	
	}
	Nodo *cimaVieja = pila.cima;
	
	dato = cimaVieja->dato;
	
	return dato;
}


//NODOS
void pushNodo(Pila *pila,Nodo *nodo)
{
	if(pilaLlena(*pila))
	{
		printf("\nOVERFLOW");
		return;
	}
	nodo->sig = pila->cima;	
	pila->cima = nodo; 
	pila->cantidad++;
}

Nodo* popNodo(Pila *pila)
{
	Nodo *cimaVieja = NULL;
	if(pilaVacia(*pila))
	{
		printf("\nUNDERFLOW");
		return cimaVieja;	
	}
	cimaVieja = pila->cima;
	pila->cima = pila->cima->sig;	
	pila->cantidad--;	
	cimaVieja->sig = NULL;
	return cimaVieja;
}

//VACIAR/ELIMINAR PILA
void vaciarPila(Pila *pila)
{
	while(!pilaVacia(*pila))
	{
		popDato(pila);
	}
}

void eliminarPila(Pila *pila)
{
	while(!pilaVacia(*pila))
	{
		void * dato = popDato(pila);
		if(pila->liberar)
			pila->liberar(dato);
	}	
}


//IMPRIMIR RESPETAR LIFO
void imprimirPila(Pila pila)
{	
	Pila aux = {NULL,0,-1,NULL,NULL};	
	printf("\n [%d]PILA:",pila.cantidad);
	//IMPRIMIR CIMAS ORIGINAL
	//REMOVER LOS NODOS DE LA ORIGINAL
	//PASARLOS A LA AUX
	while(!pilaVacia(pila))
	{
		printf("\n");
		pila.imprimir( pila.cima->dato);
		pushNodo( &aux , popNodo(&pila) );
	}	
	//RESTAURAR
	//REMOVER LOS NODOS DE LA AUX
	//PASARLOS A LA ORIGINAL
	while( !pilaVacia(aux))
	{
		pushNodo( &pila , popNodo(&aux) );
	}	
}


void ordenarPila(Pila *pila, int (*comparar)(void*,void*))
{
    
    Pila p1={NULL,0,pila->capacidad,pila->imprimir,NULL};
    Pila p2={NULL,0,pila->capacidad,pila->imprimir,NULL};
    
	
    void *temp;


    while(!pilaVacia(*pila))
    {
        temp = popDato(pila);


		while(!pilaVacia(p1) && comparar(p1.cima->dato, temp) < 0)
		{
			pushDato(&p2, popDato(&p1));
		}

        pushDato(&p1, temp);

        while(!pilaVacia(p2))
        {
            pushDato(&p1, popDato(&p2));
        }
		
    }
	
	while(!pilaVacia(p1))
		pushDato(pila, popDato(&p1));


}

int palindromo(char *cadena)
{
	Pila pila = {NULL,0,-1,NULL,NULL};

	
	if(cadena== NULL){
		return 0;
	}
	
	int valorCadena = strlen(cadena);
	
	char cadenita[valorCadena];
	int j=0;
	for(int i=0; cadena[i]!='\0' ; i++){
	
		if(cadena[i] != ' '){
			cadena[i] = tolower(cadena[i]);
			cadenita[j] = cadena[i];
		
			j++;
		}
	}
	printf("\n");
	
	for(int i=0;i<j; i++){
		char *nuevo = malloc(sizeof(char));
        *nuevo = cadenita[i];
		pushDato(&pila,nuevo);
	
	}

	int cambio=0;
	char *letrita;

	for(int i=0; i<j; i++){
		letrita = (char*)popDato(&pila);
	
		if(*letrita == cadenita[i]){
				printf("%c",*letrita);
		}else{
				cambio=1;
				goto salir;
		}
	
	}
	
	if(cambio==1){
		salir:
		//printf("No es palindromo!!!");
		return 0;
	}else{
		printf("\n");
		//printf("\nEs palindromo!!!");
		return 1;
	}


}

int verificarParentesis(char *cadena)
{
	Pila pila = {NULL,0,-1,NULL,NULL};

	for(int i=0; cadena[i]!= '\0' ; i++)// hasta que cadena se nulo
	{
		if(cadena[i]=='('||cadena[i]=='['||cadena[i]=='{')// si contiene alguno d estos lo inserta en la pila
		{
			char *nuevo = malloc(sizeof(char));
			*nuevo = cadena[i];
			pushDato(&pila, nuevo);
		}
		
		if(cadena[i]==')'||cadena[i]==']'||cadena[i]=='}')//si contiene algumos de estos los saca de la pila
		{
			if(pilaVacia(pila))//si la pila esta vacia significa que habrio mal el parentesis error al iniciar
              return 0;

            char *temp = (char*)popDato(&pila);
			char apertura = *temp;
			free(temp);

			if(!esPareja(apertura, cadena[i]))//si son del mismo 
				return 0;
		}
	}
	
	if(pilaVacia(pila)){ //si la pila esta vacia signica que si se ejecuto bien
		return 1;
	}else{
		return 0;//si existe algo es que la pila tiene corchetes incorectos
	}
}
int esPareja(char a, char c)
{
    if(a == '(' && c == ')') return 1;
    if(a == '[' && c == ']') return 1;
    if(a == '{' && c == '}') return 1;
    return 0;
}
