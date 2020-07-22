#include "maestrovuelosview.h"
#include "ui_maestrovuelosview.h"

//Incluyendo las vistas
#include "mainview.h"

MaestroVuelosView::MaestroVuelosView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MaestroVuelosView)
{
    ui->setupUi(this);
}

MaestroVuelosView::~MaestroVuelosView()
{
    delete ui;
}

void MaestroVuelosView::on_btnSalir_clicked()
{
    MainView *mainView = new MainView();
    mainView->show();

    close();
}
