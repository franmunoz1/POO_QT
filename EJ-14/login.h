#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QPixmap>

class Formulario;

class Login : public QWidget {
    Q_OBJECT
public:
    Login(QWidget *parent = nullptr);

private slots:
    void verificarLogin();
    void abrirFormulario();
    void mostrarMensajeInicioSesionExitoso();
    void obtenerTemperaturaCordoba();
    void toggleMostrarTemperatura();

private:
    QLabel *lbl_usuario;
    QLabel *lbl_contrasena;
    QLabel *lbl_temperatura;
    QLabel *lbl_fondo;

    QLineEdit *txt_usuario;
    QLineEdit *txt_contrasena;

    QPushButton *btn_login;
    QPushButton *btn_mostrar_ocultar_temperatura;

    Formulario *formulario;
};

class Formulario : public QWidget {
    Q_OBJECT
public:
    Formulario(QWidget *parent = nullptr);

private slots:
    void limpiarCampos();

private:
    QLabel *lbl_legajo;
    QLabel *lbl_nombre;
    QLabel *lbl_apellido;

    QLineEdit *txt_legajo;
    QLineEdit *txt_nombre;
    QLineEdit *txt_apellido;

    QPushButton *btn_enviar;
    QPushButton *btn_limpiar;
};

#endif // LOGIN_H
