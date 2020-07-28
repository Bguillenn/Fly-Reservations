#include "loginview.h"

#include <QApplication>
#include <connector.h>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    try {
        //Inicializamos la base de datos de SQLite
        Connector conexion;
        QSqlDatabase db = conexion.initDataBase();
        if(!db.open()){
            throw QString(db.lastError().text());
        }
        //Comenzamos la creacion de las tablas en caso no existan
        QSqlQuery q;
        //Creamos la tabla empleado si no existe
        q.exec("CREATE TABLE IF NOT EXISTS empleado ("
               "codigo VARCHAR(10) NOT NULL, "
               "nombres VARCHAR(40) NOT NULL, "
               "apellidos VARCHAR(40) NOT NULL, "
               "fnacimiento VARCHAR(22) NOT NULL DEFAULT '2000-03-11 00:00:00', "
               "sexo ENUM('M','F') NOT NULL DEFAULT 'M',"
               "dni VARCHAR(8) NOT NULL DEFAULT '00000000', "
               "contrasenia VARCHAR(20) NOT NULL, "
               "tipo ENUM('V', 'A') NOT NULL DEFAULT 'V', "
               "PRIMARY KEY('codigo'))");

        //Creamos la tabla origen si no existe
        q.exec("CREATE TABLE IF NOT EXISTS origen ("
               "codigo VARCHAR(10) NOT NULL,"
               "nombre VARCHAR(50) NOT NULL DEFAULT 'UNDEFINED',"
               "ciudad VARCHAR(50) NOT NULL DEFAULT 'UNDEFINED',"
               "pais VARCHAR(50) NOT NULL DEFAULT 'UNDEFINED',"
               "PRIMARY KEY('codigo'))");
        //Creamos la tabla destino si no existe
        q.exec("CREATE TABLE IF NOT EXISTS destino ("
               "codigo VARCHAR(10) NOT NULL,"
               "nombre VARCHAR(50) NOT NULL DEFAULT 'UNDEFINED',"
               "ciudad VARCHAR(50) NOT NULL DEFAULT 'UNDEFINED',"
               "pais VARCHAR(50) NOT NULL DEFAULT 'UNDEFINED',"
               "PRIMARY KEY('codigo'))");

        //Creamos la tabla vuelo
        q.exec("CREATE TABLE IF NOT EXISTS vuelo ("
               "codigo VARCHAR(10) NOT NULL, "
               "origen VARCHAR(10) NOT NULL,"
               "destino VARCHAR(10) NOT NULL,"
               "capacidad INT NOT NULL DEFAULT '40',"
               "fecha VARCHAR(22) NOT NULL DEFAULT '2000-01-01 00:00:00', "
               "asientosLibres INT NOT NULL,"
               "precio REAL NOT NULL DEFAULT '0.0', "
               "PRIMARY KEY('codigo'), "
               "FOREIGN KEY('origen') REFERENCES origen('codigo'), "
               "FOREIGN KEY('destino') REFERENCES destino('codigo'))");

        //Creamos la tabla reserva
        q.exec("CREATE TABLE IF NOT EXISTS reserva ("
               "codigo VARCHAR(10) NOT NULL, "
               "vuelo VARCHAR(10) NOT NULL, "
               "vendedor VARCHAR(10) NOT NULL, "
               "dniCliente VARCHAR(8) NOT NULL, "
               "asientos INT NOT NULL DEFAULT '1', "
               "total REAL NOT NULL DEFAULT '0.0' , "
               "fecha VARCHAR(22) NOT NULL DEFAULT '2000-01-01 00:00:00', "
               "PRIMARY KEY('codigo'), "
               "FOREIGN KEY('vuelo') REFERENCES vuelo('codigo'), "
               "FOREIGN KEY('vendedor') REFERENCES empleado('codigo'))");

         //Cerramos la base de datos
        db.close();
    } catch (QString &e) {
        QMessageBox::warning(nullptr, "Error", e);
        return 0;
    }
    LoginView w;
    w.show();
    return a.exec();
}
