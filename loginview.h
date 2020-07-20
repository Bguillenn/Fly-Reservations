#ifndef LOGINVIEW_H
#define LOGINVIEW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class LoginView; }
QT_END_NAMESPACE

class LoginView : public QMainWindow
{
    Q_OBJECT

public:
    LoginView(QWidget *parent = nullptr);
    ~LoginView();

private slots:
    void on_btnSalir_clicked();

    void on_btnEntrar_clicked();

private:
    Ui::LoginView *ui;
};
#endif // LOGINVIEW_H
