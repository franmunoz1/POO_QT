#ifndef REGISTRO_H
#define REGISTRO_H

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>

class Registro : public QWidget
{
    Q_OBJECT

public:
    explicit Registro(QWidget *parent = nullptr);

private slots:
    void manejarRegistro();

private:
    QLineEdit *nombreUsuarioLineEdit;
    QLineEdit *contrasenaLineEdit;
    QPushButton *botonRegistro;
};

#endif // REGISTRO_H
