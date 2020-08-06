#include "vueloscontroller.h"
#include <QMessageBox>
VuelosController::VuelosController()
{

}
QVector<Vuelo> VuelosController::filtrarVuelos(QString codOri,QString codDest, int pasajeros, QDateTime fecha){
    QVector<Vuelo>data;
    QVector<Vuelo>vuelos =Vuelo::todos();
    try {
        for(int i=0; i< vuelos.size();i++){
                if((QString::compare(vuelos[i].getOrigenCodigo(),codOri,Qt::CaseInsensitive) == 0
                        && QString::compare(vuelos[i].getDestinoCodigo(),codDest,Qt::CaseInsensitive) == 0)
                        && vuelos[i].getAsientosDisponibles() >= pasajeros//asientos disponibles > pasajeros
                        && vuelos[i].getFechaPartida() >= fecha){ //Comparamos la fecha
                    data << Vuelo(
                                vuelos[i].getCodigo(),
                                vuelos[i].getOrigenCodigo(),
                                vuelos[i].getDestinoCodigo(),
                                vuelos[i].getCapacidad(),
                                vuelos[i].getFechaPartida(),
                                vuelos[i].getAsientosDisponibles(),
                                vuelos[i].getPrecioAsiento()
                                );
                }
            }
        if(data.isEmpty()){
            throw  QString  ("No se encontro vuelos disponibles");

        }else{
            return data;
        }


    } catch (QString &e) {
        throw e;
    }
}
bool VuelosController::reducirAsientosDisponibles(QString vueloCod , int asientos){
    Vuelo vuelo = Vuelo::buscarPorCodigo(vueloCod);
    try {
        if(vuelo.getAsientosDisponibles()>0){
            if(asientos <= vuelo.getAsientosDisponibles()){
                int newCapacity = vuelo.getAsientosDisponibles()-asientos;//disminución de la capacidad
                vuelo.setAsientosDisponibles(newCapacity);
                Vuelo::modificar(vuelo);
                return true;
            }else{
                throw QString("No hay asientos disponibles");
                return false;
            }
        }else{
            throw QString("No hay asientos disponibles");
            return false;
        }
    } catch (QString &e) {
        throw e;
    }
}

bool VuelosController::ampliarAsientosDisponibles(QString vueloCod , int asientos){
    Vuelo vuelo = Vuelo::buscarPorCodigo(vueloCod);
    try {

        if(asientos+vuelo.getAsientosDisponibles() <= vuelo.getCapacidad()){
            int newCapacity = vuelo.getAsientosDisponibles()+asientos;//disminución de la capacidad
            vuelo.setAsientosDisponibles(newCapacity);
            Vuelo::modificar(vuelo);
            return true;
        }else{
            throw QString("Los asientos disponibles añadidos sobrepasa la capacidad");
            return false;
        }
    } catch (QString &e) {
        throw e;
    }
}

bool VuelosController::realizado(QString vueloCod){
    Vuelo vuelo = Vuelo::buscarPorCodigo(vueloCod);

    QDateTime fecAct;
    fecAct = QDateTime::currentDateTime();
    if(vuelo.getFechaPartida()<fecAct){
        return true;
    }else {
        return false;
    }
}

