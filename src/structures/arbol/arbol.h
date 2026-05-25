#ifndef ARBOL_H
#define ARBOL_H

#include "../nodos/nodoarbol.h"
#include <stdio.h>

#define PREORDEN 1
#define ORDEN 2
#define POSTORDEN 3
#define INVERSO 4
#define IZQUIERDA 0
#define DERECHA 1

typedef struct
{
	NodoA *padre;
	NodoA *nodo;
	void *dato;
	int rama;
}Resultado;

typedef struct
{
	NodoA *raiz;
	int cantidad;
	void (*imprimir)(void*);
	int (*comparar)(void*,void*);
	void (*liberar)(void*);
	
}Arbol;

Resultado buscarNodoEnArbol(Arbol arbol,void *dato);
void* buscarEnArbol(Arbol arbol,void *dato);

void invertirArbol(Arbol *arbol);
void eliminarArbol(Arbol *arbol);
void insertarArbol(Arbol *arbol,void *dato);
void imprimirArbol(Arbol arbol);

void imprimir_arbol(NodoA *nodo, int nivel,void (*imprimir)(void*));
void imprimirOrden(Arbol arbol,int opcion);

void insertarArbolOrdenado(NodoA *raiz,void *dato,int (*comparar)(void*,void*));
void orden(NodoA *raiz,void (*imprimir)(void*));
void inverso(NodoA *raiz,void (*imprimir)(void*));
void postorden(NodoA *raiz,void (*imprimir)(void*));
void eliminar_NodosA(NodoA *raiz,void (*liberar)(void*));
void* buscarEnArbolDato(Arbol arbol,void *dato);


int igualesEstructuraDatos(NodoA *n1, NodoA *n2, int (*comparar)(void*, void*));
#endif