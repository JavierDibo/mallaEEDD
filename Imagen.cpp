#include "Imagen.h"
#include <cstdlib>
#include <ctime>
#include <string>

#include <stdexcept>

Imagen::Imagen() {
}

Imagen::Imagen(const string &id, const std::string &email, const std::string &fichero, const int tam,
               const Fecha &fecha,
               const deque<Etiqueta *> &etiquetada, UTM utm) {
    this->id = id;
    this->fichero = fichero;
    this->email = email;
    this->tam = tam;
    this->fecha = fecha;
    this->etiquetada = etiquetada;
    this->utm = utm;
}

Imagen::Imagen(const Imagen &other) {
    this->id = other.id;
    this->fichero = other.fichero;
    this->email = other.email;
    this->tam = other.tam;
    this->fecha = other.fecha;
    this->etiquetada = other.etiquetada;
    this->utm = other.utm;
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
    this->utm = other.utm;

    return *this;
}

bool Imagen::operator==(const Imagen &valor) const {
    return (id == valor.id && fichero == valor.fichero && tam == valor.tam);
}

void Imagen::annadirEtiqueta(Etiqueta *etiqueta) {
    etiquetada.push_back(etiqueta);
}

const UTM &Imagen::getUTM() const {
    return utm;
}

const string &Imagen::getEmail() const {
    return email;
}

const deque<Etiqueta *> &Imagen::getEtiquetada() const {
    return etiquetada;
}

const UTM &Imagen::getUtm() const {
    return utm;
}

int Imagen::getLikes() const {
    return likes;
}

void Imagen::nuevoLike() {
    likes++;
}

void Imagen::setLikes(int likes) {
    Imagen::likes = likes;
}


