#include "vuelo.h"


Vuelo::Vuelo(){

}
Vuelo::Vuelo(QString codigo, QString origen, QString destino,int capacidad, QDateTime fecha_partida,int asientos_disponibles,float precio_asiento){
    this->Codigo=codigo;
    this->OrigenAeropuertoCodigo=origen;
    this->DestinoAeropuertoCodigo=destino;
    this->Capacidad=capacidad;
    this->Fecha_partida=fecha_partida;
    this->Asientos_Disponibles=asientos_disponibles;
    this->Precio_Asiento=precio_asiento;
}

bool Vuelo::guardar(Vuelo vuelo){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QString sql = "INSERT INTO vuelo VALUES (?,?,?,?,?,?,?)";
            QSqlQuery query;
            query.prepare(sql);
            query.bindValue(0,vuelo.getCodigo());
            query.bindValue(1,vuelo.getOrigenCodigo());
            query.bindValue(2,vuelo.getDestinoCodigo());
            query.bindValue(3,vuelo.getCapacidad());
            query.bindValue(4,vuelo.getFechaPartida().toString("yyyy-MM-dd"));
            query.bindValue(5,vuelo.getAsientosDisponibles());
            query.bindValue(6,vuelo.getPrecioAsiento());

            if(query.exec()){
                db.close();
                  return  true;
              }else{
                db.close();
                throw QString(query.lastError().text());
              }
        }else{
            throw QString("Error, no se pudo abrir la BD");
        }
    } catch (QString &e) {
        throw  e;
    }
}
bool Vuelo::modificar(Vuelo vuelo){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QString sql = "UPDATE vuelo SET origen=?,destino=?,capacidad=?,fecha=?,asientosLibres=?,precio=? WHERE codigo=?";
            QSqlQuery query;
            query.prepare(sql);
            query.addBindValue(vuelo.getOrigenCodigo());
            query.addBindValue(vuelo.getDestinoCodigo());
            query.addBindValue(vuelo.getCapacidad());
            query.addBindValue(vuelo.getFechaPartida().toString("yyyy-MM-dd"));
            query.addBindValue(vuelo.getAsientosDisponibles());
            query.addBindValue(vuelo.getPrecioAsiento());
            query.addBindValue(vuelo.getCodigo());

            if(query.exec()){
                if(query.numRowsAffected()>0){
                    db.close();
                    return true;
                }else{
                    db.close();
                    throw  QString("Registro inexistente o no Disponible");
                }
            }else{
                db.close();
                throw  QString(query.lastError().text());
            }
        }else{
            throw QString("Error, no se pudo abrir la BD");
        }
    } catch (QString &e) {
        throw  e;
    }

}
bool Vuelo::eliminar(QString cod){
    Connector con ;
    try {
        QSqlDatabase db = con.initDataBase();
       if(db.open()){
           QString sql = "DELETE FROM vuelo WHERE codigo=?";
           QSqlQuery query;
           query.prepare(sql);
           query.bindValue(0,cod);

           if(query.exec()){
               if(query.numRowsAffected()>0){
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
       }else{
           throw QString("Error, no se pudo abrir la BD");
       }
    } catch (QString &e) {
        throw e;
    }
}
Vuelo Vuelo::buscarPorCodigo(QString cod){
 Connector  con;
    try {
     QSqlDatabase db = con.initDataBase();
     if(db.open()){
         QString sql = "SELECT * FROM vuelo WHERE codigo=?";
         QSqlQuery query;
         query.prepare(sql);
         query.addBindValue(cod);

         if(query.exec()){
             if(query.next()){
                 Vuelo vuelo(
                             query.value(0).toString(),
                             query.value(1).toString(),
                             query.value(2).toString(),
                             query.value(3).toInt(),//convertir a entero
                             query.value(4).toDateTime(),
                             query.value(5).toInt(),//entero
                             query.value(6).toFloat()//flotante
                             );
                 db.close();
                 return vuelo;
             }else{
                 throw QString("Vuelo no encontrado");
             }
         }else{
             db.close();
             throw QString(query.lastError().text());
         }
     }else{
         throw QString("Error, no se pudo abrir la BD");
     }
    } catch (QString &e) {
     throw e;
    }
}
QVector<Vuelo> Vuelo::todos(){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            if(query.exec("SELECT * FROM vuelo")){
                QVector<Vuelo> data;
                QDateTime partidaVue;
                QDate partida;
                while (query.next()) {
                    partida.fromString(query.value(4).toString(),"yyyy-MM-dd");
                    partidaVue.setDate(partida);
                    data << Vuelo(
                                  query.value(0).toString(),
                                  query.value(1).toString(),
                                  query.value(2).toString(),
                                  query.value(3).toInt(),//convertir a entero
                                  partidaVue,
                                  query.value(5).toInt(),//entero
                                  query.value(6).toFloat()//flotante
                                  );
                }
                return data;
            }else{
                throw QString(query.lastError().text());
            }
        }else{
             throw QString("Error, no se pudo abrir la BD");
        }
    } catch (QString &e) {
        throw e;
    }
}
void Vuelo::setCodigo(QString codigo){
    this->Codigo=codigo;

}
void Vuelo::setOrigenCodigo(QString origen){
    this->OrigenAeropuertoCodigo=origen;
}
void Vuelo::setDestinoCodigo(QString destino){
     this->DestinoAeropuertoCodigo=destino;

}
void Vuelo::setCapacidad(int capacidad){
    this->Capacidad=capacidad;

}
void Vuelo::setFechaPartida(QDateTime fecha_partida){
    this->Fecha_partida=fecha_partida;

}
void Vuelo::setAsientosDisponibles(int asientos_disponibles){
    this->Asientos_Disponibles=asientos_disponibles;

}
void Vuelo::setPrecioAsiento(float precio_asiento){
    Vuelo::Precio_Asiento=precio_asiento;
}
QString Vuelo::getCodigo(){
    return Codigo;
}
QString Vuelo::getOrigenCodigo(){
    return OrigenAeropuertoCodigo;
}
QString Vuelo::getDestinoCodigo(){
    return DestinoAeropuertoCodigo;
}
int Vuelo::getCapacidad(){
    return Capacidad;
}
QDateTime Vuelo::getFechaPartida(){
    return Fecha_partida;
}
int Vuelo::getAsientosDisponibles(){
    return Asientos_Disponibles;
}
float Vuelo::getPrecioAsiento(){
    return Precio_Asiento;
}
