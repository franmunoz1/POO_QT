#include "ventana.h"
#include <QPainter>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QVBoxLayout>

Ventana::Ventana(QWidget *parent)
    : QWidget(parent), tamanoPincel(5), cambioTamanoPincel(1), colorPincel(Qt::blue)
{
    setFixedSize(400, 400);
    lienzo = QImage(size(), QImage::Format_ARGB32_Premultiplied);
    lienzo.fill(Qt::white);

    // Creamos el QLabel para el tamaño del pincel
    labelTamanoPincel = new QLabel("Tamaño del pincel: 100%", this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(labelTamanoPincel);
    layout->addStretch();

    // Configuramos el layout para la ventana
    setLayout(layout);

    // Actualizamos el texto del label con el tamaño inicial del pincel
    actualizarLabelTamanoPincel();
}

void Ventana::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.drawImage(0, 0, lienzo);
}

void Ventana::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_R)
        colorPincel = Qt::red;
    else if (event->key() == Qt::Key_G)
        colorPincel = Qt::green;
    else if (event->key() == Qt::Key_B)
        colorPincel = Qt::blue;
    else if (event->key() == Qt::Key_Escape)
        limpiarLienzo();

    QWidget::keyPressEvent(event);
}

void Ventana::wheelEvent(QWheelEvent *event)
{
    if (event->angleDelta().y() > 0)
        ampliarPincel();
    else
        reducirPincel();

    QWidget::wheelEvent(event);
}

void Ventana::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        puntoAnterior = event->pos();
        dibujarPunto(puntoAnterior);
    }

    QWidget::mousePressEvent(event);
}

void Ventana::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        dibujarPunto(event->pos());
    }

    QWidget::mouseMoveEvent(event);
}

void Ventana::resizeEvent(QResizeEvent *event)
{
    if (width() > lienzo.width() || height() > lienzo.height()) {
        int newWidth = qMax(width() + 128, lienzo.width());
        int newHeight = qMax(height() + 128, lienzo.height());
        QImage newImage(newWidth, newHeight, QImage::Format_ARGB32_Premultiplied);
        newImage.fill(Qt::white);
        QPainter painter(&newImage);
        painter.drawImage(0, 0, lienzo);
        lienzo = newImage;
    }

    QWidget::resizeEvent(event);
}

void Ventana::dibujarPunto(const QPoint &punto)
{
    QPainter painter(&lienzo);
    painter.setPen(QPen(colorPincel, tamanoPincel, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter.drawLine(puntoAnterior, punto);
    puntoAnterior = punto;
    update();

    // Actualizamos el texto del label con el nuevo tamaño del pincel
    actualizarLabelTamanoPincel();
}

void Ventana::ampliarPincel()
{
    if (cambioTamanoPincel < 10)
        cambioTamanoPincel++;
    tamanoPincel += cambioTamanoPincel;

    // Actualizamos el texto del label con el nuevo tamaño del pincel
    actualizarLabelTamanoPincel();
}

void Ventana::reducirPincel()
{
    if (cambioTamanoPincel < 10)
        cambioTamanoPincel++;
    tamanoPincel -= cambioTamanoPincel;
    if (tamanoPincel < 1)
        tamanoPincel = 1;

    // Actualizamos el texto del label con el nuevo tamaño del pincel
    actualizarLabelTamanoPincel();
}

void Ventana::limpiarLienzo()
{
    lienzo.fill(Qt::white);
    update();
}

void Ventana::actualizarLabelTamanoPincel()
{
    int porcentaje = (tamanoPincel * 100) / 50; // Se asume que el tamaño máximo del pincel es 50
    QString texto = "Tamaño del pincel: <b>" + QString::number(porcentaje) + "%</b>";
    labelTamanoPincel->setText(texto);
    labelTamanoPincel->setStyleSheet("QLabel { color: black; font-size: 16px; }");

}
