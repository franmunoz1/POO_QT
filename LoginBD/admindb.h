#ifndef ADMINDB_H
#define ADMINDB_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class AdminDB;
}
QT_END_NAMESPACE

class AdminDB : public QWidget
{
    Q_OBJECT

public:
    AdminDB(QWidget *parent = nullptr);
    ~AdminDB();

private:
    Ui::AdminDB *ui;
};
#endif // ADMINDB_H
