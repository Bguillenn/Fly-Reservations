#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QWidget>

namespace Ui {
class MainView;
}

class MainView : public QWidget
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent = nullptr);
    ~MainView();

private slots:
    void on_btnCerrarSesion_clicked();

    void on_btnNuevaReserva_clicked();

    void on_btnListarReservas_clicked();

    void changeDateTime();

    void on_btnBuscarReserva_clicked();

    void on_btnEmpleados_clicked();

    void on_btnVuelos_clicked();

    void on_btnCancelarReserva_clicked();

private:
    Ui::MainView *ui;
};

#endif // MAINVIEW_H
