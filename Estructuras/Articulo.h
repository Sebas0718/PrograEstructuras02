#ifndef PROGRAESTRUCTURAS02_ARTICULO_H
#define PROGRAESTRUCTURAS02_ARTICULO_H

// ESTA LÍNEA ES CLAVE
typedef struct Articulo
{
    char* titulo;
    char* nombre; // Usando los nombres de tu código
    char* apellido; // Usando los nombres de tu código
    char* fecha;
    char* abstract; // Usando los nombres de tu código
    char* ruta;
    int palabras_titulo; // Usando los nombres de tu código
    // O int palabrasTitulo; (usa el que definiste)
} Articulo; // <--- ¡Esto permite usar solo 'Articulo'!

#endif //PROGRAESTRUCTURAS02_ARTICULO_H