#ifndef ACCESO_H
#define ACCESO_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Acceso;
}
QT_END_NAMESPACE

class Acceso : public QWidget
{
    Q_OBJECT

public:
    Acceso(QWidget *parent = nullptr);
    ~Acceso();

private:
    Ui::Acceso *ui;
};
#endif // ACCESO_H
