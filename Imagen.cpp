#include "Imagen.h"

#include <stdexcept>

Imagen::Imagen() {}

Imagen::Imagen(const string &id, const std::string &email, const std::string &fichero, const int tam,
               const Fecha &fecha,
               const deque<Etiqueta *> &etiquetada, float posX, float posY) {
    this->id = id;
    this->fichero = fichero;
    this->email = email;
    this->tam = tam;
    this->fecha = fecha;
    this->etiquetada = etiquetada;
    this->posX = posX;
    this->posY = posY;
}

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

const int &Imagen::getTam() const {
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

void Imagen::setTam(const int &tam) {
    Imagen::tam = tam;
}

void Imagen::setFecha(const Fecha &fecha) {
    Imagen::fecha = fecha;
}

bool Imagen::operator<(const Imagen &rhs) const {
    if (id < rhs.id)
        return true;
    if (rhs.id < id)
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

Imagen &Imagen::operator=(const Imagen &other) {
    if (this == &other)
        return *this;

    this->id = other.id;
    this->email = other.email;
    this->fichero = other.fichero;
    this->tam = other.tam;
    this->fecha = other.fecha;
    this->etiquetada = other.etiquetada;
    this->posX = other.posX;
    this->posY = other.posY;

    return *this;
}

bool Imagen::operator==(const Imagen &valor) const {
    return (id == valor.id && fichero == valor.fichero && tam == valor.tam);
}

void Imagen::annadirEtiqueta(Etiqueta *etiqueta) {
    etiquetada.push_back(etiqueta);
}


