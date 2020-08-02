#ifndef MAESTROVUELOSVIEW_H
#define MAESTROVUELOSVIEW_H

#include <QWidget>
#include "vuelo.h"
#include <QVector>
#include <QMessageBox>
namespace Ui {
class MaestroVuelosView;
}

class MaestroVuelosView : public QWidget
{
    Q_OBJECT

public:
    explicit MaestroVuelosView(QWidget *parent = nullptr);
    ~MaestroVuelosView();

private slots:
    void on_btnSalir_clicked();

    void on_btnNuevo_clicked();

    void on_btnCancelar_clicked();

    void on_btnModificar_clicked();

    void on_btnGuardar_clicked();

    void on_btnEliminar_clicked();

private:
    Ui::MaestroVuelosView *ui;
    int op=0;
    void cargarTabla();
    void cambiarOperacion(int);
    void llenarOrigen();
    void llenarDestinos();
};

#endif // MAESTROVUELOSVIEW_H
