//
// Created by seb on 11/18/25.
//
#include "Impresor.h"


void imprimir_detalle(struct Articulo a) {
    printf("Título: %s\n", a.titulo);
    printf("         (%d palabras)\n", a.palabras_titulo);
    printf("Autor: %s %s\n", a.nombre, a.apellido);
    printf("Fecha: %s\n", a.fecha);
    printf("Resumen (Abstract): %s\n", a.abstract);
    printf("Ruta: %s\n", a.ruta);
}