#ifndef DESCARGADOR_H
#define DESCARGADOR_H

#include <QWidget>
#include <QImage>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QProgressBar>
#include <QLineEdit>
#include <QPushButton>
#include <QGridLayout>
#include <QPalette>

class Descargador : public QWidget
{
    Q_OBJECT
public:
    explicit Descargador(QWidget *parent = nullptr);

signals:
    void downloadCompleted(const QImage& image);
    void downloadProgress(int progress);

private slots:
    void startDownload();
    void onDownloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void onDownloadFinished();

private:
    QLineEdit *urlLineEdit;
    QPushButton *downloadButton;
    QProgressBar *progressBar;
    QNetworkAccessManager *manager;
    QNetworkReply *downloadReply;
    QByteArray data;

    void displayImage(const QImage& image);
};

#endif // DESCARGADOR_H
