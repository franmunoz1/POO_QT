#include "manager.h"

Manager::Manager() {
    login = new Login();
    ventana = new Ventana();

    QObject::connect(login, &Login::loginSuccessful, [this]() {
        login->hide();
        ventana->show();
    });

    QObject::connect(ventana, &Ventana::backToLogin, [this]() {
        ventana->hide();
        login->show();
    });

    login->show();
}

Manager::~Manager() {
    delete login;
    delete ventana;
}
