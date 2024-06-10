#include "codeeditor.h"
#include <QFile>
#include <QTextStream>
#include <QFileDialog>
#include <QDir>
#include <QDebug>


CodeEditor::CodeEditor(QWidget *parent) : QWidget(parent)
{
    textEdit = new QTextEdit(this);
    saveButton = new QPushButton("Guardar", this);
    loadButton = new QPushButton("Cargar", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(textEdit);
    layout->addWidget(saveButton);
    layout->addWidget(loadButton);

    setLayout(layout);

    connect(saveButton, SIGNAL(clicked()), this, SLOT(guardarCodigo()));
    connect(loadButton, SIGNAL(clicked()), this, SLOT(cargarCodigo()));

}

CodeEditor::~CodeEditor()
{
    // Destructor
}

void CodeEditor::guardarCodigo()
{
    QString codigo = textEdit->toPlainText();
    QString fileName = QFileDialog::getSaveFileName(this, "Guardar código", QDir::homePath(), "Archivos de texto (*.txt)");
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Error al abrir el archivo para escribir";
        return;
    }

    QTextStream out(&file);
    out << codigo;
    file.close();
}


void CodeEditor::cargarCodigo()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Cargar código", QDir::homePath(), "Archivos de texto (*.txt)");

    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Error al abrir el archivo para leer";
        return;
    }

    QTextStream in(&file);
    QString codigo = in.readAll();

    file.close();

    textEdit->setPlainText(codigo);
}
