# Establece la versión mínima requerida de CMake
cmake_minimum_required(VERSION 3.10)

# Define el nombre del proyecto y el lenguaje
project(PrograEstructuras02 C)

# Define el estándar de C a usar
set(CMAKE_C_STANDARD 11)

include_directories(
        Estructuras
        Impresor
        Lector
        Menu
        Programa
)

# Define el ejecutable y lista TODOS los archivos .c que lo componen.
# Los archivos .h se manejan con include_directories, NO se listan aquí.
add_executable(PrograEstructuras02
        main.c
        Lector/Lector.c
        Impresor/Impresor.c
        Menu/Menu.c
        Programa/Programa.c
)