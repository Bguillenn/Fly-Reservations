#include "loginview.h"
#include "ui_loginview.h"
#include <QPixmap>
#include <QMessageBox>
#include <mainview.h>
#include "logincontroller.h"

LoginView::LoginView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginView)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);
}

LoginView::~LoginView()
{
    delete ui;
}


void LoginView::on_btnSalir_clicked()
{
    this->close();
}

void LoginView::on_btnEntrar_clicked()
{
    QString txtCodigo = ui->txtCodigo->text();
    QString txtContra = ui->txtContra->text();

    if(txtCodigo.isEmpty() || txtContra.isEmpty()){
        QMessageBox::about(this,"Faltan datos", "Debes completar todos los campos");
        return;
    }

    try {
        LoginController::loginEmpleado(txtCodigo, txtContra);
        MainView *mainView = new MainView();
        mainView->show();

        close();
    } catch (QString &e) {
        QMessageBox::warning(this, "Error", e);
        ui->txtCodigo->setFocus();
    }
}
