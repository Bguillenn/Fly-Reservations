#ifndef reserva_H
#define reserva_H
#include <QString>
#include <QVector>
#include <QFile>
#include <connector.h>
#include <QSqlDatabase>
#include <QSqlQuery>
class Reserva
{
private:
QString codigo;
QString codigo_vuelo;
QString codigo_vendedor;
QString dni_cliente;
int cantidad_asientos;
float precio_total;
QDateTime fecha_reserva;

public:
    Reserva();
    Reserva(QString codigo, QString codigo_vuelo, QString codigo_vendedor, QString dni_cliente, int cantidad_asientos, float precio_total, QDateTime fecha_reserva);
    static bool guardar(Reserva tmp);
    static bool modificar(Reserva tmp );
    static bool eliminar(QString codigo);
    static Reserva buscarPorCodigo (QString cod);
    static QVector<Reserva> todos();
    void setCodigo(QString codigo);
    void setCodigoVuelo(QString codigo_vuelo);
    void setCodigoVendedor(QString codigo_vendedor);
    void setCantidadAsientos(int cantidad_asientos);
    void setDniCliente(QString dni_cliente);
    void setPrecioTotal(float precio_total);
    void setFechaReserva(QDateTime fecha_reserva);
    QString getCodigo();
    QString getCodigoVuelo();
    QString getCodigoVendedor();
    QString getDniCliente();
    int getCantidadAsientos();
    float getPrecioTotal();
    QDateTime getFechaReserva();
};

#endif // reserva_H
