#include "UTM.h"

UTM::UTM() : latitud(0.0), longitud(0.0) {
}

UTM::UTM(float latitud, float longitud) : latitud(latitud), longitud(longitud) {
}

UTM::UTM(const UTM &orig) : latitud(orig.latitud), longitud(orig.longitud) {
}

UTM::~UTM() {
}

float UTM::GetLongitud() const {
    return longitud;
}

float UTM::GetLatitud() const {
    return latitud;
}

