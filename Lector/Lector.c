//
// Created by seb on 11/18/25.
//

#include "Lector.h"

int leer_articulos(const char* nombre_archivo, Articulo** lista_articulos)
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

    Articulo *lista_articulos_temp = NULL;

    while (getLine(&linea,&len,archivo) != -1)
    {
        Articulo *nuevo_espacio_articulo = (Articulo*) realloc(lista_articulos_temp,(contador + 1) * sizeof(Articulo));
        if (nuevo_espacio_articulo == NULL)
        {
            perror("Error al crear espacio para el articulo");
            free(linea);
            fclose(archivo);
            return -1;
        }
        lista_articulos_temp = nuevo_espacio_articulo;
        linea[strcspn(linea,"\n")] = 0;

        char* token;
        int campo = 0;

        token = strtok(linea,DELIMITADOR);

        while (token != NULL)
        {
            switch (campo)
            {
                case 0: lista_articulos_temp[contador].titulo = strdup(token); break;
                case 1: lista_articulos_temp[contador].nombre = strdup(token); break;
                case 2: lista_articulos_temp[contador].apellido = strdup(token); break;
                case 3: lista_articulos_temp[contador].fecha = strdup(token); break;
                case 4: lista_articulos_temp[contador].abstract = strdup(token); break;
            }
            campo++;
            token = strtok(NULL,DELIMITADOR);
        }
        contador++;
    }
    free(linea);
    fclose(archivo);
    *lista_articulos = lista_articulos_temp;
    return contador;

}

void liberar_articulos(Articulo articulos[],int num_articulos)
{

    for (int i = 0; i < num_articulos; i++)
    {
        free(articulos[i].titulo);
        free(articulos[i].nombre);
        free(articulos[i].apellido);
        free(articulos[i].fecha);
        free(articulos[i].abstract);
    }
    free(articulos);

}