#include "maestroempleadosview.h"
#include "ui_maestroempleadosview.h"

//Implementando las vistas necesarias
#include "mainview.h"

MaestroEmpleadosView::MaestroEmpleadosView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MaestroEmpleadosView)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
}

MaestroEmpleadosView::~MaestroEmpleadosView()
{
    delete ui;
}

void MaestroEmpleadosView::on_btnSalir_clicked()
{
    MainView *mainView = new MainView();
    mainView->show();

    close();
}
