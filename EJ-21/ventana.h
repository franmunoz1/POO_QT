#ifndef VENTANA_H
#define VENTANA_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

class Ventana : public QWidget {
    Q_OBJECT

public:
    explicit Ventana(QWidget *parent = nullptr);
    ~Ventana();

signals:
    void backToLogin();

private slots:
    void handleBackButton();

private:
    QPushButton *backButton;
};

#endif // VENTANA_H
