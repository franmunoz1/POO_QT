#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QImage>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrl>
#include <QPushButton>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui {
class Window;
}
QT_END_NAMESPACE

class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

    void get_all_ulrs_from_file();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void downloadFinished(QNetworkReply* reply);
    void slot_next();
    void slot_prev();

private:
    Ui::Window *ui;
    QImage image;
    QNetworkAccessManager *manager;
    QPushButton *button_prev;
    QPushButton *button_next;
    QLabel *img;
    int index;
    QVector<QImage> vec;

};
#endif // WINDOW_H
