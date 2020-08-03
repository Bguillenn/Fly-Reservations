#include "origen.h"
#include "QString"
#include <fstream>
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QMessageBox>
using namespace std;

Origen::Origen()
{


}
Origen::Origen(QString codigo, QString nombre_Origen,QString nombre_ciudad,QString nombre_pais)
{
    Origen::codigo=codigo;
    Origen::Nombre_Origen=nombre_Origen;
    Origen::Nombre_Ciudad=nombre_ciudad;
    Origen::Nombre_Pais=nombre_pais;
}
bool Origen::guardar(Origen tmp){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            query.prepare("INSERT INTO origen VALUES(?,?,?,?)");
            query.bindValue(0, tmp.getCodigo());
            query.bindValue(1, tmp.getNombreOrigen());
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
bool Origen::modificar(Origen tmp){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            query.prepare("UPDATE origen SET nombre=?, ciudad=?, pais=? WHERE codigo=?");
            query.addBindValue(tmp.getNombreOrigen());
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
bool Origen::eliminar(QString codigo){
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
Origen Origen::buscarPorCodigo(QString codigo){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            query.prepare("SELECT * FROM origen WHERE codigo=?");
            query.addBindValue(codigo);
            if(query.exec()){
                if(query.next()){
                    Origen temp(
                                    query.value(0).toString(),
                                    query.value(1).toString(),
                                    query.value(2).toString(),
                                    query.value(3).toString()
                                );
                    db.close();
                    return temp;
                }else{
                    throw QString("No se encontro el Origen");
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
QVector<Origen> Origen::todos(){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            if(query.exec("SELECT * FROM origen")){
                QVector<Origen> data;
                QDateTime fechaNac;
                while(query.next()){

                    data << Origen(
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

QString Origen::getCodigo()
{
    return Origen::codigo;
}
void Origen::setCodigo(QString codigo){
    Origen::codigo= codigo;
}

QString Origen::getNombrePais()
{
    return Origen::Nombre_Pais;
}
void Origen::setNombrePais(QString Nombre_pais){
    Origen::Nombre_Pais = Nombre_pais;
}

QString Origen::getNombreCiudad()
{
    return Origen::Nombre_Ciudad;
}
void Origen::setNombreCiudad(QString Nombre_ciudad){
    Origen::Nombre_Ciudad = Nombre_ciudad;
}
QString Origen::getNombreOrigen()
{
    return Origen::Nombre_Origen;
}
void Origen::setNombreOrigen(QString Nombre_Origen){
    Origen::Nombre_Origen = Nombre_Origen;
}

