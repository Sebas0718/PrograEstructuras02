//
// Created by seb on 11/18/25.
//

// INCLUDES DE LIBRERÍAS ESTÁNDAR (¡Críticos!)
#include <stdlib.h> // for malloc, realloc, free, exit, NULL, perror
#include <string.h> // for strdup, strtok, strcmp, strlen
#include <stdio.h>  // for FILE, fopen

// INCLUDES DE CABECERAS DEL PROYECTO
#include "Lector.h" // Contiene DELIMITADOR y prototipos
#include "../Estructuras/Articulo.h"
#include "../Estructuras/Monticulo.h"
//##################################################################################

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
void swap(struct Articulo *a, struct Articulo *b) {
    struct Articulo temp = *a;
    *a = *b;
    *b = temp;
}
//##################################################################################
int comparar(struct Articulo a,struct Articulo b, int tipo) {
    switch (tipo) {

    case 1:
        if (a.titulo == NULL && b.titulo == NULL) return 0;
        if (a.titulo == NULL) return 1;  // Un NULL es "más grande", va al final del Min-Heap
        if (b.titulo == NULL) return -1; // Un no-NULL es "más pequeño", va antes
        return strcmp(a.titulo, b.titulo);

    case 2:
        return a.palabras_titulo - b.palabras_titulo;

    case 3:
        if (a.ruta == NULL && b.ruta == NULL) return 0;
        if (a.ruta == NULL) return 1;
        if (b.ruta == NULL) return -1;
        return strcmp(a.ruta, b.ruta);
    case 4:
        return (int)strlen(a.abstract) - (int)strlen(b.abstract);
    case 5:
        return strcmp(b.fecha,a.fecha);
    default:
        return 0;
    }
}

//##################################################################################
void flotar(struct Monticulo *m, int index) {
    // ... (El código de flotar es correcto con el tipo Monticulo) ...
    while (index > 0) {
        int padre = (index - 1) / 2;
        if (comparar(m->datos[index], m->datos[padre], m->tipo_ordenamiento) < 0) {
            swap(&m->datos[index], &m->datos[padre]);
            index = padre;
        } else {
            break;
        }
    }
}

//##################################################################################
void insertar(struct Monticulo *m, struct Articulo art) {
    if (m->tamano == m->capacidad) {
        m->capacidad *= 2;
        m->datos = (struct Articulo*) realloc(m->datos, m->capacidad * sizeof(struct Articulo));
        if (m->datos == NULL) {
            perror("Error fatal: No se pudo redimensionar el montículo");
            exit(1);
        }
    }

    int indice_actual = m->tamano;
    m->datos[indice_actual] = art;
    m->tamano++;

    flotar(m, indice_actual);
}
//##################################################################################
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

void hundir(struct Monticulo *m, int index) {
    int hijo_izq, hijo_der, mejor_candidato;

    while(1) {
        hijo_izq = 2 * index + 1;
        hijo_der = 2 * index + 2;
        mejor_candidato = index;

        if (hijo_izq < m->tamano && comparar(m->datos[hijo_izq], m->datos[mejor_candidato], m->tipo_ordenamiento) < 0) {
            mejor_candidato = hijo_izq;
        }

        if (hijo_der < m->tamano && comparar(m->datos[hijo_der], m->datos[mejor_candidato], m->tipo_ordenamiento) < 0) {
            mejor_candidato = hijo_der;
        }

        if (mejor_candidato != index) {
            swap(&m->datos[index], &m->datos[mejor_candidato]);
            index = mejor_candidato;
        } else {
            break;
        }
    }
}
//##################################################################################
struct Articulo extraer_tope(struct Monticulo *m) {
    if (m->tamano <= 0) {
        // Inicializa con 7 NULL/0 por si la estructura Articulo tiene 7 campos
        struct Articulo vacio = {NULL, NULL, NULL, NULL, NULL, NULL, 0};
        return vacio;
    }

    struct Articulo tope = m->datos[0];

    m->datos[0] = m->datos[m->tamano - 1];
    m->tamano--;

    if (m->tamano > 0) {
        hundir(m, 0);
    }

    return tope;
}
//##################################################################################
void destruir_monticulo(struct Monticulo *m) {
    if (m == NULL) return;

    if (m->datos != NULL) {
        free(m->datos);
    }

    free(m);
}
//##################################################################################