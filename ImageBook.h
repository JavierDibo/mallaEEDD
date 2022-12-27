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

    map<string, Imagen> images;
    list<Etiqueta> etiquetas;
    map<string, Usuario> usuarios;
    MallaRegular<Imagen*> imagePos;

    float maxX = 18.246205, minX = 18.246205, maxY = -66.12827, minY = -66.12827; // Valores de un valor aleatorio

    deque<Etiqueta *> cargarDeque(string etiquetasDelCSV);

    Fecha separateNumbers(const std::string &str);

    static void
    mostrar(int contador, const string id, const string &email, const string &nombre, int tam, const std::string &fecha,
            const deque<Etiqueta *> &etiquetada, float posX, float posY);

    void cargarEtiquetas(string miArchivo, bool mostrarPorPantalla);

    void cargarUsuarios(string miArchivo, bool mostrarPorPantalla);

    void cargarImages(const string &miArchivo, bool mostrarPorPantalla);

    void cargarMalla(bool mostrarPorPantalla);

public:
    ImageBook();

    ImageBook(const ImageBook &other);

    ~ImageBook() = default;

    map<string, Imagen> &getImages();

    const list<Etiqueta> &getEtiquetas() const;

    map<string, Usuario> &getUsuarios();

    Etiqueta *buscarEtiqueta(string nombre);

    vector<Usuario> buscarUsuarioFechaImagen(Fecha fecha);
};


#endif //PRAC5_IMAGEBOOK_H
