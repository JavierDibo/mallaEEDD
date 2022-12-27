#ifndef PRAC5_IMAGEN_H
#define PRAC5_IMAGEN_H

#include <string>
#include <deque>

#include "fecha.h"
#include "Etiqueta.h"
#include "UTM.h"

using std::string;

class Imagen {
private:
    string id = "id";
    string email = "email";
    int likes = 0;
public:
    void setLikes(int likes);

public:
    int getLikes() const;

public:
    const string &getEmail() const;

    const deque<Etiqueta *> &getEtiquetada() const;

    const UTM &getUtm() const;

private:
    string fichero = "fichero";
    int tam;
    Fecha fecha;
    deque<Etiqueta *> etiquetada;
    UTM utm;

public:

    Imagen();

    Imagen(const string &id, const string &email, const string &fichero, int tam, const Fecha &fecha,
           const deque<Etiqueta *> &etiquetada, UTM utm);

    Imagen(const Imagen &other);

    virtual ~Imagen();

    void annadirEtiqueta(Etiqueta *etiqueta);

    void nuevoLike();

    void setId(const string &id);

    void setFichero(const string &fichero);

    void setTam(const int &tam);

    void setFecha(const Fecha &fecha);

    const string &getId() const;

    const string &getFichero() const;

    const int &getTam() const;

    const UTM &getUTM() const;

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
