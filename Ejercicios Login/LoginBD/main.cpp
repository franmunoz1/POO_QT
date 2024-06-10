#include "admindb.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AdminDB w;
    w.show();
    return a.exec();
}
