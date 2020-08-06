#ifndef NUEVARESERVADVIEW_H
#define NUEVARESERVADVIEW_H

#include <QWidget>
#include "vuelo.h"

namespace Ui {
class NuevaReservaDView;
}

class NuevaReservaDView : public QWidget
{
    Q_OBJECT

public:

    explicit NuevaReservaDView(QWidget *parent = nullptr);
    ~NuevaReservaDView();
    void setVuelo(Vuelo);
    void setAsientos(int);
    void cargarData();

private slots:
    void on_btnCancelar_clicked();
    void on_btnAnterior_clicked();

    void on_btnConfirmar_clicked();

private:
    Ui::NuevaReservaDView *ui;
    Vuelo vuelo;
    int asientos;
};

#endif // NUEVARESERVADVIEW_H
