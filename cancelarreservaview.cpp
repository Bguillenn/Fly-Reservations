#include "cancelarreservaview.h"
#include "ui_cancelarreservaview.h"
#include <QMessageBox>
#include "reserva.h"
#include "vuelo.h"
#include "origen.h"
#include "destino.h"
#include "vueloscontroller.h"
#include "reservascontroller.h"

//Importando las vistas necesarias
#include "mainview.h"

CancelarReservaView::CancelarReservaView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CancelarReservaView)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
}

CancelarReservaView::~CancelarReservaView()
{
    delete ui;
}

void CancelarReservaView::on_btnCancelar_clicked()
{
    MainView *mainView = new MainView();
    mainView->show();

    close();
}

void CancelarReservaView::on_btnBuscar_clicked()
{
    if(!ui->txtCodigo->text().isEmpty()){
        try {
            Reserva reserva = Reserva::buscarPorCodigo(ui->txtCodigo->text().toUpper());
            VuelosController vuelosController;

            if(!vuelosController.realizado(reserva.getCodigoVuelo())){
                Vuelo vuelo = Vuelo::buscarPorCodigo(reserva.getCodigoVuelo());
                Origen origen = Origen::buscarPorCodigo(vuelo.getOrigenCodigo());
                Destino destino = Destino::buscarPorCodigo(vuelo.getDestinoCodigo());
                ui->lblCodigoReserva->setText(reserva.getCodigo());
                ui->lblFechaReserva->setText(reserva.getFechaReserva().toString("dd-MM-yyyy"));
                ui->lblPrecioTotal->setText("S/ "+QString::number(reserva.getPrecioTotal()));
                ui->lblCodigoVuelo->setText(reserva.getCodigoVuelo());
                ui->lblFechaVuelo->setText(vuelo.getFechaPartida().toString("dd-MM-yyyy hh:mm"));
                ui->lblAsientos->setText(QString::number(reserva.getCantidadAsientos())+ " ASIENTO(S)");
                ui->lblDestino->setText(destino.getNombreCiudad()+" - "+destino.getNombrePais());
                ui->lblOrigen->setText(origen.getNombreCiudad()+" - "+origen.getNombrePais());

                ui->btnConfirmar->setEnabled(true);
            }else
                throw QString("Esta vuelo de esta reserva ya fue efectuado, por lo que no se puede cancelar");
        } catch (QString &e) {
            QMessageBox::warning(this, "Error", e);
            ui->lblOrigen->setText("");
            ui->lblDestino->setText("");
            ui->lblAsientos->setText("");
            ui->lblFechaVuelo->setText("");
            ui->lblCodigoVuelo->setText("");
            ui->lblPrecioTotal->setText("");
            ui->lblFechaReserva->setText("");
            ui->lblCodigoReserva->setText("");

            ui->btnConfirmar->setDisabled(true);
        }
    }else
        QMessageBox::warning(this, "Error", "Debe ingresar un codigo de reserva");
}

void CancelarReservaView::on_btnConfirmar_clicked()
{
    int opc = QMessageBox::question(this, "Confirmar accion", "¿Realmente deseas cancelar la reserva?");
    if(opc == QMessageBox::Yes){
        try {
            VuelosController vuelosController;
            Reserva reserva = Reserva::buscarPorCodigo(ui->lblCodigoReserva->text());

            vuelosController.ampliarAsientosDisponibles(reserva.getCodigoVuelo(), reserva.getCantidadAsientos());

            Reserva::eliminar(reserva.getCodigo());

            QMessageBox::information(this, "Informacion", "Reserva cancelada con exito");

            MainView *mainView = new MainView();
            mainView->show();

            close();

        } catch (QString &e) {
            QMessageBox::warning(this, "Error", e );
        }
    }
}
