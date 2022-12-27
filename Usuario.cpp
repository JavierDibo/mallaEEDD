#include "Usuario.h"

Usuario::Usuario() {}

Usuario::Usuario(string email, ImageBook *linkIB) {
    this->email = email;
    this->linkIB = linkIB;
}

Usuario::Usuario(const Usuario &other) {
    this->email = other.email;
    this->userImages = other.userImages;
    this->linkIB = other.linkIB;
}

void Usuario::insertaImagen(Imagen *imagen) {
    Imagen *aux = imagen;
    userImages.insert({aux->getId(), aux});
}

vector<Imagen *> Usuario::buscarEtiq(const string et) {
    vector<Imagen *> vec;
    vec.push_back(userImages.find(et)->second);
    return vec;
}

Imagen *Usuario::buscarImagen(string id) {
    for (auto img: userImages) {
        if (img.second->getId() == id) {
            return img.second;
        }
    }

    return new Imagen();
}

void Usuario::annadirEtiquetaImagen(string id, string nombreEtiqueta) {
    Etiqueta *aux = new Etiqueta(nombreEtiqueta);
    for (auto img: userImages) {
        img.second->annadirEtiqueta(aux);
    }
}

vector<Usuario> Usuario::buscarUsuariosEtiqueta(string nombreEtiqueta) {
    vector<Usuario> vecUsers;
    for (auto usr: linkIB->getUsuarios()) {
        for (auto img: usr.second.userImages) {
            for (auto etq: img.second->getEtiqueta()) {
                if (etq->getNombre() == nombreEtiqueta) {
                    vecUsers.push_back(usr.second);
                }
            }
        }
    }
    return vecUsers;
}

Imagen *Usuario::getImagenMasAntigua() {
    Imagen *aux = nullptr;
    Fecha fechaMasVieja = Fecha(12, 12, 2050);
    for (auto img: userImages) {
        if (img.second->getFecha() < fechaMasVieja) {
            fechaMasVieja = img.second->getFecha();
            aux = img.second;
        }
    }
    return aux;
}

Imagen *Usuario::getImagenMasReciente() {
    Imagen *aux = nullptr;
    Fecha fechaMasVieja = Fecha(1, 1, 1970);
    for (auto img: userImages) {
        if (!(img.second->getFecha() < fechaMasVieja)) {
            fechaMasVieja = img.second->getFecha();
            aux = img.second;
        }
    }
    return aux;
}

vector<Imagen *> Usuario::getImagenesFecha(Fecha fecha) {
    vector<Imagen *> vectorImgs;
    for (auto img: userImages) {
        if (img.second->getFecha().mismoDia(fecha)) {
            vectorImgs.push_back(img.second);
        }
    }
    return vectorImgs;
}

vector<Imagen *> Usuario::imagenEnZona(float rxmin, float rymin, float rxmax, float rymax) {
    vector<Imagen *> resultado;
    vector<Imagen *> vec = linkIB->buscarImagLugar(rxmin, rymin, rxmax, rymax);

    for (auto img: vec) {
        if (img->getEmail() == email) {
            resultado.push_back(img);
        }
    }

    return resultado;
}

void Usuario::likeAutomaticoZona(float rxmin, float rymin, float rxmax, float rymax) {
    vector<Imagen *> vec = linkIB->getImagePos().buscarRango(rxmin, rymin, rxmax, rymax);
    for (auto img: vec) {
        img->nuevoLike();
    }
}

const int Usuario::numImages() const {
    return userImages.size();
}

const string &Usuario::getEmail() const {
    return email;
}

const map<string, Imagen *> &Usuario::getUserImages() const {
    return userImages;
}

bool Usuario::operator<(const Usuario &other) const {
    return email < other.email;
}

bool Usuario::operator>(const Usuario &other) const {
    return other < *this;
}

bool Usuario::operator<=(const Usuario &other) const {
    return !(other < *this);
}

bool Usuario::operator>=(const Usuario &other) const {
    return !(*this < other);
}

