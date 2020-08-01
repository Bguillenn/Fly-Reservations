#ifndef DESTINO_H
#define DESTINO_H
#include <QString>
#include <QVector>
#include <QFile>
#include <connector.h>
#include <QSqlDatabase>
#include <QSqlQuery>
class destino
{
    QString codigo;
    QString Nombre_aeropuerto;
    QString Nombre_Ciudad;
    QString Nombre_Pais;

    public:
        destino();
        bool guardar(destino temp);
        bool modificar(destino temp );
        bool eliminar(QString codigo);
        destino buscarPorCodigo(QString cod);
        QVector<destino> todos();
        destino(QString codigo, QString nombre_aeropuerto,QString nombre_ciudad,QString nombre_pais);
        void setCodigo(QString codigo);
        void setNombreAeropuerto(QString Nombre_aeropuerto);
        void setNombreCiudad(QString Nombre_ciudad);
        void setNombrePais(QString Nombre_pais);
        QString getCodigo();
        QString getNombreAeropuerto();
        QString getNombreCiudad();
        QString getNombrePais();
};

#endif // DESTINO_H
