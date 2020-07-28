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
    this->setWindowFlag(Qt::FramelessWindowHint);
    /*Configurando el JTable*/
    QStringList headers;
    ui->tblVuelos->setColumnCount(5);
    headers <<"Codigo"<<"Origen"<<"Destino"<<"Fecha y hora de partida"<<"Asientos disponibles";
    ui->tblVuelos->setHorizontalHeaderLabels(headers);
    ui->tblVuelos->setColumnWidth(0,70);
    ui->tblVuelos->setColumnWidth(1,170);
    ui->tblVuelos->setColumnWidth(2,170);
    ui->tblVuelos->setColumnWidth(3,170);
    ui->tblVuelos->setColumnWidth(4,120);
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
