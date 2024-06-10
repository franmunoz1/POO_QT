#include "login.h"
#include "codeeditor.h"
#include <QGridLayout>
#include <QDebug>
#include <QPainter>
#include <QNetworkRequest>

Login::Login(QWidget *parent) : QWidget(parent), imageDownloaded(false)
{
    lUsuario = new QLabel("Usuario:");
    lClave = new QLabel("Clave:");
    leUsuario = new QLineEdit;
    leClave = new QLineEdit;
    leClave->setEchoMode(QLineEdit::Password);
    pbValidar = new QPushButton("Validar");
    networkManager = new QNetworkAccessManager(this);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(lUsuario, 0, 0);
    layout->addWidget(leUsuario, 0, 1);
    layout->addWidget(lClave, 1, 0);
    layout->addWidget(leClave, 1, 1);
    layout->addWidget(pbValidar, 2, 0, 1, 2);

    setLayout(layout);

    connect(pbValidar, SIGNAL(pressed()), this, SLOT(slot_ValidarUsuario()));
    connect(leClave, SIGNAL(returnPressed()), this, SLOT(slot_ValidarUsuario()));

    QNetworkRequest request(QUrl("data:image/jpeg;base64,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"));
    networkManager->get(request);
    connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(imagenDescargada(QNetworkReply*)));
}

Login::~Login()
{
}

void Login::paintEvent(QPaintEvent *event)
{
    QWidget::paintEvent(event);

    if (imageDownloaded)
    {
        QPainter painter(this);
        painter.drawImage(0, 0, backgroundImage.scaled(size()));
    }
}

void Login::slot_ValidarUsuario()
{
    QString usuario = leUsuario->text();
    QString clave = leClave->text();

    if (usuario == "admin" && clave == "123")
    {
        qDebug() << "Usuario valido";

        CodeEditor *editor = new CodeEditor;
        editor->show();

        close();
    }
    else
    {
        qDebug() << "Usuario invalido";
    }
}


void Login::imagenDescargada(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
    {
        QByteArray imageData = reply->readAll();
        if (backgroundImage.loadFromData(imageData))
        {
            imageDownloaded = true;
            update();
        }
    }

    reply->deleteLater();
}

