#include "ghalia.h"
#include "ui_ghalia.h"

ghalia::ghalia(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ghalia)
{
    ui->setupUi(this);
}

ghalia::~ghalia()
{
    delete ui;
}
