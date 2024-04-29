#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QImage>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void slot_validar();
    void imagenDescargada(QNetworkReply *reply);

private:
    Ui::Login *ui;
    QImage backgroundImage;
    bool imageDownloaded;
    int failedAttemp;
    QNetworkAccessManager *networkManager;
};

#endif // LOGIN_H
