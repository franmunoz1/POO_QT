#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include "login.h"
#include "ventana.h"

class Manager : public QObject {
    Q_OBJECT

public:
    Manager();
    ~Manager();

private:
    Login *login;
    Ventana *ventana;
};

#endif // MANAGER_H
