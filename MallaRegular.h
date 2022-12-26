#ifndef MALLA_MALLAREGULAR_H
#define MALLA_MALLAREGULAR_H

#include <vector>
#include <algorithm>

#include "Casilla.h"

using std::vector;

template<typename T>
class Casilla;

template<typename T>
class MallaRegular {
    float xMin, yMin, xMax, yMax; // Tamaño real global
    float tamaCasillaX, tamaCasillaY; // Tamaño real de cada casilla
    vector<vector<Casilla<T> >> mr; // Vector 2D de casillas

    Casilla<T> *obtenerCasilla(float x, float y);

public:

    // Default constructor
    MallaRegular() : xMin{}, yMin{}, xMax{}, yMax{}, tamaCasillaX{}, tamaCasillaY{}, mr{} {}

    // Parametrized constructor
    MallaRegular(float xMin, float yMin, float xMax, float yMax, float tamaCasillaX, float tamaCasillaY) :
            xMin{xMin}, yMin{yMin}, xMax{xMax}, yMax{yMax}, tamaCasillaX{tamaCasillaX}, tamaCasillaY{tamaCasillaY},
            mr{} {}

    // Copy constructor
    MallaRegular(const MallaRegular &other) :
            xMin{other.xMin}, yMin{other.yMin}, xMax{other.xMax}, yMax{other.yMax},
            tamaCasillaX{other.tamaCasillaX}, tamaCasillaY{other.tamaCasillaY}, mr{other.mr} {}

    void insertar(float x, float y, const T &dato);

    T *buscar(float x, float y, const T &dato);

    bool borrar(float x, float y, const T &dato);

    vector<T> buscarRango(float rxmin, float rymin, float rxmax, float rymax);

    unsigned int maxElementosPorCelda();

    float promedioElementosPorCelda();

};


#endif //MALLA_MALLAREGULAR_H
