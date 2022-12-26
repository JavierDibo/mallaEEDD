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
    string fichero = "fichero";
    string tam = "tam";
    Fecha fecha;
    deque<Etiqueta*> etiquetada;
    int posX, posY;

public:

    Imagen();

    Imagen(const string &id, const string &fichero, const string &tam, const Fecha &fecha,
           const deque<Etiqueta *> &etiquetada, int posX, int posY);

    Imagen(const Imagen& other);

    virtual ~Imagen();

    void annadirEtiqueta(Etiqueta *etiqueta);

    void setId(const string &id);

    void setFichero(const string &fichero);

    void setTam(const string &tam);

    void setFecha(const Fecha &fecha);

    const string &getId() const;

    const string &getFichero() const;

    const string &getTam() const;

    Fecha &getFecha();

    const deque<Etiqueta *>  &getEtiqueta() const;

    bool operator<(const Imagen &rhs) const;

    bool operator>(const Imagen &rhs) const;

    bool operator<=(const Imagen &rhs) const;

    bool operator>=(const Imagen &rhs) const;

    Imagen &operator=(const Imagen &valor);

    bool operator==(const Imagen &valor) const;

};


#endif //PRAC5_IMAGEN_H
