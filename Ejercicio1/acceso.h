#ifndef ACCESO_H
#define ACCESO_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include "ventana.h"

class Acceso : public QWidget
{
    Q_OBJECT

public:
    explicit Acceso(QWidget *parent = nullptr);
    ~Acceso();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void slot_ValidarUsuario();
    void imagenDescargada(QNetworkReply *reply);

private:
    QLabel *lUsuario;
    QLabel *lClave;
    QLineEdit *leUsuario;
    QLineEdit *leClave;
    QPushButton *pbValidar;
    QNetworkAccessManager *networkManager;
    QImage backgroundImage;
    bool imageDownloaded;
    int failedAttemp;
    Ventana * ventana;
};

#endif // ACCESO_H
