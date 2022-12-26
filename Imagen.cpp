//
// Created by gara on 04/10/2022.
//

#include "Imagen.h"

#include <stdexcept>

Imagen::Imagen() {}

Imagen::Imagen(const string &id, const string &fichero, const string &tam, const Fecha &fecha,
               const deque<Etiqueta *> &etiquetada, int posX, int posY) : id(id), fichero(fichero), tam(tam), fecha(fecha),
                                                      etiquetada(etiquetada), posX(posX), posY(posY) {}

Imagen::Imagen(const Imagen &other) {
    this->id = other.id;
    this->fichero = other.fichero;
    this->tam = other.tam;
    this->fecha = other.fecha;
    this->etiquetada = other.etiquetada;
}

Imagen::~Imagen() = default;

const string &Imagen::getId() const {
    return id;
}

const string &Imagen::getFichero() const {
    return fichero;
}

const string &Imagen::getTam() const {
    return tam;
}

Fecha &Imagen::getFecha() {
    return fecha;
}

const deque<Etiqueta *> &Imagen::getEtiqueta() const {
    return etiquetada;
}

void Imagen::setId(const string &id) {
    Imagen::id = id;
}

void Imagen::setFichero(const string &fichero) {
    Imagen::fichero = fichero;
}

void Imagen::setTam(const string &tam) {
    Imagen::tam = tam;
}

void Imagen::setFecha(const Fecha &fecha) {
    Imagen::fecha = fecha;
}

bool Imagen::operator<(const Imagen &rhs) const {
    if (stoi(id) < stoi(rhs.id))
        return true;
    if (stoi(rhs.id) < stoi(id))
        return false;
    return true;
}

bool Imagen::operator>(const Imagen &rhs) const {
    return rhs < *this;
}

bool Imagen::operator<=(const Imagen &rhs) const {
    return !(rhs < *this);
}

bool Imagen::operator>=(const Imagen &rhs) const {
    return !(*this < rhs);
}

Imagen &Imagen::operator=(const Imagen &valor) {
    if (this == &valor)
        return *this;

    this->id = valor.id;
    this->fichero = valor.fichero;
    this->tam = valor.tam;
    this->fecha = valor.fecha;
    this->etiquetada = valor.etiquetada;

    return *this;
}

bool Imagen::operator==(const Imagen &valor) const {
    return (id == valor.id && fichero == valor.fichero && tam == valor.tam);
}

void Imagen::annadirEtiqueta(Etiqueta *etiqueta) {
    etiquetada.push_back(etiqueta);
}


