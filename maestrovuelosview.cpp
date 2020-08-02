#include "maestrovuelosview.h"
#include "ui_maestrovuelosview.h"

//Incluyendo las vistas
#include "mainview.h"

MaestroVuelosView::MaestroVuelosView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MaestroVuelosView)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    QStringList headers;
    ui->tblVuelos->setColumnCount(7);
    ui->tblVuelos->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblVuelos->setSelectionMode(QAbstractItemView::SingleSelection);
    headers<<"Código"<<"Origen"<<"Destino"<<"Capacidad"<<"Fecha de Vuelo"<<"Asientos Disponibles"<<"Precio";
    ui->tblVuelos->setHorizontalHeaderLabels(headers);
    ui->tblVuelos->setColumnWidth(0,60);
    ui->tblVuelos->setColumnWidth(1,60);
    ui->tblVuelos->setColumnWidth(2,75);
    ui->tblVuelos->setColumnWidth(3,85);
    ui->tblVuelos->setColumnWidth(4,200);
    ui->tblVuelos->setColumnWidth(5,200);
    ui->tblVuelos->setColumnWidth(6,60);
    cargarTabla();
    llenarOrigen();
    llenarDestinos();

}
void MaestroVuelosView::llenarOrigen(){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
       if(db.open()){
           QString sql = "SELECT * FROM origen";
           QSqlQuery query;
           query.prepare(sql);

           if(query.exec()){

               while (query.next()) {
                   ui->cbxOrigen->addItem(query.value(0).toByteArray().constData());
               }

           }else{
               db.close();
               throw QString("Error, no se pudo abrir la BD");
           }
       }else{
           db.close();
             throw QString("Error, no se pudo abrir la BD");
       }
    } catch (QString &e) {
        throw e;
    }
}
void MaestroVuelosView::llenarDestinos(){
    Connector con;
    try {
        QSqlDatabase db = con.initDataBase();
       if(db.open()){
           QString sql = "SELECT * FROM destino";
           QSqlQuery query;
           query.prepare(sql);

           if(query.exec()){

               while (query.next()) {
                   ui->cbxDestino->addItem(query.value(0).toByteArray().constData());
               }

           }else{
               db.close();
               throw QString("Error, no se pudo abrir la BD");
           }
       }else{
           db.close();
             throw QString("Error, no se pudo abrir la BD");
       }
    } catch (QString &e) {
        throw e;
    }
}

void MaestroVuelosView::cargarTabla(){
    try {
        QVector<Vuelo> data = Vuelo::todos();
        ui->tblVuelos->setRowCount(0);
        for(int i=0;i<data.size();i++){
            ui->tblVuelos->insertRow(i);
            QTableWidgetItem *codigo = new QTableWidgetItem();
            QTableWidgetItem *origen = new QTableWidgetItem();
            QTableWidgetItem *destino = new QTableWidgetItem();
            QTableWidgetItem *capacidad = new QTableWidgetItem();
            QTableWidgetItem *fecha = new QTableWidgetItem();
            QTableWidgetItem *disponibles = new QTableWidgetItem();
            QTableWidgetItem *precio = new QTableWidgetItem();

            codigo->setText(data[i].getCodigo());
            origen->setText(data[i].getOrigenCodigo());
            destino->setText(data[i].getDestinoCodigo());
            capacidad->setText(QString::number(data[i].getCapacidad()));
            fecha->setText(data[i].getFechaPartida().toString("yyyy-MM-dd hh:mm"));
            disponibles->setText(QString::number(data[i].getAsientosDisponibles()));
            precio->setText(QString::number(data[i].getPrecioAsiento()));

            codigo->setFlags(codigo->flags() ^ Qt::ItemIsEditable);
            origen->setFlags(origen->flags() ^ Qt::ItemIsEditable);
            destino->setFlags(destino->flags() ^ Qt::ItemIsEditable);
            capacidad->setFlags(capacidad->flags() ^ Qt::ItemIsEditable);
            fecha->setFlags(fecha->flags() ^ Qt::ItemIsEditable);
            disponibles->setFlags(disponibles->flags() ^ Qt::ItemIsEditable);
            precio->setFlags(precio->flags() ^ Qt::ItemIsEditable);

            ui->tblVuelos->setItem(i,0,codigo);
            ui->tblVuelos->setItem(i,1,origen);
            ui->tblVuelos->setItem(i,2,destino);
            ui->tblVuelos->setItem(i,3,capacidad);
            ui->tblVuelos->setItem(i,4,fecha);//corregir mostrar fecha
            ui->tblVuelos->setItem(i,5,disponibles);
            ui->tblVuelos->setItem(i,6,precio);
        }
    } catch (QString &e) {
        QMessageBox::warning(this, "Error Inesperado",e);
    }
}
void MaestroVuelosView::cambiarOperacion(int op){
    try {
        if(op!=0 && op!=1 && op!=2){
            throw QString("Error: Codigo de operacion incorrecto");
        }
        this->op = op;
    } catch (QString &e) {
        QMessageBox::warning(this,"Error del Sistema",e);
    }
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


void MaestroVuelosView::on_btnNuevo_clicked()
{
    cambiarOperacion(1);
    ui->txtCodigo->setEnabled(true);
    ui->txtCapacidad->setEnabled(true);
    ui->cbxOrigen->setEnabled(true);
    ui->cbxDestino->setEnabled(true);
    ui->dateTimeEdit->setEnabled(true);//fecha
    ui->doubleSpinBox->setEnabled(true);//precio
    //obvia disponibles
    ui->txtCodigo->setFocus();

    ui->btnCancelar->setEnabled(true);
    ui->btnGuardar->setEnabled(true);
}


void MaestroVuelosView::on_btnCancelar_clicked()
{
    if(this->op ==0){
        QMessageBox::about(this, "Información","No está realizando ninguna acción");
    }else{
        this->cambiarOperacion(0);
        ui->txtCodigo->setText("");
        ui->txtCapacidad->setValue(0);
        ui->cbxOrigen->setCurrentIndex(0);
        ui->cbxDestino->setCurrentIndex(0);
        //ui->dateTimeEdit->setDateTime(); arreglar fecha por defecto
        ui->doubleSpinBox->setValue(0);

        ui->txtCodigo->setEnabled(true);
        ui->txtCapacidad->setEnabled(true);
        ui->cbxOrigen->setEnabled(true);
        ui->cbxDestino->setEnabled(true);
        ui->dateTimeEdit->setEnabled(true);//fecha
        ui->doubleSpinBox->setEnabled(true);//precio

        ui->btnGuardar->setEnabled(false);
        ui->btnCancelar->setEnabled(false);
        ui->btnNuevo->setEnabled(true);
        ui->btnModificar->setEnabled(true);
    }
}


void MaestroVuelosView::on_btnModificar_clicked()
{
    if(ui->tblVuelos->selectionModel()->hasSelection()){
        try {
            QModelIndex index = ui->tblVuelos->selectionModel()->currentIndex();
            QVariant value = index.sibling(index.row(),0).data();
            Vuelo vuelo = Vuelo::buscarPorCodigo(value.toString());
            this->cambiarOperacion(2);
            ui->btnModificar->setDisabled(true);
            ui->btnNuevo->setDisabled(true);
            ui->btnCancelar->setEnabled(true);
            ui->btnGuardar->setEnabled(true);

            ui->txtCodigo->setText(vuelo.getCodigo());
            ui->txtCapacidad->setValue(vuelo.getCapacidad());

            //lista de origen
            int iO= ui->cbxOrigen->findText(vuelo.getOrigenCodigo());//recupera la posicion del codigo buscado
            ui->cbxOrigen->setCurrentIndex(iO);
            //lista de destino
            int iD=ui->cbxDestino->findText(vuelo.getDestinoCodigo());//recupera la posicion del codigo buscado
            ui->cbxDestino->setCurrentIndex(iD);

            ui->dateTimeEdit->setDateTime(vuelo.getFechaPartida());
            ui->doubleSpinBox->setValue(vuelo.getPrecioAsiento());

            ui->txtCapacidad->setEnabled(true);
            ui->cbxOrigen->setEnabled(true);
            ui->cbxDestino->setEnabled(true);
            ui->dateTimeEdit->setEnabled(true);
            ui->doubleSpinBox->setEnabled(true);


        } catch (QString &e) {
            QMessageBox::warning(this, "Error",e);
        } catch(QException &e){
            QMessageBox::warning(this,"Error",e.what());
        }
    }else{
        QMessageBox::warning(this, "Error", "Debe seleccionar un item de la lista");
    }
}

void MaestroVuelosView::on_btnGuardar_clicked()
{
    if(this->op !=0){
        switch (op) {
        case 1:
            {
                Vuelo vuelo(
                            ui->txtCodigo->text().toUpper(),
                            ui->cbxOrigen->currentText(),
                            ui->cbxDestino->currentText(),
                            ui->txtCapacidad->value(),
                            ui->dateTimeEdit->dateTime(),
                            ui->txtCapacidad->value(),//asientos disponbles
                            ui->doubleSpinBox->value()
                            );
                try {
                    Vuelo::guardar(vuelo);
                    QMessageBox::information(this, "Exito", "Registro añadido");
                    this->on_btnCancelar_clicked();
                    cargarTabla();
                } catch (QString &e) {
                    QMessageBox::warning(this, "Error", e);
                    this->on_btnCancelar_clicked();
                }
                break;

            }
        case 2:
            {
                try {
                    Vuelo vuelo = Vuelo::buscarPorCodigo(ui->txtCodigo->text());
                    vuelo.setOrigenCodigo(ui->cbxOrigen->currentText());
                    vuelo.setDestinoCodigo(ui->cbxDestino->currentText());
                    vuelo.setCapacidad(ui->txtCapacidad->value());
                    vuelo.setFechaPartida(ui->dateTimeEdit->dateTime());
                    vuelo.setAsientosDisponibles(ui->txtCapacidad->value());//modificar disponibles
                    vuelo.setPrecioAsiento(ui->doubleSpinBox->value());

                    Vuelo::modificar(vuelo);
                    QMessageBox::information(this, "Operacion exitosa", "Registro modificado con exito");
                    this->on_btnCancelar_clicked();
                    this->cargarTabla();
                } catch (QString &e) {
                    this->on_btnCancelar_clicked();
                    QMessageBox::warning(this, "Error", e);
                } catch (QException &e){
                    this->on_btnCancelar_clicked();
                    QMessageBox::warning(this, "Error", e.what());
                }

            break;
            }
        }
    }else{
        QMessageBox::warning(this, "Informacion", "No se eligio ninguna accion");
    }
}

void MaestroVuelosView::on_btnEliminar_clicked()
{
    if(ui->tblVuelos->selectionModel()->hasSelection()){
        try {
            QModelIndex index = ui->tblVuelos->selectionModel()->currentIndex();
            QVariant value = index.sibling(index.row(),0).data();
            Vuelo vuelo = Vuelo::buscarPorCodigo(value.toString());

            int opc = QMessageBox::question(this,"Mensaje de Confirmación","¿Esta seguro que desea eliminar el registro?");

            if(opc==QMessageBox::Yes){
                Vuelo::eliminar(vuelo.getCodigo());
                QMessageBox::information(this, "Informacion","Registro eliminado con exito");
                cargarTabla();
            }
        } catch (QString &e) {
            QMessageBox::warning(this, "Error", e);
        }
    }else{
        QMessageBox::warning(this, "Error", "Debe seleccionar un item de la lista");
    }
}
