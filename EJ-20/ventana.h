#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>

class Ventana : public QWidget
{
    Q_OBJECT

public:
    explicit Ventana(QWidget *parent = nullptr);
    ~Ventana();

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // VENTANA_H
