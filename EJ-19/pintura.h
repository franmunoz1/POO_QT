#ifndef PINTURA_H
#define PINTURA_H

#include <QWidget>
#include <QLabel>

class Pintura : public QWidget
{
    Q_OBJECT

public:
    Pintura(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    QImage lienzo;
    QPoint puntoAnterior;
    QColor colorPincel;
    int tamanoPincel;
    int cambioTamanoPincel;
    QLabel *labelTamanoPincel;

    void dibujarPunto(const QPoint &punto);
    void ampliarPincel();
    void reducirPincel();
    void limpiarLienzo();
    void actualizarLabelTamanoPincel();
};

#endif // PINTURA_H
