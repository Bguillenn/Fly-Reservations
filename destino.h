#ifndef DESTINO_H
#define DESTINO_H
#include <QString>
#include <QVector>
#include <QFile>
#include <connector.h>
#include <QSqlDatabase>
#include <QSqlQuery>
class Destino
{
    QString codigo;
    QString Nombre_Destino;
    QString Nombre_Ciudad;
    QString Nombre_Pais;

    public:
        Destino();
        bool guardar(Destino temp);
        bool modificar(Destino temp );
        bool eliminar(QString codigo);
        Destino buscarPorCodigo(QString cod);
        QVector<Destino> todos();
        Destino(QString codigo, QString nombre_Destino,QString nombre_ciudad,QString nombre_pais);
        void setCodigo(QString codigo);
        void setNombreDestino(QString Nombre_Destino);
        void setNombreCiudad(QString Nombre_ciudad);
        void setNombrePais(QString Nombre_pais);
        QString getCodigo();
        QString getNombreDestino();
        QString getNombreCiudad();
        QString getNombrePais();
};

#endif // DESTINO_H
