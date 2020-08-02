#include "destino.h"
#include "QString"
#include <fstream>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
using namespace std;
destino::destino()
{
}
destino::destino(QString codigo, QString nombre_aeropuerto,QString nombre_ciudad,QString nombre_pais)
{
    destino::codigo=codigo;
    destino::Nombre_aeropuerto=nombre_aeropuerto;
    destino::Nombre_Ciudad=nombre_ciudad;
    destino::Nombre_Pais=nombre_pais;
}
bool destino::guardar(destino tmp){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            query.prepare("INSERT INTO destino VALUES(?,?,?,?)");
            query.bindValue(0, tmp.getCodigo());
            query.bindValue(1, tmp.getNombreAeropuerto());
            query.bindValue(2, tmp.getNombreCiudad());
            query.bindValue(3, tmp.getNombrePais());

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
bool destino::modificar(destino tmp){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            query.prepare("UPDATE destino SET nombre=?, ciudad=?, pais=? WHERE codigo=?");
            query.addBindValue(tmp.getNombreAeropuerto());
            query.addBindValue(tmp.getNombreCiudad());
            query.addBindValue(tmp.getNombrePais());

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
bool destino::eliminar(QString codigo){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            query.prepare("DELETE FROM destino WHERE codigo = ?");
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
destino destino::buscarPorCodigo(QString codigo){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            query.prepare("SELECT * FROM destino WHERE codigo=?");
            query.addBindValue(codigo);
            if(query.exec()){
                if(query.next()){
                    destino temp(
                                    query.value(0).toString(),
                                    query.value(1).toString(),
                                    query.value(2).toString(),
                                    query.value(3).toString()
                                );
                    db.close();
                    return temp;
                }else{
                    throw QString("No se encontro el aeropuerto");
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
QVector<destino> destino::todos(){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            if(query.exec("SELECT * FROM destino")){
                QVector<destino> data;
                QDateTime fechaNac;
                while(query.next()){

                    data << destino(
                                query.value(0).toString(),
                                query.value(1).toString(),
                                query.value(2).toString(),
                                query.value(3).toString()
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

QString destino::getCodigo()
{
    return destino::codigo;
}
void destino::setCodigo(QString codigo){
    destino::codigo= codigo;
}

QString destino::getNombrePais()
{
    return destino::Nombre_Pais;
}
void destino::setNombrePais(QString Nombre_pais){
    destino::Nombre_Pais = Nombre_pais;
}

QString destino::getNombreCiudad()
{
    return destino::Nombre_Ciudad;
}
void destino::setNombreCiudad(QString Nombre_ciudad){
    destino::Nombre_Ciudad = Nombre_ciudad;
}
QString destino::getNombreAeropuerto()
{
    return destino::Nombre_aeropuerto;
}
void destino::setNombreAeropuerto(QString Nombre_aeropuerto){
    destino::Nombre_aeropuerto = Nombre_aeropuerto;
}
