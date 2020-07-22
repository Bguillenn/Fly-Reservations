#include "buscarreservaview.h"
#include "ui_buscarreservaview.h"

/*Importacion de las vistas*/
#include "mainview.h"
#include "detallesreservaview.h"

BuscarReservaView::BuscarReservaView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuscarReservaView)
{
    ui->setupUi(this);
    QStringList headers;
    //Configurando la table
    ui->tblResultados->setColumnCount(6);
    headers<<"Codigo R"<<"Codigo V"<<"Asientos"<<"Fecha R" << "DNI cliente" << "P Total";
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
    DetallesReservaView *detallesReserva = new DetallesReservaView();
    detallesReserva->show();

    close();

}
