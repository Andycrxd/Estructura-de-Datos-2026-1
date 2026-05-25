
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
void invertirRamas(NodoA *nodo);
int invertir_arbol(Arbol *arbol);

void extraerMitades(int *arr1,int *arr2,int longitud,int *i);

void myprintf(char *msg,char *formato,...);

int main(void)
{
	Arbol arbol;
	arbol.raiz = NULL;
	arbol.cantidad = 0;
	arbol.imprimir = &imprimirEntero;
	arbol.comparar = &compararEntero;
	arbol.liberar = &free;
	
	insertarArbol(&arbol, crearEntero(9));
	insertarArbol(&arbol, crearEntero(8));
	insertarArbol(&arbol, crearEntero(11));
	insertarArbol(&arbol, crearEntero(7));
	insertarArbol(&arbol, crearEntero(6));
	insertarArbol(&arbol, crearEntero(5));
	insertarArbol(&arbol, crearEntero(10));
	insertarArbol(&arbol, crearEntero(12));
	insertarArbol(&arbol, crearEntero(9));
	insertarArbol(&arbol, crearEntero(1));
	insertarArbol(&arbol, crearEntero(1));
	insertarArbol(&arbol, crearEntero(1));
	insertarArbol(&arbol, crearEntero(1));
	insertarArbol(&arbol, crearEntero(1));
	insertarArbol(&arbol, crearEntero(1));
	insertarArbol(&arbol, crearEntero(0));
	
	printf("\n");
	imprimirArbol(arbol);		
	
	//int valor =11;
	//void *dato = buscarEnArbol(arbol,&valor);
	//if(dato)
		//printf("\n ENCONTRADO");
	//else
		//printf("\n NO ENCONTRADO");
	
	//imprimirResultado(buscarNodoEnArbol(arbol,&valor));

	int num;
	printf("\n");
	printf("Ingresa l numero que deseas buscar dentro del Arbol: ");
	scanf("%d",&num);
	
	void *dat= &num;
	void *datos =buscarEnArbolDato(arbol,dat);
	
	
	printf("\n");
	printf("\n");
	printf("\n");
	
	
	invertir_arbol(&arbol);
	
	imprimirArbol(arbol);
	
	
	if( datos ==NULL){
		printf("\nNo lo encontro :V");
	}else if(datos != NULL)
		printf("\nLo encontro %d",*(int*)datos);
	
	printf("\n");
	printf("\n");
	printf("\n");
	

	
	eliminarArbol(&arbol);
	printf("\n\n FIN DE PROGRAMA\n");
	
	return 0;
	
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