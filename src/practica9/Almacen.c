#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Almacen.h"


static int foldingCadena(const char *cadena)
{
    int key = 0, sector = 1, suma = 0;

    for(int i = 0; cadena[i] != '\0'; i++)
    {
        suma += (unsigned char)cadena[i];

        if(i != 0 && (i + 1) % 3 == 0)
        {
            key += sector * suma;
            suma = 0;
            sector++;
        }
    }

    key += sector * suma;
    return key;
}


int foldingISBN(void *data)
{
    Libro *libro = (Libro*)data;
    int suma = 0;

    for(int i = 0; libro->isbn[i] != '\0'; i++)
    {
        if(libro->isbn[i] != '-')
            suma += (unsigned char)libro->isbn[i];
    }

    return suma;
}


int foldingTitulo(void *data)
{
    Libro *libro = (Libro*)data;
    return foldingCadena(libro->titulo);
}


int foldingAutor(void *data)
{
    Libro *libro = (Libro*)data;
    return foldingCadena(libro->autor);
}


int foldingFecha(void *data)
{
    Libro *libro = (Libro*)data;
    return libro->fecha;
}


int compararISBN(void *a, void *b)
{
    Libro *libro1 = (Libro*)a;
    Libro *libro2 = (Libro*)b;
    return strcmp(libro1->isbn, libro2->isbn);
}



int compararTitulo(void *a, void *b)
{
    Libro *libro1 = (Libro*)a;
    Libro *libro2 = (Libro*)b;
    return strcmp(libro1->titulo, libro2->titulo);
}


int compararAutor(void *a, void *b)
{
    Libro *libro1 = (Libro*)a;
    Libro *libro2 = (Libro*)b;
    return strcmp(libro1->autor, libro2->autor);
}


int compararFecha(void *a, void *b)
{
    Libro *libro1 = (Libro*)a;
    Libro *libro2 = (Libro*)b;

    if(libro1->fecha < libro2->fecha) return -1;
    if(libro1->fecha > libro2->fecha) return 1;
    return 0;
}


void inicializarHashLibro(HashQTable *hash, int len, fn_folding folding, fn_comparar comparar)
{
    hash->table = calloc(len, sizeof(void*));
    hash->len = len;
    hash->cant = 0;
    hash->min = 30;
    hash->max = 60;
    hash->fixed = 60;
    hash->verbose = 0;
    hash->folding = folding;
    hash->imprimir = imprimirLibro;
    hash->comparar = comparar;
}