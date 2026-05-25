#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <HashQ.h>
#include "Libro.h"
#include "Almacen.h"
#include <ctype.h>


int compararTituloQsort(const void *a, const void *b);
int compararAutorQsort(const void *a, const void *b);
int compararFechaTituloQsort(const void *a, const void *b);

void buscarTituloRango(Acervo acervo);
void buscarAutorRango(Acervo acervo);
void buscarFechaRango(Acervo acervo);

void mostrarLibrosDelAutor(Acervo acervo, const char *autor);
void mostrarLibrosDelAnio(Acervo acervo, int anio);

void convertirMinusculas(char *cadena);

int main(void)
{
    Acervo acervo = obtener_libros();

    HashQTable hashISBN;
    HashQTable hashTitulo;
    HashQTable hashAutor;
    HashQTable hashFecha;

    inicializarHashLibro(&hashISBN, 100, foldingISBN, compararISBN);
    inicializarHashLibro(&hashTitulo, 100, foldingTitulo, compararTitulo);
    inicializarHashLibro(&hashAutor, 100, foldingAutor, compararAutor);
    inicializarHashLibro(&hashFecha, 100, foldingFecha, compararFecha);

    for(int i = 0; i < acervo.cantidad; i++)
    {
        fn_insertKey(&hashISBN, &acervo.libros[i]);
        fn_insertKey(&hashTitulo, &acervo.libros[i]);
        fn_insertKey(&hashAutor, &acervo.libros[i]);
        fn_insertKey(&hashFecha, &acervo.libros[i]);
    }

    int op = 0;
	int e = 0;

    do
    {
        printf("\n------------- Tablas H -------------\n");
        printf("1. Busqueda ISBN\n");
        printf("2. Busqueda en base Titulo\n");
        printf("3. Busqueda en base Autor\n");
        printf("4. Busqueda en base a la fecha\n");
        printf("5. Salir\n");
        printf("------------------------------------\n");
        printf("\nElige la opcion: ");
        scanf("%d", &op);

        switch(op)
        {
            case 1:
            {
				
				
				printf("--------- 	ISBN ----------------\n");
				printf("1.Eliminar por sbn\n");
				printf("0.Buscar por isbn\n");
				printf("Elige la opcion: ");
				scanf("%d", &e);
				
				
				if(e==1)
				{
					char isbn[MAX_ISBN];
					Libro temp = {0};

					printf("\n ISBN: ");
					scanf(" %19[^\n]", isbn);
					strcpy(temp.isbn, isbn);

					Libro *encontrado = fn_searchKey(&hashISBN, &temp);
					
					if(encontrado)
					{
						fn_deleteKey(&hashISBN, encontrado);
						fn_deleteKey(&hashTitulo, encontrado);
						fn_deleteKey(&hashAutor, encontrado);
						fn_deleteKey(&hashFecha, encontrado);

						printf("ISBN eliminado correctamente\n");
					}else{
						printf("No encontrado el isbn!!\n");
					}
					
				}else{
					char isbn[MAX_ISBN];
					Libro temp = {0};

					printf("\nISBN: ");
					scanf(" %19[^\n]", isbn);
					strcpy(temp.isbn, isbn);

					Libro *encontrado = fn_searchKey(&hashISBN, &temp);

					if(encontrado)
					{
						printf("\n");
						imprimirLibro(encontrado);
					}
					else
					{
						printf("\nNo encontrado");
					}
				}
            }
			
            break;

            case 2:
            {
                int subop;

                printf("\n1. Buscar titulo exacto");
                printf("\n2. Buscar por rango");
                printf("\nOpcion: ");
                scanf("%d", &subop);

                switch(subop)
                {
                    case 1:
                    {
                        char titulo[MAX_TITULO];
                        Libro temp = {0};

                        printf("\nTitulo: ");
                        scanf(" %44[^\n]", titulo);
                        strcpy(temp.titulo, titulo);

                        Libro *encontrado = fn_searchKey(&hashTitulo, &temp);

                        if(encontrado)
                        {
                            printf("\n");
                            imprimirLibro(encontrado);
                        }
                        else
                        {
                            printf("\nNo encontrado");
                        }
                    }
                    break;

                    case 2:
                        buscarTituloRango(acervo);
                    break;

                    default:
                        printf("\nOpcion invalida");
                }
            }
            break;

            case 3:
            {
                int subop;

                printf("\n1. Buscar autor exacto");
                printf("\n2. Buscar autor por rango");
                printf("\nOpcion: ");
                scanf("%d", &subop);

                switch(subop)
                {
                    case 1:
                    {
                        char autor[MAX_AUTOR];
						Libro temp = {0};

                        printf("\nAutor: ");
                        scanf(" %29[^\n]",autor);
                        strcpy(temp.autor, autor);

                        Libro *encontrado = fn_searchKey(&hashAutor, &temp);

                        if(encontrado)
                        {
                            mostrarLibrosDelAutor(acervo, autor);
                        }
                        else
                        {
                            printf("\nNo encontrado");
                        }
                    }
                    break;

                    case 2:
                        buscarAutorRango(acervo);
                    break;

                    default:
                        printf("\nOpcion invalida");
                }
            }
            break;

            case 4:
            {
                int subop;

                printf("\n1. Buscar por año");
                printf("\n2. Buscar por rango");
                printf("\nOpcion: ");
                scanf("%d", &subop);

                switch(subop)
                {
                    case 1:
                    {
                        int fecha;
                        Libro temp = {0};

                        printf("\nAño de publicacion: ");
                        scanf("%d", &fecha);
                        temp.fecha = fecha;

                        Libro *encontrado = fn_searchKey(&hashFecha, &temp);

                        if(encontrado)
                        {
                            mostrarLibrosDelAnio(acervo, fecha);
                        }
                        else
                        {
                            printf("\nNo encontrado");
                        }
                    }
                    break;

                    case 2:
                        buscarFechaRango(acervo);
                    break;

                    default:
                        printf("\nOpcion invalida");
                }
            }
            break;

            case 5:
                break;

            default:
                printf("\nOpcion invalida\n");
        }

    } while(op != 5);

    return 0;
}

/* ===================== Búsquedas por rango ===================== */
void buscarTituloRango(Acervo acervo)
{
    char inferior[MAX_TITULO];
    char superior[MAX_TITULO];

    printf("\nLimite inferior: ");
    scanf(" %44[^\n]", inferior);

    printf("Limite superior: ");
    scanf(" %44[^\n]", superior);

    convertirMinusculas(inferior);
    convertirMinusculas(superior);

    Libro *copia = malloc(acervo.cantidad * sizeof(Libro));

    for(int i = 0; i < acervo.cantidad; i++)
    {
        copia[i] = acervo.libros[i];
    }

    qsort(copia, acervo.cantidad, sizeof(Libro), compararTituloQsort);

    printf("\n--- LIBROS EN RANGO DE TITULO ---\n");

    for(int i = 0; i < acervo.cantidad; i++)
    {
        char tituloTemp[MAX_TITULO];

        strcpy(tituloTemp, copia[i].titulo);

        convertirMinusculas(tituloTemp);

        if(tituloTemp[0] >= inferior[0] &&
           tituloTemp[0] <= superior[0])
        {
            imprimirLibro(&copia[i]);
            printf("\n");
        }
    }

    free(copia);
}

void buscarAutorRango(Acervo acervo)
{
    char inferior[MAX_AUTOR];
    char superior[MAX_AUTOR];

    printf("\nLimite inferior: ");
    scanf(" %29[^\n]", inferior);

    printf("Limite superior: ");
    scanf(" %29[^\n]", superior);

    convertirMinusculas(inferior);
    convertirMinusculas(superior);

    Libro *copia = malloc(acervo.cantidad * sizeof(Libro));

    for(int i = 0; i < acervo.cantidad; i++)
    {
        copia[i] = acervo.libros[i];
    }

    qsort(copia, acervo.cantidad, sizeof(Libro), compararAutorQsort);

    printf("\n--- AUTORES EN RANGO ---\n");

    for(int i = 0; i < acervo.cantidad; i++)
    {
        char autorTemp[MAX_AUTOR];

        strcpy(autorTemp, copia[i].autor);

        convertirMinusculas(autorTemp);

        if(autorTemp[0] >= inferior[0] &&
           autorTemp[0] <= superior[0])
        {
            imprimirLibro(&copia[i]);
            printf("\n");
        }
    }

    free(copia);
}

void buscarFechaRango(Acervo acervo)
{
    int inferior;
    int superior;

    printf("\nAño inferior: ");
    scanf("%d", &inferior);

    printf("Año superior: ");
    scanf("%d", &superior);

    Libro *copia = malloc(acervo.cantidad * sizeof(Libro));

    for(int i = 0; i < acervo.cantidad; i++)
    {
        copia[i] = acervo.libros[i];
    }

    qsort(copia, acervo.cantidad, sizeof(Libro), compararFechaTituloQsort);

    printf("\n--- LIBROS EN RANGO DE FECHAS ---\n");

    for(int i = 0; i < acervo.cantidad; i++)
    {
        if(copia[i].fecha >= inferior &&
           copia[i].fecha <= superior)
        {
            imprimirLibro(&copia[i]);
            printf("\n");
        }
    }

    free(copia);
}

void mostrarLibrosDelAutor(Acervo acervo, const char *autor)
{
    Libro *coincidencias = malloc(acervo.cantidad * sizeof(Libro));
    if(!coincidencias)
    {
        printf("\nError de memoria");
        return;
    }

    int n = 0;

    for(int i = 0; i < acervo.cantidad; i++)
    {
        if(strcmp(acervo.libros[i].autor, autor) == 0)
        {
            coincidencias[n++] = acervo.libros[i];
        }
    }

    if(n == 0)
    {
        printf("\nNo encontrado");
        free(coincidencias);
        return;
    }

    qsort(coincidencias, n, sizeof(Libro), compararFechaTituloQsort);

    printf("\n--- LIBROS DEL AUTOR ORDENADOS POR FECHA ---\n");
    for(int i = 0; i < n; i++)
    {
        imprimirLibro(&coincidencias[i]);
        printf("\n");
    }

    free(coincidencias);
}

void mostrarLibrosDelAnio(Acervo acervo, int anio)
{
    Libro *coincidencias = malloc(acervo.cantidad * sizeof(Libro));
    if(!coincidencias)
    {
        printf("\nError de memoria");
        return;
    }

    int n = 0;

    for(int i = 0; i < acervo.cantidad; i++)
    {
        if(acervo.libros[i].fecha == anio)
        {
            coincidencias[n++] = acervo.libros[i];
        }
    }

    if(n == 0)
    {
        printf("\nNo encontrado");
        free(coincidencias);
        return;
    }

    qsort(coincidencias, n, sizeof(Libro), compararTituloQsort);

    printf("\n--- LIBROS DEL AÑO ORDENADOS POR TITULO ---\n");
    for(int i = 0; i < n; i++)
    {
        imprimirLibro(&coincidencias[i]);
        printf("\n");
    }

    free(coincidencias);
}


int compararTituloQsort(const void *a, const void *b)
{
    return compararTitulo((void *)a, (void *)b);
}

int compararAutorQsort(const void *a, const void *b)
{
    return compararAutor((void *)a, (void *)b);
}

              int compararFechaTituloQsort(const void *a, const void *b)
{
    const Libro *l1 = (const Libro *)a;
    const Libro *l2 = (const Libro *)b;

    if(l1->fecha != l2->fecha)
    {
        return l1->fecha - l2->fecha;
    }

    return strcmp(l1->titulo, l2->titulo);
}
void convertirMinusculas(char *cadena)
{
    for(int i = 0; cadena[i] != '\0'; i++)
    {
        cadena[i] = tolower((unsigned char)cadena[i]);
    }
}

