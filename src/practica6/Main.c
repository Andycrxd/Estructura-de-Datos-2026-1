#include <stdio.h>
#include <stdlib.h>
#include <pila.h>
#include <iostring.h>
#include <windows.h> //para el sleep

//(A+b-(c*(a/b)^B*a))+(a+b)

void ingresarInfix(char *cadena);
int ingresaOpcion();
void convertirPostFix(char  infix [],char postfix[],Pila *pila);
int procedencia(char c);
void mostrar(char postfix[],Pila pila);

int main(void)
{
	Pila pila = {NULL,0,-1,NULL,NULL};
	char  infix [100];
	char postfix[100];
	
	int opc= 0;
	
	do{
		opc=ingresaOpcion();
		switch(opc){
		case 1:
			ingresarInfix(infix );
			
			if(verificarParentesis(infix)==0)
			{
				printf("\nNo es posoble\n");
				break;
			}

			convertirPostFix(infix,postfix,&pila);
			
			mostrar(postfix,pila);
		break;
		case 2:
				printf("Saliendo ");
				for(int i=0; i<3 ;i++){
					Sleep(500);
					printf(". ");
				}
				
		break;
			default:
			printf("valor ingresado es invalido\n");
		}
		
		
	}while(opc!=2);
  
    printf("\n\n FIN DE PROGRAMA\n\n");
    return 0;
	
}

void convertirPostFix(char infix[], char postfix[], Pila *pila)
{
    int j = 0;

    for(int i = 0; infix[i] != '\0'; i++)
    {
        char c = infix[i];

        // OPERANDO
        if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
        {
            postfix[j++] = c;
        }

        // PARÉNTESIS IZQ
        else if(c == '(')
        {
            char *dato = malloc(sizeof(char));
            *dato = c;
            pushDato(pila, dato);
        }

        // PARÉNTESIS DER
        else if(c == ')')
        {
            while(!pilaVacia(*pila))
            {
                char *top = (char*)peekPila(*pila);

                if(*top == '(')
                {
                    free(popDato(pila));
                    break;
                }

                top = (char*)popDato(pila);
                postfix[j++] = *top;
                free(top);
            }
        }

        // OPERADORES
        else if(procedencia(c) > 0)
        {
            while(!pilaVacia(*pila))
            {
                char *top = (char*)peekPila(*pila);

                if(procedencia(*top) >= procedencia(c))
                {
                    top = (char*)popDato(pila);
                    postfix[j++] = *top;
                    free(top);
                }
                else break;
            }

            char *dato = malloc(sizeof(char));
            *dato = c;
            pushDato(pila, dato);
        }
    }

    // VACIAR PILA
    while(!pilaVacia(*pila))
    {
        char *dato = (char*)popDato(pila);
        postfix[j++] = *dato;
        free(dato);
    }

    postfix[j] = '\0';
}


void mostrar(char postfix[], Pila pila)
{
    printf("Postfix: ");

    for(int i = 0; postfix[i] != '\0'; i++)
    {
        printf("%c", postfix[i]);
    }

    printf("\n");
}

int procedencia(char c){
	switch(c){
	case '+':
	case '-':
	return 1;
	case '*':case'/':
	return 2;
	case '^':
	return 3;
	case '(':
	return -1;	
	}
	return 0;
}
	

void ingresarInfix(char  infix []){
	printf("Ingesa el valor de infix: ");
	scanf("%s", infix );
}

int ingresaOpcion()
{
	int num;
	printf("===========MENU===========\n");
	printf("1.convertir  el Infix a PostFix\n");
	printf("2.Salir\n");
	scanf("%d",&num);
	
	return num;
}