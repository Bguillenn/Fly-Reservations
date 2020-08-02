#ifndef VUELO_H
#define VUELO_H

#include <QDateTime>
#include <QVector>
#include <QString>
#include <connector.h>
#include <QSqlDatabase>
#include <QSqlQuery>


class Vuelo
{
private:
     QString Codigo;
     QString OrigenAeropuertoCodigo;
     QString DestinoAeropuertoCodigo;
     int Capacidad;
     QDateTime Fecha_partida;
     int Asientos_Disponibles;
     float Precio_Asiento;
public:
    Vuelo();
    Vuelo(QString codigo, QString origen, QString destino,int capacidad, QDateTime fecha_partida,int asientos_disponibles,float precio_asientoF);
    static bool guardar(Vuelo);
    static bool modificar(Vuelo);
    static bool eliminar(QString);
    static Vuelo buscarPorCodigo(QString);
    static QVector<Vuelo> todos();
    void setCodigo(QString);
    void setOrigenCodigo(QString);
    void setDestinoCodigo(QString);
    void setCapacidad(int);
    void setFechaPartida(QDateTime);
    void setAsientosDisponibles(int);
    void setPrecioAsiento(float);
    QString getCodigo();
    QString getOrigenCodigo();
    QString getDestinoCodigo();
    int getCapacidad();
    QDateTime getFechaPartida();
    int getAsientosDisponibles();
    float getPrecioAsiento();
};
#endif // VUELO_H
