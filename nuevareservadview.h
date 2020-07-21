#ifndef NUEVARESERVADVIEW_H
#define NUEVARESERVADVIEW_H

#include <QWidget>

namespace Ui {
class NuevaReservaDView;
}

class NuevaReservaDView : public QWidget
{
    Q_OBJECT

public:
    explicit NuevaReservaDView(QWidget *parent = nullptr);
    ~NuevaReservaDView();

private slots:
    void on_btnCancelar_clicked();

    void on_btnAnterior_clicked();

private:
    Ui::NuevaReservaDView *ui;
};

#endif // NUEVARESERVADVIEW_H
