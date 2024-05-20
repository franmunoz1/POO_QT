#include <QApplication>
#include "ventana.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Ventana w;
    w.show();
    return a.exec();
}
