#include "AdminDB.h"

AdminDB::AdminDB(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("usuarios.db");

    if (!db.open()) {
        qDebug() << "Error: conexión con la base de datos fallida";
    } else {
        qDebug() << "Base de datos: conexión exitosa";

        QSqlQuery query;
        query.exec("CREATE TABLE IF NOT EXISTS usuarios ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "nombreUsuario TEXT NOT NULL, "
                   "contrasena TEXT NOT NULL)");
    }
}

AdminDB& AdminDB::instancia()
{
    static AdminDB instancia;
    return instancia;
}

bool AdminDB::crearUsuario(const QString& nombreUsuario, const QString& contrasena)
{
    QSqlQuery query;
    query.prepare("INSERT INTO usuarios (nombreUsuario, contrasena) VALUES (:nombreUsuario, :contrasena)");
    query.bindValue(":nombreUsuario", nombreUsuario);
    query.bindValue(":contrasena", contrasena);
    return query.exec();
}

bool AdminDB::autenticarUsuario(const QString& nombreUsuario, const QString& contrasena)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM usuarios WHERE nombreUsuario = :nombreUsuario AND contrasena = :contrasena");
    query.bindValue(":nombreUsuario", nombreUsuario);
    query.bindValue(":contrasena", contrasena);
    query.exec();
    return query.next();
}

QSqlQuery AdminDB::obtenerTodosLosUsuarios()
{
    QSqlQuery query;
    query.exec("SELECT * FROM usuarios");
    return query;
}
