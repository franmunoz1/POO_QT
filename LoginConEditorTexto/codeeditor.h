#ifndef CODEEDITOR_H
#define CODEEDITOR_H

#include <QWidget>
#include <QTextEdit>
#include <QPushButton>
#include <QBoxLayout>

class CodeEditor : public QWidget
{
    Q_OBJECT

public:
    explicit CodeEditor(QWidget *parent = nullptr);
    ~CodeEditor();

private:
    QTextEdit *textEdit;
    QPushButton *saveButton;
    QPushButton *loadButton;

private slots:
    void guardarCodigo();
    void cargarCodigo();
};

#endif // CODEEDITOR_H
