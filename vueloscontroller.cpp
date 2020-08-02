#include "vueloscontroller.h"

vuelosController::vuelosController()
{

}
QVector<Vuelo> vuelosController::filtrarVuelos(QString codOri,QString codDest, int pasajeros){
    QVector<Vuelo>data;
    QVector<Vuelo>vuelos =Vuelo::todos();
    try {
        for(int i=0; i< vuelos.size();i++){
                if((QString::compare(vuelos[i].getOrigenCodigo(),codOri,Qt::CaseInsensitive)==1
                        && QString::compare(vuelos[i].getDestinoCodigo(),codDest,Qt::CaseInsensitive)==1)
                        || vuelos[i].getCapacidad()== pasajeros){//pasajeros y capacidad con dudas
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
            throw  QString  ("No se, encontro Vuelos disponibles");

        }else{
            return data;
        }


    } catch (QString &e) {
        throw e;
    }
}
bool vuelosController::reducirAsientosDisponibles(QString vueloCod , int asientos){
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
bool vuelosController::realizado(QString vueloCod){
    Vuelo vuelo = Vuelo::buscarPorCodigo(vueloCod);

    QDateTime fecAct;
    fecAct = QDateTime::currentDateTime();
    if(vuelo.getFechaPartida()<fecAct){
        return true;
    }else {
        return false;
    }
}

