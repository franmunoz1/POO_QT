#include "login.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>
#include <QApplication>
#include <QPixmap>
#include <QPainter>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QEventLoop>
#include <QDebug>

LoginWidget::LoginWidget(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupSignalsAndSlots();
}

void LoginWidget::validateUser() {
    QString username = usernameEdit->text();
    QString password = passwordEdit->text();

    if (username == "44579795" && password == "795") {
        QLabel *label = new QLabel; // Crear label aquí
        QString avatarUrl = "https://iili.io/JcKKMAv.png"; // URL de la imagen en la nube
        LoadAvatar(avatarUrl, *label); // Ahora puedes usar label
    } else {
        passwordEdit->clear();
        ++failedAttempts;
        if (failedAttempts >= 3) {
            QMessageBox::critical(this, "Error", "Demasiados intentos fallidos. La aplicación se cerrará.");
            QApplication::quit();
        }
    }
}

void LoadAvatar(const QString &strAvatarUrl, QLabel &label)
{
    // Tamaño del cuadrado
    int squareSize = 150;

    QUrl url(strAvatarUrl);
    QNetworkAccessManager manager;
    QEventLoop loop;

    QNetworkReply *reply = manager.get(QNetworkRequest(url));
    QObject::connect(reply, &QNetworkReply::finished, &loop, [&reply, &label, &loop, squareSize]() {
        if (reply->error() == QNetworkReply::NoError)
        {
            QByteArray imageData = reply->readAll();
            QPixmap originalPixmap;
            originalPixmap.loadFromData(imageData);
            if (!originalPixmap.isNull())
            {
                // Redimensionar la imagen para que tenga aproximadamente 100x100 píxeles
                QPixmap scaledPixmap = originalPixmap.scaled(QSize(100, 100), Qt::KeepAspectRatio, Qt::SmoothTransformation);

                // Calcular las coordenadas para centrar la imagen en el cuadrado
                int x = (squareSize - scaledPixmap.width()) / 2;
                int y = (squareSize - scaledPixmap.height()) / 2;

                // Crear un QPixmap para el cuadrado
                QPixmap squarePixmap(squareSize, squareSize);
                squarePixmap.fill(Qt::transparent);

                // Crear un QPainter para dibujar en el QPixmap del cuadrado
                QPainter painter(&squarePixmap);
                painter.setRenderHint(QPainter::Antialiasing, true);

                // Dibujar el cuadrado alrededor de la imagen
                painter.setPen(Qt::red); // Color del cuadrado (puedes cambiarlo según lo necesites)
                painter.drawRect(0, 0, squareSize - 1, squareSize - 1);

                // Dibujar la imagen centrada en el cuadrado
                painter.drawPixmap(x, y, scaledPixmap);

                // Establecer la imagen en el QLabel
                label.clear();
                label.setPixmap(squarePixmap);
                label.show();
            }
            else
            {
                qDebug() << "La imagen está vacía o no se pudo cargar correctamente.";
            }
        }
        else
        {
            qDebug() << "Error al descargar la imagen:" << reply->errorString();
        }
        loop.quit();
    });

    loop.exec();
}




void LoginWidget::setupUI() {
    QVBoxLayout *layout = new QVBoxLayout(this);
    QGridLayout *gridLayout = new QGridLayout;

    QLabel *titleLabel = new QLabel("Login");
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    titleLabel->setFont(QFont("Arial", 16, QFont::Bold));

    QLabel *usernameLabel = new QLabel("Usuario:");
    usernameEdit = new QLineEdit;

    QLabel *passwordLabel = new QLabel("Contraseña:");
    passwordEdit = new QLineEdit;
    passwordEdit->setEchoMode(QLineEdit::Password);

    gridLayout->addWidget(usernameLabel, 0, 0);
    gridLayout->addWidget(usernameEdit, 0, 1);
    gridLayout->addWidget(passwordLabel, 1, 0);
    gridLayout->addWidget(passwordEdit, 1, 1);

    QPushButton *loginButton = new QPushButton("Ingresar");
    layout->addLayout(gridLayout);
    layout->addWidget(loginButton, 0, Qt::AlignBottom | Qt::AlignRight);

    connect(loginButton, &QPushButton::clicked, this, &LoginWidget::validateUser);

    setFixedSize(250, 120);
    setWindowTitle("Login");
}

void LoginWidget::setupSignalsAndSlots() {
    connect(passwordEdit, &QLineEdit::returnPressed, this, &LoginWidget::validateUser);
}
