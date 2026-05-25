#include "Alumno.h"
#include <iostring.h>
#include "../../structures/nodos/nododoble.h"
Alumno* crearAlumno(void)
{
	Alumno *nuevo = calloc(1,sizeof(Alumno));
	inputEntero("\n Matricula: ",( int*)&nuevo->matricula);
	inputCadena("\n Nombre: ",nuevo->nombre,LEN);
	inputEntero("\n Semetres: ",&nuevo->semestre);
	inputFloat("\n Promedio: ",&nuevo->promedio);
	return nuevo;	
}




void imprimirAlumno(void *dato)
{
	 Alumno *a = (Alumno*)dato;
	printf("\n %-7u | ",a->matricula);
	printf("%-40s | ",a->nombre);
	printf("%-2d | ",a->semestre);
	printf("%.2f  ",a->promedio);
	printf("\n");
}
//comparar
// NEGATIVO si datoA < datoB
// CERO si datoA == datoB
// POSITIVO si datoA > datoB
int compararMatricula(void *datoA,void *datoB)
{
	Alumno *alumA = datoA,*alumB = datoB;
	return alumA->matricula - alumB->matricula;	
}
int compararNombre(void *datoA,void *datoB)
{
	Alumno *alumA = datoA,*alumB = datoB;
	return strcmp(alumA->nombre,alumB->nombre);	
}
int compararSemestre(void *datoA,void *datoB)
{
	Alumno *alumA = datoA,*alumB = datoB;
	return alumA->semestre - alumB->semestre;	
	
}
int compararPromedio(void *datoA,void *datoB)
{
	Alumno *alumA = datoA,*alumB = datoB;
	if( alumA->promedio < alumB->promedio) return -1;
	else if( alumA->promedio > alumB->promedio) return 1;
	else return 0;
}
int compararAlumno(void *datoA,void *datoB)
{
	return 0;
}