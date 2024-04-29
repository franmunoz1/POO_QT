// formulario.cpp
#include "formulario.h"
#include "ui_formulario.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QGridLayout>
#include <QDebug>

Formulario::Formulario(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Formulario)
{
    ui->setupUi(this);

    // Conectar la señal clicked del PushButton con el slot on_pbEnviar_clicked()
    connect(ui->pbEnviar,SIGNAL(pressed()), this, SLOT(on_pbEnviar_clicked()));
}

Formulario::~Formulario()
{
    delete ui;
}

void Formulario::on_pbEnviar_clicked()
{
    emit enviarClicked();
}

void Formulario::enviarTexto()
{
    QString texto = ui->leTexto->text();
    QFile archivo("/Users/franciscomunoz/Desktop/POO_QT/EscribirTexto/datos.txt");
    if (archivo.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QTextStream out(&archivo);
        out << texto;
        archivo.close();
        QMessageBox::information(this, "Éxito", "Texto enviado correctamente");
    }
    else
    {
        QMessageBox::critical(this, "Error", "No se pudo abrir el archivo");
    }
}
