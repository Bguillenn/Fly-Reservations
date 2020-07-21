#include "nuevareservadview.h"
#include "ui_nuevareservadview.h"
#include <QMessageBox>

/*Importacion de las vistas*/
#include "mainview.h"
#include "nuevareservauview.h"

NuevaReservaDView::NuevaReservaDView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NuevaReservaDView)
{
    ui->setupUi(this);
}

NuevaReservaDView::~NuevaReservaDView()
{
    delete ui;
}

void NuevaReservaDView::on_btnCancelar_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Cancelar Nueva Reserva", "¿Realmente deseas cancelar la operación?", QMessageBox::Yes|QMessageBox::No);

    if(reply == QMessageBox::Yes){
        MainView *mainView = new MainView();
        mainView->show();

        close();
    }
}

void NuevaReservaDView::on_btnAnterior_clicked()
{
    NuevaReservaUView *anteriorPaso = new NuevaReservaUView();
    anteriorPaso->show();

    close();
}
