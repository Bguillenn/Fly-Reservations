#ifndef VUELOSCONTROLLER_H
#define VUELOSCONTROLLER_H

#include "vuelo.h"

#include <QVector>



class vuelosController
{
public:
    vuelosController();
    QVector<Vuelo> filtrarVuelos(QString, QString,int);
    bool reducirAsientosDisponibles(QString,int);
    bool realizado(QString);
};

#endif // VUELOSCONTROLLER_H
