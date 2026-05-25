#include <stdio.h>
#include <stdlib.h>
#include <pila.h>
#include <iostring.h>
#include "Laberinto.h"

int main(void)
{
    Laberinto lab = crear_laberinto();
    Coordenada *punto;
    Movimientos mov;
    Coordenada origen  = {1,1};
    Coordenada destino = {25,24};
    int pasos = 0;
    unsigned int nuevasCoor = 0;

    inputEnteroSinSigno("\n Nuevas coordenadas? (1:SI 0:NO) : ", &nuevasCoor);

    if(nuevasCoor)
    {
        inputEntero("\n Captura Origen X: ",  &origen.x);
        inputEntero(" Captura Origen Y: ",    &origen.y);
        inputEntero("\n Captura Destino X: ", &destino.x);
        inputEntero(" Captura Destino Y: ",   &destino.y);
    }

    setOrigen(lab, origen);
    setDestino(lab, destino);

    printf("\n Laberinto inicial:");
    imprimirLab(lab);

    Pila pila = {NULL, 0, -1, imprimirCoordenada, free};

    // Push inicial del origen
    punto = crearCoordenada(origen.x, origen.y);
    lab[punto->x][punto->y] = 'A';
    pushDato(&pila, punto);

    while( !pilaVacia(pila) )
    {
        pasos++;
        if(pasos > 100000){
            printf("\n LOOP INFINITO DETECTADO\n");
            break;
        }

        // 1. Ver tope de la pila
        punto = peekPila(pila);

        // 2. Llegamos al destino
        if(punto->x == destino.x && punto->y == destino.y)
            break;

        // 3. Calcular movimientos posibles
        mov = movimientosPosibles(lab, *punto);

        // 4. retroceder
        if( bloqueado(mov) )
        {
            while( !pilaVacia(pila) )
            {
                // Marcar celda actual sin salida
                lab[punto->x][punto->y] = 'F';
                free(popDato(&pila));

                if( pilaVacia(pila) )
                    break;

                // Actualizar punto al nuevo tope
                punto = peekPila(pila);

                // Recalcular movimientos desde la celda anterior
                mov = movimientosPosibles(lab, *punto);

                // Si hay camino libre, salir del retroceso
                if( !bloqueado(mov) )
                    break;
            }

            // Sin solución
            if( pilaVacia(pila) ){
                printf("\n SIN SOLUCIÓN\n");
                break;
            }

            // Recalcular tras el retroceso
            punto = peekPila(pila);
            mov   = movimientosPosibles(lab, *punto);
        }

        // 5. Moverse a la siguiente celda
        if( mov.up == 1 )
            punto = crearCoordenada(punto->x - 1, punto->y);
        else if( mov.down == 1 )
            punto = crearCoordenada(punto->x + 1, punto->y);
        else if( mov.right == 1 )
            punto = crearCoordenada(punto->x, punto->y + 1);
        else if( mov.left == 1 )
            punto = crearCoordenada(punto->x, punto->y - 1);

        // Solo marcar '.' si NO es el destino y  respetar la b
        if(punto->x != destino.x || punto->y != destino.y)
            lab[punto->x][punto->y] = '.';

        pushDato(&pila, punto);
    }

    printf("\n Pasos: %d\n", pasos);
    printf("\n\n Laberinto resuelto:");
    imprimirLab(lab);
    liberarLaberinto(lab);
    printf("\n\n FIN DE PROGRAMA\n\n");

    return 0;
}