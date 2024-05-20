#include <QApplication>
#include <QDir>
#include "adminDB.h"

int main( int argc, char** argv )  {
    QApplication a( argc, argv );

    qDebug() << QDir::currentPath();

    AdminDB adminDB;
    if (adminDB.conectar( "/Users/franciscomunoz/Desktop/db.sqlite" ) )
        qDebug() << "Conexion exitosa";
    else
        qDebug() << "Conexion NO exitosa";

    return 0;
}
