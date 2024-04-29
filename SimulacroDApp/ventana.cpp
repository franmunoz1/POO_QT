#include "ventana.h"
#include "ui_ventana.h"
#include <QPainter>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QPainter>


Ventana::Ventana(QWidget *parent) : QWidget(parent), ui(new Ui::Ventana), manager(new QNetworkAccessManager(this)), indiceActual(0)
{
    ui->setupUi(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_descargaFinalizada(QNetworkReply*)));


    QString sUrl = obtenerUrlDesdeArchivo(indiceActual);
    cargarImagenDesdeUrl(sUrl);
    qDebug() << "sUrl" << sUrl;


    connect(ui->pbAnterior, SIGNAL(clicked()), this, SLOT(anterior()));
    connect(ui->pbSiguiente, SIGNAL(clicked()), this, SLOT(siguiente()));
}


Ventana::~Ventana()
{
    delete ui;
}


void Ventana::slot_descargaFinalizada(QNetworkReply *reply)
{
    im = QImage::fromData(reply->readAll());
    qDebug() << "imagen" << im.isNull();
    this->repaint();
}

QString Ventana::obtenerUrlDesdeArchivo(int indice)
{
    QString url;
    QFile file("/Users/franciscomunoz/Desktop/POO_QT/SimulacroDApp/urls.txt");
    //qDebug() << QDir::currentPath();
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        for (int i = 0; i < indice; ++i) {
            url = in.readLine();
            if (url.isNull()) {
                break;
            }
        }
        file.close();
    } else {
        qDebug() << "Error al leer el archivo de URLs";
    }
    return url;
}

void Ventana::cargarImagenDesdeUrl(const QString &url)
{
    manager->get(QNetworkRequest(QUrl(url)));
}

void Ventana::paintEvent(QPaintEvent *)
{
    QPainter painter( this );
    painter.drawImage(0,0,im.scaled(this->width(),this->height()));
}

void Ventana::anterior()
{
    if (indiceActual > 0) {
        indiceActual--;
        cargarImagenDesdeUrl(obtenerUrlDesdeArchivo(indiceActual));
    }
}

void Ventana::siguiente()
{
    QString url = obtenerUrlDesdeArchivo(indiceActual + 1);
    if (!url.isEmpty()) {
        indiceActual++;
        cargarImagenDesdeUrl(url);
    }
}

