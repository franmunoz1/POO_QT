#include "ListaUsuarios.h"
#include "AdminDB.h"
#include <QVBoxLayout>
#include <QHeaderView>

ListaUsuarios::ListaUsuarios(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    treeWidgetUsuarios = new QTreeWidget(this);
    treeWidgetUsuarios->setColumnCount(3);
    treeWidgetUsuarios->setHeaderLabels(QStringList() << "ID" << "Nombre de Usuario" << "Contraseña");
    treeWidgetUsuarios->setEditTriggers(QAbstractItemView::DoubleClicked | QAbstractItemView::SelectedClicked | QAbstractItemView::EditKeyPressed);

    layout->addWidget(treeWidgetUsuarios);

    // Conexión utilizando la nueva sintaxis de señales y slots
    connect(treeWidgetUsuarios, &QTreeWidget::itemChanged, this, [=](QTreeWidgetItem *item, int column) {
        manejarEdicionItem(item, column);
    });

    poblarListaUsuarios();
}

void ListaUsuarios::poblarListaUsuarios()
{
    QSqlQuery query = AdminDB::instancia().obtenerTodosLosUsuarios();

    while (query.next()) {
        QTreeWidgetItem *item = new QTreeWidgetItem(treeWidgetUsuarios);
        item->setText(0, query.value("id").toString());
        item->setText(1, query.value("nombreUsuario").toString());
        item->setText(2, query.value("contrasena").toString());
        item->setFlags(item->flags() | Qt::ItemIsEditable);
    }

    treeWidgetUsuarios->resizeColumnToContents(0);
    treeWidgetUsuarios->resizeColumnToContents(1);
    treeWidgetUsuarios->resizeColumnToContents(2);
}

void ListaUsuarios::manejarEdicionItem(QTreeWidgetItem *item, int column)
{
    int id = item->text(0).toInt();
    QString nombreUsuario = item->text(1);
    QString contrasena = item->text(2);

    actualizarUsuarioEnDB(id, nombreUsuario, contrasena);
}

void ListaUsuarios::actualizarUsuarioEnDB(int id, const QString& nombreUsuario, const QString& contrasena)
{
    QSqlQuery query;
    query.prepare("UPDATE usuarios SET nombreUsuario = :nombreUsuario, contrasena = :contrasena WHERE id = :id");
    query.bindValue(":nombreUsuario", nombreUsuario);
    query.bindValue(":contrasena", contrasena);
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error al actualizar el usuario en la base de datos:" << query.lastError();
    } else {
        qDebug() << "Usuario actualizado correctamente en la base de datos.";
    }
}
