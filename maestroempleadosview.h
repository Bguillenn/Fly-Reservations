#ifndef MAESTROEMPLEADOSVIEW_H
#define MAESTROEMPLEADOSVIEW_H

#include <QWidget>
#include <QVector>

namespace Ui {
class MaestroEmpleadosView;
}

class MaestroEmpleadosView : public QWidget
{
    Q_OBJECT

public:
    explicit MaestroEmpleadosView(QWidget *parent = nullptr);
    ~MaestroEmpleadosView();

private slots:
    void on_btnSalir_clicked();

    void on_btnNuevo_clicked();

    void on_btnCancelar_clicked();

    void on_btnModificar_clicked();

    void on_btnGuardar_clicked();

    void on_btnEliminar_clicked();

private:
    Ui::MaestroEmpleadosView *ui;
    int op = 0; //Operacion que se esta realizando en el crud
    // 0 : NADA
    // 1 : NUEVO
    // 2 : MODIFICANDO
    void cargarTabla();
    void cambiarOperacion(int);
};

#endif // MAESTROEMPLEADOSVIEW_H
