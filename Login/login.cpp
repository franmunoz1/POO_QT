#include "login.h"
#include "ventana.h"

Login::Login(QWidget *parent) : QWidget(parent) {
    QLabel *lblUsuario = new QLabel("Usuario:");
    QLabel *lblClave = new QLabel("Clave:");
    leUsuario = new QLineEdit;
    leClave = new QLineEdit;
    leClave->setEchoMode(QLineEdit::Password);
    QPushButton *pbValidar = new QPushButton("Validar");

    ventana = new Ventana;

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(lblUsuario, 0, 0);
    layout->addWidget(leUsuario, 0, 1);
    layout->addWidget(lblClave, 1, 0);
    layout->addWidget(leClave, 1, 1);
    layout->addWidget(pbValidar, 2, 0, 1, 2);

    setLayout(layout);

    connect(pbValidar, SIGNAL(pressed()), this, SLOT(slot_validarUsuario()));
    connect(leClave, SIGNAL(returnPressed()), this, SLOT(slot_validarUsuario()));
}

void Login::slot_validarUsuario() {
    QString usuario = leUsuario->text();
    QString clave = leClave->text();

    if (usuario == "admin" && clave == "123") {
        qDebug() << "Usuario válido";

        ventana->show();
    } else {
        qDebug() << "Usuario o clave incorrectos";
    }
}
