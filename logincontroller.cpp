#include "logincontroller.h"
#include <QMessageBox>

Empleado* LoginController::userLogged;

bool LoginController::loginEmpleado(QString idUser, QString contrasenia){
    try {
        Empleado tmp = Empleado::buscarPorCodigo(idUser);
        if(tmp.getContrasenia().compare(contrasenia) == 0)
            LoginController::userLogged = new Empleado(
                            tmp.getCodigo(),
                            tmp.getNombres(),
                            tmp.getApellidos(),
                            tmp.getFechaNacimiento(),
                            tmp.getSexo(),
                            tmp.getDNI(),
                            tmp.getContrasenia(),
                            tmp.getTipo()
                        );
        else
            throw QString("La contraseña no es la correcta");
    } catch (QString &e) {
        throw e;
    }
}

Empleado* LoginController::getUserLogged(){
    return LoginController::userLogged;
}

bool LoginController::closeSession(){
    LoginController::userLogged = nullptr;
}
