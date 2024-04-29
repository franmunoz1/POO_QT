#include "login.h"
#include "ui_login.h"

Login::Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Login),
    // instanciamos la ventana
    ventana (new Ventana)
{
    ui->setupUi(this);

    //dar foco al le del usuario
    ui->leUsuario->setFocus();

    //realizamos la conexion con la ventana
    connect(ui -> pbValidar, SIGNAL(pressed()), this, SLOT(slot_validar()));
    // tambien conectamos la senal que se emite cuiando estamos en el line edit escribiendo y que reconozca el enter
    connect(ui->leContra, SIGNAL(returnPressed()), this, SLOT(slot_validar()));
}

Login::~Login()
{
    delete ui;
}

void Login::slot_validar()
{
    //si el line edit del usuario es admin y el line edit de la password es 1234
    if (ui->leUsuario->text() == "admin" && ui->leContra->text() == "1234"){
        // imprime por consola usuario valido
        qDebug() << "Usuario valido";
        // si es valido oculamos el login y mostramos la ventana con show.
        this->hide();
        ventana->show();
    } else{
        qDebug() << "Usuario no valido";
        // si no es valido cierra el login y al ser el utlimo, la aplicacion tambien se va a cerrar
        this->close();
    }
}
