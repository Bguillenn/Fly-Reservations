#include "reservascontroller.h"

ReservasController::ReservasController()
{

}

QVector<Reserva> ReservasController::filtrarReservasPorVendedor(QString codVen){
    try {
        QVector<Reserva> data = Reserva::todos();
        QVector<Reserva> items;
        for(int i = 0; i< data.size(); i++)
            if(data[i].getCodigoVendedor().compare(codVen) == 0)
                items << data[i];
        if(items.size() > 0)
            return items;
        else
            throw QString("No hay reservas puestas por este vendedor");
    } catch (QString &e) {
        throw e;
    }
}
QVector<Reserva> ReservasController::filtrarReservaPorDNI(QString dni){
    try {
        QVector<Reserva> data = Reserva::todos();
        QVector<Reserva> items;
        for(int i = 0; i< data.size(); i++)
            if(data[i].getDniCliente().compare(dni) == 0)
                items << data[i];
        if(items.size() > 0)
            return items;
        else
            throw QString("No hay reservas con ese DNI");
    } catch (QString &e) {
        throw e;
    }
}
float ReservasController::calcularPrecioTotal(QString vuelo_codigo, int asientos){
    try {
        Vuelo vuelo = Vuelo::buscarPorCodigo(vuelo_codigo);
        return vuelo.getPrecioAsiento() * asientos;
    } catch (QString &e) {
        throw e;
    }
}

QString ReservasController::obtenerCodigoReservaNuevo(){
    QVector<Reserva> reservas = Reserva::todos();
    QString codigoReserva = "RSV-";
    int numero = reservas.size()+1;
    codigoReserva += QString::number(numero);
    return codigoReserva;
}
