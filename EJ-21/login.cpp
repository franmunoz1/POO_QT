#include "login.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

Login::Login(QWidget *parent) : QWidget(parent) {
    usernameEdit = new QLineEdit(this);
    passwordEdit = new QLineEdit(this);
    passwordEdit->setEchoMode(QLineEdit::Password);
    loginButton = new QPushButton("Login", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(usernameEdit);
    layout->addWidget(passwordEdit);
    layout->addWidget(loginButton);

    connect(loginButton, &QPushButton::clicked, this, &Login::validateLogin);

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/franciscomunoz/Desktop/POO_QT/EJ-21/db.sqlite");

    if (!db.open()) {
        QMessageBox::critical(this, "Database Error", db.lastError().text());
    }
}

Login::~Login() {
    db.close();
}

void Login::validateLogin() {
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    QSqlQuery query;
    query.prepare("SELECT * FROM usuarios WHERE usuario = :username AND clave = :password");
    query.bindValue(":username", username);
    query.bindValue(":password", password);

    if (query.exec() && query.next()) {
        emit loginSuccessful();
    } else {
        QMessageBox::warning(this, "Login Failed", "Invalid username or password");
    }
}
