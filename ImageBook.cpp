#include "ImageBook.h"
#include <cstring>

void
ImageBook::mostrar(int contador, const string id, const string &email, const string &nombre, int tam,
                   const std::string &fecha, const deque<Etiqueta *> &etiquetada, float posX, float posY) {
    std::cout << contador
              << " Imagen: ( ID=" << id
              << " Email=" << email << " Fichero=" << nombre << " Tam=" << tam
              << " Fecha=" << fecha
              << " Etiqueta=";
    for (auto x: etiquetada) {
        printf("%s ", x->getNombre().c_str());
    }
    std::cout << " X=" << posX << " Y=" << posY;
    printf(")\n");
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

deque<Etiqueta *> ImageBook::cargarDeque(string etiquetasDelCSV) {
    deque<Etiqueta *> etiquetasDeque;
    string str = etiquetasDelCSV;
    size_t posComa = 0;
    string palabra;
    while ((posComa = str.find(',')) != string::npos) {
        palabra = str.substr(0, posComa);
        Etiqueta aux = Etiqueta(palabra);
        std::list<Etiqueta>::iterator it;
        it = std::find(etiquetas.begin(), etiquetas.end(), aux);
        etiquetasDeque.emplace_back(&*it);
        str.erase(0, posComa + 1);
        if (palabra == "final") {
            int i = 0;
        }
    }
    Etiqueta aux = Etiqueta(str);
    std::list<Etiqueta>::iterator it;
    it = std::find(etiquetas.begin(), etiquetas.end(), aux);
    etiquetasDeque.emplace_back(&*it);

    return etiquetasDeque;
}

Fecha ImageBook::separateNumbers(const std::string &str) {
    std::stringstream ss(str);
    int numA, numB, numC;
    char delimiter = '/';

    ss >> numA >> delimiter >> numB >> delimiter >> numC;
    Fecha fecha(numA, numB, numC);

    return fecha;
}

void ImageBook::cargarImages(const string &miArchivo, bool mostrarPorPantalla) {
    std::ifstream file(miArchivo);
    if (file.good()) {
        clock_t t_ini = clock();

        std::string line;
        while (std::getline(file, line)) {
            if (line.empty()) continue;

            //formato de fila: id;email;nombreFichero;tam;fechaString;etiquetada;posX;posY
            std::istringstream iss(line);
            std::string id, tamS, posXs, posYs, email, nombreFichero, fechaString, etiquetasDelCSV;

            std::getline(iss, id, ';');
            std::getline(iss, email, ';');
            std::getline(iss, nombreFichero, ';');
            std::getline(iss, tamS, ';');
            std::getline(iss, fechaString, ';');
            std::getline(iss, etiquetasDelCSV, ';');
            std::getline(iss, posXs, ';');
            std::getline(iss, posYs, ';');

            int tam, contador = 0;
            float posX, posY;

            std::istringstream(tamS) >> tam;
            std::istringstream(posXs) >> posX;
            std::istringstream(posYs) >> posY;

            deque<Etiqueta *> dequeEtiquetas = cargarDeque(etiquetasDelCSV);

            Fecha fecha = separateNumbers(fechaString);

            Imagen imagenAux(id, email, nombreFichero, tam, fecha, dequeEtiquetas, posX, posY);
            images[contador] = imagenAux;
            usuarios.find(email)->second.insertaImagen(&(images[contador]));
            ++contador;

            if (mostrarPorPantalla) {
                mostrar(contador, id, email, nombreFichero, tam, fechaString, dequeEtiquetas, posX, posY);
                std::cout << usuarios.find(email)->second.numImages() << " "
                          << usuarios.find(email)->second.getEmail() << std::endl;
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
    images = vector<Imagen>(10000);
    cargarUsuarios("../usuarios.txt", false);
    cargarEtiquetas("../etiquetas.txt", false);
    cargarImages("../imagenes_v2_mod.csv", true);
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






