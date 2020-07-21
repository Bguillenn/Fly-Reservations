#include "nuevareservauview.h"
#include "ui_nuevareservauview.h"
#include <QMessageBox>

/*Importacion de las vistas*/
#include "mainview.h"
#include "nuevareservadview.h"

NuevaReservaUView::NuevaReservaUView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NuevaReservaUView)
{
    ui->setupUi(this);
}

NuevaReservaUView::~NuevaReservaUView()
{
    delete ui;
}

void NuevaReservaUView::on_btnCancelar_clicked()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Cancelar Nueva Reserva", "¿Realmente deseas cancelar la operación?", QMessageBox::Yes|QMessageBox::No);

    if(reply == QMessageBox::Yes){
        MainView *mainView = new MainView();
        mainView->show();

        close();
    }
}

void NuevaReservaUView::on_btnSiguiente_clicked()
{
    NuevaReservaDView *siguientePaso = new NuevaReservaDView();
    siguientePaso->show();

    close();
}
