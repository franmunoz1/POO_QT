#include "imagedownloader.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageDownloader w;
    w.show();
    return a.exec();
}
