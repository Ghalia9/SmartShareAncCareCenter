#include "destitute.h"
#include "ui_destitute.h"

Destitute::Destitute(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Destitute)
{
    ui->setupUi(this);
}

Destitute::~Destitute()
{
    delete ui;
}
