//
// Created by gara on 15/11/2022.
//

#ifndef IMAGENES_USUARIO_H
#define IMAGENES_USUARIO_H

#include <string>
#include <vector>
#include <map>

#include "Imagen.h"
#include "ImageBook.h"

using std::string;

class ImageBook;

class Usuario {
private:
    string email;
    map<string, Imagen *> userImages;
    ImageBook *linkIB;
public:

    Usuario();

    Usuario(string email, ImageBook *linkIB);

    Usuario(const Usuario &other);

    void insertaImagen(Imagen *imagen);

    vector<Imagen *> buscarEtiq(const string et);

    Imagen *buscarImagen(string id);

    void annadirEtiquetaImagen(string id, string nombreEtiqueta);

    vector<Usuario> buscarUsuariosEtiqueta(string nombreEtiqueta);

    Imagen *getImagenMasAntigua();

    Imagen *getImagenMasReciente();

    vector<Imagen *> getImagenesFecha(Fecha fecha);

    const int numImages() const {
        return userImages.size();
    }

    const string &getEmail() const {
        return email;
    }

    const map<string, Imagen *> &getUserImages() const {
        return userImages;
    }

    bool operator<(const Usuario &other) const {
        return email < other.email;
    }

    bool operator>(const Usuario &other) const {
        return other < *this;
    }

    bool operator<=(const Usuario &other) const {
        return !(other < *this);
    }

    bool operator>=(const Usuario &other) const {
        return !(*this < other);
    }

    virtual ~Usuario() {}

};


#endif //IMAGENES_USUARIO_H
