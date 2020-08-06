#include "detallesreservaview.h"
#include "ui_detallesreservaview.h"
#include "vuelo.h"
#include "origen.h"
#include "destino.h"
#include "vueloscontroller.h"

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

void DetallesReservaView::setReserva(Reserva reserva){
    this->reserva = reserva;
}

void DetallesReservaView::cargarData(){
    Vuelo vuelo = Vuelo::buscarPorCodigo(this->reserva.getCodigoVuelo());
    Origen origen = Origen::buscarPorCodigo(vuelo.getOrigenCodigo());
    Destino destino = Destino::buscarPorCodigo(vuelo.getDestinoCodigo());
    VuelosController vuelosController;

    ui->lblOrigen->setText(origen.getNombreCiudad()+" - "+origen.getNombrePais());
    ui->lblDestino->setText(destino.getNombreCiudad()+" - "+destino.getNombrePais());
    ui->lblAsientos->setText(QString::number(this->reserva.getCantidadAsientos())+ " ASIENTO(s)");
    if(vuelosController.realizado(vuelo.getCodigo()))
        ui->lblRealizado->setText("REALIZADO");
    else
        ui->lblRealizado->setText("SIN REALIZAR");

    ui->lblFechaVuelo->setText(vuelo.getFechaPartida().toString("dd-MM-yyyy hh:mm"));
    ui->lblCodigoVuelo->setText(vuelo.getCodigo());
    ui->lblPrecioTotal->setText("S/ "+QString::number(this->reserva.getPrecioTotal()));
    ui->lblFechaReserva->setText(this->reserva.getFechaReserva().toString("dd-MM-yyyy"));
    ui->lblCodigoReserva->setText(this->reserva.getCodigo());

}
