// ventana.cpp
#include "ventana.h"

Ventana::Ventana(QWidget *parent) : QWidget(parent)
{
    // Cargar la imagen desde una URL (aquí utilizamos una imagen de prueba)
    imagen.load("https://www.example.com/ejemplo-imagen.png");
    // Redimensionar la ventana para que coincida con el tamaño de la imagen
    resize(imagen.size());
}

void Ventana::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    // Creamos un objeto QPainter para dibujar
    QPainter painter(this);
    // Dibujamos la imagen en las coordenadas (0, 0)
    painter.drawImage(0, 0, imagen);
}
