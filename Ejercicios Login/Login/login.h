#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QtWidgets>
#include "ventana.h"

class Login : public QWidget {
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);

public slots:
    void slot_validarUsuario();

private:
    QLineEdit *leUsuario;
    QLineEdit *leClave;
    Ventana *ventana;
};

#endif // LOGIN_H
