#include "ventana.h"
#include "ui_ventana.h"

Ventana::Ventana(QString usuario, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ventana)
{
    ui->setupUi(this);
    ui->lBienvenida->setText("Hola " + usuario);
}

Ventana::~Ventana()
{
    delete ui;
}
