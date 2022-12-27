#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>
#include <unordered_set>

#include "img.h"
#include "ImageBook.h"
#include "Imagen.h"

using namespace std;

int main(int argc, const char *argv[]) {
    ImageBook principal;

    // Mostrar los identificadores de las imágenes que se encuentran en el rango
    // (rxmin=34.04, rymin=-81.06) y (rxmax=55.04, rymax=-65.06) y que comparten alguna
    // de las etiquetas de la imagen más reciente del usuario “kenny_ohara73@yahoo.com”.
    cout << "El numero de identificadores en el rango es: ";

    vector<Imagen *> imagenesZona = principal.buscarImagLugar(34.04, -81.06, 55.04, -65.06);
    int contadorImagenes = 0;

    for (auto img: imagenesZona) {
        contadorImagenes++;
    }

    cout << contadorImagenes << endl;

    cout << "\nLas estiquetas de la imagen mas reciente de kenny son:" << endl;

    Imagen *imagenKenny = principal.getUsuarios().find("kenny_ohara73@yahoo.com")->second.getImagenMasReciente();

    vector<string> etiquetasKenny;

    for (auto etq: imagenKenny->getEtiqueta())
        etiquetasKenny.push_back(etq->getNombre());

    for (auto etq: etiquetasKenny) {
        cout << etq << endl;
    }

    cout
            << "\nLos identificadores de las imagenes que comparten etiquetas en la zona proporcionada con la ultima foto de "
               "Kenny son: " << endl;

    for (auto img: imagenesZona) {
        for (auto etq: img->getEtiqueta()) {
            for (auto etqKenny: etiquetasKenny) {
                if (etq->getNombre() == etqKenny) {
                    cout << img->getId() << endl;
                }
            }
        }
    }


    // Mostrar el email de todos los usuarios que han tomado una foto en el rango
    // (rxmin=36.388698, rymin=-121.72439) y (rxmax=39.388698, rymax=-89.72439).

    vector<string> imagenesZona2 = principal.buscarUsurLugar(36.388698, -121.72439, 39.388698, -89.72439);
    int valUsuarios = 0;

    cout << "\nLos usuarios que han publicado una foto en la zona son: " << endl;
    for (auto usr: imagenesZona2) {
        valUsuarios++;
        //Omitido por ser muchas para la consola
        //cout << usr << endl;
    }

    cout << valUsuarios << endl;

    // Mostrar el nombre de la etiqueta que más se repite en aquellas imágenes localizadas en
    // el rango (rxmin=30.0201, rymin=-98.2340) y (rxmax=60.0039, rymax=-80.99).

    string etiquetaMasRepe = principal.buscarEtiquetaRepetida(30.0201, -98.2340, 60.0039, -80.99);

    cout << "\nLa etiqueta mas repetida en la zona es: " << endl << etiquetaMasRepe << endl;

    //Buscar las imágenes del usuario “beau1@hotmail.com” que se encuentran localizadas
    //en el rango (rxmin=30.8304, rymin=-94.8684) y (rxmax=47.3304, rymax=-65.3684) y
    //obtener de ellas la imagen con más likes (en caso de empate coger una de ellas).

    cout << "\nImagenes del usuario en la zona: " << endl;

    vector<Imagen *> imagenesZona3 = principal.buscarImagLugar(30.8304, -94.8684, 47.3304, -65.3684);
    vector<Imagen *> imagenesBeau;

    for (auto img: imagenesZona3) {
        if (img->getEmail() == "beau1@hotmail.com") {
            imagenesBeau.push_back(img);
            cout << img->getId() << endl;
        }
    }

    cout << "\nLa imagen con mas likes es: " << endl;

    int maxLikes = 0;
    Imagen imagenMasLikes;

    for (auto img: imagenesBeau) {
        if (img->getLikes() > maxLikes) {
            imagenMasLikes = *img;
            maxLikes = img->getLikes();
        }
    }

    cout << imagenMasLikes.getId() << endl;

    // A continuación, dar like a aquellas imágenes que están localizadas dentro del rango de la
    // imagen con más likes (rxmin=longitudImagenMásLikes-0.1,
    // rymin=latitudImagenMásLikes-0.1) y (rxmax=longitudImagenMásLikes+0.1,
    // rymax=latitudImagenMásLikes+0.1). Para comprobar que los likes se han asignado
    // correctamente, mostrar los likes de las imágenes antes y después del cambio.

    float rxmin = imagenMasLikes.getUTM().GetLatitud()-0.1,
        rymin = imagenMasLikes.getUTM().GetLongitud()-0.1,
        rxmax = imagenMasLikes.getUTM().GetLatitud()+0.1,
        rymax = imagenMasLikes.getUTM().GetLongitud()+0.1;

    cout << "\nImagenes dentro de la zona: " << endl;

    vector<Imagen *> imagenesZona4 = principal.buscarImagLugar(rxmin, rymin, rxmax, rymax);

    for (auto img: imagenesZona4) {
        cout << img->getId() << ": " << img->getLikes() << endl;
    }

    cout << "\nImagenes dentro de la zona tras darle like: " << endl;

    for (auto img: imagenesZona4) {
        img->nuevoLike();
        cout << img->getId() << ": " << img->getLikes() << endl;
    }
    
    return EXIT_SUCCESS;
}
