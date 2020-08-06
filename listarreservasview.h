#ifndef LISTARRESERVASVIEW_H
#define LISTARRESERVASVIEW_H

#include <QWidget>

namespace Ui {
class ListarReservasView;
}

class ListarReservasView : public QWidget
{
    Q_OBJECT

public:
    explicit ListarReservasView(QWidget *parent = nullptr);
    ~ListarReservasView();

private slots:
    void on_btnSalir_clicked();

    void on_chkTodas_stateChanged(int arg1);

private:
    Ui::ListarReservasView *ui;
    void actualizarLabelResultados();
    void cargarTabla();
};

#endif // LISTARRESERVASVIEW_H
