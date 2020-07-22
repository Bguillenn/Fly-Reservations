#include "mainview.h"
#include "ui_mainview.h"
#include <QMessageBox>
#include <QTimer>
#include <QDateTime>

/* Importación de las vistas*/
#include <loginview.h>
#include "nuevareservauview.h"
#include "listarreservasview.h"
#include "buscarreservaview.h"
#include "cancelarreservaview.h"
#include "maestroempleadosview.h"
#include "maestrovuelosview.h"

MainView::MainView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(changeDateTime()));
    timer->start();
}

MainView::~MainView()
{
    delete ui;
}

void MainView::on_btnCerrarSesion_clicked()
{
   QMessageBox::StandardButton reply;
   reply = QMessageBox::question(this, "Cerrar Sesión", "¿Realmente deseas cerrar sesión?", QMessageBox::Yes|QMessageBox::No);

   if(reply == QMessageBox::Yes){
       LoginView *loginView = new LoginView();
       loginView->show();

       close();
   }
}

void MainView::on_btnNuevaReserva_clicked()
{
    NuevaReservaUView *nuevaReservaView = new NuevaReservaUView();
    nuevaReservaView->show();

    close();
}

void MainView::on_btnListarReservas_clicked()
{
    ListarReservasView *listarReservas = new ListarReservasView();
    listarReservas->show();

    close();
}

void MainView::changeDateTime(){
    QDateTime dateTime;
    dateTime = QDateTime::currentDateTime();
    QTime hora = dateTime.time();
    ui->lblTime->setText(hora.toString());
    QString fecha = dateTime.date().toString("dd/MM/yyyy");
    ui->lblDate->setText(fecha);
}

void MainView::on_btnBuscarReserva_clicked()
{
    BuscarReservaView *buscarReserva = new BuscarReservaView();
    buscarReserva->show();

    close();
}

void MainView::on_btnEmpleados_clicked()
{
    MaestroEmpleadosView *maestroEmpleados = new MaestroEmpleadosView();
    maestroEmpleados->show();

    close();
}

void MainView::on_btnVuelos_clicked()
{
    MaestroVuelosView *maestroVuelos = new MaestroVuelosView();
    maestroVuelos->show();

    close();
}

void MainView::on_btnCancelarReserva_clicked()
{
    CancelarReservaView *cancelarReserva = new CancelarReservaView();
    cancelarReserva->show();

    close();
}
