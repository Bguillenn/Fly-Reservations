#ifndef DETALLESRESERVAVIEW_H
#define DETALLESRESERVAVIEW_H

#include <QWidget>

namespace Ui {
class DetallesReservaView;
}

class DetallesReservaView : public QWidget
{
    Q_OBJECT

public:
    explicit DetallesReservaView(QWidget *parent = nullptr);
    ~DetallesReservaView();

private slots:
    void on_btnSalir_clicked();

private:
    Ui::DetallesReservaView *ui;
};

#endif // DETALLESRESERVAVIEW_H
