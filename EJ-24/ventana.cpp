#include "ventana.h"
#include "ui_ventana.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QPainter>
#include <QRegularExpression>

Ventana::Ventana(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Ventana)
{
    ui->setupUi(this);
    connect(ui->btnDescargar, &QPushButton::clicked, this, &Ventana::on_btnDescargar_clicked);
    connect(ui->btnCargarImagen, &QPushButton::clicked, this, &Ventana::on_btnCargarImagen_clicked);
}

Ventana::~Ventana()
{
    delete ui;
}

void Ventana::on_btnDescargar_clicked()
{
    QString urlStr = ui->leUrl->text();
    QUrl url(urlStr);

    QNetworkAccessManager manager;
    QNetworkReply *reply = manager.get(QNetworkRequest(url));
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QString html = reply->readAll();
    ui->teHtml->setPlainText(html);

    QRegularExpression re("<img[^>]+src=\"([^\"]+)\"|<link[^>]+href=\"([^\"]+)\"|<script[^>]+src=\"([^\"]+)\"");
    QRegularExpressionMatchIterator it = re.globalMatch(html);
    QStringList urls;
    while (it.hasNext()) {
        QRegularExpressionMatch match = it.next();
        if (match.captured(1).isEmpty()) {
            urls << match.captured(2) << match.captured(3);
        } else {
            urls << match.captured(1);
        }
    }

    QString saveDir = QFileDialog::getExistingDirectory(this, tr("Seleccionar Directorio"), "");
    if (saveDir.isEmpty()) return;

    foreach (const QString &urlPath, urls) {
        if (urlPath.isEmpty()) continue;
        QUrl resourceUrl = url.resolved(QUrl(urlPath));
        QNetworkReply *resourceReply = manager.get(QNetworkRequest(resourceUrl));
        connect(resourceReply, &QNetworkReply::finished, [&]() {
            QString filePath = saveDir + "/" + resourceUrl.fileName();
            QFile file(filePath);
            if (file.open(QIODevice::WriteOnly)) {
                file.write(resourceReply->readAll());
                file.close();
            }
            resourceReply->deleteLater();
        });
    }
}

void Ventana::on_btnCargarImagen_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Seleccionar Imagen"), "", tr("Images (*.png *.xpm *.jpg *.jpeg)"));
    if (!filePath.isEmpty()) {
        image.load(filePath);
        update(); // Trigger paintEvent to redraw the image
    }
}

void Ventana::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);
    if (!image.isNull()) {
        QPainter painter(this);
        painter.drawImage(10, 10, image); // Adjust the position as needed
    }
}
