#include "descargador.h"
#include <QPainter>
#include <QUrl>

Descargador::Descargador(QWidget *parent) : QWidget(parent)
{
    urlLineEdit = new QLineEdit("https://images.pexels.com/photos/417074/pexels-photo-417074.jpeg");
    urlLineEdit->setReadOnly(true);

    downloadButton = new QPushButton("Download");
    connect(downloadButton, &QPushButton::clicked, this, &Descargador::startDownload);

    progressBar = new QProgressBar;

    manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, &Descargador::onDownloadFinished);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(urlLineEdit, 0, 0, 1, 1);
    layout->addWidget(downloadButton, 0, 1, 1, 1);
    layout->addWidget(progressBar, 1, 0, 1, 2, Qt::AlignBottom); // Aligned to the bottom
    setLayout(layout);
}

void Descargador::startDownload()
{
    QUrl url(urlLineEdit->text());
    downloadReply = manager->get(QNetworkRequest(url));
    connect(downloadReply, &QNetworkReply::downloadProgress, this, &Descargador::onDownloadProgress);
}

void Descargador::displayImage(const QImage& image)
{
    QPalette palette;
    palette.setBrush(this->backgroundRole(), QBrush(image));
    this->setPalette(palette);
}



void Descargador::onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if (bytesTotal > 0)
    {
        int progress = (bytesReceived * 100) / bytesTotal;
        progressBar->setValue(progress);
        emit downloadProgress(progress);
    }
}




void Descargador::onDownloadFinished()
{
    if (downloadReply->error() == QNetworkReply::NoError)
    {
        data = downloadReply->readAll();
        QImage image;
        image.loadFromData(data);
        displayImage(image);
        emit downloadCompleted(image);
    }
    else
    {
        qDebug() << "Error during download:" << downloadReply->errorString();
    }
    downloadReply->deleteLater();
}

