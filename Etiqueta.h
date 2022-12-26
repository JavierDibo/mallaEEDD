//
// Created by gara on 26/11/2022.
//

#ifndef PRAC5_ETIQUETA_H
#define PRAC5_ETIQUETA_H

#include <string>

using std::string;

class Etiqueta {
private:
    string nombre;
public:
    Etiqueta();

    Etiqueta(string et);

    Etiqueta& operator=(Etiqueta other);

    const string &getNombre() const;

    bool operator==(const Etiqueta &rhs) const {
        return nombre == rhs.nombre;
    }

    bool operator!=(const Etiqueta &rhs) const {
        return !(rhs == *this);
    }

    bool operator<(const Etiqueta &rhs) const {
        return nombre < rhs.nombre;
    }

    bool operator>(const Etiqueta &rhs) const {
        return rhs < *this;
    }

    bool operator<=(const Etiqueta &rhs) const {
        return !(rhs < *this);
    }

    bool operator>=(const Etiqueta &rhs) const {
        return !(*this < rhs);
    }

    ~Etiqueta();
};


#endif //PRAC5_ETIQUETA_H
