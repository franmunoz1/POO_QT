#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

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
};

#endif // LOGIN_H
