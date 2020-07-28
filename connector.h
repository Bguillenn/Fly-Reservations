#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <QtSql>
#include <QSqlQuery>

class Connector
{
public:
    QSqlDatabase initDataBase();
};

#endif // CONNECTOR_H
