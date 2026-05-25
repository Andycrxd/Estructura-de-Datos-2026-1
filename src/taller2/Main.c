#include <stdio.h>
#include "../iostring/iostring.h"
#include "../structures/lista/lista.h"
//#include <listadoble.h>
#include "../structures/pila/pila.h"
#include "Alumno.h"

void imprimirEntero(void *dato);
int compararEnteros(void*,void*);

int comparar(void*,void*);
int main()
{
	Pila pila = {NULL,0,7,imprimirEntero,NULL};
	int arreglo[7] = {8,5,6,10,2,3,9};
	for(int i=0; i<7;i++)
		pushDato(&pila,&arreglo[i]);
	
	imprimirPila(pila);
	
	ordenarPila(&pila,compararEnteros);
	imprimirPila(pila);
	return 0;
}

void imprimirEntero(void *dato)
{
	int *datoA = dato;
	printf(" %d",*datoA);
}



int compararEnteros(void *a, void *b)
{
    return (*(int*)a - *(int*)b);
}

