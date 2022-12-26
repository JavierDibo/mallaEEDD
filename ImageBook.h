#ifndef PRAC5_IMAGEBOOK_H
#define PRAC5_IMAGEBOOK_H

#include <vector>
#include <algorithm>
#include <list>
#include <map>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>

#include "Imagen.h"
#include "Etiqueta.h"
#include "Usuario.h"
#include "MallaRegular.h"

using std::string;

class Usuario;

class ImageBook {
private:
    vector<Imagen> images;
    list<Etiqueta> etiquetas;
    map<string, Usuario> usuarios;

    deque<Etiqueta *> cargarDeque(string etiquetasDelCSV);

    Fecha separateNumbers(const std::string &str);

    static void
    mostrar(int contador, const string id, const string &email, const string &nombre, int tam, const std::string& fecha,
            const deque<Etiqueta *> &etiquetada, float posX, float posY);

    void cargarEtiquetas(string miArchivo, bool mostrarPorPantalla);

    void cargarUsuarios(string miArchivo, bool mostrarPorPantalla);

    void cargarImages(const string &miArchivo, bool mostrarPorPantalla);

public:
    ImageBook();

    ImageBook(const ImageBook &other);

    ~ImageBook() = default;

    vector<Imagen> &getImages();

    const list<Etiqueta> &getEtiquetas() const;

    map<string, Usuario> &getUsuarios();

    Etiqueta *buscarEtiqueta(string nombre);

    vector<Usuario> buscarUsuarioFechaImagen(Fecha fecha);
};


#endif //PRAC5_IMAGEBOOK_H
