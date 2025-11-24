#ifndef PROGRAESTRUCTURAS02_MONTICULO_H
#define PROGRAESTRUCTURAS02_MONTICULO_H
#include "Articulo.h"

/**
 * @struct Monticulo
 * @brief Estructura que implementa un árbol de montículo (Heap Tree) utilizando un arreglo
 * para almacenar los elementos. Esta estructura puede funcionar como Min-Heap
 * para diferentes tipos de llaves (numéricas o de texto).
 */
struct Monticulo
{
    struct Articulo* datos;
    int tamano;
    int capacidad;
    int tipo_ordenamiento;
};

#endif //PROGRAESTRUCTURAS02_MONTICULO_H