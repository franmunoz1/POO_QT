#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QImage>
#include <QPaintEvent>

namespace Ui {
class Ventana;
}

class Ventana : public QWidget
{
    Q_OBJECT

public:
    explicit Ventana(QWidget *parent = nullptr);
    ~Ventana();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void on_btnDescargar_clicked();
    void on_btnCargarImagen_clicked();

private:
    Ui::Ventana *ui;
    QImage image;
};

#endif // VENTANA_H
