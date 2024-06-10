#include "ventana.h"
#include "ui_ventana.h"
#include <QPainter>

Ventana::Ventana(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Ventana)
    // llamamos al manager para que descargue la imagen de internet
    , manager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);

    //realizamos la conexion
    connect ( manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_descargaFinalizada(QNetworkReply*)));


    //colocamos la URL de la imagen
    QString sUrl = "https://blogthinkbig.com/wp-content/uploads/sites/4/2021/12/MicrosoftTeams-image-32.jpg?fit=2440%2C900";
    //metodo get nos permite enviar una solicitud hacia el servidor y cuando responde vamos a finished a descargar esa imagen
    manager->get(QNetworkRequest(QUrl(sUrl)));
}

Ventana::~Ventana()
{
    delete ui;
}

void Ventana::paintEvent(QPaintEvent *)
{
    // dibujamos una imagen en una ventana
    QPainter painter(this);


    //si la imagen no es nula, la pinto con painter.drawImage y esta escalada con el ancho y el alto de la ventana
    if( !im.isNull() ){
        painter.drawImage(0,0, im.scaled(this->width(), this->height()));
    }

}

void Ventana::slot_descargaFinalizada(QNetworkReply *reply)
{
    im = QImage::fromData( reply->readAll() );
    this->repaint();
}
