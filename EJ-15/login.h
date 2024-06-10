#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QRandomGenerator>

class Formulario;

class Login : public QWidget {
    Q_OBJECT
public:
    Login(QWidget *parent = nullptr);

private slots:
    void verificarLogin();
    void abrirFormulario();

private:
    QLabel *lbl_usuario;
    QLabel *lbl_contrasena;
    QLabel *lbl_captcha;

    QLineEdit *txt_usuario;
    QLineEdit *txt_contrasena;
    QLineEdit *txt_captcha;

    QPushButton *btn_login;

    Formulario *formulario;
};

class Formulario : public QWidget {
    Q_OBJECT
public:
    Formulario(QWidget *parent = nullptr);

private slots:
    void limpiarCampos();
    void verificarCaptcha();

private:
    QLabel *lbl_legajo;
    QLabel *lbl_nombre;
    QLabel *lbl_apellido;
    QLabel *lbl_captcha;

    QLineEdit *txt_legajo;
    QLineEdit *txt_nombre;
    QLineEdit *txt_apellido;
    QLineEdit *txt_captcha;

    QPushButton *btn_enviar;
    QPushButton *btn_limpiar;

    int captcha_generado;
};

#endif // LOGIN_H
