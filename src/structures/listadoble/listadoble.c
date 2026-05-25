#include "listadoble.h"
#include "../../practica2/Alumno.h"



void insertarFinalD(ListaD *lista,void *dato)
{
	NodoD *nuevo = crearNodoD(dato);
	//LISTA VACIA
	if(!lista->inicio)
	{
		lista->inicio = lista->fin = nuevo;
	}
	//LISTA NO VACIA
	else
	{
		lista->fin->sig = nuevo;
		nuevo->ant = lista->fin;
		lista->fin = nuevo;
	}
	lista->cant++;
}

void imprimirListaDIF(ListaD lista)
{
	printf("\n [%d] LISTA:",lista.cant);
	if(!lista.inicio)
	{
		printf("VACIA");
		printf("\n");
		return;
	}
	for(NodoD *aux = lista.inicio; aux!=NULL;  aux=aux->sig )
	{
		printf("\n");
		lista.imprimir( aux->dato);
	}
		printf("\n");
}

void imprimirListaDFI(ListaD lista)
{
	printf("\n [%d] LISTA:",lista.cant);
	if(!lista.inicio)
	{
		printf("VACIA");
		printf("\n");
		return;
	}
	for(NodoD *aux = lista.fin; aux!=NULL;  aux=aux->ant )
	{
		printf("\n");
		lista.imprimir( aux->dato);
	}
	printf("\n");
}



void borrarInicioD(ListaD *lista)
{
	NodoD *aux;
	if(!lista->inicio)
		return;	
	
	aux = lista->inicio;
	//UNICO NODO
	if( lista->inicio == lista->fin)
	{
		lista->inicio = lista->fin = NULL;
	}	
	//MINIMO 2
	else
	{
		lista->inicio = aux->sig;
		lista->inicio->ant = NULL;	
	}
	
	if(lista->liberar)
		lista->liberar( aux->dato);
	
	free(aux);	
	lista->cant--;	
	
}

void borrarListaD(ListaD *lista)
{
	while(lista->inicio)
	{
		borrarInicioD(lista);
	}	
}

ListaD inicializarListaD(void){
	
	ListaD lista = {NULL,NULL,0,imprimirAlumno,compararMatricula,free};
	 
	return lista;
}

//BUSCAR
NodoD* buscarDatoD(ListaD lista, void *dato)
{
    for(NodoD *aux = lista.inicio; aux != NULL; aux = aux->sig)
    {
        if(lista.comparar(aux->dato, dato) == 0)
            return aux;
    }

    return NULL;
}


//insertar
void insertEnOrdenD(ListaD *lista,void *dato){
	
	NodoD *nuevo = crearNodoD(dato);
	//LISTA VACIA?
	if (!lista->inicio)
	{	
		lista->inicio = lista->fin = nuevo;
	}	
	//LISTA YA TIENE ALGO
	else
	{
	
		for (NodoD *q = NULL,*aux = lista->inicio; aux!= NULL ;q=aux, aux = aux->sig)
		{

			if(NoMtriculaRepetida(lista,nuevo) == 1){
				printf("\n!Error no es posible poner matriculas repetidas!\n");
				return;
			}

			if( lista->comparar( nuevo->dato , aux->dato  ) < 0)
			{
				//REEMPLAZAR INICIO
				if(aux == lista->inicio)
				{
					nuevo->sig = aux;
					aux->ant = nuevo;
					lista->inicio = nuevo;
				}
				//INSERTAR EN MEDIO DE NODOS
				else
				{
					q->sig = nuevo;
					nuevo->ant= q;
					aux->ant=nuevo;
					nuevo->sig = aux;
				}
				break;
			}
			else if ( aux == lista->fin)
			{
				
				aux->sig = nuevo;
				nuevo->ant= aux;
				lista->fin = nuevo;
				break;
			}						
		}			
	}	
	lista->cant++;
	
}

void insertarInicioD(ListaD*lista,void*dato)
{
	NodoD *nuevo = crearNodoD(dato);
	
	//lista 
	if( lista->inicio == NULL )
	{
		lista->inicio= nuevo;
		lista->fin = nuevo;
	}
	//LISTA TIENE MINIMO UN NODO
	else
	{
		lista->inicio->ant= nuevo;
		nuevo->sig= lista->inicio;
		lista->inicio= nuevo;
	}
	
	lista->cant++;
	
}

int NoMtriculaRepetida(ListaD *lista,NodoD *nuevo){
	int v= 0;
	
	
	for (NodoD *aux = lista->inicio; aux!= NULL ; aux = aux->sig)
	{
	Alumno *existente = (Alumno*) aux->dato;
	Alumno *nuevoAl = (Alumno*) nuevo->dato;

		if(existente->matricula == nuevoAl->matricula){
			v=1;
			return v;
		}
	}
	
	return v;
	
}

void* removerInicio(ListaD *lista)
{
	if(!lista->inicio)
		return NULL;
	void *dato = lista->inicio->dato;
	lista->inicio->dato = NULL;
	borrarInicioD(lista);
	return dato;
}


void reordenarD(ListaD *lista, int (*comparar)(void*,void*))
{
	ListaD aux = {NULL,NULL,0,lista->imprimir,comparar,lista->liberar};
	void *dato;
	while( lista->cant  )
	{
		dato = removerInicio(lista);
		insertEnOrdenD(&aux,dato);		
	}
	*lista = aux;
	
}

void borrarDatoD(ListaD *lista,void *dato)
{
	NodoD *res = buscarDatoD(*lista,dato);
	if(res)
	{
		if( res == lista->inicio)
			borrarInicioD(lista);
		else if (res == lista->fin)
			borrarFinD(lista);
		else
		{
			res->ant->sig = res->sig;
			res->sig->ant= res->ant;
			if(lista->liberar) lista->liberar(res->dato);
			free(res);
			lista->cant--;
		}
	}
}
int borrarEnD(ListaD *lista, int index)
{
	//verificamos
    if (index < 0 || index > lista->cant)
        return 0;

    // eliminar inicio
    if (index == 1)
    {
        borrarInicioD(lista);
        return 1;
    }
	
	NodoD *eliminar = NULL;
  
	NodoD *aux1 = lista->inicio;

	for (int i = 0; i < index; i++)
	{
		eliminar = aux1;
		aux1 = aux1->sig;
	}
    NodoD *aux;
	
	if (eliminar == lista->fin){
        aux = eliminar->ant;
		lista->fin = aux;
		aux->sig= NULL;
	}else{
	    aux = eliminar-> ant;
		aux->sig= eliminar->sig;
		eliminar->sig->ant =aux;
	}
    
    free(eliminar);
    lista->cant--;

    return 1;
}


void borrarFinD(ListaD *lista)
{
	
	if(lista->inicio)
	{	
		NodoD *res = buscarDatoD(*lista,lista->fin->dato);
		lista->fin = res->ant; //PENULTIMO
		if(lista->fin)
			lista->fin->sig = NULL;
		else 
			lista->inicio = NULL;
		if(lista->liberar) lista->liberar(res->dato);
		free(res); //FIN
		lista->cant--;
	}	
}

