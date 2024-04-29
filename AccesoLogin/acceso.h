// acceso.h

#ifndef ACCESO_H
#define ACCESO_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QImage>
#include <QPaintEvent>
#include "ventana.h" // Incluir la clase de la ventana

QT_BEGIN_NAMESPACE
namespace Ui { class Acceso; }
QT_END_NAMESPACE

class Acceso : public QWidget
{
    Q_OBJECT

public:
    Acceso(QWidget *parent = nullptr);
    ~Acceso();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void slot_validar();
    void imagenDescargada(QNetworkReply *reply);

private:
    Ui::Acceso *ui;
    QImage backgroundImage;
    bool imageDownloaded;
    int failedAttemp;
    QNetworkAccessManager *networkManager;
};

#endif // ACCESO_H
