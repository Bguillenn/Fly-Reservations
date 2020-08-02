#include "aeropuerto.h"
#include "QString"
#include <fstream>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
using namespace std;

aeropuerto::aeropuerto()
{


}
aeropuerto::aeropuerto(QString codigo, QString nombre_aeropuerto,QString nombre_ciudad,QString nombre_pais)
{
    aeropuerto::codigo=codigo;
    aeropuerto::Nombre_aeropuerto=nombre_aeropuerto;
    aeropuerto::Nombre_Ciudad=nombre_ciudad;
    aeropuerto::Nombre_Pais=nombre_pais;
}
bool aeropuerto::guardar(aeropuerto tmp){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            query.prepare("INSERT INTO origen VALUES(?,?,?,?)");
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
bool aeropuerto::modificar(aeropuerto tmp){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            query.prepare("UPDATE origen SET nombre=?, ciudad=?, pais=? WHERE codigo=?");
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
bool aeropuerto::eliminar(QString codigo){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            query.prepare("DELETE FROM origen WHERE codigo = ?");
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
aeropuerto aeropuerto::buscarPorCodigo(QString codigo){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            query.prepare("SELECT * FROM origen WHERE codigo=?");
            query.addBindValue(codigo);
            if(query.exec()){
                if(query.next()){
                    aeropuerto temp(
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
QVector<aeropuerto> aeropuerto::todos(){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            if(query.exec("SELECT * FROM origen")){
                QVector<aeropuerto> data;
                QDateTime fechaNac;
                while(query.next()){

                    data << aeropuerto(
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

QString aeropuerto::getCodigo()
{
    return aeropuerto::codigo;
}
void aeropuerto::setCodigo(QString codigo){
    aeropuerto::codigo= codigo;
}

QString aeropuerto::getNombrePais()
{
    return aeropuerto::Nombre_Pais;
}
void aeropuerto::setNombrePais(QString Nombre_pais){
    aeropuerto::Nombre_Pais = Nombre_pais;
}

QString aeropuerto::getNombreCiudad()
{
    return aeropuerto::Nombre_Ciudad;
}
void aeropuerto::setNombreCiudad(QString Nombre_ciudad){
    aeropuerto::Nombre_Ciudad = Nombre_ciudad;
}
QString aeropuerto::getNombreAeropuerto()
{
    return aeropuerto::Nombre_aeropuerto;
}
void aeropuerto::setNombreAeropuerto(QString Nombre_aeropuerto){
    aeropuerto::Nombre_aeropuerto = Nombre_aeropuerto;
}

