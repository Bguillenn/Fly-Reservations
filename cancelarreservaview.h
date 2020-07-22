#ifndef CANCELARRESERVAVIEW_H
#define CANCELARRESERVAVIEW_H

#include <QWidget>

namespace Ui {
class CancelarReservaView;
}

class CancelarReservaView : public QWidget
{
    Q_OBJECT

public:
    explicit CancelarReservaView(QWidget *parent = nullptr);
    ~CancelarReservaView();

private slots:
    void on_btnCancelar_clicked();

private:
    Ui::CancelarReservaView *ui;
};

#endif // CANCELARRESERVAVIEW_H
