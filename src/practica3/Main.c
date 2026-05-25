#include <stdio.h>
#include <iostring.h>
#include <pila.h>
#include <windows.h> //para el sleep

#define MAX 100


int elecion();

int main(void)
{
	char *cadena = NULL;
	int opc=0;
	do{
	opc=elecion();
		switch(opc){
			case 1:
			inputCadenaDinamica("\nCaptura cadena: ",&cadena,MAX);
			printf("Es palindromo: %s\n", palindromo(cadena) ? "SI" : "NO");
			break;
			case 2:
			inputCadenaDinamica("Captura expresion: ",&cadena,MAX);
			printf("Parentesis correctos : %s", verificarParentesis(cadena) ? "SI" : "NO");
			printf("\n");
			break;
			case 3:
				printf("Saliendo ");
				for(int i=0; i<3 ;i++){
					Sleep(500);
					printf(". ");
				}
			break;
			default:
				printf("OPCION INCORRECTA !!\n\n");
		}
		
	}while(opc != 3);
	
	free(cadena);
	printf("\n\nFIN DE PROGRAMA");
	
	return 0;
}


int elecion(){
	int num=0;
	printf("----------------Menu----------------\n");
	printf("1.Palindromo\n");
	printf("2.Verificación de paréntesis\n");
	printf("3.Salir\n");
	printf("Elige la opcion: ");
	scanf("%d",&num);
	while(getchar()!='\n');
	return num;
}

