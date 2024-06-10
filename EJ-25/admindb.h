#ifndef ADMINDB_H
#define ADMINDB_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class AdminDB : public QObject
{
    Q_OBJECT

public:
    static AdminDB& instancia();
    bool crearUsuario(const QString& nombreUsuario, const QString& contrasena);
    bool autenticarUsuario(const QString& nombreUsuario, const QString& contrasena);
    QSqlQuery obtenerTodosLosUsuarios();

private:
    explicit AdminDB(QObject *parent = nullptr);
    AdminDB(const AdminDB&) = delete;
    AdminDB& operator=(const AdminDB&) = delete;

    QSqlDatabase db;
};

#endif // ADMINDB_H
