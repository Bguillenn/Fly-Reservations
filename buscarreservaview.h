#ifndef BUSCARRESERVAVIEW_H
#define BUSCARRESERVAVIEW_H

#include <QWidget>

namespace Ui {
class BuscarReservaView;
}

class BuscarReservaView : public QWidget
{
    Q_OBJECT

public:
    explicit BuscarReservaView(QWidget *parent = nullptr);
    ~BuscarReservaView();

private slots:
    void on_btnSalir_clicked();

    void on_btnMostrarInfo_clicked();

private:
    Ui::BuscarReservaView *ui;
};

#endif // BUSCARRESERVAVIEW_H
