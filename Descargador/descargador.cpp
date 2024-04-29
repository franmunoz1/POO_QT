#include "descargador.h"
#include <QPainter>
#include <QUrl>

Descargador::Descargador(QWidget *parent) : QWidget(parent)
{
    urlLineEdit = new QLineEdit("https://images.pexels.com/photos/417074/pexels-photo-417074.jpeg");
    urlLineEdit->setReadOnly(true);

    descargarButton = new QPushButton("Descargar");
    connect(descargarButton, SIGNAL(clicked()), this, SLOT(iniciarDescarga()));

    progresoBar = new QProgressBar;
    progresoBar->setStyleSheet("QProgressBar { background-color: white; border: 2px solid grey; border-radius: 5px; }"
                               "QProgressBar::chunk { background-color: green; width: 20px; }");

    networkManager = new QNetworkAccessManager(this);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(onDescargaFinalizada()));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(urlLineEdit, 0, 0, 1, 1);
    layout->addWidget(descargarButton, 0, 1, 1, 1);
    layout->addWidget(progresoBar, 1, 0, 1, 2, Qt::AlignBottom);
    setLayout(layout);
}

void Descargador::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    QPainter painter(this);
    if (!imagen.isNull())
        painter.drawImage(0, 0, imagen);
}

void Descargador::iniciarDescarga()
{
    QUrl url(urlLineEdit->text());
    reply = networkManager->get(QNetworkRequest(url));
    connect(reply, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(onDescargaProgreso(qint64, qint64)));
}

void Descargador::onDescargaProgreso(qint64 bytesRecibidos, qint64 bytesTotales)
{
    if (bytesTotales > 0)
    {
        int progreso = static_cast<int>((bytesRecibidos * 100) / bytesTotales);
        progresoBar->setValue(progreso);
        emit progresoDescarga(progreso);
    }
}

void Descargador::onDescargaFinalizada()
{
    if (reply->error() == QNetworkReply::NoError)
    {
        imagenData = reply->readAll();
        imagen.loadFromData(imagenData);
        update();
        emit downloadFinished(imagen);
    }
    else
    {
        qDebug() << "Error en la descarga:" << reply->errorString();
    }
    reply->deleteLater();
}
