#ifndef AEROPUERTO_H
#define AEROPUERTO_H
#include <QString>
#include <QVector>
#include <QFile>
#include <connector.h>
#include <QSqlDatabase>
#include <QSqlQuery>
class aeropuerto
{
QString codigo;
QString Nombre_aeropuerto;
QString Nombre_Ciudad;
QString Nombre_Pais;

public:
    aeropuerto();
    bool guardar(aeropuerto temp);
    bool modificar(aeropuerto temp );
    bool eliminar(QString codigo);
    aeropuerto buscarPorCodigo(QString cod);
    QVector<aeropuerto> todos();
    aeropuerto(QString codigo, QString nombre_aeropuerto,QString nombre_ciudad,QString nombre_pais);
    void setCodigo(QString codigo);
    void setNombreAeropuerto(QString Nombre_aeropuerto);
    void setNombreCiudad(QString Nombre_ciudad);
    void setNombrePais(QString Nombre_pais);
    QString getCodigo();
    QString getNombreAeropuerto();
    QString getNombreCiudad();
    QString getNombrePais();

};

#endif // AEROPUERTO_H
