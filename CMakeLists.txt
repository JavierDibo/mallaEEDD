cmake_minimum_required(VERSION 3.23)
project(Malla)

set(CMAKE_CXX_STANDARD 14)

add_executable(Malla main.cpp Etiqueta.cpp Etiqueta.h etiquetas.txt fecha.h fecha.cpp ImageBook.cpp ImageBook.h Imagen.cpp Imagen.h imagenes_v2_mod.csv img.cpp img.h Usuario.h Usuario.cpp usuarios.txt UTM.cpp UTM.h MallaRegular.cpp MallaRegular.h Casilla.cpp Casilla.h)
