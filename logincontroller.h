#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include "empleado.h"

class LoginController
{
public:
    static Empleado *userLogged;
    static bool loginEmpleado(QString idUser, QString contrasenia);
    static Empleado* getUserLogged();
    static bool closeSession();
};

#endif // LOGINCONTROLLER_H
