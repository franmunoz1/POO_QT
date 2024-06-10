#include "ventana.h"
#include "ui_ventana.h"
#include <QRegularExpression>
#include <QDebug>
#include <QNetworkReply>
#include <QUrl>
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QPainter>

Ventana::Ventana(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ventana),
    downloadDirectory(QDir::homePath())
{
    ui->setupUi(this);

    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
    connect(ui->pbUrl, SIGNAL(clicked()), this, SLOT(slot_pbUrl_clicked()));
    connect(ui->pbSelectDirectory, SIGNAL(clicked()), this, SLOT(slot_selectDirectory_clicked()));
    connect(ui->pbImage, SIGNAL(clicked()), this, SLOT(slot_selectImage_clicked()));
}

Ventana::~Ventana()
{
    delete ui;
}

void Ventana::replyFinished(QNetworkReply *reply)
{
    qDebug() << reply;
    if (reply->error()) {
        ui->leText->setPlainText(reply->errorString());
        return;
    }
    QString HTML = reply->readAll();
    ui->leText->setPlainText(HTML);

    QString htmlFileName = downloadDirectory + "/index.html";
    QFile htmlFile(htmlFileName);
    if (htmlFile.open(QIODevice::WriteOnly)) {
        htmlFile.write(HTML.toUtf8());
        htmlFile.close();
        qDebug() << "Saved HTML to" << htmlFileName;
    } else {
        qDebug() << "Failed to save HTML to" << htmlFileName;
    }

    QUrl baseUrl = reply->url();

    QRegularExpression urlRegex(R"((https?://[^\s'"]+\.(?:js|css))|(?:href|src)=['"]([^'"]+\.(?:js|css))['"])");
    QRegularExpressionMatchIterator i = urlRegex.globalMatch(HTML);

    while (i.hasNext()) {
        QRegularExpressionMatch match = i.next();
        QString url = match.captured(1);
        if (url.isEmpty()) {
            url = match.captured(2);
        }
        QUrl fullUrl = baseUrl.resolved(url);
        if (fullUrl.isValid() && (fullUrl.scheme() == "http" || fullUrl.scheme() == "https")) {
            qDebug() << "Found URL:" << fullUrl.toString();
            downloadFile(fullUrl.toString());
        } else {
            qDebug() << "Invalid URL:" << fullUrl.toString();
        }
    }
}

void Ventana::slot_pbUrl_clicked() {
    QNetworkRequest request(QUrl(ui->leUrl->text()));
    manager.get(request);
}

void Ventana::slot_selectDirectory_clicked() {
    QString dir = QFileDialog::getExistingDirectory(this, tr("Select Download Directory"),
                                                    QDir::homePath(),
                                                    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    if (!dir.isEmpty()) {
        downloadDirectory = dir;
        qDebug() << "Download directory set to:" << downloadDirectory;
    }
}

void Ventana::slot_selectImage_clicked() {
    QString fileName = QFileDialog::getOpenFileName(this,
                                                    tr("Select Image"),
                                                    QDir::homePath(),
                                                    tr("Images (*.png *.jpg *.jpeg *.bmp *.gif)"));
    if (!fileName.isEmpty()) {
        image.load(fileName);
        update();
    }
}

void Ventana::downloadFile(const QString &urlString)
{
    QUrl url(urlString);
    QNetworkRequest request(url);
    QNetworkReply *reply = manager.get(request);
    connect(reply, &QNetworkReply::finished, this, [this, reply, url]() {
        if (reply->error()) {
            qDebug() << "Error downloading" << url.toString() << ":" << reply->errorString();
        } else {
            qDebug() << "Downloaded" << url.toString() << "successfully.";
            // Guardar el archivo descargado en disco
            QString filePath = downloadDirectory + "/" + url.fileName();
            QFile file(filePath);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(reply->readAll());
                file.close();
                qDebug() << "Saved" << url.fileName() << "to" << filePath;
            } else {
                qDebug() << "Failed to save" << url.fileName();
            }
        }
        reply->deleteLater();
    });
}

void Ventana::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if (!image.isNull()) {
        QPainter painter(this);
        painter.drawImage(0, 0, image, Qt::KeepAspectRatioByExpanding);
    }
}
