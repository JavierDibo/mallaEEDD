#include "Casilla.h"

template<typename T>
T *Casilla<T>::buscar(const T &dato) {
    typename std::list<T>::iterator it;
    it = puntos.begin();
    for (; it != puntos.end(); ++it) {
        if (*it == dato)
            return &(*it);
    }
    return 0;
}

template<typename T>
bool Casilla<T>::borrar(const T &dato) {
    typename std::list<T>::iterator it;
    it = puntos.begin();
    for (; it != puntos.end(); ++it) {
        if (*it == dato) {
            puntos.erase(it);
            return true;
        }
    }
    return false;
}