#ifndef UTM_H
#define UTM_H

class UTM {
public:
    UTM();
    UTM(float latitud, float longitud);
    UTM(const UTM& orig);
    virtual ~UTM();
    float GetLongitud() const;
    float GetLatitud() const;
private:
    float latitud;
    float longitud;
};

#endif /* UTM_H */

