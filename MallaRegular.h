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
    MallaRegular(int aXMin, int aYMin, int aXMax, int aYMax, int aNDiv);

    void insertar(float x, float y, const T &dato);

    T *buscar(float x, float y, const T &dato);

    bool borrar(float x, float y, const T &dato);

    vector<T> buscarRango(float rxmin, float rymin, float rxmax, float rymax);

    unsigned int maxElementosPorCelda();

    float promedioElementosPorCelda();

};


#endif //MALLA_MALLAREGULAR_H
