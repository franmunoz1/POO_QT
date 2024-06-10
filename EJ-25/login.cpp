#include "Login.h"
#include "Registro.h"
#include "AdminDB.h"
#include "ListaUsuarios.h"
#include <QVBoxLayout>
#include <QMessageBox>

Login::Login(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    nombreUsuarioLineEdit = new QLineEdit(this);
    nombreUsuarioLineEdit->setPlaceholderText("Nombre de Usuario");

    contrasenaLineEdit = new QLineEdit(this);
    contrasenaLineEdit->setPlaceholderText("Contraseña");
    contrasenaLineEdit->setEchoMode(QLineEdit::Password);

    botonLogin = new QPushButton("Iniciar Sesión", this);
    etiquetaRegistro = new QLabel("<a href='#'>Registrarse</a>", this);
    etiquetaRegistro->setTextFormat(Qt::RichText);
    etiquetaRegistro->setTextInteractionFlags(Qt::TextBrowserInteraction);
    etiquetaRegistro->setOpenExternalLinks(false);

    layout->addWidget(nombreUsuarioLineEdit);
    layout->addWidget(contrasenaLineEdit);
    layout->addWidget(botonLogin);
    layout->addWidget(etiquetaRegistro);

    // Conexión utilizando la nueva sintaxis de señales y slots
    connect(botonLogin, &QPushButton::clicked, this, [=]() {
        manejarLogin();
    });

    connect(etiquetaRegistro, &QLabel::linkActivated, this, [=]() {
        mostrarRegistro();
    });
}

void Login::manejarLogin()
{
    QString nombreUsuario = nombreUsuarioLineEdit->text();
    QString contrasena = contrasenaLineEdit->text();

    if (AdminDB::instancia().autenticarUsuario(nombreUsuario, contrasena)) {
        ListaUsuarios *listaUsuarios = new ListaUsuarios();
        listaUsuarios->show();
        this->close();
    } else {
        QMessageBox::warning(this, "Inicio de Sesión Fallido", "Nombre de usuario o contraseña incorrectos");
    }
}

void Login::mostrarRegistro()
{
    Registro *ventanaRegistro = new Registro();
    ventanaRegistro->show();
}
