#ifndef HEAD_H
#define HEAD_H

#include "../nodos/nodoarbol.h"
#include <stdio.h>
#include <stdlib.h>
#include <pila.h>

#define HEAP_MIN 0
#define HEAP_MAX 1

typedef int (*fn_comparar)(void*,void*);
typedef void (*fn_imprimir)(void*);

typedef struct
{
	unsigned char tipo;
	int cantidad;
	void **datos;
	NodoA *raiz;
	fn_comparar comparar;
	fn_imprimir imprimir;
}Heap;

typedef struct {
    char nombre[50];
    int paginas;
} Archivo;

Heap crearHeap(unsigned char tipo,fn_comparar comparar,fn_imprimir imprimir);
void insertarHeap( Heap *heap,void *dato);
void* eliminarHeap( Heap *heap);
void imprimirHeap( Heap heap);



void heapify_min(Heap *heap,int padre);
void heapify(Heap *heap);



//--- FUNCIONES DEL PROGRAMA ---
void agregarArchivo(Heap *heap);
void imprimirArchivoCola(Heap *heap);
void eliminarArchivo(Heap *heap);
void vaciarCola(Heap *heap);
void cambiarPrioridad(Heap *heap);
void mostrarTop5(Heap heap);

//--- FUNCIONES AUXILIARES ---
int compararArchivos(void *a, void *b);
void imprimirArchivoHeap(void *a);
void cambiarPrioridad(Heap *heap);

#endif