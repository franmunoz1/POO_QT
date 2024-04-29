#include "home.h"

Home::Home(const QString &imagePath, QWidget *parent) : QMainWindow(parent) {
    setFixedSize(400, 300);
    setWindowTitle("Home");


    image.load(imagePath);


    imageLabel = new QLabel(this);
    imageLabel->setPixmap(image);


    imageLabel->setFixedSize(image.size());


    setCentralWidget(imageLabel);
}

void Home::showHomeWindow() {
    show();
}
