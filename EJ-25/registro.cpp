#include "Registro.h"
#include "AdminDB.h"
#include <QVBoxLayout>
#include <QMessageBox>

Registro::Registro(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    nombreUsuarioLineEdit = new QLineEdit(this);
    nombreUsuarioLineEdit->setPlaceholderText("Nombre de Usuario");

    contrasenaLineEdit = new QLineEdit(this);
    contrasenaLineEdit->setPlaceholderText("Contraseña");
    contrasenaLineEdit->setEchoMode(QLineEdit::Password);

    botonRegistro = new QPushButton("Registrarse", this);

    layout->addWidget(nombreUsuarioLineEdit);
    layout->addWidget(contrasenaLineEdit);
    layout->addWidget(botonRegistro);

    // Conexión utilizando la nueva sintaxis de señales y slots
    connect(botonRegistro, &QPushButton::clicked, this, [=]() {
        manejarRegistro();
    });
}

void Registro::manejarRegistro()
{
    QString nombreUsuario = nombreUsuarioLineEdit->text();
    QString contrasena = contrasenaLineEdit->text();

    if (AdminDB::instancia().crearUsuario(nombreUsuario, contrasena)) {
        QMessageBox::information(this, "Registro Exitoso", "Usuario registrado con éxito");
        this->close();
    } else {
        QMessageBox::warning(this, "Registro Fallido", "No se pudo registrar el usuario");
    }
}
