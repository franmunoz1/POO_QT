#include "editor.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

Editor::Editor(QWidget *parent) : QWidget(parent)
{
    textEdit = new QTextEdit(this);
    textEdit->setGeometry(20, 20, 300, 200);

    lineEdit = new QLineEdit(this);
    lineEdit->setGeometry(20, 230, 150, 30);

    buscarButton = new QPushButton("Buscar", this);
    buscarButton->setGeometry(180, 230, 90, 30);
    connect(buscarButton, &QPushButton::clicked, this, &Editor::buscarOcurrencias);

    guardarButton = new QPushButton("Guardar", this); // Agregado
    guardarButton->setGeometry(280, 230, 90, 30); // Agregado
    connect(guardarButton, &QPushButton::clicked, this, &Editor::guardarTexto); // Agregado

    resultadoLabel = new QLabel(this);
    resultadoLabel->setGeometry(20, 270, 300, 30);
}

void Editor::buscarOcurrencias()
{
    QString textoBuscar = lineEdit->text();
    QString textoCompleto = textEdit->toPlainText();

    int ocurrencias = textoCompleto.count(textoBuscar);
    resultadoLabel->setText(QString::number(ocurrencias) + " ocurrencias.");
}

void Editor::guardarTexto()
{
    QString nombreArchivo = QFileDialog::getSaveFileName(this, tr("Guardar archivo"), "", tr("Archivos de texto (*.txt)"));
    if (nombreArchivo.isEmpty())
        return; // El usuario canceló el diálogo, no hacemos nada

    QFile file(nombreArchivo);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QString texto = textEdit->toPlainText();
        QTextStream out(&file);
        out << texto;
        file.close();
        resultadoLabel->setText("Archivo guardado como: " + nombreArchivo);
    }
    else
    {
        resultadoLabel->setText("Error al guardar el archivo.");
    }
}
