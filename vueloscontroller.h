#ifndef VuelosController_H
#define VuelosController_H

#include "vuelo.h"

#include <QVector>



class VuelosController
{
public:
    VuelosController();
    QVector<Vuelo> filtrarVuelos(QString, QString,int, QDateTime);
    bool reducirAsientosDisponibles(QString,int);
    bool ampliarAsientosDisponibles(QString, int);
    bool realizado(QString);
};

#endif // VuelosController_H
