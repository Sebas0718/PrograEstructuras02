#include <stdio.h>
#include <stdlib.h>
#include "Menu.h"

/**
 * @brief Muestra el menú principal y retorna la opción elegida por el usuario.
 * @return La opción elegida (entero entre 0 y 5).
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
    printf("5. Mostrar el primer artículo cargado (Verificación)\n");
    printf("0. Salir\n");
    printf("==============================================\n");

    // Llama a la función que solicita y valida la entrada
    return obtener_opcion(0, 5);
}

/**
 * @brief Solicita y valida la opción del menú al usuario.
 * @param min El valor mínimo válido para la opción.
 * @param max El valor máximo válido para la opción.
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
                printf("❌ Opción fuera de rango. Ingrese un número entre %d y %d.\n", min, max);
            }
        } else {
            // La entrada no fue un entero
            printf("❌ Entrada inválida. Por favor, ingrese un número.\n");
        }
    }
}