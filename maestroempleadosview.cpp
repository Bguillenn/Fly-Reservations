#include "maestroempleadosview.h"
#include "ui_maestroempleadosview.h"
#include "empleado.h"
#include <QMessageBox>

//Implementando las vistas necesarias
#include "mainview.h"

MaestroEmpleadosView::MaestroEmpleadosView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MaestroEmpleadosView)
{
    ui->setupUi(this);
    this->setWindowFlag(Qt::FramelessWindowHint);
    //Configurando la tabla
    QStringList headers;
    ui->tblEmpleados->setColumnCount(5);
    ui->tblEmpleados->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tblEmpleados->setSelectionMode(QAbstractItemView::SingleSelection);
    headers << "Codigo" << "Nombres y Apellidos" << "DNI" << "Sexo" << "Tipo";
    ui->tblEmpleados->setHorizontalHeaderLabels(headers);
    ui->tblEmpleados->setColumnWidth(0, 60);
    ui->tblEmpleados->setColumnWidth(1, 200);
    ui->tblEmpleados->setColumnWidth(2, 80);
    ui->tblEmpleados->setColumnWidth(3, 45);
    ui->tblEmpleados->setColumnWidth(4, 45);

    cargarTabla();
}

//Metodos propios
void MaestroEmpleadosView::cargarTabla(){
    try {
        QVector<Empleado> data = Empleado::todos();

        ui->tblEmpleados->setRowCount(0);
        for(int i=0; i<data.size(); i++){
            ui->tblEmpleados->insertRow(i);
            QTableWidgetItem *codigo = new QTableWidgetItem();
            QTableWidgetItem *nombres = new QTableWidgetItem();
            QTableWidgetItem *dni = new QTableWidgetItem();
            QTableWidgetItem *sexo = new QTableWidgetItem();
            QTableWidgetItem *tipo = new QTableWidgetItem();

            codigo->setText(data[i].getCodigo());
            nombres->setText(data[i].getNombres() + " "+data[i].getApellidos() );
            dni->setText(data[i].getDNI());
            sexo->setText(data[i].getSexo());
            tipo->setText(data[i].getTipo());

            codigo->setFlags(codigo->flags() ^ Qt::ItemIsEditable);
            nombres->setFlags(nombres->flags() ^ Qt::ItemIsEditable);
            dni->setFlags(dni->flags() ^ Qt::ItemIsEditable);
            sexo->setFlags(sexo->flags() ^ Qt::ItemIsEditable);
            tipo->setFlags(tipo->flags() ^ Qt::ItemIsEditable);

            ui->tblEmpleados->setItem(i, 0, codigo);
            ui->tblEmpleados->setItem(i, 1, nombres);
            ui->tblEmpleados->setItem(i, 2, dni);
            ui->tblEmpleados->setItem(i, 3, sexo);
            ui->tblEmpleados->setItem(i, 4, tipo);
        }
    } catch (QString &e) {
        QMessageBox::warning(this, "Error inesperado", e);
    }
}

void MaestroEmpleadosView::cambiarOperacion(int op){
    try {
        if(op != 0 && op != 1 && op != 2)
            throw QString("ERROR: Codigo de operacion incorrecto");
        this->op = op;
    } catch (QString &e) {
        QMessageBox::warning(this, "Error del sistema", e);
    }
}

//METODOS GENERADOS

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

void MaestroEmpleadosView::on_btnNuevo_clicked()
{
    cambiarOperacion(1);
    ui->txtCodigo->setEnabled(true);
    ui->txtNombres->setEnabled(true);
    ui->txtApellidos->setEnabled(true);
    ui->txtFecha->setEnabled(true);
    ui->cbxSexo->setEnabled(true);
    ui->txtDocumento->setEnabled(true);
    ui->txtContrasenia->setEnabled(true);
    ui->cbxTipo->setEnabled(true);

    ui->txtCodigo->setFocus();

    ui->btnCancelar->setEnabled(true);
    ui->btnGuardar->setEnabled(true);
}

void MaestroEmpleadosView::on_btnCancelar_clicked()
{
    if(this->op == 0)
        QMessageBox::about(this, "Informacion", "No esta realizando ninguna accion");
    else{
            this->cambiarOperacion(0);
            ui->txtCodigo->setText("");
            ui->txtNombres->setText("");
            ui->txtApellidos->setText("");
            ui->txtDocumento->setText("");
            ui->txtContrasenia->setText("");

            ui->txtCodigo->setDisabled(true);
            ui->txtNombres->setDisabled(true);
            ui->txtApellidos->setDisabled(true);
            ui->txtDocumento->setDisabled(true);
            ui->txtContrasenia->setDisabled(true);
            ui->txtFecha->setDisabled(true);
            ui->cbxSexo->setDisabled(true);
            ui->cbxTipo->setDisabled(true);

            ui->btnGuardar->setEnabled(false);
            ui->btnCancelar->setEnabled(false);
            ui->btnNuevo->setEnabled(true);
            ui->btnModificar->setEnabled(true);

    }
}

void MaestroEmpleadosView::on_btnModificar_clicked()
{

    if(ui->tblEmpleados->selectionModel()->hasSelection()){
        try {
            QModelIndex index = ui->tblEmpleados->selectionModel()->currentIndex();
            QVariant value=index.sibling(index.row(),0).data();
            Empleado empleado = Empleado::buscarPorCodigo(value.toString());
            this->cambiarOperacion(2);
            ui->btnModificar->setDisabled(true);
            ui->btnNuevo->setDisabled(true);
            ui->btnCancelar->setEnabled(true);
            ui->btnGuardar->setEnabled(true);
            ui->txtCodigo->setText(empleado.getCodigo());
            ui->txtNombres->setText(empleado.getNombres());
            ui->txtApellidos->setText(empleado.getApellidos());
            ui->txtDocumento->setText(empleado.getDNI());
            ui->txtContrasenia->setText(empleado.getContrasenia());
            ui->txtFecha->setDateTime(empleado.getFechaNacimiento());
            if(QString::compare(empleado.getTipo(), "V", Qt::CaseInsensitive) == 1)
                ui->cbxTipo->setCurrentIndex(0);
            else
                ui->cbxTipo->setCurrentIndex(1);

            if(QString::compare(empleado.getSexo(), "M", Qt::CaseInsensitive) == 1)
                ui->cbxSexo->setCurrentIndex(0);
            else
                ui->cbxSexo->setCurrentIndex(1);

            ui->txtNombres->setEnabled(true);
            ui->txtApellidos->setEnabled(true);
            ui->txtDocumento->setEnabled(true);
            ui->txtFecha->setEnabled(true);
            ui->txtContrasenia->setEnabled(true);
            ui->cbxSexo->setEnabled(true);
            ui->cbxTipo->setEnabled(true);

        } catch (QString &e) {
            QMessageBox::warning(this, "Error", e);
        }catch (QException &e){
            QMessageBox::warning(this, "Error", e.what());
        }

    }else
        QMessageBox::warning(this, "Error", "Debe seleccionar un item de la lista");
}

void MaestroEmpleadosView::on_btnGuardar_clicked()
{
    if(this->op != 0){
        switch(op){
            case 1:
                    {
                        QString tipo;
                        QString sexo;
                        if(ui->cbxSexo->currentIndex() == 0)
                            sexo = "M";
                        else
                            sexo = "F";

                        if(ui->cbxTipo->currentIndex() == 0)
                            tipo = "V";
                        else
                            tipo = "A";

                        Empleado empleado(
                                        ui->txtCodigo->text().toUpper(),
                                        ui->txtNombres->text().toUpper(),
                                        ui->txtApellidos->text().toUpper(),
                                        ui->txtFecha->dateTime(),
                                        sexo,
                                        ui->txtDocumento->text(),
                                        ui->txtContrasenia->text(),
                                        tipo
                                    );
                        try {
                            Empleado::guardar(empleado);
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
                        QString tipo;
                        QString sexo;
                        if(ui->cbxSexo->currentIndex() == 0)
                            sexo = "M";
                        else
                            sexo = "F";

                        if(ui->cbxTipo->currentIndex() == 0)
                            tipo = "V";
                        else
                            tipo = "A";
                        try {
                            Empleado empleado = Empleado::buscarPorCodigo(ui->txtCodigo->text());
                            empleado.setNombres(ui->txtNombres->text().toUpper());
                            empleado.setApellidos(ui->txtApellidos->text().toUpper());
                            empleado.setFechaNacimiento(ui->txtFecha->dateTime());
                            empleado.setDNI(ui->txtDocumento->text());
                            empleado.setContrasenia(ui->txtContrasenia->text());
                            empleado.setSexo(sexo);
                            empleado.setTipo(tipo);

                            Empleado::modificar(empleado);

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

void MaestroEmpleadosView::on_btnEliminar_clicked()
{
    if(ui->tblEmpleados->selectionModel()->hasSelection()){
        try {
            QModelIndex index = ui->tblEmpleados->selectionModel()->currentIndex();
            QVariant value=index.sibling(index.row(),0).data();
            Empleado empleado = Empleado::buscarPorCodigo(value.toString());
            int opc = QMessageBox::question(this, "Confirmacion", "¿Realmente desea eliminar el registro?");
            if(opc == QMessageBox::Yes){
                Empleado::eliminar(empleado.getCodigo());
                QMessageBox::information(this,"Informacion", "Registro eliminado con exito");
                cargarTabla();
            }
        }catch(QString &e){
            QMessageBox::warning(this, "Error", e);
        }
    }else{
        QMessageBox::warning(this, "Error", "Debe seleccionar un item de la lista");
    }
}
