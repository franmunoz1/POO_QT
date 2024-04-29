#include "ventana.h"
#include "ui_ventana.h" // Agrega esta línea

#include <QPainter>
#include <QString>

Ventana::Ventana(QWidget *parent) : QWidget(parent), ui(new Ui::Ventana), manager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_descargaFinalizada(QNetworkReply*)));

    QString sUrl = "https://e00-marca.uecdn.es/blogs/espanasemueve/imagenes_posts/2022/06/03/205885.jpg";
    manager->get(QNetworkRequest(QUrl(sUrl)));
}

Ventana::~Ventana()
{
    delete ui;
}

void Ventana::paintEvent(QPaintEvent *) // Aquí cambia painEvent por paintEvent
{
    QPainter painter(this);

    if (!im.isNull())
    {
        painter.drawImage(0, 0, im.scaled(this->width(), this->height()));
    }
}

void Ventana::slot_descargaFinalizada(QNetworkReply *reply)
{
    im = QImage::fromData(reply->readAll());
    this->repaint();
}
