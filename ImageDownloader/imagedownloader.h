#ifndef IMAGEDOWNLOADER_H
#define IMAGEDOWNLOADER_H

#include <QWidget>
#include <QImage>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui {
class ImageDownloader;
}
QT_END_NAMESPACE

class ImageDownloader : public QWidget
{
    Q_OBJECT

public:
    ImageDownloader(QWidget *parent = nullptr);
    ~ImageDownloader();

    void setUrl(const QUrl &url);

    const QImage &image() const {
        return m_image;
    }

signals:
    void imageDownloaded(const QImage &image);

private slots:
    void downloadingFinished(QNetworkReply *reply);
    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);

private:
    Ui::ImageDownloader *ui;
    QImage m_image;
    QUrl m_url;
    QNetworkAccessManager m_manager;
    bool m_downloading;
};

#endif // IMAGEDOWNLOADER_H
