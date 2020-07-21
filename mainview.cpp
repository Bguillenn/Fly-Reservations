#include "mainview.h"
#include "ui_mainview.h"
#include <QMessageBox>

/* Importación de las vistas*/
#include <loginview.h>
#include "nuevareservauview.h"

MainView::MainView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainView)
{
    ui->setupUi(this);
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
