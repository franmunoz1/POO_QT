#include "login.h"
#include "ui_login.h"

#include <QJsonObject>
#include <QJsonDocument>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QDebug>

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login)
    , manager(new QNetworkAccessManager(this))
{
    ui->setupUi(this);
    connect(ui->pbLogin, SIGNAL(clicked()), this, SLOT(slot_make_request()));
}

Login::~Login()
{
    delete ui;
}

void Login::slot_make_request()
{
    QUrl url("http://127.0.0.1:8000/validar-usuario");

    QUrlQuery query;
    query.addQueryItem("username", ui->leUser->text());
    query.addQueryItem("password", ui->lePassword->text());
    url.setQuery(query);

    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    manager->post(request, QByteArray());
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(slot_login_user(QNetworkReply*)));
}

void Login::slot_login_user(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QByteArray response = reply->readAll();
        QJsonObject json = QJsonDocument::fromJson(response).object();
        qDebug() << "Response:" << json;
        if (json["success"].toString() == "true") {
            qDebug() << json["user"].toString();
            qDebug() << json["password"].toString();
        } else {
            qDebug() << "Login failed";
        }
    } else {
        qDebug() << "Network error:" << reply->errorString();
    }
    reply->deleteLater();
}
