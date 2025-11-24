#include <stdio.h>
#include <stdlib.h>
#include "Menu.h"


//#######################################################################
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
int mostrar_menu() {
    printf("\n==============================================\n");
    printf("         🔍  BÚSQUEDA DE ARTÍCULOS\n");
    printf("==============================================\n");
    printf("Opciones de Ordenamiento (Montículo Mínimo):\n");
    printf("1. Ordenar por Título (A-Z)\n");
    printf("2. Ordenar por Palabras en el Título (Menor a Mayor)\n");
    printf("3. Ordenar por Ruta del Archivo\n");
    printf("4. Ordenamiento Propio: Longitud del Resumen (Menor a Mayor)\n");
    printf("5. Ordenamiento Propio: Fecha mas reciente\n");
    printf("6. Mostrar el primer artículo cargado (Verificación)\n");
    printf("0. Salir\n");
    printf("==============================================\n");

    // Llama a la función que solicita y valida la entrada
    return obtener_opcion(0, 6);
}
//#######################################################################
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
int obtener_opcion(int min, int max) {
    int opcion;
    char buffer[100]; // Buffer para leer la línea de entrada

    while (1) {
        printf("Ingrese su opción (%d-%d): ", min, max);

        // Usar fgets para leer la línea completa
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            // Manejo de error de lectura
            printf("\nError de lectura. Intentando de nuevo...\n");
            continue;
        }

        // Intentar leer un entero del buffer
        if (sscanf(buffer, "%d", &opcion) == 1) {
            // Validar si la opción está dentro del rango permitido
            if (opcion >= min && opcion <= max) {
                return opcion; // Opción válida
            } else {
                printf("Opción fuera de rango. Ingrese un número entre %d y %d.\n", min, max);
            }
        } else {
            // La entrada no fue un entero
            printf("Entrada inválida. Por favor, ingrese un número.\n");
        }
    }
}
//#######################################################################