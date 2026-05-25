
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

void imprimirArchivoHeap(void *a);
int main() {
    int op;
	Heap heap = crearHeap(HEAP_MIN, compararArchivos, imprimirArchivoHeap);
	
    do {
        printf("\n------------- IMPRESION -------------\n");
        mostrarTop5(heap);

        printf("\n0. Cambiar prioridad\n");
        printf("1. Mostrar cola\n");
        printf("2. Agregar archivo\n");
        printf("3. Imprimir archivo\n");
        printf("4. Eliminar archivo\n");
        printf("5. Vaciar cola\n");
        printf("6. Salir\n");
		printf("--------------------------------------\n");
		printf("\nElige la opcion: ");
		
        scanf("%d", &op);

        switch(op) 
		{
            case 0: 
				printf("\nANTES:\n");
                imprimirHeap(heap);

				printf("Invierte la pioridad\n");
                cambiarPrioridad(&heap);

                printf("\nDESPUES:\n");
                imprimirHeap(heap);
			break;
            case 1: 
				imprimirHeap(heap);
				printf("\n");
				construirArbol(heap);
			break;
            case 2:
                agregarArchivo(&heap);
                break;

            case 3:
                imprimirArchivoCola(&heap);
                break;

            case 4:
                eliminarArchivo(&heap);
                break;

            case 5:
                vaciarCola(&heap);
                break;

            case 6:
                printf("\nLiberando memoria...\n");
                vaciarCola(&heap);
                printf("Programa terminado.\n");
                break;

            default:
                printf("\nOpcion invalida\n");
        }

    } while(op != 6);

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



void imprimirArchivoHeap(void *a) {
    Archivo *arch = (Archivo*)a;
    printf("%d", arch->paginas);
}