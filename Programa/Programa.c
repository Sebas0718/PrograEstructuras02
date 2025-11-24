//
// Created by seb on 11/22/25.
//

#include "Programa.h"

//###############################################################
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
int leer_cant_parametros_flujo_entrada(int argc,char *argv[]){
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <nombre_archivo_articulos>\n", argv[0]);
        return 1;
    }
    return 0;

}
//###############################################################
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
int cargar_articulos(struct Articulo **lista_articulos, int num_articulos, char *argv[]){

    printf("Cargando artículos desde %s...\n", argv[1]);
    num_articulos = leer_articulos(argv[1], lista_articulos);

    if (num_articulos <= 0) {
        printf("Error: No se pudieron cargar artículos o el archivo está vacío.\n");
        return -1;
    }
    printf("Se cargaron %d artículos exitosamente.\n\n", num_articulos);
    return num_articulos;
}
//###############################################################
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
void iniciar_programa(int argc, char *argv[]){

     // 1. Verificación de argumentos
    if (leer_cant_parametros_flujo_entrada(argc,argv) != 0) {
    return;
    }

    struct Articulo *lista_articulos = NULL;
    int num_articulos = 0;

    // 2. Cargar artículos
    if ((num_articulos = cargar_articulos(&lista_articulos, num_articulos, argv)) == -1) {
    return;
    }

    int opcion;
    do {
        opcion = mostrar_menu();

        struct Monticulo *monticulo_ordenamiento = NULL;

        switch (opcion) {

            // =================================================================
            // CASO 1: Ordenar por Título (Tipo 1)
            // =================================================================
            case 1:
                printf("\n\n-- Ha elegido: Ordenar por Título (A-Z) --\n");
                eleccion(&monticulo_ordenamiento,lista_articulos,opcion,num_articulos);
                break;

            // =================================================================
            // CASO 2: Ordenar por Palabras en el Título (Tipo 2)
            // =================================================================
            case 2:
                printf("\n\n-- Ha elegido: Ordenar por Palabras en el Título (Menor a Mayor) --\n");
                eleccion(&monticulo_ordenamiento,lista_articulos,opcion,num_articulos);
                break;
            // =================================================================
            // CASO 3: Ordenar por Ruta (Tipo 3)
            // =================================================================
            case 3:
                printf("\n\n-- Ha elegido: Ordenar por Ruta del Archivo --\n");
                eleccion(&monticulo_ordenamiento,lista_articulos,opcion,num_articulos);
                break;

            // =================================================================
            // CASO 4: Ordenamiento Propio: Longitud del Resumen (Tipo 4)
            // =================================================================
            case 4:
                printf("\n\n-- Ha elegido: Ordenamiento Propio: Longitud del Resumen (Menor a Mayor) --\n");
                eleccion(&monticulo_ordenamiento,lista_articulos,opcion,num_articulos);
                break;

            // =================================================================
            // CASO 5: Ordenamiento segun fecha mas reciente
            // =================================================================
            case 5:
                printf("\n\n-- Ha elegido: Ordenar por Fecha mas reciente --\n");
                eleccion(&monticulo_ordenamiento,lista_articulos,opcion,num_articulos);
                break;

            //Muestra el primer articulo cargado (verifacion)
            case 6:
                printf("\n\n-- Ha elegido: Mostrar primer artículo cargado --\n");
               mostrar_primer_articulo(lista_articulos,num_articulos);
            // =================================================================
            // CASO 0: Salir
            // =================================================================
            case 0:
                printf("\nSaliendo del programa. ¡Memoria liberada!\n");
                break;

            default:
                printf("Opción inválida. Intente de nuevo.\n");
                break;
        }
    } while (opcion != 0);
// La liberación de lista_articulos:
    liberar_articulos(lista_articulos, num_articulos);

}
//##########################################################################
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
void mostrar_primer_articulo(struct Articulo *lista_articulos, int num_articulos){
    printf("\n\n-- Ha elegido: Mostrar primer artículo cargado --\n");
    if (num_articulos > 0) {
        imprimir_detalle(lista_articulos[0]);
    } else {
        printf("No hay artículos cargados para mostrar.\n");
    }
}

//##########################################################################
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
void eleccion(struct Monticulo **monticulo_ordenamiento,struct Articulo *lista_articulos,int tipo,int num_articulos){

    *monticulo_ordenamiento = crear_monticulo(num_articulos, tipo);
    if (*monticulo_ordenamiento == NULL) {
        fprintf(stderr, "Error al crear el montículo.\n");
        return;
    }
    // 2. Insertar todos los artículos
    for (int i = 0; i < num_articulos; i++) {
        insertar(*monticulo_ordenamiento, lista_articulos[i]);
    }

    printf("\n--- RESULTADO ORDENADO ---\n");
    // 3. Extraer y mostrar en orden
    for (int i = 0; i < num_articulos; i++) {
        struct Articulo articulo = extraer_tope(*monticulo_ordenamiento);
        imprimir_detalle(articulo);
        printf("--------------------------------------\n");
    }
    destruir_monticulo(*monticulo_ordenamiento);
    *monticulo_ordenamiento = NULL;
}
//##########################################################################