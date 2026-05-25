#include "heap.h"



Heap crearHeap(unsigned char tipo,fn_comparar comparar,fn_imprimir imprimir)
{
	Heap heap = {tipo,0,NULL,NULL,comparar,imprimir};
	return heap;
}

void insertarHeap( Heap *heap,void *dato)
{
	void **aux = NULL;
	if(!heap->cantidad)
		heap->datos = calloc(1,sizeof(void*));
	else
	{
		while(!aux)
			aux = realloc(heap->datos, (heap->cantidad+1) * sizeof(void*) );
		heap->datos = aux;
	}	
	//inserta el dato
	heap->datos[heap->cantidad++] = dato;
	//HEAPIFY
	heapify(heap);
}



void heapify(Heap *heap)
{
	int indice = heap->cantidad/2-1;
	heapify_min(heap,indice);

}

void heapify_min( Heap *heap,int padre)
{
	if( padre < 0 || padre > (heap->cantidad/2-1) )
		return; 
	
	int min = padre; //1  0
	int izq = 2*padre+1;  //3  1
	int dch = 2*padre+2;  //4   2
	switch(heap->tipo)
	{
		case HEAP_MIN:			
			if( heap->comparar( heap->datos[min] , heap->datos[izq] ) > 0 )
				min = izq;
			if( dch < heap->cantidad && heap->comparar( heap->datos[min] , heap->datos[dch] ) > 0 )
				min = dch;
			break;			
		case HEAP_MAX:			
			if( heap->comparar( heap->datos[izq] , heap->datos[min] ) > 0 )
				min = izq;
			if( dch < heap->cantidad && heap->comparar( heap->datos[dch] , heap->datos[min] ) > 0 )
				min = dch;
			break;
	}
	if( min!=padre)
	{
		void *dato = heap->datos[padre];
		heap->datos[padre] = heap->datos[min];
		heap->datos[min] = dato;
		heapify_min(heap,min);
	}
	heapify_min(heap,padre-1);
	
	
}


void* eliminarHeap(Heap *heap)
{
	void *dato = NULL;
	if(!heap->cantidad)
		return dato;
	dato = heap->datos[0];
	if(heap->cantidad == 1)		
	{
		free(heap->datos);
		heap->datos = NULL;
		heap->cantidad--;
		return dato;
	}
	heap->datos[0] = heap->datos[heap->cantidad-1];
	void **aux = NULL;
	while(!aux)
		aux = realloc(heap->datos, (heap->cantidad-1) * sizeof(void*) );
	heap->datos = aux;
	heap->cantidad--;
	//HEAPIFY
	heapify(heap);
	return dato;	
}


void imprimirHeap( Heap heap)
{
	printf("\n HEAP: \n");
	if(heap.cantidad)
	{
		for( int i = 0; i < heap.cantidad; i++)
		{
			printf(" [%d] ",i);
			heap.imprimir( heap.datos[i] );
			printf("\n");
		}
		
	}
	else		
		printf("VACIO");		
}








//--


int compararArchivos(void *a, void *b) {
    Archivo *a1 = (Archivo*)a;
    Archivo *a2 = (Archivo*)b;

    return a1->paginas - a2->paginas;
}
void agregarArchivo(Heap *heap) {
    Archivo *a = malloc(sizeof(Archivo));

    char *nombres[] = {"Tarea", "Reporte", "Factura", "Proyecto", "Examen"};
    char *ext[] = {"c", "java", "asm"};

    int totalNombres = sizeof(nombres) / sizeof(nombres[0]);
    int totalExt = sizeof(ext) / sizeof(ext[0]);

    a->paginas = rand() % 50 + 1;

    sprintf(a->nombre, "%s%d.%s",
            nombres[rand() % totalNombres],
            rand() % 100,
            ext[rand() % totalExt]);

    printf("\nNuevo archivo: %s (%d paginas)\n", a->nombre, a->paginas);

    insertarHeap(heap, a);
}


void imprimirArchivoCola(Heap *heap) {
    if (heap->cantidad == 0) {
        printf("\nNo hay archivos.\n");
        return;
    }

    printf("\nANTES:\n");
    imprimirHeap(*heap);

    Archivo *a = (Archivo*) eliminarHeap(heap);

    printf("\nImprimiendo: %s (%d pags)\n", a->nombre, a->paginas);

    free(a); // importante

    printf("\nDESPUES:\n");
    imprimirHeap(*heap);
}

void eliminarArchivo(Heap *heap) {
    if (heap->cantidad == 0) {
        printf("\nNo hay archivos.\n");
        return;
    }

    imprimirHeap(*heap);

    int i;
    printf("\nIndice a eliminar: ");
    scanf("%d", &i);

    if (i < 0 || i >= heap->cantidad) {
        printf("Indice invalido\n");
        return;
    }

    printf("\nANTES:\n");
    imprimirHeap(*heap);

    free(heap->datos[i]);

    heap->datos[i] = heap->datos[heap->cantidad - 1];
    heap->cantidad--;

    heapify(heap);

    printf("\nDESPUES:\n");
    imprimirHeap(*heap);
}

void vaciarCola(Heap *heap) {
    for (int i = 0; i < heap->cantidad; i++) {
        free(heap->datos[i]);
    }

    free(heap->datos);
    heap->datos = NULL;
    heap->cantidad = 0;

    printf("\n vaciada!!\n");
}





void mostrarTop5(Heap heap) {
    printf("\n----------- TOP 5 -----------\n");

    for (int i = 0; i < heap.cantidad && i < 5; i++) {
        Archivo *a = (Archivo*) heap.datos[i];
        printf("%s (%d pags)\n", a->nombre, a->paginas);
    }
}
void cambiarPrioridad(Heap *heap) {
    heap->tipo = (heap->tipo == HEAP_MIN) ? HEAP_MAX : HEAP_MIN;
    heapify(heap);
