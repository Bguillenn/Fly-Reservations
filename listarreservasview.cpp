#include "listarreservasview.h"
#include "ui_listarreservasview.h"
#include <QMessageBox>

/*Importando las vistas*/
#include "mainview.h"
#include "reserva.h"
#include "reservascontroller.h"
#include "logincontroller.h"

ListarReservasView::ListarReservasView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListarReservasView)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    /*Configurando la tabla*/
    QStringList headers;
    ui->tblReservas->setColumnCount(6);
    headers<<"Codigo R"<<"Codigo V"<<"Asientos"<<"Fecha R" << "DNI cliente" << "P Total";
    ui->tblReservas->setHorizontalHeaderLabels(headers);
    ui->tblReservas->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblReservas->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tblReservas->setColumnWidth(0,118);
    ui->tblReservas->setColumnWidth(1,118);
    ui->tblReservas->setColumnWidth(2,118);
    ui->tblReservas->setColumnWidth(3,118);
    ui->tblReservas->setColumnWidth(4,118);
    ui->tblReservas->setColumnWidth(5,118);

    cargarTabla();
}

ListarReservasView::~ListarReservasView()
{
    delete ui;
}

void ListarReservasView::actualizarLabelResultados(){
    int res_cant = ui->tblReservas->rowCount();
    ui->lblResultados->setText("Total de resultados: "+QString::number(res_cant));
}


void ListarReservasView::cargarTabla(){
    try {
        ReservasController reservasController;
        QVector<Reserva> data;
        if(ui->chkTodas->isChecked())
            data = reservasController.filtrarReservasPorVendedor(LoginController::getUserLogged()->getCodigo());
        else
            data = Reserva::todos();

        ui->tblReservas->setRowCount(0);

        for(int i=0; i<data.size(); i++){
            ui->tblReservas->insertRow(i);

            QTableWidgetItem *codigoR = new QTableWidgetItem();
            QTableWidgetItem *codigoV = new QTableWidgetItem();
            QTableWidgetItem *asientos = new QTableWidgetItem();
            QTableWidgetItem *fecha = new QTableWidgetItem();
            QTableWidgetItem *dni = new QTableWidgetItem();
            QTableWidgetItem *total = new QTableWidgetItem();

            codigoR->setText(data[i].getCodigo());
            codigoV->setText(data[i].getCodigoVuelo());
            asientos->setText(QString::number(data[i].getCantidadAsientos()));
            fecha->setText(data[i].getFechaReserva().toString("dd-MM-yyyy hh:mm"));
            dni->setText(data[i].getDniCliente());
            total->setText(QString::number(data[i].getPrecioTotal()));

            codigoR->setFlags(codigoR->flags() ^ Qt::ItemIsEditable);
            codigoV->setFlags(codigoV->flags() ^ Qt::ItemIsEditable);
            asientos->setFlags(asientos->flags() ^ Qt::ItemIsEditable);
            fecha->setFlags(fecha->flags() ^ Qt::ItemIsEditable);
            dni->setFlags(dni->flags() ^ Qt::ItemIsEditable);
            total->setFlags(total->flags() ^ Qt::ItemIsEditable);

            ui->tblReservas->setItem(i, 0, codigoR);
            ui->tblReservas->setItem(i, 1, codigoV);
            ui->tblReservas->setItem(i, 2, asientos);
            ui->tblReservas->setItem(i, 3, fecha);
            ui->tblReservas->setItem(i, 4, dni);
            ui->tblReservas->setItem(i, 5, total);
            this->actualizarLabelResultados();
        }
    } catch (QString &e) {
        QMessageBox::warning(this, "Error inesperado", e);
    }
}

void ListarReservasView::on_btnSalir_clicked()
{
    MainView *mainView = new MainView();
    mainView->show();

    close();
}

void ListarReservasView::on_chkTodas_stateChanged(int arg1)
{
    cargarTabla();
}
