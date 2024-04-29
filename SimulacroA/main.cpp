#include <QApplication>
#include "login.h"
#include "home.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    // Crear instancias de LoginWidget y Home
    LoginWidget loginWidget;
    Home home("C:/Users/Alesso/Desktop/7780607.png");

    // Conectar la señal loginSuccessful de LoginWidget con la función showHomeWindow de Home
    QObject::connect(&loginWidget, &LoginWidget::loginSuccessful, &home, &Home::showHomeWindow);

    // Mostrar la ventana de inicio de sesión
    loginWidget.show();

    return a.exec();
}
