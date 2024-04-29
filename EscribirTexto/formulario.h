// formulario.h
#ifndef FORMULARIO_H
#define FORMULARIO_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Formulario; }
QT_END_NAMESPACE

class Formulario : public QWidget
{
    Q_OBJECT

public:
    explicit Formulario(QWidget *parent = nullptr);
    ~Formulario();

signals:
    void enviarClicked();

private slots:
    void on_pbEnviar_clicked();
    void enviarTexto();

private:
    Ui::Formulario *ui;
};

#endif // FORMULARIO_H
