#ifndef EMPLEADO_H
#define EMPLEADO_H


#include <QDateTime>
#include <QString>
#include <QVector>
//REQUERIDO PARA LA BASE DE DATOS
#include <connector.h>
#include <QSqlDatabase>
#include <QSqlQuery>

class Empleado
{
private:
        QString Codigo;
        QString Nombres;
        QString Apellidos;
        QDateTime Fecha_Nacimiento;
        QString sexo;
        QString DNI;
        QString Contrasenia;
        QString Tipo;
    public:
        static bool guardar(Empleado);
        static bool modificar(Empleado);
        static bool eliminar(QString);
        static Empleado buscarPorCodigo(QString);
        static QVector<Empleado> todos();
        Empleado();
        Empleado(QString Codigo, QString Nombres, QString Apellidos, QDateTime Fecha_Nacimiento, QString Sexo, QString DNI, QString Contrasenia, QString Tipo);
        void setCodigo(QString);
        void setNombres(QString);
        void setApellidos(QString);
        void setFechaNacimiento(QDateTime);
        void setSexo(QString);
        void setDNI(QString);
        void setContrasenia(QString);
        void setTipo(QString);
        QString getCodigo();
        QString getNombres();
        QString getApellidos();
        QDateTime getFechaNacimiento();
        QString getSexo();
        QString getDNI();
        QString getContrasenia();
        QString getTipo();
};

#endif // EMPLEADO_H
