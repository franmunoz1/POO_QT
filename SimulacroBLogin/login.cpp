#include "login.h"
#include "editor.h"


Login::Login(QWidget *parent) : QWidget(parent)
{
    setFixedSize(300, 150);

    userLineEdit = new QLineEdit(this);
    userLineEdit->setPlaceholderText("Usuario");
    userLineEdit->setGeometry(20, 20, 260, 30);

    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setPlaceholderText("Contraseña");
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLineEdit->setGeometry(20, 60, 260, 30);

    loginButton = new QPushButton("Iniciar Sesión", this);
    loginButton->setGeometry(20, 100, 260, 30);
    connect(loginButton, &QPushButton::clicked, this, &Login::attemptLogin);

    statusLabel = new QLabel(this);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setGeometry(20, 140, 260, 30);
}

void Login::attemptLogin()
{
    QString username = userLineEdit->text();
    QString password = passwordLineEdit->text();

    if (username == "admin" && password == "123")
    {
        statusLabel->setText("Inicio de sesión exitoso");

        Editor *editorWindow = new Editor(); // Crear instancia de Editor
        editorWindow->show(); // Mostrar la ventana del editor

        // Cerrar la ventana de inicio de sesión
        this->close();
    }
    else
    {
        statusLabel->setText("Error de inicio de sesión. Verifique usuario y contraseña.");
    }
}
