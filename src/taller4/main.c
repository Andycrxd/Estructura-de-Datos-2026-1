#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>
#include <iostring.h>
#include <heap.h>

int* crearEntero(int);
int compararEntero(void*,void*);
void imprimirEntero(void*);
void construirArbol(Heap heap);
void imprimirArbolRec(Heap heap, int i, int nivel, char lado);

int main(void)
{
	Heap heap = crearHeap(HEAP_MIN,compararEntero,imprimirEntero);
	printf("\n INICIO");
	insertarHeap(&heap, crearEntero(7));
	insertarHeap(&heap, crearEntero(4));
	insertarHeap(&heap, crearEntero(5));
	insertarHeap(&heap, crearEntero(2));
	insertarHeap(&heap, crearEntero(1));
	insertarHeap(&heap, crearEntero(3));

	
	//imprimirHeap(heap);
	heapify(&heap);
	//imprimirHeap(heap);
	heap.tipo = HEAP_MAX;
	heapify(&heap);
	imprimirHeap(heap);
	/*
	while(heap.cantidad)
	{
		printf("\n Cantidad:  %d",heap.cantidad);
		void *dato = eliminarHeap(&heap);
		printf("\n Dato eliminado: ");
		imprimirEntero(dato);
		free(dato);
	}
	*/
	printf("\n\nARBOL:\n");
	construirArbol(heap);
	
	
	
	printf("\n\n FIN DE PROGRAMA\n");
	
	
	return 0;
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



//crar un arreglo auxiliar con los mismos datos
//validar los datos 
//aux= Nodo[i]
//aux->izq = nodos[2Xi+1]
//aux-?dch (2*i+2)<cant)? nodos[2xi+2]:NULL;

void construirArbol(Heap heap)
{
    if(heap.cantidad == 0)
    {
        printf("\nHeap vacío\n");
        return;
    }

    imprimirArbolRec(heap, 0, 0, ' ');
}
void imprimirArbolRec(Heap heap, int i, int nivel, char lado)
{
    if(i >= heap.cantidad)
    {
        return;
    }

    // Dibujar líneas verticales
    for(int j = 0; j < nivel - 1; j++)
    {
        printf("|   ");
    }

    // Rama
    if(nivel > 0)
    {
        printf("|----%c ", lado);
    }

    // Imprimir dato
    heap.imprimir(heap.datos[i]);
    printf("\n");

    //  IMPORTANTE: primero derecho, luego izquierdo
    imprimirArbolRec(heap, 2*i + 2, nivel + 1, 'R');
    imprimirArbolRec(heap, 2*i + 1, nivel + 1, 'L');
}