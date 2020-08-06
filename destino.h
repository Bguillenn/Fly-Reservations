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
        static bool guardar(Destino temp);
        static bool modificar(Destino temp );
        static bool eliminar(QString codigo);
        static Destino buscarPorCodigo(QString cod);
        static QVector<Destino> todos();
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
