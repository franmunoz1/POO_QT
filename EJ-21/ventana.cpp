#include "ventana.h"

Ventana::Ventana(QWidget *parent) : QWidget(parent) {
    backButton = new QPushButton("Volver", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(backButton);

    connect(backButton, &QPushButton::clicked, this, &Ventana::handleBackButton);
}

Ventana::~Ventana() {}

void Ventana::handleBackButton() {
    emit backToLogin();
}
