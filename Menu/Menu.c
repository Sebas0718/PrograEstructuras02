//
// Created by seb on 11/18/25.
//

#include "Menu.h"

#include <stdio.h>
#include <stdlib.h>

#include "Impresor.h"

void iniciarMenu(){

    printf("BIENVENIDO AL ORDENADOR DE ARCHIVOS\n");
    printf("Ingrese la opcion que desea\n\n");
    printf("1.Pedir Ordenamiento\n");
    printf("2.Mostrar Referencias\n");
    printf("Salir\n");
    mostrarOpciones();
}

void mostrarOpciones()
{
    int opcion;

    while (1) {
        scanf("%d",&opcion);
        switch (opcion) {
        case 1:
            pedirOrdenamiento();
            break;
        case 2:
            mostrarReferencias();
            break;
        case 3:
            salir();
            break;
        default:
            printf("Opcion no valida\n");
            break;
        }
    }
}

int pedirOrdenamiento()
{
    printf("Por favor ingrese el tipo de ordenamiento que desea:\n");
    int ordenamiento;
    scanf("%d",&ordenamiento);
    while (ordenamiento != 1 && ordenamiento != 2 && ordenamiento != 3 && ordenamiento != 4)
    {
        printf("Opcion no valida\n");
        scanf("%d",&ordenamiento);
    }
    switch (ordenamiento)
    {
        case 1:
            imprimir_articulos_por_titulo();
            break;
        case 2:
            imprimir_articulos_por_nombre();
            break;
        case 3:
            imprimir_articulos_por_tamano();
            break;
        case 4:
            imprimir_articulos_por_fecha();
            break;
    }
}

void mostrarReferencias()
{
    imprimir_referencias();
}


void salir(){
    printf("Ha seleccionado salir del programa\n");
    exit(EXIT_SUCCESS);

}