#include "reserva.h"

#include "QString"
#include <fstream>
#include <QVector>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
using namespace std;

Reserva::Reserva()
{

}
Reserva::Reserva(QString codigo, QString codigo_vuelo, QString codigo_vendedor, QString dni_cliente, int cantidad_asientos, float precio_total, QDateTime fecha_reserva)
{
    Reserva::codigo=codigo;
    Reserva::codigo_vuelo=codigo_vuelo;
    Reserva::codigo_vendedor=codigo_vendedor;
    Reserva::dni_cliente=dni_cliente;
    Reserva::cantidad_asientos=cantidad_asientos;
    Reserva::precio_total=precio_total;
    Reserva::fecha_reserva=fecha_reserva;
}
bool Reserva::guardar(Reserva tmp){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            query.prepare("INSERT INTO reserva VALUES(?,?,?,?,?,?,?)");
            query.bindValue(0, tmp.getCodigo());
            query.bindValue(1, tmp.getCodigoVuelo());
            query.bindValue(2, tmp.getCodigoVendedor());
            query.bindValue(3, tmp.getDniCliente());
            query.bindValue(4, tmp.getCantidadAsientos());
            query.bindValue(5, tmp.getPrecioTotal());
            query.bindValue(6, tmp.getFechaReserva());

            if(query.exec()){
                db.close();
                return true;
            }else{
                db.close();
                throw QString(query.lastError().text());
            }
        }else
          throw QString("No se pudo abrir la base de datos");

    } catch (QString &e) {
      throw e;
    }
}
bool Reserva::modificar(Reserva tmp){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            query.prepare("UPDATE reserva SET codigo_vuelo=?, codigo_vendedor=?, dni_cliente=?, cantidad_asientos=?, precio_total=?, fecha_reserva=? WHERE codigo=?");
            query.addBindValue(tmp.getCodigoVuelo());
            query.addBindValue(tmp.getCodigoVendedor());
            query.addBindValue(tmp.getDniCliente());
            query.addBindValue(tmp.getCantidadAsientos());
            query.addBindValue(tmp.getPrecioTotal());
            query.addBindValue(tmp.getFechaReserva());

            query.addBindValue(tmp.getCodigo());

            if(query.exec()){
                if(query.numRowsAffected() > 0){
                    db.close();
                    return true;
                }else{
                    db.close();
                    throw QString("No se encontro ningun registro para actualizar");
                }
            }else{
                db.close();
                throw QString(query.lastError().text());
            }
        }else
            throw QString("No se pudo abrir la base de datos");
    } catch (QString &e) {
        throw e;
    }
}
bool Reserva::eliminar(QString codigo){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            query.prepare("DELETE FROM reserva WHERE codigo = ?");
            query.bindValue(0, codigo);
            if(query.exec()){
                if(query.numRowsAffected() > 0){
                    db.close();
                    return true;
                }else{
                    db.close();
                    throw QString("No se encontro el registro a eliminar");
                }
            }else{
                db.close();
                throw QString(query.lastError().text());
            }
        }else
            throw QString("No se pudo abrir la base de datos");
    } catch (QString &e) {
        throw e;
    }
}
Reserva Reserva::buscarPorCodigo(QString codigo){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            query.prepare("SELECT * FROM reserva WHERE codigo=?");
            query.addBindValue(codigo);
            if(query.exec()){
                if(query.next()){
                    Reserva temp(
                                query.value(0).toString(),
                                query.value(1).toString(),
                                query.value(2).toString(),
                                query.value(3).toString(),
                                query.value(4).toInt(),
                                query.value(5).toFloat(),
                                query.value(6).toDateTime()
                                );
                    db.close();
                    return temp;
                }else{
                    throw QString("No se encontro la reserva");
                }
            }else{
                db.close();
                throw QString(query.lastError().text());
            }
        }else
            throw QString("No se pudo abrir la base de datos");
    } catch (QString &e) {
        throw e;
    }
}
QVector<Reserva> Reserva::todos(){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            if(query.exec("SELECT * FROM reserva")){
                QVector<Reserva> data;
                while(query.next()){

                    data << Reserva(
                      query.value(0).toString(),
                      query.value(1).toString(),
                      query.value(2).toString(),
                      query.value(3).toString(),
                      query.value(4).toInt(),
                      query.value(5).toFloat(),
                      query.value(6).toDateTime()
                            );
               }
                return data;
            }else{
                throw QString(query.lastError().text());
            }
        }else
            throw QString("Error al aperturar la base de datos");
    } catch (QString &e) {
        throw e;
    }
}

//---------------------------------------------------
//getters
//---------------------------------------------------
QString Reserva::getCodigo()
{
    return Reserva::codigo;
}
QString Reserva::getCodigoVuelo()
{
  return Reserva::codigo_vuelo;
}
QString Reserva::getCodigoVendedor()
{
  return Reserva::codigo_vendedor;
}
QString Reserva::getDniCliente()
{
  return Reserva::dni_cliente;
}
int Reserva::getCantidadAsientos()
{
  return Reserva::cantidad_asientos;
}
float Reserva::getPrecioTotal()
{
  return Reserva::precio_total;
}
QDateTime Reserva::getFechaReserva()
{
  return Reserva::fecha_reserva;
}

//---------------------------------------------------
//setters
//---------------------------------------------------
void Reserva::setCodigo(QString codigo)
{
  Reserva::codigo=codigo;
}
void Reserva::setCodigoVuelo(QString codigo_vuelo)
{
  Reserva::codigo_vuelo=codigo_vuelo;
}
void Reserva::setCodigoVendedor(QString codigo_vendedor)
{
  Reserva::codigo_vendedor=codigo_vendedor;
}
void Reserva::setCantidadAsientos(int cantidad_asientos)
{
  Reserva::cantidad_asientos=cantidad_asientos;
}
void Reserva::setDniCliente(QString dni_cliente)
{
  Reserva::dni_cliente=dni_cliente;
}
void Reserva::setPrecioTotal(float precio_total)
{
  Reserva::precio_total=precio_total;
}
void Reserva::setFechaReserva(QDateTime fecha_reserva)
{
  Reserva::fecha_reserva=fecha_reserva;
}

