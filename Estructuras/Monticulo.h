#ifndef PROGRAESTRUCTURAS02_MONTICULO_H
#define PROGRAESTRUCTURAS02_MONTICULO_H
#include "Articulo.h"

// ESTA LÍNEA ES CLAVE
typedef struct Monticulo
{
    Articulo* datos;
    int tamano;
    int capacidad;
    int tipo_ordenamiento;
} Monticulo; // <--- ¡Esto permite usar solo 'Monticulo'!

#endif //PROGRAESTRUCTURAS02_MONTICULO_H