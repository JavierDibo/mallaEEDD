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
    MallaRegular<Imagen *> imagePos;
public:
    const MallaRegular<Imagen *> getImagePos() const;

private:

    float maxX = 71.2995224, minX = 17.734211, maxY = -64.7346954, minY = -176.636749; // Valores max/min, son ajustados dinamicamente

    deque<Etiqueta *> cargarDeque(string etiquetasDelCSV);

    Fecha separateNumbers(const std::string &str);

    static void
    mostrar(int contador, const string id, const string &email, const string &nombre, int tam, const std::string &fecha,
            const deque<Etiqueta *> &etiquetada, float posX, float posY);

    void cargarEtiquetas(string miArchivo, bool mostrarPorPantalla);

    void cargarUsuarios(string miArchivo, bool mostrarPorPantalla);

    void cargarImages(const string &miArchivo, bool mostrarPorPantalla);

    void cargarMalla();

public:
    ImageBook();

    ImageBook(const ImageBook &other);

    ~ImageBook() = default;

    map<string, Imagen> &getImages();

    const list<Etiqueta> &getEtiquetas() const;

    map<string, Usuario> &getUsuarios();

    Etiqueta *buscarEtiqueta(string nombre);

    vector<Usuario> buscarUsuarioFechaImagen(Fecha fecha);

    std::vector<Imagen *> buscarImagLugar(float rxmin, float rymin, float rxmax, float rymax);

    vector<Imagen *> buscarEtiLugar(const string &nombre, float rxmin, float rymin, float rxmax, float rymax);

    vector<string> buscarUsurLugar(float rxmin, float rymin, float rxmax, float rymax);

    string buscarEtiquetaRepetida(float rxmin, float rymin, float rxmax, float rymax);

    bool sonCoordenadasValidas(float rxmin, float rymin, float rxmax, float rymax);

};


#endif //PRAC5_IMAGEBOOK_H
