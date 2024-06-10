#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>

QT_BEGIN_NAMESPACE
namespace Ui { class Login; }
QT_END_NAMESPACE

class Login : public QWidget
{
    Q_OBJECT

public:
    Login(QWidget *parent = nullptr);
    ~Login();

private slots:
    void slot_make_request();
    void slot_login_user(QNetworkReply* reply);

private:
    Ui::Login *ui;
    QNetworkAccessManager *manager;
};

#endif // LOGIN_H
