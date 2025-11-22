//
// Created by seb on 11/18/25.
//

#ifndef PROGRAESTRUCTURAS02_LECTOR_H
#define PROGRAESTRUCTURAS02_LECTOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DELIMITADOR ";"
//
// Created by seb on 11/18/25.
//

#include <stdlib.h>
#include <string.h>
#include "../Estructuras/Articulo.h"
#include "../Estructuras/Monticulo.h"
#include <stdio.h>

int leer_articulos(const char* nombre_archivo, struct Articulo** lista_articulos);
void liberar_articulos(struct Articulo* articulos,int num_articulos);
void swap(struct Articulo *a, struct Articulo *b);
int comparar(struct Articulo a,struct Articulo b, int tipo);
void flotar(struct Monticulo *m, int index);
void insertar(struct Monticulo *m, struct Articulo art) ;
struct Monticulo* crear_monticulo(int capacidad, int tipo);
void hundir(struct Monticulo *m, int index);
struct Articulo extraer_tope(struct Monticulo *m) ;
void destruir_monticulo(struct Monticulo *m);


#endif //PROGRAESTRUCTURAS02_LECTOR_H