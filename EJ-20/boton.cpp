#include "boton.h"
#include <QPainter>
#include <QMouseEvent>

// Colores

//color = QColor(255, 0, 0); // Rojo

//color = QColor(255, 140, 0); // Naranja

//olor = QColor(0, 255, 0); // Verde

//color = QColor(0, 0, 255); // Azul

//color = QColor(128, 0, 128); // Morado


Boton::Boton(const QString &text, Color color, QWidget *parent)
    : QWidget(parent), buttonText(text), currentColor(color)
{
    setFixedSize(300, 50); // Tamaño fijo para el botón
}

void Boton::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    QColor color;

    switch (currentColor) {
    case Rojo:
        color = QColor(255, 0, 0); // Rojo
        break;
    case Violeta:
        color = QColor(105,85,147); // Violeta
        break;
    case Naranja:
        color = QColor(255, 140, 0); // Naranja
        break;
    case Verde:
        color = QColor(0, 255, 0); // Verde
        break;
    case Azul:
        color = QColor(0, 0, 255); // Azul
        break;
    case Morado:
        color = QColor(128, 0, 128); // Morado
        break;
    }

    painter.fillRect(rect(), color);
    painter.setPen(Qt::white);
    painter.setFont(QFont("Arial", 16));
    painter.drawText(rect(), Qt::AlignLeft, buttonText);
}

void Boton::mousePressEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    emit signal_clic();
}
