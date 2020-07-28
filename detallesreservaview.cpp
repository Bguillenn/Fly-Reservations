#include "detallesreservaview.h"
#include "ui_detallesreservaview.h"

//Incluyendo las vistas necesarias
#include "buscarreservaview.h"

DetallesReservaView::DetallesReservaView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DetallesReservaView)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
}

DetallesReservaView::~DetallesReservaView()
{
    delete ui;
}

void DetallesReservaView::on_btnSalir_clicked()
{
    BuscarReservaView *buscarReserva = new BuscarReservaView();
    buscarReserva->show();

    close();
}
