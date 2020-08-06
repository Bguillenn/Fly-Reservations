#ifndef DETALLESRESERVAVIEW_H
#define DETALLESRESERVAVIEW_H

#include <QWidget>
#include "reserva.h"

namespace Ui {
class DetallesReservaView;
}

class DetallesReservaView : public QWidget
{
    Q_OBJECT

public:
    explicit DetallesReservaView(QWidget *parent = nullptr);
    ~DetallesReservaView();
    void setReserva(Reserva);
    void cargarData();

private slots:
    void on_btnSalir_clicked();

private:
    Ui::DetallesReservaView *ui;
    Reserva reserva;
};

#endif // DETALLESRESERVAVIEW_H
