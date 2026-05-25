#include <stdio.h>
#include <iostring.h>
#include <listadoble.h>
#include "Alumno.h"

int eleccion();

int main()
{	
	int opc=0,opc2=0,opc3=0;
	Alumno *a;
	ListaD lista = inicializarListaD();
	
	
	do{
		printf("▬▬▬▬▬▬▬▬▬▬Menu▬▬▬▬▬▬▬▬▬▬\n");
		printf("1  Registrar Alumno\n");
		printf("2  Desplegar Alumnos\n");
		printf("3  Reordenar\n");
		printf("4. Buscar Alumno \n");
		printf("5. Borrar Alumno \n");
		printf("6. Finalizar programa \n");
		printf("Ingresa la opcion: ");
		scanf("%d",&opc);
		
		switch(opc){
			case 1:
				a = crearAlumno();
				insertEnOrdenD(&lista,a);
			break;
			case 2:
				
				printf("\nDesea imprimir \n1.ASCENDENTE\n2.DESCENDENTE\nElige opcion: ");
				scanf("%d",&opc3);
				
				if(opc3==1){
					imprimirListaDIF(lista);
				}else if(opc3==2){
				    imprimirListaDFI(lista);
				}
			break;
			case 3:
			  opc2 = eleccion();
				  switch(opc2)
				  {
					  case 1:
						reordenarD( &lista ,compararMatricula );
					  break;
					  case 2:
					    reordenarD( &lista ,compararNombre );
					  break;
					  case 3:
						reordenarD( &lista ,compararSemestre );
					  break;
					  case 4:
						reordenarD( &lista ,compararPromedio );
					  break;
					  default:
						printf("Error de opcion\n");
				  }
			break;
			case 4:
		{
			int tipo = eleccion();
			Alumno temp ;
			NodoD *r;
			ListaD lista2 =lista;
			
				switch(tipo)
				{
					case 1:
						printf("Matricula: ");
						scanf("%u",&temp.matricula);
						lista.comparar = compararMatricula;
					break;

					case 2:
						printf("Nombre: ");
						scanf("%s",temp.nombre);
						lista.comparar = compararNombre;
					break;

					case 3:
						printf("Semestre: ");
						scanf("%d",&temp.semestre);
						lista.comparar = compararSemestre;
					break;

					case 4:
						printf("Promedio: ");
						scanf("%f",&temp.promedio);
						lista.comparar = compararPromedio;
					break;

					default:
						printf("Opcion invalida\n");
						break;
				}

			r = buscarDatoD(lista,&temp);
			imprimirAlumno(r->dato);
			lista=lista2;
		}
			break;
			case 5:
			{
				ListaD lista2 =lista;	
				
					Alumno temp;
					
					printf("Matricula a eliminar: ");
					scanf("%u",&temp.matricula);

					lista.comparar = compararMatricula;

					borrarDatoD(&lista,&temp);
					
				lista.comparar = lista2.comparar;
			}
			break;
			case 6:
				printf("Saliendo del programa...");
			break;
			default:
				printf("Error opcion incorrecta");
		}
		
	}while(opc!=6);
	
	

	
	return 0;
}



int eleccion(){
	int opc;
	printf("\nElige el tipo  \n");
	printf("1. Matricula \n");
	printf("2. Nombre \n");
	printf("3. Semetres \n");
	printf("4. Promedio \n");
	printf("Elige la opcion : ");
	scanf("%d",&opc);
	
	return opc;

}
