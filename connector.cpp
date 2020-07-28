#include "connector.h"
#include <QMessageBox>

QSqlDatabase Connector::initDataBase(){
    try {
        //Inicializamos la base de datos como SQLite y definimos la
        //ruta donde se encuentra nuestro archivo de base de datos
        if(!QSqlDatabase::isDriverAvailable("QSQLITE")){
            QMessageBox::warning(nullptr, "Error en el driver", "Error en el driver de la base de datos");
            throw "Error en el driver";
        }
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
        //QString  dir = QDir::homePath() + "/DB/database.db";
        QString  dir = "./database.db";
        db.setDatabaseName(dir);
        return db;
    } catch (QException &e) {
        throw e;
    }
}
