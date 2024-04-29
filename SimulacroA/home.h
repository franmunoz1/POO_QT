#ifndef HOME_H
#define HOME_H

#include <QMainWindow>
#include <QLabel>
#include <QPixmap>

class Home : public QMainWindow {
    Q_OBJECT

public:
    Home(const QString &imagePath, QWidget *parent = nullptr);

public slots:
    void showHomeWindow();

private:
    QPixmap image;
    QLabel *imageLabel;
};

#endif // HOME_H
