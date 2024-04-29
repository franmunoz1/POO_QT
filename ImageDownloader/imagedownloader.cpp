#include "imagedownloader.h"
#include "ui_imagedownloader.h"

ImageDownloader::ImageDownloader(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageDownloader),
    m_downloading(false)
{
    ui->setupUi(this);

    connect(&m_manager, &QNetworkAccessManager::finished, this, &ImageDownloader::downloadingFinished);
}

ImageDownloader::~ImageDownloader()
{
    delete ui;
}

void ImageDownloader::setUrl(const QUrl &url)
{
    m_url = url;
}

void ImageDownloader::download()
{
    if (m_downloading || m_url.isEmpty())
        return;

    QNetworkRequest request(m_url);
    QNetworkReply *reply = m_manager.get(request);
    connect(reply, &QNetworkReply::downloadProgress, this, &ImageDownloader::downloadProgress);
    m_downloading = true;
}

void ImageDownloader::downloadingFinished(QNetworkReply *reply)
{
    m_downloading = false;
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray data = reply->readAll();
        m_image.loadFromData(data);
        emit imageDownloaded(m_image);
    }
    reply->deleteLater();
}

void ImageDownloader::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if (bytesTotal > 0)
        ui->progressBar->setValue(100 * bytesReceived / bytesTotal);
    else
        ui->progressBar->setValue(0);
}
