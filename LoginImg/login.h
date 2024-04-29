#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "ventana.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private:
    Ui::Login *ui;
    Ventana * ventana;

    // para cuando presionemos el boton, se ejecute este metodo
private slots:
    void slot_validar();

};
#endif // LOGIN_H
