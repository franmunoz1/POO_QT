#include "ventana.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QDebug>

Ventana::Ventana(QWidget *parent) : QWidget(parent) {
    currentIndex = 0;

    // Cargar las URLs de las imágenes desde el archivo de texto
    loadImagesFromFile("images.txt");

    // Crear la interfaz de usuario
    QVBoxLayout *layout = new QVBoxLayout(this);
    photoLabel = new QLabel(this);
    layout->addWidget(photoLabel);

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    prevButton = new QPushButton("<<", this);
    nextButton = new QPushButton(">>", this);
    connect(prevButton, &QPushButton::clicked, this, &Ventana::showPrevious);
    connect(nextButton, &QPushButton::clicked, this, &Ventana::showNext);
    buttonLayout->addWidget(prevButton);
    buttonLayout->addWidget(nextButton);
    layout->addLayout(buttonLayout);

    // Mostrar la primera imagen
    showImage(currentIndex);
}

void Ventana::loadImagesFromFile(const QString &fileName) {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error al abrir el archivo:" << file.errorString();
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (!line.isEmpty()) {
            imageUrls.append(QUrl(line));
        }
    }

    file.close();
}

void Ventana::showImage(int index) {
    if (index >= 0 && index < imageUrls.size()) {
        QPixmap pixmap(imageUrls[index].toLocalFile());
        photoLabel->setPixmap(pixmap.scaled(photoLabel->size(), Qt::KeepAspectRatio));
    }
}

void Ventana::showPrevious() {
    currentIndex = (currentIndex - 1 + imageUrls.size()) % imageUrls.size();
    showImage(currentIndex);
}

void Ventana::showNext() {
    currentIndex = (currentIndex + 1) % imageUrls.size();
    showImage(currentIndex);
}
