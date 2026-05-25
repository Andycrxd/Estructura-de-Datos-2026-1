#include <stdio.h>
#include "Alumno.h"
#include <Lista.h>

int eleccion();

int main()
{	
	int opc=0,opc2=0;
	Alumno *a;
	Lista lista = {NULL,NULL,0,imprimirAlumno,compararNombre,free};

	do{
		printf("         Menu        \n");
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
				agregarEnOrden(&lista,a);
			break;
			case 2:
				imprimirLista(lista);
			break;
			case 3:
			  opc2 = eleccion();
				  switch(opc2){
					  case 1:
						reordenar( &lista ,compararMatricula );
					  break;
					  case 2:
					    reordenar( &lista ,compararNombre );
					  break;
					  case 3:
						reordenar( &lista ,compararSemestre );
					  break;
					  case 4:
						reordenar( &lista ,compararPromedio );
					  break;
					  default:
						printf("Error de opcion\n");
				  }
			break;
			case 4:
{
			int tipo = eleccion();
			Alumno temp ;
			Resultado r;
			Lista lista2 =lista;
				switch(tipo){
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

			r = buscar(lista,&temp);
			imprimirResultado(lista,r);
			lista=lista2;
			}
			break;
			case 5:
			{
				Lista lista2 =lista;
					Alumno temp;
					printf("Matricula a eliminar: ");
					scanf("%u",&temp.matricula);

					lista.comparar = compararMatricula;

					eliminarDato(&lista,&temp);
					
				lista.comparar = lista2.comparar;	
			}
			break;
			case 6:
				printf("Saliendo del programa...");
			break;
			default:
				printf("Error opcion incorrecta!!\n\n");
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
