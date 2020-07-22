#ifndef MAESTROEMPLEADOSVIEW_H
#define MAESTROEMPLEADOSVIEW_H

#include <QWidget>

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

private:
    Ui::MaestroEmpleadosView *ui;
};

#endif // MAESTROEMPLEADOSVIEW_H
