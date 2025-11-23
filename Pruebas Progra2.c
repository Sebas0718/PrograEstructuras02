//
// Created by emmanuel on 22/11/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char cadena[] = "LA PUTA MADRE, VAMOS A MAMAR ESTA PROGRA, DIOS AYUDAME; ESTO ESTA HORRIBLE, ESPECIFICAMENTE ESTO: USTED";
    char delimitadores[] = ",:;";
    char *token;

    printf("Cadena original: %s \n", cadena);

    token = strtok(cadena, delimitadores);
    printf("Token1:  %s \n", token);

    while ((token = strtok(NULL, delimitadores)) != NULL) {
        printf("Token2: %s\n", token);

    }
}