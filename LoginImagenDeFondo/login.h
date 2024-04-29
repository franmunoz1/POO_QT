#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "ventana.h"
#include <QImage>
#include <QtNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>

QT_BEGIN_NAMESPACE
namespace Ui {
class Login;
}
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

protected:
    void paintEvent(QPaintEvent *);

private:
    Ui::Login *ui;
    Ventana * ventana;

    QImage im;
    QNetworkAccessManager *manager;

private slots:
    void slot_validar();

    void slot_descargaFinalizada(QNetworkReply *);
};
#endif // LOGIN_H
