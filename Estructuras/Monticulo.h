#ifndef PROGRAESTRUCTURAS02_MONTICULO_H
#define PROGRAESTRUCTURAS02_MONTICULO_H
#include "Articulo.h"

// ESTA LÍNEA ES CLAVE
struct Monticulo
{
    struct Articulo* datos;
    int tamano;
    int capacidad;
    int tipo_ordenamiento;
}; // <--- ¡Esto permite usar solo 'Monticulo'!

#endif //PROGRAESTRUCTURAS02_MONTICULO_H