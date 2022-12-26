//
// Created by gara on 26/11/2022.
//

#include "Etiqueta.h"

#include <utility>

Etiqueta::Etiqueta() {
    nombre = "";
}

Etiqueta::Etiqueta(string et) {
    nombre = std::move(et);
}

Etiqueta& Etiqueta::operator=(const Etiqueta other) {
    if (this == &other)
        return *this;

    this->nombre = other.nombre;

    return *this;
}

Etiqueta::~Etiqueta() = default;

const string &Etiqueta::getNombre() const {
    return nombre;
}
