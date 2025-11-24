//
// Created by seb on 11/18/25.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "Lector.h"
#include "../Estructuras/Articulo.h"
#include "../Estructuras/Monticulo.h"
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
int contar_palabras(char *texto) {
    if (texto == NULL || strlen(texto) == 0) {
        return 0;
    }
    char *copia_texto = strdup(texto);
    char *segunda_copia_texto = copia_texto;

    if (copia_texto == NULL) {
        return 0; // Fallo de memoria, retornamos 0
    }
    int contador = 0;
    char *token;
    const char *delimitadores = " \t\n.,?!:()[]\"";
    token = strtok_r(copia_texto, delimitadores,&segunda_copia_texto);

    while (token != NULL) {
        contador++;
        token = strtok_r(NULL, delimitadores,&segunda_copia_texto);
    }
    free(copia_texto); // Liberar la memoria de la copia
    return contador;
}
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
int leer_articulos(const char* nombre_archivo, struct Articulo** lista_articulos)
{
    FILE *archivo = fopen(nombre_archivo, "r");
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo");
        return -1;
    }
    char *linea = NULL;
    size_t len = 0;
    int contador = 0;

    struct Articulo *lista_articulos_temp = NULL;

    while (getline(&linea,&len,archivo) != -1)
    {

        // 1. Limpiar el salto de línea y verificar si la línea está vacía
        linea[strcspn(linea,"\n")] = 0;

        // NUEVA LÍNEA: ELIMINAR EL RETORNO DE CARRO
        linea[strcspn(linea,"\r")] = 0;

        if (strlen(linea) == 0) {
            continue; // Ignora líneas vacías
        }

        // 2. Realloc y manejo de errores
        struct Articulo *nuevo_espacio_articulo = (struct Articulo*) realloc(lista_articulos_temp,(contador + 1) * sizeof(struct Articulo));
        if (nuevo_espacio_articulo == NULL)
        {
            perror("Error al crear espacio para el articulo");
            free(linea);
            fclose(archivo);
            return -1;
        }
        lista_articulos_temp = nuevo_espacio_articulo;

        lista_articulos_temp[contador].titulo = NULL;
        lista_articulos_temp[contador].nombre = NULL;
        lista_articulos_temp[contador].apellido = NULL;
        lista_articulos_temp[contador].fecha = NULL;
        lista_articulos_temp[contador].abstract = NULL;
        lista_articulos_temp[contador].ruta = NULL;
        lista_articulos_temp[contador].palabras_titulo = 0;

        char* token;
        int campo = 0;

        token = strtok(linea,DELIMITADOR);
        while (token != NULL)
        {
            // Verificación defensiva
            if (strlen(token) > 0) {

                switch (campo)
                {
                case 0: // Primer campo en el archivo: Nombre
                    lista_articulos_temp[contador].nombre = strdup(token);
                    break;
                case 1: // Segundo campo en el archivo: Apellidos
                    lista_articulos_temp[contador].apellido = strdup(token);
                    break;
                case 2: // Tercer campo en el archivo: Titulo
                    lista_articulos_temp[contador].titulo = strdup(token);
                    lista_articulos_temp[contador].palabras_titulo = contar_palabras(token);
                    break;
                case 3: // Cuarto campo en el archivo: Ruta
                    lista_articulos_temp[contador].ruta = strdup(token);
                    break;
                case 4: // Quinto campo en el archivo: Fecha
                    lista_articulos_temp[contador].fecha = strdup(token);
                    break;
                case 5: // Sexto campo en el archivo: Abstract
                    lista_articulos_temp[contador].abstract = strdup(token);
                    break;
                }
            }
            campo++;
            token = strtok(NULL,DELIMITADOR);
        }
        if (lista_articulos_temp[contador].titulo == NULL) lista_articulos_temp[contador].titulo = strdup("");
        if (lista_articulos_temp[contador].nombre == NULL) lista_articulos_temp[contador].nombre = strdup("");
        if (lista_articulos_temp[contador].apellido == NULL) lista_articulos_temp[contador].apellido = strdup("");
        if (lista_articulos_temp[contador].fecha == NULL) lista_articulos_temp[contador].fecha = strdup("");
        if (lista_articulos_temp[contador].abstract == NULL) lista_articulos_temp[contador].abstract = strdup("");
        if (lista_articulos_temp[contador].ruta == NULL) lista_articulos_temp[contador].ruta = strdup("");

        contador++;
    }
    free(linea);
    fclose(archivo);
    *lista_articulos = lista_articulos_temp;
    return contador;
}
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
void liberar_articulos(struct Articulo* articulos,int num_articulos)
{
    if (articulos == NULL) return; // Mejor check

    for (int i = 0; i < num_articulos; i++)
    {
        free(articulos[i].titulo);
        free(articulos[i].nombre); // Usando 'nombre'
        free(articulos[i].apellido); // Usando 'apellido'
        free(articulos[i].fecha);
        free(articulos[i].abstract);
    }
    free(articulos);
}

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
void swap(struct Articulo *a, struct Articulo *b) {
    struct Articulo temp = *a;
    *a = *b;
    *b = temp;
}
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
int comparar(struct Articulo articuloA,struct Articulo articuloB, int tipo) {
    switch (tipo) {

    case 1:
        if (articuloA.titulo == NULL && articuloB.titulo == NULL) return 0;
        if (articuloA.titulo == NULL) return 1;  // Un NULL es "más grande", va al final del Min-Heap
        if (articuloA.titulo == NULL) return -1; // Un no-NULL es "más pequeño", va antes
        return strcmp(articuloA.titulo, articuloB.titulo);

    case 2:
        return articuloA.palabras_titulo - articuloB.palabras_titulo;

    case 3:
        if (articuloA.ruta == NULL && articuloB.ruta == NULL) return 0;
        if (articuloA.ruta == NULL) return 1;
        if (articuloA.ruta == NULL) return -1;
        return strcmp(articuloA.ruta, articuloB.ruta);
    case 4:
        return (int)strlen(articuloA.abstract) - (int)strlen(articuloB.abstract);
    case 5:
        return strcmp(articuloB.fecha,articuloA.fecha);
    default:
        return 0;
    }
}

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
void flotar(struct Monticulo *monticulo, int index) {
    // ... (El código de flotar es correcto con el tipo Monticulo) ...
    while (index > 0) {
        int padre = (index - 1) / 2;
        if (comparar(monticulo->datos[index], monticulo->datos[padre], monticulo->tipo_ordenamiento) < 0) {
            swap(&monticulo->datos[index], &monticulo->datos[padre]);
            index = padre;
        } else {
            break;
        }
    }
}

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

void insertar(struct Monticulo *monticulo, struct Articulo art) {
    if (monticulo->tamano == monticulo->capacidad) {
        monticulo->capacidad *= 2;
        monticulo->datos = (struct Articulo*) realloc(monticulo->datos, monticulo->capacidad * sizeof(struct Articulo));
        if (monticulo->datos == NULL) {
            perror("Error fatal: No se pudo redimensionar el montículo");
            exit(1);
        }
    }

    int indice_actual = monticulo->tamano;
    monticulo->datos[indice_actual] = art;
    monticulo->tamano++;

    flotar(monticulo, indice_actual);
}
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

struct Monticulo* crear_monticulo(int capacidad, int tipo) {
    struct Monticulo *m = (struct Monticulo*) malloc(sizeof(struct Monticulo));
    if (m == NULL) return NULL;

    m->datos = (struct Articulo*) malloc(capacidad * sizeof(struct Articulo));
    if (m->datos == NULL) {
        free(m);
        return NULL;
    }

    m->tamano = 0;
    m->capacidad = capacidad;
    m->tipo_ordenamiento = tipo;

    return m;
}
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
void hundir(struct Monticulo *monticulo, int index) {
    int hijo_izq, hijo_der, mejor_candidato;

    while(1) {
        hijo_izq = 2 * index + 1;
        hijo_der = 2 * index + 2;
        mejor_candidato = index;

        if (hijo_izq < monticulo->tamano && comparar(monticulo->datos[hijo_izq], monticulo->datos[mejor_candidato], monticulo->tipo_ordenamiento) < 0) {
            mejor_candidato = hijo_izq;
        }

        if (hijo_der < monticulo->tamano && comparar(monticulo->datos[hijo_der], monticulo->datos[mejor_candidato], monticulo->tipo_ordenamiento) < 0) {
            mejor_candidato = hijo_der;
        }

        if (mejor_candidato != index) {
            swap(&monticulo->datos[index], &monticulo->datos[mejor_candidato]);
            index = mejor_candidato;
        } else {
            break;
        }
    }
}
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

struct Articulo extraer_tope(struct Monticulo *monticulo) {
    if (monticulo->tamano <= 0) {
        // Inicializa con 7 NULL/0 por si la estructura Articulo tiene 7 campos
        struct Articulo vacio = {NULL, NULL, NULL, NULL, NULL, NULL, 0};
        return vacio;
    }

    struct Articulo tope = monticulo->datos[0];

    monticulo->datos[0] = monticulo->datos[monticulo->tamano - 1];
    monticulo->tamano--;

    if (monticulo->tamano > 0) {
        hundir(monticulo, 0);
    }

    return tope;
}
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
void destruir_monticulo(struct Monticulo *monticulo) {
    if (monticulo == NULL) return;

    if (monticulo->datos != NULL) {
        free(monticulo->datos);
    }

    free(monticulo);
}
//##################################################################################