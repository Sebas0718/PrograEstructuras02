//
// Created by seb on 11/18/25.
//

#ifndef PROGRAESTRUCTURAS02_LECTOR_H
#define PROGRAESTRUCTURAS02_LECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELIMITADOR "|"
//
// Created by seb on 11/18/25.
//

#include <stdlib.h>
#include <string.h>
#include "../Estructuras/Articulo.h"
#include "../Estructuras/Monticulo.h"
#include <stdio.h>

//##################################################################################
/**
 * @function leer_articulos
 * @brief Carga los metadatos de los artículos desde un archivo de texto.
 *
 * Lee el archivo línea por línea, usando el delimitador especificado (DELIMITADOR)
 * para separar los campos de cada artículo. Asigna dinámicamente memoria para cada
 * campo usando strdup y para el arreglo completo de artículos usando realloc.
 * Maneja errores de apertura de archivo, asignación de memoria y limpia saltos de línea.
 *
 * @param nombre_archivo La ruta del archivo de texto a leer.
 * @param lista_articulos Puntero a puntero que será actualizado con la dirección
 * del arreglo dinámico de estructuras Articulo cargado.
 * @return El número de artículos cargados exitosamente; -1 en caso de error.
 */
int leer_articulos(const char* nombre_archivo, struct Articulo** lista_articulos);
//##################################################################################
/**
 * @function liberar_articulos
 * @brief Libera toda la memoria dinámica asociada al arreglo de artículos.
 *
 * Itera sobre todos los artículos del arreglo para liberar la memoria de cada
 * campo de cadena (char*) asignado con strdup (titulo, nombre, apellido, etc.).
 * Finalmente, libera la memoria del arreglo Articulo principal.
 *
 * @param articulos Puntero al arreglo de estructuras Articulo.
 * @param num_articulos El número de artículos cargados en el arreglo.
 */
void liberar_articulos(struct Articulo* articulos,int num_articulos);

//##################################################################################
/**
 * @function swap
 * @brief Intercambia el contenido de dos estructuras Articulo.
 *
 * Función auxiliar utilizada por los algoritmos de Montículo (flotar y hundir)
 * para reubicar los elementos dentro del arreglo base del montículo.
 *
 * @param a Puntero al primer artículo.
 * @param b Puntero al segundo artículo.
 */
void swap(struct Articulo *a, struct Articulo *b);
//##################################################################################
/**
 * @function comparar
 * @brief Determina el orden relativo de dos artículos basándose en el tipo de ordenamiento.
 *
 * Actúa como la llave de comparación del Montículo Mínimo.
 * Devuelve un valor negativo si 'a' es menor (debe ir antes),
 * un valor positivo si 'a' es mayor (debe ir después), o 0 si son iguales.
 * Incluye manejo defensivo para punteros NULL en campos de texto (Min-Heap: NULL va al final).
 *
 * @param articuloA Primer artículo a comparar.
 * @param articuloB Segundo artículo a comparar.
 * @param tipo El criterio de ordenamiento (1=Título, 2=Palabras, 3=Ruta, 4=Longitud Abstract, 5=Fecha).
 * @return Un entero: < 0 (a es menor), > 0 (a es mayor), 0 (iguales).
 */
int comparar(struct Articulo articuloA,struct Articulo articuloB, int tipo);

//##################################################################################
/**
 * @function flotar
 * @brief Restaura la propiedad del Montículo Mínimo subiendo (flotando) un nodo.
 *
 * Se utiliza después de una inserción. Compara el nodo en 'index' con su padre;
 * si el hijo es "menor" según la función 'comparar', los intercambia y repite el proceso
 * hasta que el nodo esté en su posición correcta o llegue a la raíz.
 *
 * @param monticulo Puntero al Montículo.
 * @param index El índice del nodo recién insertado o modificado que debe flotar.
 */
void flotar(struct Monticulo *monticulo, int index);
//##################################################################################

/**
 * @function insertar
 * @brief Inserta un nuevo artículo en el Montículo Mínimo.
 *
 * Si el montículo está lleno, duplica su capacidad usando realloc.
 * Agrega el nuevo artículo al final del arreglo e invoca 'flotar' para
 * restaurar la propiedad del Montículo Mínimo.
 *
 * @param monticulo Puntero al Montículo.
 * @param art La estructura Articulo a insertar.
 */
void insertar(struct Monticulo *monticulo, struct Articulo art) ;
//##################################################################################
/**
 * @function crear_monticulo
 * @brief Asigna memoria e inicializa una nueva estructura Monticulo.
 *
 * Reserva espacio para la estructura Monticulo y para su arreglo de datos (struct Articulo*).
 * Establece el tamaño inicial a cero y guarda la capacidad y el tipo de ordenamiento deseado.
 *
 * @param capacidad La capacidad inicial del arreglo interno del montículo.
 * @param tipo El criterio de ordenamiento inicial (tipo_ordenamiento).
 * @return Puntero a la nueva estructura Monticulo; NULL en caso de fallo de asignación de memoria.
 */
struct Monticulo* crear_monticulo(int capacidad, int tipo);
//##################################################################################
/**
 * @function hundir
 * @brief Restaura la propiedad del Montículo Mínimo bajando (hundiendo) un nodo.
 *
 * Se utiliza después de extraer la raíz. Compara el nodo en 'index' con sus hijos;
 * lo intercambia con el hijo "menor" y repite el proceso hasta que el nodo
 * esté en una posición donde es menor o igual que sus hijos, o llegue a una hoja.
 *
 * @param monticulo Puntero al Montículo.
 * @param index El índice del nodo que debe hundirse (generalmente la raíz, índice 0).
 */
void hundir(struct Monticulo *monticulo, int index);
//##################################################################################
/**
 * @function extraer_tope
 * @brief Extrae y retorna el elemento con la llave más pequeña (la raíz) del Montículo Mínimo.
 *
 * El elemento en la raíz (índice 0) se guarda, se reemplaza con el último elemento del arreglo,
 * se decrementa el tamaño, y se llama a 'hundir' para restaurar la propiedad del montículo.
 *
 * @param monticulo Puntero al Montículo.
 * @return La estructura Articulo que era el tope (el elemento más pequeño).
 * Retorna una estructura Articulo vacía si el montículo está vacío.
 */
struct Articulo extraer_tope(struct Monticulo *monticulo) ;
//##################################################################################
/**
 * @function destruir_monticulo
 * @brief Libera la memoria asignada al Montículo.
 *
 * Libera primero la memoria del arreglo de datos (m->datos) y luego la memoria
 * de la propia estructura Monticulo.
 * NOTA: Asume que la memoria de las cadenas dentro de los Articulos ya fue
 * liberada previamente por 'liberar_articulos' o una función similar.
 *
 * @param monticulo Puntero al Montículo.
 */
void destruir_monticulo(struct Monticulo *monticulo);

//##################################################################################


/**
 * @function contar_palabras
 * @brief Cuenta el número de palabras en una cadena de texto dada.
 *
 * Utiliza la función thread-safe strtok_r para tokenizar la cadena por
 * delimitadores comunes (espacios, signos de puntuación, etc.) y retorna el conteo.
 * Se crea una copia de la cadena de entrada usando strdup para evitar modificar
 * la cadena original (el título del artículo).
 *
 * @param texto La cadena (título del artículo) a analizar.
 * @return El número de palabras encontradas; 0 si la cadena es nula o vacía.
 */
int contar_palabras(char *texto);

#endif //PROGRAESTRUCTURAS02_LECTOR_H