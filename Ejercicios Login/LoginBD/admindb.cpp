#include "admindb.h"
#include "ui_admindb.h"

AdminDB::AdminDB(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminDB)
{
    ui->setupUi(this);
}

AdminDB::~AdminDB()
{
    delete ui;
}
