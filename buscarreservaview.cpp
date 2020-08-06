#include "buscarreservaview.h"
#include "ui_buscarreservaview.h"

/*Importacion de las vistas*/
#include "mainview.h"
#include "detallesreservaview.h"
#include <QMessageBox>
#include "reservascontroller.h"

BuscarReservaView::BuscarReservaView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuscarReservaView)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    QStringList headers;
    //Configurando la table
    ui->tblResultados->setColumnCount(6);
    headers<<"Codigo R"<<"Codigo V"<<"Asientos"<<"Fecha R" << "DNI cliente" << "P Total";
    ui->tblResultados->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblResultados->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tblResultados->setHorizontalHeaderLabels(headers);
    ui->tblResultados->setColumnWidth(0,118);
    ui->tblResultados->setColumnWidth(1,118);
    ui->tblResultados->setColumnWidth(2,118);
    ui->tblResultados->setColumnWidth(3,118);
    ui->tblResultados->setColumnWidth(4,118);
    ui->tblResultados->setColumnWidth(5,118);
}

BuscarReservaView::~BuscarReservaView()
{
    delete ui;
}

void BuscarReservaView::on_btnSalir_clicked()
{
    MainView *mainView = new MainView();
    mainView->show();

    close();
}

void BuscarReservaView::on_btnMostrarInfo_clicked()
{
    if(ui->tblResultados->selectionModel()->hasSelection()){
        try {
            QModelIndex index = ui->tblResultados->selectionModel()->currentIndex();
            QVariant value=index.sibling(index.row(),0).data();
            Reserva reserva = Reserva::buscarPorCodigo(value.toString());
            DetallesReservaView *detallesView = new DetallesReservaView();
            detallesView->setReserva(reserva);
            detallesView->cargarData();
            detallesView->show();

            close();
        } catch (QString &e) {
            QMessageBox::warning(this, "Error",e);
        }
    }else
        QMessageBox::warning(this, "Error", "Debe seleccionar un registro de la tabla");

}


void BuscarReservaView::cargarResultados(int opc){
    if(!ui->txtQuery->text().isEmpty()){
        try {
            QVector<Reserva> data;
            ReservasController reservasController;
            if(opc == 0){
                data = reservasController.filtrarReservaPorDNI(ui->txtQuery->text());
            }else{
                QVector<Reserva> aux;
                aux << Reserva::buscarPorCodigo(ui->txtQuery->text());
                data = aux;
            }

            ui->tblResultados->setRowCount(0);
            for(int i=0; i<data.size(); i++){
                ui->tblResultados->insertRow(i);

                QTableWidgetItem *codigoR = new QTableWidgetItem();
                QTableWidgetItem *codigoV = new QTableWidgetItem();
                QTableWidgetItem *asientos = new QTableWidgetItem();
                QTableWidgetItem *fecha = new QTableWidgetItem();
                QTableWidgetItem *dni = new QTableWidgetItem();
                QTableWidgetItem *precioTotal = new QTableWidgetItem();

                codigoR->setText(data[i].getCodigo());
                codigoV->setText(data[i].getCodigoVuelo());
                asientos->setText(QString::number(data[i].getCantidadAsientos()) + " ASIENTO(s)");
                fecha->setText(data[i].getFechaReserva().toString("dd-MM-yyyy"));
                dni->setText(data[i].getDniCliente());
                precioTotal->setText("S/ "+QString::number(data[i].getPrecioTotal()));

                codigoR->setFlags(codigoR->flags() ^ Qt::ItemIsEditable);
                codigoV->setFlags(codigoV->flags() ^ Qt::ItemIsEditable);
                asientos->setFlags(asientos->flags() ^ Qt::ItemIsEditable);
                fecha->setFlags(fecha->flags() ^ Qt::ItemIsEditable);
                dni->setFlags(dni->flags() ^ Qt::ItemIsEditable);
                precioTotal->setFlags(precioTotal->flags() ^ Qt::ItemIsEditable);

                ui->tblResultados->setItem(i , 0, codigoR);
                ui->tblResultados->setItem(i , 1, codigoV);
                ui->tblResultados->setItem(i , 2, asientos);
                ui->tblResultados->setItem(i , 3, fecha);
                ui->tblResultados->setItem(i , 4, dni);
                ui->tblResultados->setItem(i , 5, precioTotal);
            }
        } catch (QString &e) {
            QMessageBox::warning(this, "Error", e);
        }

    }else
        QMessageBox::warning(this, "Error", "Debe llenar el cuadro de texto");
}

void BuscarReservaView::on_btnBuscarDni_clicked()
{
    cargarResultados(0);
}

void BuscarReservaView::on_btnBuscarCodigo_clicked()
{
    cargarResultados(1);
}
