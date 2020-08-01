#include "empleado.h"
#include <QMessageBox>
// Implementacion del constructor
Empleado::Empleado(){
//VACIO PARA QUE FUNCIONE EL QVECTOR
    //LOS QCHAR POR QSTRING
}
Empleado::Empleado(QString Codigo, QString Nombres, QString Apellidos, QDateTime Fecha_Nacimiento, QString Sexo, QString DNI, QString Contrasenia, QString Tipo){
    this->Codigo = Codigo;
    this->Nombres = Nombres;
    this->Apellidos = Apellidos;
    this->Fecha_Nacimiento = Fecha_Nacimiento;
    this->sexo = Sexo;
    this->DNI = DNI;
    this->Contrasenia = Contrasenia;
    this->Tipo = Tipo;
}

// Implementacion metodos estaticos
bool Empleado::guardar(Empleado empleado){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            query.prepare("INSERT INTO empleado VALUES(?,?,?,?,?,?,?,?)");
            query.bindValue(0, empleado.getCodigo());
            query.bindValue(1, empleado.getNombres());
            query.bindValue(2, empleado.getApellidos());
            query.bindValue(3, empleado.getFechaNacimiento().toString("yyyy-MM-dd"));
            query.bindValue(4, empleado.getSexo());
            query.bindValue(5, empleado.getDNI());
            query.bindValue(6, empleado.getContrasenia());
            query.bindValue(7, empleado.getTipo());

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
bool Empleado::modificar(Empleado empleado){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            query.prepare("UPDATE empleado SET nombres=?, apellidos=?, fnacimiento=?, sexo=?, dni=?, contrasenia=?, tipo=? WHERE codigo=?");
            query.addBindValue(empleado.getNombres());
            query.addBindValue(empleado.getApellidos());
            query.addBindValue(empleado.getFechaNacimiento().toString("yyyy-MM-dd"));
            query.addBindValue(empleado.getSexo());
            query.addBindValue(empleado.getDNI());
            query.addBindValue(empleado.getContrasenia());
            query.addBindValue(empleado.getTipo());
            query.addBindValue(empleado.getCodigo());

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
bool Empleado::eliminar(QString codigo){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            query.prepare("DELETE FROM empleado WHERE codigo = ?");
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
Empleado Empleado::buscarPorCodigo(QString codigo){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            query.prepare("SELECT * FROM empleado WHERE codigo=?");
            query.addBindValue(codigo);
            if(query.exec()){
                if(query.next()){
                    Empleado empleado(
                                    query.value(0).toString(),
                                    query.value(1).toString(),
                                    query.value(2).toString(),
                                    query.value(3).toDateTime(),
                                    query.value(4).toString(),
                                    query.value(5).toString(),
                                    query.value(6).toString(),
                                    query.value(7).toString()
                                );
                    db.close();
                    return empleado;
                }else{
                    throw QString("No se encontro el empleado");
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

QVector<Empleado> Empleado::todos(){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
        if(db.open()){
            QSqlQuery query;
            if(query.exec("SELECT * FROM empleado")){
                QVector<Empleado> data;
                QDateTime fechaNac;
                QDate fecha;
                while(query.next()){
                    fecha.fromString(query.value(3).toString(), "yyyy-MM-dd");
                    fechaNac.setDate(fecha);
                    data << Empleado(
                                query.value(0).toString(),
                                query.value(1).toString(),
                                query.value(2).toString(),
                                fechaNac,
                                query.value(4).toString(),
                                query.value(5).toString(),
                                query.value(6).toString(),
                                query.value(7).toString()
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


// Implementacion setters
void Empleado::setCodigo(QString Codigo)
{
    this->Codigo = Codigo;
}
void Empleado::setNombres(QString Nombres)
{
    this->Nombres = Nombres;
}
void Empleado::setApellidos(QString Apellidos)
{
    this->Apellidos = Apellidos;
}
void Empleado::setFechaNacimiento(QDateTime Fecha_Nacimiento)
{
    this->Fecha_Nacimiento = Fecha_Nacimiento;
}
void Empleado::setSexo(QString Sexo)
{
    this->sexo = Sexo;
}
void Empleado::setDNI(QString DNI)
{
    this->DNI = DNI;
}
void Empleado::setContrasenia(QString Contrasenia)
{
    this->Contrasenia = Contrasenia;
}
void Empleado::setTipo(QString Tipo)
{
    this->Tipo = Tipo;
}
// Implementacion getters
QString Empleado::getCodigo()
{
    return Codigo;
}
QString Empleado::getNombres()
{
    return Nombres;
}
QString Empleado::getApellidos()
{
    return Apellidos;
}
QDateTime Empleado::getFechaNacimiento()
{
    return Fecha_Nacimiento;
}
QString Empleado::getSexo()
{
    return sexo;
}
QString Empleado::getDNI()
{
    return DNI;
}
QString Empleado::getContrasenia()
{
    return Contrasenia;
}
QString Empleado::getTipo()
{
    return Tipo;
}
