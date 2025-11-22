# Establece la versión mínima requerida de CMake
cmake_minimum_required(VERSION 3.10)

# Define el nombre del proyecto y el lenguaje
project(PrograEstructuras02 C)

# Define el estándar de C a usar
set(CMAKE_C_STANDARD 11)

# Lista de todos los directorios que contienen archivos de cabecera (.h)
# La ruta 'Estructuras' es vital para que Monticulo.h encuentre a Articulo.h
include_directories(
        Estructuras
        Impresor
        Lector
        Menu
)

# Define el ejecutable y lista TODOS los archivos .c que lo componen.
# Los archivos .h se manejan con include_directories, NO se listan aquí.
add_executable(PrograEstructuras02
        main.c
        Lector/Lector.c        # <--- ¡Contiene toda la lógica del Heap y lectura!
        Impresor/Impresor.c    # <--- Archivo de impresión (si existe)
        Menu/Menu.c            # <--- Archivo de menú
)