#include "window.h"
#include "ui_window.h"
#include <QFile>
#include <QDebug>
#include <QMessageBox>
#include <QPainter>
#include <QBoxLayout>
#include <QGridLayout>
#include <QLabel>

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
    , manager (new QNetworkAccessManager(this))
    , index(0)
{
    ui->setupUi(this);
    get_all_ulrs_from_file();
    QGridLayout *layout = new QGridLayout;

    img = new QLabel();
    button_prev = new QPushButton("Anterior", this);
    button_next = new QPushButton("Siguiente", this);

    layout->addWidget(img, 0, 0);
    layout->setRowStretch(0, 0);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(button_prev);
    buttonLayout->addWidget(button_next);
    layout->addLayout(buttonLayout, 1, 0, 1, 2);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(downloadFinished(QNetworkReply*)));
    connect(button_next, SIGNAL(pressed()), this, SLOT(slot_next()));
    connect(button_prev, SIGNAL(pressed()), this, SLOT(slot_prev()));
}

Window::~Window()
{
    delete ui;
}

void Window::get_all_ulrs_from_file()
{
    QFile file("text.txt");
    if(!file.open(QIODevice::ReadOnly)) {
        QMessageBox::information(0, "error", file.errorString());
    }

    QTextStream in(&file);

    while(!in.atEnd()) {
        QString line = in.readLine();
        qDebug() << line;
        manager->get(QNetworkRequest(QUrl(line)));
    }

    file.close();
}

void Window::paintEvent(QPaintEvent *)
{
    QPainter p(this);

    if (!vec.empty()) {
        p.drawImage(0, 0, vec.at(index).scaled(this->width(), this->height()));
    }
}

void Window::downloadFinished(QNetworkReply *reply)
{
    QImage downloaded_image = QImage::fromData(reply->readAll());
    vec.push_back(downloaded_image);
    qDebug() << vec.size();
    if (vec.size() == 1) {
        repaint();
    }
}


void Window::slot_next()
{
    if (index < vec.size() - 1) {
        index++;
        repaint();
    }
}

void Window::slot_prev()
{
    if (index > 0) {
        index--;
        repaint();
    }
}
