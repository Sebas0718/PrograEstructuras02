//
// Created by seb on 11/22/25.
//

#include "Programa.h"
int leer_cant_parametros_flujo_entrada(int argc,char *argv[]){
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <nombre_archivo_articulos>\n", argv[0]);
        return 1;
    }
    return 0;

}

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
void mostrar_primer_articulo(struct Articulo *lista_articulos, int num_articulos){
    printf("\n\n-- Ha elegido: Mostrar primer artículo cargado --\n");
    if (num_articulos > 0) {
        imprimir_detalle(lista_articulos[0]);
    } else {
        printf("No hay artículos cargados para mostrar.\n");
    }
}

//##########################################################################
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