#ifndef MALLA_MALLAREGULAR_H
#define MALLA_MALLAREGULAR_H

#include <vector>
#include <algorithm>
#include <float.h>
#include <iostream>
#include <cmath>


#include "Casilla.h"
#include "Imagen.h"

using std::vector;

template<typename T>
class Casilla;

template<typename T>
class MallaRegular {
    float xMin, yMin, xMax, yMax; // Tamaño real global
    float tamaCasillaX, tamaCasillaY; // Tamaño real de cada casilla
    vector<vector<Casilla<T> >> mr; // Vector 2D de casillas
    int altura, ancho;

    Casilla<T> *obtenerCasilla(float x, float y) {
        int vectorCol = floor((x - xMin) / (xMax - xMin) * ancho);
        int vectorRow = floor((y - yMin) / (yMax - yMin) * altura);
        if (vectorCol > ancho || vectorCol < 0 || vectorRow > altura || vectorRow < 0) {
            cout << "\nvectorCol=" << vectorCol << "vectorRow=" << vectorRow << endl;
            throw out_of_range("obetenerCasilla");
        }
        return &mr[vectorRow][vectorCol];
    }

public:

    // Default constructor
    MallaRegular() {}

    // Parametrized constructor
    MallaRegular(float xMin, float yMin, float xMax, float yMax, float tamaCasillaX, float tamaCasillaY) :
            xMin{xMin}, yMin{yMin}, xMax{xMax}, yMax{yMax}, tamaCasillaX{tamaCasillaX}, tamaCasillaY{tamaCasillaY},
            mr{} {
        altura = floor((xMax - xMin) / tamaCasillaX);
        ancho = floor((yMax - yMin) / tamaCasillaY);
        mr = vector<vector<Casilla<T>>>(altura, vector<Casilla<T>>(ancho));
    }

    // Copy constructor
    MallaRegular(const MallaRegular &other) :
            xMin{other.xMin}, yMin{other.yMin}, xMax{other.xMax}, yMax{other.yMax},
            tamaCasillaX{other.tamaCasillaX}, tamaCasillaY{other.tamaCasillaY}, mr{other.mr} {}

    void insertar(float x, float y, const T &dato) {
        Casilla<T> *cas = obtenerCasilla(x, y);
        cas->puntos.push_back(dato);
    }

    T *buscar(float x, float y, const T &dato) {
        Casilla<T> *casilla = obtenerCasilla(x, y);
        return casilla->buscar(dato);
    }

    bool borrar(float x, float y, const T &dato) {
        Casilla<T> *casilla = obtenerCasilla(x, y);
        return casilla->borrar(dato);
    }

    vector<T> buscarRango(float rxmin, float rymin, float rxmax, float rymax) {
        vector<T> resultado;
        for (auto &fila: mr) {
            for (auto &casilla: fila) {
                for (auto &dato: casilla.getDatos()) {
                    float x = dato.getX();
                    float y = dato.getY();
                    if (x >= rxmin && x <= rxmax && y >= rymin && y <= rymax) {
                        resultado.push_back(dato);
                    }
                }
            }
        }
        return resultado;
    }

    unsigned int maxElementosPorCelda() {
        unsigned int max = 0, aux;
        for (auto &fila: mr) {
            for (auto &casilla: fila) {
                aux = casilla.numElementos();
                if (max < aux) {
                    max = aux;
                }
            }
        }
        return max;
    }

    float promedioElementosPorCelda() {
        int totalElements = 0;
        int numCells = 0;

        for (auto &fila: mr) {
            for (auto &casilla: fila) {
                totalElements += casilla.numElementos();
                numCells++;
            }
        }

        return totalElements / (float) numCells;
    }
};


#endif //MALLA_MALLAREGULAR_H
