#include "MallaRegular.h"

template<typename T>
void MallaRegular<T>::insertar(float x, float y, const T &dato) {
    Casilla<T> *casilla = obtenerCasilla(x, y);
    casilla->insertar(dato);
}

template<typename T>
T *MallaRegular<T>::buscar(float x, float y, const T &dato) {
    Casilla<T> *casilla = obtenerCasilla(x, y);
    return casilla->buscar(dato);
}

template<typename T>
bool MallaRegular<T>::borrar(float x, float y, const T &dato) {
    Casilla<T> *casilla = obtenerCasilla(x, y);
    return casilla->borrar(dato);
}

template<typename T>
Casilla<T> *MallaRegular<T>::obtenerCasilla(float x, float y) {
    int i = (x - xMin) / tamaCasillaX;
    int j = (y - yMin) / tamaCasillaY;
    return &mr[i][j];
}

// Devuelve el número máximo de elementos que hay en una casilla de la imagePos regular

template<typename T>
unsigned int MallaRegular<T>::maxElementosPorCelda() {
    unsigned int max = 0;
    for (auto &fila: mr) {
        for (auto &casilla: fila) {
            max = std::max(max, casilla.numElementos());
        }
    }
    return max;
}

// Devuelve el promedio del número de elementos que hay en cada casilla de la imagePos regular

template<typename T>
float MallaRegular<T>::promedioElementosPorCelda() {
    float suma = 0;
    unsigned int numCasillas = 0;
    for (auto &fila: mr) {
        for (auto &casilla: fila) {
            suma += casilla.numElementos();
            ++numCasillas;
        }
    }
    return suma / numCasillas;
}


// Devuelve un vector con todos los elementos que se encuentran en casillas cuyas coordenadas estén incluidas en este rango
template<typename T>
vector<T> MallaRegular<T>::buscarRango(float rxmin, float rymin, float rxmax, float rymax) {
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

