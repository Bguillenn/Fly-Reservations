#include "buscarreservaview.h"
#include "ui_buscarreservaview.h"

/*Importacion de las vistas*/
#include "mainview.h"

BuscarReservaView::BuscarReservaView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BuscarReservaView)
{
    ui->setupUi(this);
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
