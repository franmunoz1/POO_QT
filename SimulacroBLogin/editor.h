// editor.h
#ifndef EDITOR_H
#define EDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class Editor : public QWidget
{
    Q_OBJECT

public:
    explicit Editor(QWidget *parent = nullptr);

private slots:
    void buscarOcurrencias();
    void guardarTexto();

private:
    QTextEdit *textEdit;
    QLineEdit *lineEdit;
    QPushButton *buscarButton;
    QPushButton *guardarButton; // Agregado
    QLabel *resultadoLabel;
};

#endif // EDITOR_H
