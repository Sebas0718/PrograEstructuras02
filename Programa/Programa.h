//
// Created by seb on 11/22/25.
//

#ifndef PROGRAESTRUCTURAS02_PROGRAMA_H
#define PROGRAESTRUCTURAS02_PROGRAMA_H

#include "../Impresor/Impresor.h"
#include "../Estructuras/Articulo.h"
#include "../Estructuras/Monticulo.h"
#include "../Lector/Lector.h"
#include "../Menu/Menu.h"

//###########################################################################
/**
 * @function iniciar_programa
 * @brief Función principal de control del flujo del programa.
 *
 * Se encarga de la verificación inicial de argumentos, la carga de artículos en memoria,
 * la gestión del menú principal y el bucle de opciones, y la liberación final de la memoria.
 *
 * @param argc El número de argumentos pasados.
 * @param argv El arreglo de punteros a cadenas de argumentos.
 */
void iniciar_programa(int argc, char *argv[]);
//###########################################################################
/**
 * @function cargar_articulos
 * @brief Controla el proceso de lectura de datos desde el archivo y carga los artículos en memoria.
 *
 * Llama a 'leer_articulos' para realizar la lectura real y el manejo de memoria.
 * Utiliza un doble puntero (struct Articulo **) para asegurar que el puntero de la lista
 * en 'iniciar_programa' se actualice con la dirección de la memoria asignada.
 *
 * @param lista_articulos Puntero al puntero de la lista de artículos, para actualizar la dirección de la lista cargada.
 * @param num_articulos El número inicial de artículos (generalmente 0).
 * @param argv El arreglo de argumentos, usado para obtener la ruta del archivo (argv[1]).
 * @return El número de artículos cargados exitosamente; -1 si ocurre un error de lectura o archivo vacío.
 */
int cargar_articulos(struct Articulo **lista_articulos, int num_articulos, char *argv[]);
//###########################################################################
/**
 * @function leer_cant_parametros_flujo_entrada
 * @brief Verifica la cantidad de argumentos pasados al programa en la línea de comandos.
 *
 * El programa requiere exactamente dos argumentos: el nombre del ejecutable (argv[0])
 * y la ruta del archivo de datos de artículos (argv[1]). Si no se cumple, imprime
 * un mensaje de error de uso.
 *
 * @param argc El número de argumentos pasados.
 * @param argv El arreglo de punteros a cadenas de argumentos.
 * @return 0 si el número de argumentos es correcto; 1 en caso contrario.
 */
int leer_cant_parametros_flujo_entrada(int argc,char *argv[]);
//###########################################################################
/**
 * @function mostrar_primer_articulo
 * @brief Muestra los detalles del primer artículo que fue cargado en el arreglo.
 *
 * Es una función auxiliar de verificación para confirmar que la lista de artículos
 * fue cargada y es accesible en memoria después de la lectura del archivo.
 *
 * @param lista_articulos Puntero al arreglo de estructuras Articulo.
 * @param num_articulos El número total de artículos cargados.
 */
void mostrar_primer_articulo(struct Articulo *lista_articulos,int num_articulos);
//###########################################################################
/**
 * @function eleccion
 * @brief Ejecuta el algoritmo de ordenamiento por Montículo Mínimo (Heap Sort).
 *
 * 1. Crea dinámicamente el montículo con la capacidad y el tipo de ordenamiento dados.
 * 2. Inserta todos los artículos de la lista en el montículo (Fase de construcción del Heap).
 * 3. Extrae el tope repetidamente (Fase de ordenamiento) e imprime los resultados en orden.
 * 4. Destruye y libera la memoria del montículo al finalizar.
 *
 * @param monticulo_ordenamiento Puntero al puntero del Montículo, usado para crear el montículo dinámicamente.
 * @param lista_articulos El arreglo de artículos a ordenar.
 * @param tipo El tipo de ordenamiento a aplicar (1-5).
 * @param num_articulos La cantidad de artículos a procesar.
 */
void eleccion(struct Monticulo **monticulo_ordenamiento,struct Articulo *lista_articulos,int tipo,int num_articulos);
//###########################################################################
#endif //PROGRAESTRUCTURAS02_PROGRAMA_H