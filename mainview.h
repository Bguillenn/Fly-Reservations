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

private:
    Ui::MainView *ui;
};

#endif // MAINVIEW_H
