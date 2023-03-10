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
        int columna = floor((x - xMin) / (xMax - xMin) * ancho);
        int fila = floor((y - yMin) / (yMax - yMin) * altura);
        if (columna > ancho || columna < 0 || fila > altura || fila < 0) {
            cout << "\ncolumna=" << columna << "fila=" << fila << endl;
            throw out_of_range("obetenerCasilla");
        }
        return &mr[fila][columna];
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
        Casilla<T> *casilla = obtenerCasilla(x, y);
        casilla->puntos.push_back(dato);
    }

    T *buscar(float x, float y, const T &dato) {
        Casilla<T> *casilla = obtenerCasilla(x, y);
        return casilla->buscar(dato);
    }

    bool borrar(float x, float y, const T &dato) {
        Casilla<T> *casilla = obtenerCasilla(x, y);
        return casilla->borrar(dato);
    }

    vector<T> buscarRango(float rxmin, float rymin, float rxmax, float rymax) const {
        vector<T> vec;
        for (auto &fila: mr) {
            for (auto &casilla: fila) {
                for (auto &img: casilla.getDatos()) {
                    float x = img->getUTM().GetLatitud();
                    float y = img->getUTM().GetLongitud();
                    if (x >= rxmin && x <= rxmax && y >= rymin && y <= rymax) {
                        vec.push_back(img);
                    }
                }
            }
        }
        return vec;
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
        int numElementos = 0;
        int numCeldas = 0;

        for (auto &fila: mr) {
            for (auto &casilla: fila) {
                numElementos += casilla.numElementos();
                numCeldas++;
            }
        }

        return numElementos / (float) numCeldas;
    }

    int size() {
        int numElementos = 0;

        for (auto &fila: mr) {
            for (auto &casilla: fila) {
                numElementos += casilla.numElementos();
            }
        }

        return numElementos;
    }

};


#endif //MALLA_MALLAREGULAR_H
