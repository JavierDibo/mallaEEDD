//
// Created by gara on 26/11/2022.
//

#include "ImageBook.h"
#include <string.h>

void
ImageBook::mostrar(int contador, const string &id, const string &email, const string &nombre, int tam, int dia, int mes,
                   int anno, const deque<Etiqueta *> &etiquetada, int posX, int posY) {
    std::cout << contador
              << " Imagen: ( ID=" << id
              << " Email=" << email << " Fichero=" << nombre << " Tam=" << tam
              << " Fecha=" << dia << "/" << mes << "/" << anno
              << " Etiqueta=";
    for (auto x: etiquetada) {
        printf("%s ", x->getNombre().c_str());
    }
    std::cout << " X=" << posX << " Y=" << posY;
    printf(")\n");
}

void
ImageBook::mostrar(int contador, const string &id, const string &email, const string &nombre, int tam, int dia, int mes,
                   int anno) {
    std::cout << contador
              << " Imagen: ( ID=" << id
              << " Email=" << email << " Fichero=" << nombre << " Tam=" << tam
              << " Fecha=" << dia << "/" << mes << "/" << anno
              << endl;
}

void ImageBook::cargarEtiquetas(string miArchivo, bool mostrarPorPantalla) {
    std::ifstream archivo;
    std::stringstream columnas;
    std::string etiqueta, fila;
    int contador = 0;

    archivo.open(miArchivo);
    if (archivo.good()) {

        clock_t t_ini = clock();

        while (getline(archivo, fila)) {

            if (!fila.empty()) {

                columnas.str(fila);

                getline(columnas, etiqueta, '\n');
                fila = "";
                columnas.clear();

                etiquetas.emplace_back(etiqueta);
                ++contador;

                if (mostrarPorPantalla)
                    std::cout << etiqueta << std::endl;
            }
        }
        archivo.close();
        cout << endl << "Tamanno del contendor [etiquetas]: " << etiquetas.size() << endl;
        std::cout << "Tiempo lectura del archivo 'etiquetas.txt': " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC)
                  << " segs." << std::endl;

    } else {
        std::cout << "Error de apertura en archivo\n";
    }
}

void ImageBook::cargarUsuarios(string miArchivo, bool mostrarPorPantalla) {
    std::ifstream archivo;
    std::stringstream columnas;
    std::string email, fila;
    int contador = 0;

    archivo.open(miArchivo);
    if (archivo.good()) {

        clock_t t_ini = clock();

        while (getline(archivo, fila)) {

            if (!fila.empty()) {

                columnas.str(fila);

                getline(columnas, email, '\n');
                fila = "";
                columnas.clear();
                Usuario nuevo(email, this);

                usuarios.insert({email, nuevo});
                ++contador;

                if (mostrarPorPantalla)
                    std::cout << email << std::endl;
            }
        }
        archivo.close();
        cout << endl << "Tamanno del contendor [usuarios]: " << usuarios.size() << endl;
        cout << "Tiempo lectura del archivo 'usuarios.txt': " << ((clock() - t_ini) / (float) CLOCKS_PER_SEC)
             << " segs." << std::endl;

    } else {
        cout << "Error de apertura en archivo\n";
    }
}

void ImageBook::cargarImages(string miArchivo, bool mostrarPorPantalla) {
    std::ifstream file;
    std::stringstream columnas;
    std::string fila, id, email, nombre, etiquetas_todas;
    std::map<std::string, Imagen> images;
    int tam = 0, dia = 0, mes = 0, anno = 0, contador = 0, posX = 0, posY = 0;

    file.open(miArchivo);
    if (file.good()) {

        clock_t t_ini = clock();

        while (getline(file, fila)) {

            if (!fila.empty()) {

                columnas.str(fila);

                //formato de fila: id;email;nombre;tam;fecha;etiquetada;posX;posY

                getline(columnas, id, ';');
                getline(columnas, email, ';');
                getline(columnas, nombre, ';');

                columnas >> tam >> posX >> posY;
                columnas.ignore();

                columnas >> dia;
                columnas.ignore();
                columnas >> mes;
                columnas.ignore();
                columnas >> anno;
                columnas.ignore();

                getline(columnas, etiquetas_todas);
                fila = "";
                columnas.clear();

                Fecha fecha(dia, mes, anno);

                deque<Etiqueta *> etiquetada;
                string etiqueta;
                int pos = 0, pos2 = 0;

                while (pos != -1) {
                    pos = etiquetas_todas.find_last_of(',');
                    etiqueta = etiquetas_todas.substr(pos + 1);
                    pos2 = etiquetas_todas.find(',' + etiqueta);
                    if (pos2 != -1) {
                        etiquetas_todas.erase(pos2);
                    }
                    Etiqueta aux = Etiqueta(etiqueta);
                    std::list<Etiqueta>::iterator it;
                    it = std::find(etiquetas.begin(), etiquetas.end(), aux);
                    etiquetada.emplace_back(&*it);
                }

                Imagen imagenAux(id, nombre, to_string(tam), fecha, etiquetada, posX, posY);
                images[id] = imagenAux;
                usuarios.find(email)->second.insertaImagen(&(images[id]));
                ++contador;

                if (mostrarPorPantalla) {
                    mostrar(contador, id, email, nombre, tam, dia, mes, anno, etiquetada, posX, posY);
                    cout << usuarios.find(email)->second.numImages() << " "
                         << usuarios.find(email)->second.getEmail() << endl;
                }
            }
        }
        file.close();
        std::cout << "Tiempo lectura del archivo 'imagenes_v2_mod.csv': "
                  << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs." << std::endl;

    } else {
        std::cout << "Error de apertura en archivo\n";
    }
}

ImageBook::ImageBook() {
    cargarImages("../imagenes_v2_mod.csv", true);
    cargarUsuarios("../usuarios.txt", false);
    cargarEtiquetas("../etiquetas.txt", false);
}

ImageBook::ImageBook(const ImageBook &other) {
    images = other.images;
    etiquetas = other.etiquetas;
    usuarios = other.usuarios;
}

vector<Imagen> &ImageBook::getImages() {
    return images;
}

const list<Etiqueta> &ImageBook::getEtiquetas() const {
    return etiquetas;
}

map<string, Usuario> &ImageBook::getUsuarios() {
    return usuarios;
}

Etiqueta *ImageBook::buscarEtiqueta(string nombre) {
    Etiqueta aux = Etiqueta(nombre);
    std::list<Etiqueta>::iterator it;
    it = std::find(etiquetas.begin(), etiquetas.end(), aux);
    if (!&*it) {
        return nullptr;
    }
    return &*it;
}

vector<Usuario> ImageBook::buscarUsuarioFechaImagen(const Fecha fecha) {
    vector<Usuario> vecUsers;
    for (auto user: usuarios) {
        map<string, Imagen *> imgs = user.second.getUserImages();
        for (auto img: imgs) {
            if (img.second->getFecha().mismoDia(fecha)) {
                vecUsers.push_back(user.second);
            }
        }
    }
    return vecUsers;
}






