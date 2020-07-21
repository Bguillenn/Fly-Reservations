#include "listarreservasview.h"
#include "ui_listarreservasview.h"

/*Importando las vistas*/
#include "mainview.h"

ListarReservasView::ListarReservasView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ListarReservasView)
{
    ui->setupUi(this);
    /*Configurando la tabla*/
    QStringList headers;
    ui->tblReservas->setColumnCount(6);
    headers<<"Codigo R"<<"Codigo V"<<"Asientos"<<"Fecha R" << "DNI cliente" << "P Total";
    ui->tblReservas->setHorizontalHeaderLabels(headers);
    ui->tblReservas->setColumnWidth(0,118);
    ui->tblReservas->setColumnWidth(1,118);
    ui->tblReservas->setColumnWidth(2,118);
    ui->tblReservas->setColumnWidth(3,118);
    ui->tblReservas->setColumnWidth(4,118);
    ui->tblReservas->setColumnWidth(5,118);

    actualizarLabelResultados();
}

ListarReservasView::~ListarReservasView()
{
    delete ui;
}

void ListarReservasView::actualizarLabelResultados(){
    int res_cant = ui->tblReservas->rowCount();
    ui->lblResultados->setText(QString("Total de resultados: ").append(res_cant));
}

void ListarReservasView::on_btnSalir_clicked()
{
    MainView *mainView = new MainView();
    mainView->show();

    close();
}
