#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "collects.h"
#include "QtDebug"
#include <QMessageBox>
#include<iostream>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_read->setModel(Etmp.afficher());
    ui->le_budget->setValidator(new QDoubleValidator(0, 9999999, 3, this));
     ui->le_collect->setValidator(new QDoubleValidator(0, 9999999, 3, this));
  //   ui->le_date->setMinimumDate(QDate::currentDate());
     ui->le_date->setMinimumDateTime(QDateTime::currentDateTime());
    ui->le_ID->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{0,255}"), this));
     ui->le_location->setValidator(new QRegExpValidator (QRegExp ("[A-Za-z]{0,255}"),this));
     ui->le_des->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{0,255}"), this));
     ui->le_IDS->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{0,255}"), this));
     ui->le_find->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{0,255}"), this));



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ajouter_clicked()
{
        QString Collect_ID = ui->le_ID->text();
        QString Collect_name = ui->le_name->text();
        QString location = ui->le_location->text();
        QDate collect_date = ui->le_date->date();
        double collect_budget = ui->le_budget->text().toDouble();
        double collections = ui->le_collect->text().toDouble();
        QString description_c = ui->le_des->text();

        Collects newCollect(Collect_ID, Collect_name, location, collect_date, collect_budget, collections, description_c);

        if (newCollect.ajouter()) {
            QMessageBox::information(this, "Success", "Collect added successfully.");
            ui->tab_read->setModel(Etmp.afficher());

        } else {
            QMessageBox::critical(this, "Error", "Failed to add Collect.");
        }

        ui->le_ID->clear();
        ui->le_name->clear();
        ui->le_location->clear();
        ui->le_date->setDate(QDate::currentDate());
        ui->le_budget->clear();
        ui->le_collect->clear();
        ui->le_des->clear();}


void MainWindow::on_pushButton_supprimer_clicked()
{
    Collects E1;

 E1.setCollectID(ui->le_IDS->text());
bool test=Etmp.supprimer(E1.getCollectID());

if(test)
{

    // (actualiser)
    ui->tab_read->setModel(Etmp.afficher());

QMessageBox::information(nullptr, QObject::tr("OK"),
QObject::tr("Suppression effectué\n"
             "Click cancel to exit."),QMessageBox::Cancel);
ui->le_IDS->clear();

}
else
QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
QObject::tr("Suppression non effectué\n"
             "Click cancel to exit."),QMessageBox::Cancel);

}

void MainWindow::on_pb_modifier_clicked()
{

    QString Collect_ID = ui->le_ID->text();
    QString Collect_name = ui->le_name->text();
    QString location = ui->le_location->text();
    QDate collect_date = ui->le_date->date();
    double collect_budget = ui->le_budget->text().toDouble();
    double collections = ui->le_collect->text().toDouble();
    QString description_c = ui->le_des->text();
    QString recherche=ui->le_find->text();

    Collects newCollect(Collect_ID, Collect_name, location, collect_date, collect_budget, collections, description_c);


    if (newCollect.rechercherID(recherche)->rowCount()!=0 and recherche.length()!=0)
    {
                bool test= newCollect.modifier(recherche);
                               if(test){
                                   MainWindow w;
                               w.show();
                               QMessageBox::information(nullptr, QObject::tr("database is open"),
                                           QObject::tr("Modification effectué.\n"
                                                       "Click Cancel to exit."), QMessageBox::Cancel);
                                  ui->tab_read->setModel(newCollect.afficher());
                           }
                           else
                               QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                                           QObject::tr("Modification non effectué.\n"
                                                       "Click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {QMessageBox::critical(nullptr, QObject::tr("ERREUR"),
                   QObject::tr("Modification non effectué !\n"
                     "Cliquer sur Cancel to exit."), QMessageBox::Cancel);}


    ui->tab_read->setModel(newCollect.afficher());
     }




void MainWindow::on_confirm_sort_clicked()
{

    Collects C;
        if(ui->comboBox->currentIndex()==0){
            ui->tab_recherche->setModel(C.triDate());

        }
        else if (ui->comboBox->currentIndex()==1)
        {
           ui->tab_recherche->setModel(C.triCosts());

        }
        else if(ui->comboBox->currentIndex()==2)
        {
            ui->tab_recherche->setModel(C.triCollects());

        }
        else
           std::cout << "no combobox" << std::endl;
}

void MainWindow::on_confirm_search_clicked()
{
    Collects C;
    QString recherche = ui->le_search->text();
    if(recherche.length()!=0)
{

        if(ui->comboBox_3->currentIndex()==0){
            ui->tab_recherche->setModel(C.rechercherID(recherche));

        }
        else if (ui->comboBox_3->currentIndex()==1)
        {

             ui->tab_recherche->setModel(C.rechercherDate(recherche));


        }
        else if(ui->comboBox_3->currentIndex()==2)
        {
            ui->tab_recherche->setModel(C.rechercherName(recherche));


    }
    else
    {
       ui->tab_recherche->setModel(C.afficher());
    }
}
}
