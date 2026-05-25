#ifndef ALMACEN_H
#define ALMACEN_H

#include "Libro.h"
#include "HashQ.h"

int foldingISBN(void *data);
int foldingTitulo(void *data);
int foldingAutor(void *data);
int foldingFecha(void *data);

int compararISBN(void *a, void *b);
int compararTitulo(void *a, void *b);
int compararAutor(void *a, void *b);
int compararFecha(void *a, void *b);

void inicializarHashLibro(HashQTable *hash, int len, fn_folding folding, fn_comparar comparar);

#endif