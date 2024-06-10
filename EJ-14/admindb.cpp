#include "admindb.h"
#include <QCryptographicHash>

AdminDB::AdminDB(QObject *parent) : QObject(parent) {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/Users/franciscomunoz/Desktop/POO_QT/EJ-14/db.sqlite");

    if (!db.open()) {
        qDebug() << "Error: no se pudo conectar a la base de datos.";
    } else {
        qDebug() << "Conexión exitosa con la base de datos.";
    }
}

AdminDB::~AdminDB() {
    db.close();
}

QStringList AdminDB::validarUsuario(const QString &tabla, const QString &usuario, const QString &clave) {
    QStringList datosPersonales;

    if (!db.isOpen())
        return datosPersonales;

    QSqlQuery query(db);
    QString claveMd5 = QCryptographicHash::hash(clave.toUtf8(), QCryptographicHash::Md5).toHex();

    query.exec("SELECT nombre, apellido FROM " + tabla + " WHERE usuario = '" + usuario + "' AND clave = '" + claveMd5 + "'");

    while (query.next()) {
        QSqlRecord registro = query.record();

        datosPersonales << query.value(registro.indexOf("nombre")).toString();
        datosPersonales << query.value(registro.indexOf("apellido")).toString();
    }

    return datosPersonales;
}

QVector<QStringList> AdminDB::select(const QString &comando) {
    QVector<QStringList> resultados;

    if (!db.isOpen())
        return resultados;

    QSqlQuery query(db);
    query.exec(comando);

    while (query.next()) {
        QSqlRecord registro = query.record();
        QStringList fila;
        for (int i = 0; i < registro.count(); i++) {
            fila << query.value(i).toString();
        }
        resultados.append(fila);
    }

    return resultados;
}
