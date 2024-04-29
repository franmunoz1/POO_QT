#include "Acceso.h"
#include <QtWidgets>
#include <QGridLayout>
#include <QDebug>
#include <QPainter>
#include <QNetworkAccessManager>
#include <QNetworkReply>

Acceso::Acceso(QWidget *parent) : QWidget(parent), imageDownloaded(false), failedAttemp(0) // Inicializar el contador de intentos fallidos
{
    lUsuario = new QLabel("Usuario:");
    lClave = new QLabel("Clave:");
    leUsuario = new QLineEdit;
    leClave = new QLineEdit;
    leClave->setEchoMode(QLineEdit::Password);
    pbValidar = new QPushButton("Validar");
    networkManager = new QNetworkAccessManager(this);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(lUsuario, 0, 0);
    layout->addWidget(leUsuario, 0, 1);
    layout->addWidget(lClave, 1, 0);
    layout->addWidget(leClave, 1, 1);
    layout->addWidget(pbValidar, 2, 1, 1, 1);

    // Ajustar el espaciado del diseño
    layout->setSpacing(10);

    setLayout(layout);

    connect(pbValidar, SIGNAL(pressed()), this, SLOT(slot_ValidarUsuario()));
    connect(leClave, SIGNAL(returnPressed()), this, SLOT(slot_ValidarUsuario()));

    // Limitar el tamaño máximo del widget Acceso
    setMaximumSize(400, 200);

    // Descargar la imagen de fondo
    QNetworkRequest request(QUrl("https://blogthinkbig.com/wp-content/uploads/sites/4/2021/12/MicrosoftTeams-image-32.jpg?fit=2440%2C900"));
    networkManager->get(request);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(imagenDescargada(QNetworkReply*)));
}

Acceso::~Acceso()
{
}

void Acceso::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if (imageDownloaded)
    {
        QPainter painter(this);
        painter.drawImage(0, 0, backgroundImage.scaled(size()));
    }
}

void Acceso::slot_ValidarUsuario()
{
    QString usuario = leUsuario->text();
    QString clave = leClave->text();

    if ((usuario == "admin" && clave == "1234") || (usuario == "user" && clave == "4321"))
    {
        qDebug() << "Usuario valido";
        // Mostrar la ventana de usuario si las credenciales son válidas
        this->hide();
    }
    else
    {
        qDebug() << "Usuario invalido";
        leUsuario->clear();
        leClave->clear();

        failedAttemp++; // Incrementar el contador de intentos fallidos

        if (failedAttemp >= 3) // Comprobar si se han realizado tres intentos fallidos
        {
            QApplication::quit(); // Cerrar la aplicación
        }
    }
}

void Acceso::imagenDescargada(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray imageData = reply->readAll();
        if (backgroundImage.loadFromData(imageData))
        {
            imageDownloaded = true;
            update(); // Redibujar el widget con la imagen de fondo
        }
    }

    reply->deleteLater();
}
