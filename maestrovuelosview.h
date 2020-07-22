#ifndef MAESTROVUELOSVIEW_H
#define MAESTROVUELOSVIEW_H

#include <QWidget>

namespace Ui {
class MaestroVuelosView;
}

class MaestroVuelosView : public QWidget
{
    Q_OBJECT

public:
    explicit MaestroVuelosView(QWidget *parent = nullptr);
    ~MaestroVuelosView();

private slots:
    void on_btnSalir_clicked();

private:
    Ui::MaestroVuelosView *ui;
};

#endif // MAESTROVUELOSVIEW_H
