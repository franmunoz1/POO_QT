#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include <QLabel>

class QLineEdit;

class LoginWidget : public QWidget {
    Q_OBJECT

public:
    LoginWidget(QWidget *parent = nullptr);

signals:
    void loginSuccessful();

private slots:
    void validateUser();

private:
    void setupUI();
    void setupSignalsAndSlots();

    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    int failedAttempts = 0;
};

// Declaración de la función LoadAvatar
void LoadAvatar(const QString &strAvatarUrl, QLabel &label);

#endif // LOGIN_H
