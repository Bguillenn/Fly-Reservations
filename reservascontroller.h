#ifndef RESERVASCONTROLLER_H
#define RESERVASCONTROLLER_H

#include <QVector>
#include <reserva.h>
#include <vuelo.h>

class ReservasController
{
public:
    ReservasController();
    QVector<Reserva> filtrarReservasPorVendedor(QString);
    QVector<Reserva> filtrarReservaPorDNI(QString);
    float calcularPrecioTotal(QString vuelo_codigo, int asientos);
    QString obtenerCodigoReservaNuevo();
};

#endif // RESERVASCONTROLLER_H
