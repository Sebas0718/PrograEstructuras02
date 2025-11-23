#include <stdlib.h>
// Incluye tus cabeceras de estructuras
#include "Estructuras/Articulo.h"
#include "Estructuras/Monticulo.h"

// Incluye tus cabeceras de módulos
#include "Menu/Menu.h"
#include "Lector/Lector.h"

// NOTA: Si tienes las funciones de impresión en Impresor/Impresor.c,
// debes incluirlas aquí con #include "Impresor/Impresor.h"

// --- Función que causó el error ---
// La función `imprimir_detalle` con el nombre de campo corregido:

void imprimir_detalle(Articulo a) {
    printf("Título: %s\n", a.titulo);
    printf("         (%d palabras)\n", a.palabras_titulo);

    // Asumiendo que quieres 'Nombre Apellido'
    printf("Autor: %s %s\n", a.nombre, a.apellido);

    // ¡AQUÍ ESTÁ LA CORRECCIÓN!
    printf("Fecha: %s\n", a.fecha);
    printf("Resumen (Abstract): %s\n", a.abstract);
    printf("Ruta: %s\n", a.ruta);
}

// --- Fin de la función corregida ---

#include <stdio.h>

int main(int argc, char *argv[]) {
    // 1. Verificación de argumentos
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <nombre_archivo_articulos>\n", argv[0]);
        return 1;
    }

    Articulo *lista_articulos = NULL;
    int num_articulos = 0;

    // 2. Cargar artículos
    printf("Cargando artículos desde %s...\n", argv[1]);
    // Asume que leer_articulos requiere el nombre del archivo y el puntero al array
    num_articulos = leer_articulos(argv[1], &lista_articulos);

    if (num_articulos <= 0) {
        fprintf(stderr, "Error: No se pudieron cargar artículos o el archivo está vacío.\n");
        return 1;
    }

    printf("Se cargaron %d artículos exitosamente.\n\n", num_articulos);

    int opcion;
    do {
        // Asume que mostrar_menu() y obtener_opcion() están en Menu/Menu.c
        opcion = mostrar_menu();

        // Declaración del puntero al montículo fuera del switch para evitar errores de compilación
        Monticulo *monticulo_ordenamiento = NULL;

        switch (opcion) {

            // =================================================================
            // CASO 1: Ordenar por Título (Tipo 1)
            // =================================================================
            case 1:
                printf("\n\n-- Ha elegido: Ordenar por Título (A-Z) --\n");

                // 1. Crear el montículo con tipo de ordenamiento 1
                monticulo_ordenamiento = crear_monticulo(num_articulos, 1);
                if (monticulo_ordenamiento == NULL) {
                    fprintf(stderr, "Error al crear el montículo.\n");
                    break;
                }

                // 2. Insertar todos los artículos en el montículo
                for (int i = 0; i < num_articulos; i++) {
                    insertar(monticulo_ordenamiento, lista_articulos[i]);
                }

                printf("\n--- RESULTADO ORDENADO ---\n");
                // 3. Extraer y mostrar en orden
                for (int i = 0; i < num_articulos; i++) {
                    Articulo a = extraer_tope(monticulo_ordenamiento);
                    imprimir_detalle(a);
                    printf("--------------------------------------\n");
                }

                // 4. Liberar la memoria del montículo
                destruir_monticulo(monticulo_ordenamiento);
                break;

            // =================================================================
            // CASO 2: Ordenar por Palabras en el Título (Tipo 2)
            // =================================================================
            case 2:
                printf("\n\n-- Ha elegido: Ordenar por Palabras en el Título (Menor a Mayor) --\n");

                // 1. Crear el montículo con tipo de ordenamiento 2
                monticulo_ordenamiento = crear_monticulo(num_articulos, 2);
                if (monticulo_ordenamiento == NULL) {
                    fprintf(stderr, "Error al crear el montículo.\n");
                    break;
                }

                // 2. Insertar todos los artículos
                for (int i = 0; i < num_articulos; i++) {
                    insertar(monticulo_ordenamiento, lista_articulos[i]);
                }

                printf("\n--- RESULTADO ORDENADO ---\n");
                // 3. Extraer y mostrar en orden
                for (int i = 0; i < num_articulos; i++) {
                    Articulo a = extraer_tope(monticulo_ordenamiento);
                    imprimir_detalle(a);
                    printf("--------------------------------------\n");
                }

                // 4. Liberar la memoria
                destruir_monticulo(monticulo_ordenamiento);
                break;

            // =================================================================
            // CASO 3: Ordenar por Ruta (Tipo 3)
            // =================================================================
            case 3:
                printf("\n\n-- Ha elegido: Ordenar por Ruta del Archivo --\n");

                // 1. Crear el montículo con tipo de ordenamiento 3
                monticulo_ordenamiento = crear_monticulo(num_articulos, 3);
                if (monticulo_ordenamiento == NULL) {
                    fprintf(stderr, "Error al crear el montículo.\n");
                    break;
                }

                // 2. Insertar todos los artículos
                for (int i = 0; i < num_articulos; i++) {
                    insertar(monticulo_ordenamiento, lista_articulos[i]);
                }

                printf("\n--- RESULTADO ORDENADO ---\n");
                // 3. Extraer y mostrar en orden
                for (int i = 0; i < num_articulos; i++) {
                    Articulo a = extraer_tope(monticulo_ordenamiento);
                    imprimir_detalle(a);
                    printf("--------------------------------------\n");
                }

                // 4. Liberar la memoria
                destruir_monticulo(monticulo_ordenamiento);
                break;

            // =================================================================
            // CASO 4: Ordenamiento Propio: Longitud del Resumen (Tipo 4)
            // =================================================================
            case 4:
                printf("\n\n-- Ha elegido: Ordenamiento Propio: Longitud del Resumen (Menor a Mayor) --\n");

                // 1. Crear el montículo con tipo de ordenamiento 4
                monticulo_ordenamiento = crear_monticulo(num_articulos, 4);
                if (monticulo_ordenamiento == NULL) {
                    fprintf(stderr, "Error al crear el montículo.\n");
                    break;
                }

                // 2. Insertar todos los artículos
                for (int i = 0; i < num_articulos; i++) {
                    insertar(monticulo_ordenamiento, lista_articulos[i]);
                }

                printf("\n--- RESULTADO ORDENADO ---\n");
                // 3. Extraer y mostrar en orden
                for (int i = 0; i < num_articulos; i++) {
                    Articulo a = extraer_tope(monticulo_ordenamiento);
                    imprimir_detalle(a);
                    printf("--------------------------------------\n");
                }

                // 4. Liberar la memoria
                destruir_monticulo(monticulo_ordenamiento);
                break;

            // =================================================================
            // CASO 5: Muestra el primer artículo cargado
            // =================================================================
            case 6:
                printf("\n\n-- Ha elegido: Mostrar primer artículo cargado --\n");
                if (num_articulos > 0) {
                    imprimir_detalle(lista_articulos[0]);
                } else {
                    printf("No hay artículos cargados para mostrar.\n");
                }
                break;

            case 5:
                printf("\n\n-- Ha elegido: Ordenar por Fecha mas reciente --\n");

                // 1. Crear el montículo con tipo de ordenamiento 3
                monticulo_ordenamiento = crear_monticulo(num_articulos, 3);
                if (monticulo_ordenamiento == NULL) {
                    fprintf(stderr, "Error al crear el montículo.\n");
                    break;
                }

                // 2. Insertar todos los artículos
                for (int i = 0; i < num_articulos; i++) {
                    insertar(monticulo_ordenamiento, lista_articulos[i]);
                }

                printf("\n--- RESULTADO ORDENADO ---\n");
                // 3. Extraer y mostrar en orden
                for (int i = 0; i < num_articulos; i++) {
                    Articulo a = extraer_tope(monticulo_ordenamiento);
                    imprimir_detalle(a);
                    printf("--------------------------------------\n");
                }

                // 4. Liberar la memoria
                destruir_monticulo(monticulo_ordenamiento);
                break;

            // =================================================================
            // CASO 0: Salir
            // =================================================================
            case 0:
                printf("\nSaliendo del programa. ¡Memoria liberada! 👋\n");
                break;

            default:
                printf("Opción inválida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 0);

// La liberación de lista_articulos se mantiene fuera del loop:
    liberar_articulos(lista_articulos, num_articulos);

    return 0;
}