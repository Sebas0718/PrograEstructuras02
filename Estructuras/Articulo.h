#ifndef PROGRAESTRUCTURAS02_ARTICULO_H
#define PROGRAESTRUCTURAS02_ARTICULO_H

/**
 * @struct Articulo
 * @brief Estructura que representa los metadatos de un artículo o documento cargado.
 * * Cada artículo contiene información clave utilizada para el procesamiento,
 * el ordenamiento mediante montículos y la impresión de resultados.
 */
struct Articulo
{
    char* titulo;
    char* nombre; // Usando los nombres de tu código
    char* apellido; // Usando los nombres de tu código
    char* fecha;
    char* abstract; // Usando los nombres de tu código
    char* ruta;
    int palabras_titulo; // Usando los nombres de tu código
};

#endif //PROGRAESTRUCTURAS02_ARTICULO_H