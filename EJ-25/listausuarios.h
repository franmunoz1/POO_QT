#ifndef LISTAUSUARIOS_H
#define LISTAUSUARIOS_H

#include <QWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

class ListaUsuarios : public QWidget
{
    Q_OBJECT

public:
    explicit ListaUsuarios(QWidget *parent = nullptr);

private slots:
    void manejarEdicionItem(QTreeWidgetItem *item, int column);

private:
    QTreeWidget *treeWidgetUsuarios;
    void poblarListaUsuarios();
    void actualizarUsuarioEnDB(int id, const QString& nombreUsuario, const QString& contrasena);
};

#endif // LISTAUSUARIOS_H
