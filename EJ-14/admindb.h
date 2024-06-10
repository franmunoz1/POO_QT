#ifndef ADMINDB_H
#define ADMINDB_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <QVector>
#include <QStringList>

class AdminDB : public QObject {
    Q_OBJECT
public:
    AdminDB(QObject *parent = nullptr);
    ~AdminDB();

    QStringList validarUsuario(const QString &tabla, const QString &usuario, const QString &clave);
    QVector<QStringList> select(const QString &comando);

private:
    QSqlDatabase db;
};

#endif // ADMINDB_H
