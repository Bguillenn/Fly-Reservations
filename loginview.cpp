#include "loginview.h"
#include "ui_loginview.h"
#include <QPixmap>
#include <QMessageBox>

LoginView::LoginView(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::LoginView)
{
    ui->setupUi(this);
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
}
