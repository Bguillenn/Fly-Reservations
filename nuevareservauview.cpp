#include "nuevareservauview.h"
#include "ui_nuevareservauview.h"
#include <QMessageBox>
#include "vueloscontroller.h"
#include "origen.h"
#include "destino.h"

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
    ui->tblVuelos->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblVuelos->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tblVuelos->setColumnWidth(0,70);
    ui->tblVuelos->setColumnWidth(1,170);
    ui->tblVuelos->setColumnWidth(2,170);
    ui->tblVuelos->setColumnWidth(3,170);
    ui->tblVuelos->setColumnWidth(4,120);
    llenarTabla();
    llenarOrigen();
    llenarDestino();

    ui->txtFecha->setDateTime(QDateTime::currentDateTime());
}

void NuevaReservaUView::llenarTabla(){
    try {
        QVector<Vuelo> data = Vuelo::todos();
        ui->tblVuelos->setRowCount(0);
        Origen *origenItem = new Origen();
        Destino *destinoItem = new Destino();

        for(int i=0; i<data.size(); i++){
            ui->tblVuelos->insertRow(i);
            *origenItem = Origen::buscarPorCodigo(data[i].getOrigenCodigo());
            *destinoItem = Destino::buscarPorCodigo(data[i].getDestinoCodigo());

            QTableWidgetItem *codigo = new QTableWidgetItem();
            QTableWidgetItem *origen = new QTableWidgetItem();
            QTableWidgetItem *destino = new QTableWidgetItem();
            QTableWidgetItem *fecha = new QTableWidgetItem();
            QTableWidgetItem *asientos = new QTableWidgetItem();

            codigo->setText(data[i].getCodigo());
            origen->setText(origenItem->getNombreCiudad()+"-"+origenItem->getNombrePais());
            destino->setText(destinoItem->getNombreCiudad()+"-"+destinoItem->getNombrePais());
            fecha->setText(data[i].getFechaPartida().toString("dd-MM-yyyy hh:mm"));
            asientos->setText(QString::number(data[i].getAsientosDisponibles()));

            codigo->setFlags(codigo->flags() ^ Qt::ItemIsEditable);
            origen->setFlags(codigo->flags() ^ Qt::ItemIsEditable);
            destino->setFlags(codigo->flags() ^ Qt::ItemIsEditable);
            fecha->setFlags(codigo->flags() ^ Qt::ItemIsEditable);
            asientos->setFlags(codigo->flags() ^ Qt::ItemIsEditable);

            ui->tblVuelos->setItem(i, 0, codigo);
            ui->tblVuelos->setItem(i, 1, origen);
            ui->tblVuelos->setItem(i, 2, destino);
            ui->tblVuelos->setItem(i, 3, fecha);
            ui->tblVuelos->setItem(i, 4, asientos);
        }
    } catch (QString &e) {
        QMessageBox::warning(this, "Error inesperado", e);
    }
}

void NuevaReservaUView::llenarTablaConFiltro(QString codOrigen, QString codDestino, int asientos, QDateTime fecha){
    try {
        VuelosController vuelosController;
        QVector<Vuelo> data = vuelosController.filtrarVuelos(codOrigen, codDestino, asientos, fecha);

        ui->tblVuelos->setRowCount(0);
        Origen *origenItem = new Origen();
        Destino *destinoItem = new Destino();

        for(int i=0; i<data.size(); i++){
            ui->tblVuelos->insertRow(i);
            *origenItem = Origen::buscarPorCodigo(data[i].getOrigenCodigo());
            *destinoItem = Destino::buscarPorCodigo(data[i].getDestinoCodigo());

            QTableWidgetItem *codigo = new QTableWidgetItem();
            QTableWidgetItem *origen = new QTableWidgetItem();
            QTableWidgetItem *destino = new QTableWidgetItem();
            QTableWidgetItem *fecha = new QTableWidgetItem();
            QTableWidgetItem *asientos = new QTableWidgetItem();

            codigo->setText(data[i].getCodigo());
            origen->setText(origenItem->getNombreCiudad()+"-"+origenItem->getNombrePais());
            destino->setText(destinoItem->getNombreCiudad()+"-"+destinoItem->getNombrePais());
            fecha->setText(data[i].getFechaPartida().toString("dd-MM-yyyy hh:mm"));
            asientos->setText(QString::number(data[i].getAsientosDisponibles()));

            codigo->setFlags(codigo->flags() ^ Qt::ItemIsEditable);
            origen->setFlags(codigo->flags() ^ Qt::ItemIsEditable);
            destino->setFlags(codigo->flags() ^ Qt::ItemIsEditable);
            fecha->setFlags(codigo->flags() ^ Qt::ItemIsEditable);
            asientos->setFlags(codigo->flags() ^ Qt::ItemIsEditable);

            ui->tblVuelos->setItem(i, 0, codigo);
            ui->tblVuelos->setItem(i, 1, origen);
            ui->tblVuelos->setItem(i, 2, destino);
            ui->tblVuelos->setItem(i, 3, fecha);
            ui->tblVuelos->setItem(i, 4, asientos);
        }
    } catch (QString &e) {
        QMessageBox::warning(this, "Error", e);
    }
}

void NuevaReservaUView::llenarOrigen(){
    try {
        QVector<Origen> data = Origen::todos();
        for(int i=0; i<data.size(); i++)
            ui->cbxOrigen->addItem(data[i].getCodigo());
    } catch (QString &e) {
        QMessageBox::warning(this, "Error inesperado", e);
    }
}

void NuevaReservaUView::llenarDestino(){
    try {
        QVector<Destino> data = Destino::todos();
        for(int i=0; i<data.size(); i++)
            ui->cbxDestino->addItem(data[i].getCodigo());
    } catch (QString &e) {
        QMessageBox::warning(this, "Error inesperado", e);
    }
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
    if(ui->tblVuelos->selectionModel()->hasSelection()){
        try {
            QModelIndex index = ui->tblVuelos->selectionModel()->currentIndex();
            QVariant value=index.sibling(index.row(),0).data();
            Vuelo vuelo = Vuelo::buscarPorCodigo(value.toString());
            NuevaReservaDView *siguientePaso = new NuevaReservaDView();
            siguientePaso->setVuelo(vuelo);
            siguientePaso->setAsientos(ui->txtPasajeros->value());
            siguientePaso->cargarData();
            siguientePaso->show();

            close();
        } catch (QString &e) {
            QMessageBox::warning(this, "Error",e);
        }
    }else
        QMessageBox::warning(this, "Error", "Debe seleccionar un registro de la tabla");

}

void NuevaReservaUView::on_btnBuscar_clicked()
{
    QString origenCod = ui->cbxOrigen->currentText();
    QString destinoCod = ui->cbxDestino->currentText();
    QDate fecha = ui->txtFecha->date();
    int asientos = ui->txtPasajeros->value();

    if(QDate::currentDate() <= fecha){
        if(asientos > 10 || asientos < 1)
            QMessageBox::warning(this, "Error", "Los pasajeros no deben ser mayor a 10 ni menores a 1");
        else
            llenarTablaConFiltro(origenCod, destinoCod, asientos, QDateTime(fecha));
    }else
        QMessageBox::warning(this, "Error en la fecha", "La fecha debe ser mayor a la actual");
}
