#include "acceso.h"
#include "QtGui/qpainter.h"
#include "ui_acceso.h"
#include "ventana.h"

Acceso::Acceso(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Acceso)
    , imageDownloaded(false)
    , failedAttemp(0)
    , networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    setMaximumSize(400, 200);

    connect(ui->pbValidar, SIGNAL(pressed()), this, SLOT(slot_validar()));
    connect(ui->leClave, SIGNAL(returnPressed()), this, SLOT(slot_validar()));


    QNetworkRequest request(QUrl("https://blogthinkbig.com/wp-content/uploads/sites/4/2021/12/MicrosoftTeams-image-32.jpg?fit=2440%2C900"));
    networkManager->get(request);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(imagenDescargada(QNetworkReply*)));
}

Acceso::~Acceso()
{
    delete ui;
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

void Acceso::slot_validar()
{
    QString usuario = ui->leUsuario->text();
    QString clave = ui->leClave->text();

    if ((usuario == "admin" && clave == "1234") || (usuario == "user" && clave == "4321"))
    {
        qDebug() << "Usuario valido";
        this->hide(); // Ocultar la ventana de acceso al validar correctamente


        Ventana *ventana = new Ventana(usuario, this);
        ventana->show();
    }
    else
    {
        qDebug() << "Usuario invalido";
        ui->leUsuario->clear();
        ui->leClave->clear();

        failedAttemp++;

        if (failedAttemp >= 3)
        {
            QApplication::quit();
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
            update();


            this->show();
        }
    }

    reply->deleteLater();
}
