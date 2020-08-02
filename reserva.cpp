#include "reserva.h"
#include "QString"
#include <fstream>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
using namespace std;

reserva::reserva()
{

}
reserva(QString codigo, QString codigo_vuelo, QString codigo_vendedor, QString dni_cliente, int cantidad_asientos, float precio_total, QDateTime fecha_reserva)
{
    reserva::codigo=codigo;
    reserva::codigo_vuelo=codigo_vuelo;
    reserva::codigo_vendedor=codigo_vendedor;
    reserva::dni_cliente=dni_cliente;
    reserva::cantidad_asientos=cantidad_asientos;
    reserva::precio_total=precio_total;
    reserva::fecha_reserva=fecha_reserva;
}
bool reserva::guardar(reserva tmp){
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
bool reserva::modificar(reserva tmp){
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
bool reserva::eliminar(QString codigo){
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
reserva reserva::buscarPorCodigo(QString codigo){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            query.prepare("SELECT * FROM reserva WHERE codigo=?");
            query.addBindValue(codigo);
            if(query.exec()){
                if(query.next()){
                    reserva temp(
                                    query.value(0).toString(),
                                    query.value(1).toString(),
                                    query.value(2).toString(),
                                    query.value(3).toString(),
                                    QString::fromStdString(query.value(4).toString()).toInt(),
                                    QString::fromStdString(query.value(5).toString()).toFloat();,
                                    query.value(6).toString()
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
QVector<reserva> reserva::todos(){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            if(query.exec("SELECT * FROM reserva")){
                QVector<reserva> data;
                while(query.next()){

                    data << reserva(
                      query.value(0).toString(),
                      query.value(1).toString(),
                      query.value(2).toString(),
                      query.value(3).toString(),
                      QString::fromStdString(query.value(4).toString()).toInt(),
                      QString::fromStdString(query.value(5).toString()).toFloat();,
                      query.value(6).toString()
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
QString reserva::getCodigo()
{
    return reserva::codigo;
}
QString getCodigoVuelo()
{
  return reserva::codigo_vuelo;
}
QString getCodigoVendedor()
{
  return reserva::codigo_vendedor;
}
QString getDniCliente()
{
  return reserva::dni_cliente;
}
int getCantidadAsientos()
{
  return reserva::cantidad_asientos;
}
float getPrecioTotal()
{
  return reserva::precio_total;
}
QDateTime getFechaReserva()
{
  return reserva::fecha_reserva;
}

//---------------------------------------------------
//setters
//---------------------------------------------------
void setCodigo(QString codigo)
{
  reserva::codigo=codigo;
}
void setCodigoVuelo(QString codigo_vuelo)
{
  reserva::codigo_vuelo=codigo_vuelo;
}
void setCodigoVendedor(QString codigo_vendedor)
{
  reserva::codigo_vendedor=codigo_vendedor;
}
void setCantidadAsientos(int cantidad_asientos)
{
  reserva::cantidad_asientos=cantidad_asientos;
}
void setDniCliente(QString dni_cliente)
{
  reserva::dni_cliente=dni_cliente;
}
void setPrecioTotal(float precio_total)
{
  reserva::precio_total=precio_total;
}
void setFechaReserva(QDateTime fecha_reserva)
{
  reserva::fecha_reserva=fecha_reserva;
}
