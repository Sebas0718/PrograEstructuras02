//
// Created by seb on 11/18/25.
//

#ifndef PROGRAESTRUCTURAS02_MENU_H
#define PROGRAESTRUCTURAS02_MENU_H

//############################################################
/**
 * @function obtener_opcion
 * @brief Maneja la interacción con el usuario para solicitar y validar una opción numérica.
 *
 * Implementa un bucle infinito que solo termina cuando el usuario ingresa un número
 * que está dentro del rango especificado (min y max). Utiliza fgets y sscanf para
 * leer la línea completa, lo que previene errores causados por caracteres basura
 * en el búfer de entrada (stdin) y garantiza una validación robusta de la entrada.
 *
 * @param min El valor entero mínimo aceptable para la opción.
 * @param max El valor entero máximo aceptable para la opción.
 * @return La opción válida ingresada por el usuario.
 */
int obtener_opcion(int min, int max);
//############################################################
/**
 * @function mostrar_menu
 * @brief Despliega el menú de opciones de ordenamiento y control del programa al usuario.
 *
 * Muestra las diferentes opciones de ordenamiento basadas en el Montículo Mínimo,
 * utilizando las llaves de texto (Título, Ruta) y llaves numéricas (Palabras, Longitud de Abstract, Fecha).
 * Delega la captura y validación de la entrada del usuario a la función 'obtener_opcion'.
 *
 * @return El número de la opción elegida por el usuario.
 */
int mostrar_menu();
//############################################################
#endif //PROGRAESTRUCTURAS02_MENU_H