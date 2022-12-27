#ifndef MALLA_CASILLA_H
#define MALLA_CASILLA_H

#include <list>

template<typename T>
class MallaRegular;

template<typename T>
class Casilla {
    std::list<T> puntos;
public:
    friend class MallaRegular<T>;

    Casilla() : puntos({}) {
    }

    void insertar(const T &dato) {
        auto a = dato;
        puntos.push_back(a);
    }

    T *buscar(const T &dato);

    bool borrar(const T &dato);

    int numElementos() const { return puntos.size(); }
};


#endif //MALLA_CASILLA_H
