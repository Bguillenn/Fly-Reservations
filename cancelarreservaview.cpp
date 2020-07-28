#include "cancelarreservaview.h"
#include "ui_cancelarreservaview.h"

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
