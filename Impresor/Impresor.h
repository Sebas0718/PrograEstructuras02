//
// Created by seb on 11/18/25.
//

#ifndef PROGRAESTRUCTURAS02_IMPRESOR_H
#define PROGRAESTRUCTURAS02_IMPRESOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Estructuras/Articulo.h"


/**
 * @function imprimir_detalle
 * @brief Imprime en la consola todos los metadatos relevantes de una estructura Articulo.
 *
 * Esta función toma una estructura Articulo por valor y muestra sus campos
 * (Título, conteo de palabras, Autor, Fecha, Resumen y Ruta) en un formato
 * legible para el usuario.
 *
 * @param articulo La estructura Articulo cuyos detalles serán impresos.
 * La función asume que los punteros de cadena (char*) en 'a' no son NULL
 * o que han sido inicializados (cadena vacía) para evitar fallos de segmentación.
 */
void imprimir_detalle(struct Articulo articulo);

#endif //PROGRAESTRUCTURAS02_IMPRESOR_H