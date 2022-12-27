#include "ImageBook.h"
#include "UTM.h"
#include <cstring>
#include <set>

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

            srand(stoi(id)/3721);
            int tam, contador = 0;
            float posX, posY;
            int a = rand() % 15 + 1;

            std::istringstream(tamS) >> tam;
            std::istringstream(posXs) >> posX;
            std::istringstream(posYs) >> posY;

            deque<Etiqueta *> dequeEtiquetas = cargarDeque(etiquetasDelCSV);

            Fecha fecha = separateNumbers(fechaString);

            UTM utm(posX, posY);

            Imagen imagenAux(id, email, nombreFichero, tam, fecha, dequeEtiquetas, utm);

            images[id] = imagenAux;

            if (maxX < posX) maxX = posX;
            if (maxY < posY) maxY = posY;
            if (minX > posX) minX = posX;
            if (minY > posY) minY = posY;

            images[id].setLikes(a);

            usuarios.find(email)->second.insertaImagen(&(images[id]));
            ++contador;

            if (mostrarPorPantalla) {
                mostrar(contador, id, email, nombreFichero, tam, fechaString, dequeEtiquetas, posX, posY);
                std::cout << usuarios.find(email)->second.numImages() << " "
                          << usuarios.find(email)->second.getEmail() << std::endl;
            }
        }
        file.close();

        cout << endl << "Tamanno del contendor [images]: " << images.size() << endl;
        std::cout << "Tiempo lectura del archivo 'imagenes_v2_mod.csv': "
                  << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs.\n" << std::endl;
    } else {
        std::cout << "Error de apertura en archivo\n";
    }
}

void ImageBook::cargarMalla() {

    clock_t t_ini = clock();

    float tamannoCasilla = 3; // Da justo 15 de media
    imagePos = MallaRegular<Imagen *>(floor(minX), floor(minY), ceil(maxX),
                                      ceil(maxY), tamannoCasilla, tamannoCasilla);
    auto it = images.begin();
    while (it != images.end()) {
        imagePos.insertar(it->second.getUTM().GetLatitud(), it->second.getUTM().GetLongitud(), &(images[it->first]));
        ++it;
    }

    cout << "Tamanno del contendor [imagePos]: " << imagePos.size() << endl;
    std::cout << "Tiempo en instanciar la malla: "
              << ((clock() - t_ini) / (float) CLOCKS_PER_SEC) << " segs.\n" << std::endl;
}

ImageBook::ImageBook() {
    cargarUsuarios("../usuarios.txt", false);
    cargarEtiquetas("../etiquetas.txt", false);
    cargarImages("../imagenes_v2_mod.csv", false);
    cargarMalla();

    cout << "\nPromedio: " << imagePos.promedioElementosPorCelda() << endl
         << "\nNum elem casilla mas poblada: " << imagePos.maxElementosPorCelda() << endl;
}

ImageBook::ImageBook(const ImageBook &other) {
    images = other.images;
    etiquetas = other.etiquetas;
    usuarios = other.usuarios;
    imagePos = other.imagePos;
}

map<string, Imagen> &ImageBook::getImages() {
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

std::vector<Imagen *> ImageBook::buscarImagLugar(float rxmin, float rymin, float rxmax, float rymax) {
    if (!sonCoordenadasValidas(rxmin, rymin, rxmax, rymax)) {
        throw std::invalid_argument("Las coordenadas no son válidas");
    }

    return imagePos.buscarRango(rxmin, rymin, rxmax, rymax);
}

vector<string> ImageBook::buscarUsurLugar(float rxmin, float rymin, float rxmax, float rymax) {

    if (!sonCoordenadasValidas(rxmin, rymin, rxmax, rymax)) {
        throw std::invalid_argument("Las coordenadas no son válidas");
    }

    vector<Imagen *> vec = buscarImagLugar(rxmin, rymin, rxmax, rymax);
    vector<Imagen *> aux;
    vector<string> users;
    set<string> mapa;
    string email;

    for (auto img: vec) {
        email = img->getEmail();
        if (mapa.find(email) == mapa.end()) {
            aux.push_back(img);
            mapa.insert(email);
        }
    }

    for (const auto& usr: mapa) {
        users.push_back(usr);
    }

    return users;

}

std::vector<Imagen *>
ImageBook::buscarEtiLugar(const string &nombre, float rxmin, float rymin, float rxmax, float rymax) {

    if (!sonCoordenadasValidas(rxmin, rymin, rxmax, rymax)) {
        throw std::invalid_argument("Las coordenadas no son válidas");
    }

    vector<Imagen *> vec = buscarImagLugar(rxmin, rymin, rxmax, rymax);
    vector<Imagen *> aux;

    for (auto img: vec) {
        for (auto etiqueta: img->getEtiqueta()) {
            if (etiqueta->getNombre() == nombre) {
                aux.push_back(img);
            }
        }
    }

    return aux;
}

string ImageBook::buscarEtiquetaRepetida(float rxmin, float rymin, float rxmax, float rymax) {

    if (!sonCoordenadasValidas(rxmin, rymin, rxmax, rymax)) {
        throw std::invalid_argument("Las coordenadas no son válidas");
    }

    vector<Imagen *> vec = buscarImagLugar(rxmin, rymin, rxmax, rymax);

    map<string, int> frecuencias;
    for (auto img: vec) {
        for (auto etiqueta: img->getEtiqueta()) {
            string nombre = etiqueta->getNombre();
            if (frecuencias.count(nombre) > 0) {
                frecuencias[nombre]++;
            } else {
                frecuencias[nombre] = 1;
            }
        }
    }

    string etiqueta_mas_comun;
    int frecuencia_maxima = 0;
    for (const auto& par: frecuencias) {
        if (par.second > frecuencia_maxima) {
            etiqueta_mas_comun = par.first;
            frecuencia_maxima = par.second;
        }
    }

    return etiqueta_mas_comun;
}

bool ImageBook::sonCoordenadasValidas(float rxmin, float rymin, float rxmax, float rymax) {
    // Verificar si las coordenadas están dentro del rango válido
    return rxmin >= minX && rymin >= minY && rxmax <= maxX && rymax <= maxY;
}

const MallaRegular<Imagen *> ImageBook::getImagePos() const {
    return imagePos;
}








