#ifndef reserva_H
#define reserva_H
#include <QString>
#include <QVector>
#include <QFile>
#include <connector.h>
#include <QSqlDatabase>
#include <QSqlQuery>
class reserva
{
QString codigo;
QString codigo_vuelo;
QString codigo_vendedor;
QString dni_cliente;
int cantidad_asientos;
float precio_total;
QDateTime fecha_reserva;

public:
    reserva();
    reserva(QString codigo, QString codigo_vuelo, QString codigo_vendedor, QString dni_cliente, int cantidad_asientos, float precio_total, QDateTime fecha_reserva);
    bool guardar(reserva tmp);
    bool modificar(reserva tmp );
    bool eliminar(QString codigo);
    reserva buscarPorCodigo (QString cod);
    QVector<reserva> todos();
    void setCodigo(QString codigo);
    void setCodigoVuelo(QString codigo_vuelo);
    void setCodigoVendedor(QString codigo_vendedor);
    void setCantidadAsientos(int cantidad_asientos);
    void setDniCliente(QString dni_cliente);
    void setPrecioTotal(float precio_total);
    void setFechareserva(QDateTime fecha_reserva);
    QString getCodigo();
    QString getCodigoVuelo();
    QString getCodigoVendedor();
    QString getDniCliente();
    int getCantidadAsientos();
    float getPrecioTotal();
    QDateTime getFechareserva();
};

#endif // reserva_H
