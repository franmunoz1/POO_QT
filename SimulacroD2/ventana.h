#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>

class QLabel;
class QPushButton;

class Ventana : public QWidget {
    Q_OBJECT
public:
    explicit Ventana(QWidget *parent = nullptr);

private:
    QLabel *photoLabel;
    QPushButton *prevButton;
    QPushButton *nextButton;
    QList<QUrl> imageUrls;
    int currentIndex;

    void loadImagesFromFile(const QString &fileName);
    void showImage(int index);

private slots:
    void showPrevious();
    void showNext();
};

#endif // VENTANA_H
