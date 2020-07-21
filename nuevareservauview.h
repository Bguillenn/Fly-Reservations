#ifndef NUEVARESERVAUVIEW_H
#define NUEVARESERVAUVIEW_H

#include <QWidget>

namespace Ui {
class NuevaReservaUView;
}

class NuevaReservaUView : public QWidget
{
    Q_OBJECT

public:
    explicit NuevaReservaUView(QWidget *parent = nullptr);
    ~NuevaReservaUView();

private slots:
    void on_btnCancelar_clicked();

    void on_btnSiguiente_clicked();

private:
    Ui::NuevaReservaUView *ui;
};

#endif // NUEVARESERVAUVIEW_H
