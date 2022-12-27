#include <fstream>
#include <iostream>
#include <vector>
#include <math.h>

#include "img.h"
#include "ImageBook.h"

using namespace std;

int main(int argc, const char *argv[]) {
    ImageBook hola;

    vector<Imagen*> vec = hola.buscarEtiLugar("geografia", 25,-90,30, -80);

    for (auto x: vec) {
        cout << x->getId() << endl;
    }

    /*
    RGBColor blanco(255, 255, 255);

    Img img(1300, 700, blanco);

    int nfilas = img.numFilas();
    int ncol = img.numColumnas();

    cout << "Imagen creada con " << nfilas << " filas y " << ncol << " columnas." << endl;

    int r = 0; // azul
    int g = 0;
    int b = 255;

    // sabemos el tamaño de la caja envolvente de los datos, pero volver a calcular

    double minlat = 35.86688;
    double maxlat = 43.272616;
    double minlon = -9.99443;
    double maxlon = 3.98926;

    // Calculamos el número de pixeles asociados a un grado

    cout << "lat: xmin = " << minlat << ", " << "xmax = " << maxlat << endl;
    cout << "lon: ymin = " << minlon << ", " << "ymax = " << maxlon << endl;

    double rangox = maxlat - minlat;
    double rangoy = maxlon - minlon;

    cout << "rango x = " << rangox << endl;
    cout << "rango y = " << rangoy << endl;

    cout << "nfilas = " << nfilas << endl;
    cout << "ncol = " << ncol << endl;

    double pixelPorGradoX = (double) (nfilas - 1) / rangox;
    double pixelPorGradoY = (double) (ncol - 1) / rangoy;

    cout << "Pixel por Grado X = " << pixelPorGradoX << endl;
    cout << "Pixel por Grado Y = " << pixelPorGradoY << endl;

    // elegimos las coordenada de un recuadro cualquiera

    double lat1 = 40;
    double lon1 = -8;

    double lat2 = 42.0;
    double lon2 = -5.0;

    img.pintarRecuadro((lat1 - minlat) * pixelPorGradoX, ncol - 1 - ((lon1 - minlon) * pixelPorGradoY),
                       (lat2 - minlat) * pixelPorGradoX, ncol - 1 - ((lon2 - minlon) * pixelPorGradoY), 255, 0, 0);

    // ejemplo de punto que debe estar por el centro, lo pintamos acto seguido

    double vlat = 39.569748;
    double vlon = -3.002585;

    int posX = (vlat - minlat) * pixelPorGradoX;
    int posY = ncol - 1 - ((vlon - minlon) * pixelPorGradoY);
    img.pintarPixelGrande(posX, posY, r, g, b);
    img.pintarPixel(posX, posY, r, g, b);

    try {
        img.guardar("./mapaUsaResult.ppm");
    }
    catch (ErrorEscrituraFichero &e) {
        cout << "Error al escribir fichero" << endl;
        return 1;
    }

    cout << "Operacion realizada con exito, ahora visualizarlo con cualquier visor de imagenes" << endl;

     */

    return EXIT_SUCCESS;
}
