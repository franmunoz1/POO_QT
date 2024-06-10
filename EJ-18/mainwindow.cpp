#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , networkManager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    connect(ui->urlLineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_urlLineEdit_returnPressed);
    connect(networkManager, &QNetworkAccessManager::finished, this, &MainWindow::onFinished);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_urlLineEdit_returnPressed()
{
    QString url = ui->urlLineEdit->text();
    if (!url.isEmpty()) {
        QNetworkRequest request(QUrl(url));
        networkManager->get(request);
    }
}

void MainWindow::onFinished(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QString html = reply->readAll();
        ui->htmlTextEdit->setPlainText(html);
    } else {
        QMessageBox::warning(this, "Error", "Failed to fetch the URL.");
    }
    reply->deleteLater();
}
