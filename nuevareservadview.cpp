#include "nuevareservadview.h"
#include "ui_nuevareservadview.h"
#include <QMessageBox>
#include "origen.h"
#include "destino.h"
#include "reservascontroller.h"
#include "logincontroller.h"
#include "vueloscontroller.h"


/*Importacion de las vistas*/
#include "mainview.h"
#include "nuevareservauview.h"

NuevaReservaDView::NuevaReservaDView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NuevaReservaDView)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
}

NuevaReservaDView::~NuevaReservaDView()
{
    delete ui;
}

void NuevaReservaDView::setVuelo(Vuelo vuelo){
    this->vuelo = vuelo;
}

void NuevaReservaDView::setAsientos(int asientos){
    this->asientos = asientos;
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

void NuevaReservaDView::cargarData(){
    try {
        Origen origen = Origen::buscarPorCodigo(this->vuelo.getOrigenCodigo());
        Destino destino = Destino::buscarPorCodigo(this->vuelo.getDestinoCodigo());

        ui->lblCodigoVuelo->setText(this->vuelo.getCodigo());
        ui->lblOrigen->setText(origen.getNombreCiudad()+" - "+origen.getNombrePais());
        ui->lblDestino->setText(destino.getNombreCiudad()+" - "+destino.getNombrePais());
        ui->lblCapacidad->setText(QString::number(vuelo.getCapacidad())+" asientos");
        ui->lblFechaPartida->setText(this->vuelo.getFechaPartida().toString("dd-MM-yyyy hh:ss"));
        ui->lblAsientosReservados->setText(QString::number(this->asientos)+" asiento(s)");
        ui->lblPrecioAsiento->setText("S/ "+QString::number(this->vuelo.getPrecioAsiento()));

        ReservasController reservasController;
        float precio_total = reservasController.calcularPrecioTotal(this->vuelo.getCodigo(), this->asientos);
        ui->lblPrecioTotal->setText("S/ "+QString::number(precio_total));
    } catch (QException &e) {
        QMessageBox::warning(this, "Error inesperado", e.what());
    } catch (QString &e){
        QMessageBox::warning(this, "Error", e);
    }
}

void NuevaReservaDView::on_btnConfirmar_clicked()
{
    if(!ui->txtDniCliente->text().isEmpty()){
        if(ui->txtDniCliente->text().length() == 8){
            try {

                QString(ui->txtDniCliente->text()).toInt(); //Validamos que sean numeros si manda error no es un numero

                if(this->asientos <=  vuelo.getAsientosDisponibles()){
                    ReservasController reservasController;
                    VuelosController vuelosController;
                    QString codigoReserva = reservasController.obtenerCodigoReservaNuevo();
                    Reserva reserva(
                                    codigoReserva,
                                    this->vuelo.getCodigo(),
                                    LoginController::getUserLogged()->getCodigo(),
                                    ui->txtDniCliente->text(),
                                    this->asientos,
                                    reservasController.calcularPrecioTotal(this->vuelo.getCodigo(), this->asientos),
                                    QDateTime::currentDateTime()
                                );
                    Reserva::guardar(reserva);
                    vuelosController.reducirAsientosDisponibles(this->vuelo.getCodigo(), this->asientos);
                    QMessageBox::information(this, "Informacion", "Reserva realizada con exito con codigo: "+codigoReserva);

                    MainView *mainView = new MainView();
                    mainView->show();

                    close();
                }else
                    throw QString("Error al asignar los asientos, no hay suficientes");

            } catch (QException &e) {
                QMessageBox::warning(this, "Error", e.what());
            } catch (QString &e){
                QMessageBox::warning(this, "Error", e);
            }
        }else{
            QMessageBox::warning(this, "Error", "El campo DNI solo debe ser de 8 caracteres");
            ui->txtDniCliente->setFocus();
        }
    }else{
        QMessageBox::warning(this, "Error", "Debe llenar el campo DNI del cliente");
        ui->txtDniCliente->setFocus();
    }
}
