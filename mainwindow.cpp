#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employee.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(etmp.afficher());
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_6_clicked(){
    QString id=ui->lineEdit_id->text();
    QString nom=ui->lineEdit_lastname->text();
    QString prenom=ui->lineEdit_firstname->text();
    QString login=ui->lineEdit_login->text();
    QString password=ui->lineEdit_password->text();
    QString function=ui->lineEdit_fucntion->text();
    QString contact=ui->lineEdit_contact->text();
    float salary=ui->lineEdit_salary->text().toFloat();
    int efficiency=0;
    employee e(id,nom,prenom,login,password,function,contact,salary,efficiency);
bool test=e.ajouter();
if(test)
    {
        //REFRESH
         ui->tableView->setModel(etmp.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Added successfuly.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("NOT ADDED.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_5_clicked()
{
    QString id=ui->lineEdit_iddelete->text();
    bool test=etmp.supprimer(id);
    if(test){
        //REFRESH
        ui->tableView->setModel(etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Suppression effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("Suppression non effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

