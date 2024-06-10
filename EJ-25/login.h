#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);

private slots:
    void manejarLogin();
    void mostrarRegistro();

private:
    QLineEdit *nombreUsuarioLineEdit;
    QLineEdit *contrasenaLineEdit;
    QPushButton *botonLogin;
    QLabel *etiquetaRegistro;
};

#endif // LOGIN_H
