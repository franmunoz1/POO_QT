// ventana.h
#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>
#include <QImage>
#include <QPainter>

class Ventana : public QWidget
{
    Q_OBJECT

public:
    Ventana(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QImage imagen;
};

#endif // VENTANA_H
