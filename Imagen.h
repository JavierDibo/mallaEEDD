//
// Created by gara on 26/11/2022.
//

#ifndef PRAC5_IMAGEN_H
#define PRAC5_IMAGEN_H

#include <string>
#include <deque>

#include "fecha.h"
#include "Etiqueta.h"

using std::string;

class Imagen {
private:
    string id = "id";
    string email = "email";
    string fichero = "fichero";
    int tam;
    Fecha fecha;
    deque<Etiqueta *> etiquetada;
    int posX, posY;

public:

    Imagen();

    Imagen(const string& id, const string &email, const string &fichero, int tam, const Fecha &fecha,
           const deque<Etiqueta *> &etiquetada, float posX, float posY);

    Imagen(const Imagen &other);

    virtual ~Imagen();

    void annadirEtiqueta(Etiqueta *etiqueta);

    void setId(const string &id);

    void setFichero(const string &fichero);

    void setTam(const int &tam);

    void setFecha(const Fecha &fecha);

    const string &getId() const;

    const string &getFichero() const;

    const int &getTam() const;

    Fecha &getFecha();

    const deque<Etiqueta *> &getEtiqueta() const;

    bool operator<(const Imagen &rhs) const;

    bool operator>(const Imagen &rhs) const;

    bool operator<=(const Imagen &rhs) const;

    bool operator>=(const Imagen &rhs) const;

    Imagen &operator=(const Imagen &other);

    bool operator==(const Imagen &valor) const;

};


#endif //PRAC5_IMAGEN_H
