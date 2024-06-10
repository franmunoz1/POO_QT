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
#include <QPainter>
#include <QTimer>
#include <QCryptographicHash>
#include <QStringList>

class Formulario;
class AdminDB;

class Login : public QWidget {
    Q_OBJECT
public:
    Login(QWidget *parent = nullptr);

signals:
    void signal_usuarioValidado(QString usuario);

private slots:
    void verificarLogin();
    void abrirFormulario();
    void mostrarMensajeInicioSesionExitoso();
    void obtenerTemperaturaCordoba();
    void toggleMostrarTemperatura();
    void handleTemperaturaCordoba(QNetworkReply *reply);
    void desbloquearUsuario();

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QLabel *lbl_usuario;
    QLabel *lbl_contrasena;
    QLabel *lbl_temperatura;

    QLineEdit *txt_usuario;
    QLineEdit *txt_contrasena;

    QPushButton *btn_login;
    QPushButton *btn_mostrar_ocultar_temperatura;

    Formulario *formulario;
    AdminDB *adminDB;
    int intentosFallidos;
    QTimer *timerBloqueo;
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
