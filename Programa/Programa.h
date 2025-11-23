//
// Created by seb on 11/22/25.
//

#ifndef PROGRAESTRUCTURAS02_PROGRAMA_H
#define PROGRAESTRUCTURAS02_PROGRAMA_H

#include "../Impresor/Impresor.h"
#include "../Estructuras/Articulo.h"
#include "../Estructuras/Monticulo.h"
#include "../Lector/Lector.h"
#include "../Menu/Menu.h"


void iniciar_programa(int argc, char *argv[]);
int cargar_articulos(struct Articulo **lista_articulos, int num_articulos, char *argv[]);
int leer_cant_parametros_flujo_entrada(int argc,char *argv[]);
void mostrar_primer_articulo(struct Articulo *lista_articulos,int num_articulos);
void eleccion(struct Monticulo **monticulo_ordenamiento,struct Articulo *lista_articulos,int tipo,int num_articulos);
#endif //PROGRAESTRUCTURAS02_PROGRAMA_H