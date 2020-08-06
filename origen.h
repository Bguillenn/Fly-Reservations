#ifndef ORIGEN_H
#define ORIGEN_H


#include <QString>
#include <QVector>
#include <QFile>
#include <connector.h>
#include <QSqlDatabase>
#include <QSqlQuery>
class Origen
{
QString codigo;
QString Nombre_Origen;
QString Nombre_Ciudad;
QString Nombre_Pais;

public:
    Origen();
    static bool guardar(Origen temp);
    static bool modificar(Origen temp );
    static bool eliminar(QString codigo);
    static Origen buscarPorCodigo(QString cod);
    static QVector<Origen> todos();
    Origen(QString codigo, QString nombre_Origen,QString nombre_ciudad,QString nombre_pais);
    void setCodigo(QString codigo);
    void setNombreOrigen(QString Nombre_Origen);
    void setNombreCiudad(QString Nombre_ciudad);
    void setNombrePais(QString Nombre_pais);
    QString getCodigo();
    QString getNombreOrigen();
    QString getNombreCiudad();
    QString getNombrePais();

};


#endif // ORIGEN_H
