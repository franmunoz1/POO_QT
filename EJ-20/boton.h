#ifndef BOTON_H
#define BOTON_H

#include <QWidget>

class Boton : public QWidget
{
    Q_OBJECT

public:
    enum Color {
        Rojo,
        Violeta,
        Naranja,
        Verde,
        Azul,
        Morado
    };

    explicit Boton(const QString &text, Color color, QWidget *parent = nullptr);

signals:
    void signal_clic();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QString buttonText;
    Color currentColor;
};

#endif // BOTON_H
