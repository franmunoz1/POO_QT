#include "login.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QPainter>

Login::Login(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Login");
    setGeometry(200, 200, 300, 150);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    setLayout(mainLayout);

    QWidget *widget = new QWidget(this);
    mainLayout->addWidget(widget);

    auto layout = new QGridLayout(widget);
    widget->setLayout(layout);

    lbl_usuario = new QLabel("Usuario:");
    lbl_contrasena = new QLabel("Contraseña:");
    lbl_temperatura = new QLabel("Temperatura en Córdoba:");

    txt_usuario = new QLineEdit();
    txt_contrasena = new QLineEdit();
    txt_contrasena->setEchoMode(QLineEdit::Password);

    btn_login = new QPushButton("Ingresar");
    btn_mostrar_ocultar_temperatura = new QPushButton("Mostrar/Ocultar Temperatura");

    layout->addWidget(lbl_usuario, 0, 0);
    layout->addWidget(txt_usuario, 0, 1);
    layout->addWidget(lbl_contrasena, 1, 0);
    layout->addWidget(txt_contrasena, 1, 1);
    layout->addWidget(lbl_temperatura, 2, 0, 1, 2);
    layout->addWidget(btn_login, 3, 0, 1, 2);
    layout->addWidget(btn_mostrar_ocultar_temperatura, 4, 0, 1, 2);

    QObject::connect(txt_contrasena, SIGNAL(returnPressed()), this, SLOT(verificarLogin()));

    QObject::connect(btn_login, SIGNAL(clicked()), this, SLOT(verificarLogin()));
    QObject::connect(btn_mostrar_ocultar_temperatura, SIGNAL(clicked()), this, SLOT(toggleMostrarTemperatura()));

    obtenerTemperaturaCordoba();

    intentosFallidos = 0;
    timerBloqueo = new QTimer(this);
    connect(timerBloqueo, &QTimer::timeout, this, &Login::desbloquearUsuario);
    timerBloqueo->setSingleShot(true);
}

void Login::paintEvent(QPaintEvent *event) {
    QWidget::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Dibujar fondo
    painter.fillRect(rect(), QColor(173, 216, 230)); // Color azul claro
}

void Login::verificarLogin() {
    QString usuario_ingresado = txt_usuario->text();
    QString contrasena_ingresada = txt_contrasena->text();
    if (usuario_ingresado == "admin" && contrasena_ingresada == "1111") {
        mostrarMensajeInicioSesionExitoso();
        abrirFormulario();
    } else {
        intentosFallidos++;
        if (intentosFallidos >= 3) {
            QMessageBox::warning(this, "Error", "Se ha excedido el límite de intentos fallidos. El usuario será bloqueado durante 5 minutos.");
            txt_usuario->setEnabled(false);
            txt_contrasena->setEnabled(false);
            btn_login->setEnabled(false);
            timerBloqueo->start(300000);
        } else {
            QMessageBox::warning(this, "Error", "Usuario y/o contraseña incorrectos");
            txt_usuario->clear();
            txt_contrasena->clear();
        }
    }
}

void Login::mostrarMensajeInicioSesionExitoso() {
    QMessageBox::information(this, "Éxito", "Inicio de sesión exitoso");
}

void Login::abrirFormulario() {
    formulario = new Formulario();
    formulario->show();
    close();
}

void Login::obtenerTemperaturaCordoba() {
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QObject::connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(handleTemperaturaCordoba(QNetworkReply*)));

    QString url = "http://api.openweathermap.org/data/2.5/weather?q=Cordoba&appid=824b4c2b2e5705ce2b026d6d39dd184b&units=metric";
    manager->get(QNetworkRequest(QUrl(url)));
}

void Login::toggleMostrarTemperatura() {
    if (lbl_temperatura->isVisible()) {
        lbl_temperatura->hide();
    } else {
        lbl_temperatura->show();
        obtenerTemperaturaCordoba();
    }
}

void Login::handleTemperaturaCordoba(QNetworkReply *reply) {
    if (reply->error()) {
        qDebug() << "Error al obtener la temperatura:" << reply->errorString();
        return;
    }
    QString respuesta = reply->readAll();
    QJsonDocument jsonResponse = QJsonDocument::fromJson(respuesta.toUtf8());
    QJsonObject jsonObj = jsonResponse.object();
    if (jsonObj.contains("main")) {
        QJsonObject mainObj = jsonObj["main"].toObject();
        if (mainObj.contains("temp")) {
            double temperatura = mainObj["temp"].toDouble();
            lbl_temperatura->setText("Temperatura en Córdoba: " + QString::number(temperatura) + " °C");
        }
    }
    reply->deleteLater();
}

void Login::desbloquearUsuario() {
    txt_usuario->setEnabled(true);
    txt_contrasena->setEnabled(true);
    btn_login->setEnabled(true);
    intentosFallidos = 0;
}

Formulario::Formulario(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Formulario");
    setGeometry(300, 300, 300, 200);

    auto layout = new QGridLayout(this);

    lbl_legajo = new QLabel("Legajo:");
    lbl_nombre = new QLabel("Nombre:");
    lbl_apellido = new QLabel("Apellido:");

    txt_legajo = new QLineEdit();
    txt_nombre = new QLineEdit();
    txt_apellido = new QLineEdit();

    btn_enviar = new QPushButton("Enviar");
    btn_limpiar = new QPushButton("Limpiar campos");

    layout->addWidget(lbl_legajo, 0, 0);
    layout->addWidget(txt_legajo, 0, 1);
    layout->addWidget(lbl_nombre, 1, 0);
    layout->addWidget(txt_nombre, 1, 1);
    layout->addWidget(lbl_apellido, 2, 0);
    layout->addWidget(txt_apellido, 2, 1);
    layout->addWidget(btn_enviar, 3, 0, 1, 2);
    layout->addWidget(btn_limpiar, 4, 0, 1, 2);

    setLayout(layout);

    QObject::connect(btn_limpiar, SIGNAL(clicked()), this, SLOT(limpiarCampos()));
}

void Formulario::limpiarCampos() {
    txt_legajo->clear();
    txt_nombre->clear();
    txt_apellido->clear();
}

