//
// Created by seb on 11/18/25.
//
#include "Impresor.h"

/**
 * @function imprimir_detalle
 * @brief Imprime en la consola todos los metadatos relevantes de una estructura Articulo.
 * Esta función toma una estructura Articulo por valor y muestra sus campos
 * (Título, conteo de palabras, Autor, Fecha, Resumen y Ruta) en un formato
 * legible para el usuario.
 *
 * @param articulo La estructura Articulo cuyos detalles serán impresos.
 * La función asume que los punteros de cadena (char*) en 'a' no son NULL
 * o que han sido inicializados (cadena vacía) para evitar fallos de segmentación.
 */
void imprimir_detalle(struct Articulo articulo) {
    printf("Título: %s\n", articulo.titulo);
    printf("         (%d palabras)\n", articulo.palabras_titulo);
    printf("Autor: %s %s\n", articulo.nombre, articulo.apellido);
    printf("Fecha: %s\n", articulo.fecha);
    printf("Resumen (Abstract): %s\n", articulo.abstract);
    printf("Ruta: %s\n", articulo.ruta);
}