#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "service.h"
#include "QtDebug"
#include <QMessageBox>
#include "exportexcelobject.h"
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QString>
#include<QMessageBox>
#include<QObject>
#include <QIntValidator>
#include<iostream>
#include <QPrinter>
#include <QTextStream>
#include<QPrintDialog>
#include <QSqlQuery>
#include<QDebug>
#include <QFileDialog>
#include <QFileDialog>
#include <QTextCodec>
#include "themewidget.h"
#include "dialog.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tab_service->setModel(Etmp.afficher());
    //ui->le_ID->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{0,255}"), this));
    ui->cb_type->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{0,255}"), this));
    ui->le_name->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{0,255}"), this));
    ui->le_budget->setValidator(new QDoubleValidator(0, 9999999, 3, this));
    ui->le_qnt->setValidator(new QIntValidator(0, 9999999, this));
    ui->le_idsup->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{0,255}"), this));
    ui->le_find->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{0,255}"), this));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_ajouter_clicked()
{
QString IDservice=ui->le_ID->text();
QString Dontype=ui->le_name->text();
QString serviceName=ui->cb_type->currentText();
float budget_S = ui->le_budget->text().toDouble();
int Donquantity=ui->le_qnt->text().toInt();
Service S(IDservice,Dontype,serviceName,budget_S,Donquantity);
if (S.ajouter()) {
        QMessageBox::information(this, "Success", "Service added successfully.");
        ui->tab_service->setModel(Etmp.afficher());

        ui->le_ID->clear();
        ui->cb_type->clear();
        ui->le_name->clear();
        ui->le_budget->clear();
        ui->le_qnt->clear();
}
}

void MainWindow::on_pushButton_supprimer_clicked()
{
QString IDservice=ui->le_idsup->text();
bool test=Etmp.supprimer(IDservice);

if(test)
{

    //Refresh (actualiser)
    ui->tab_service->setModel(Etmp.afficher());

QMessageBox::information(nullptr, QObject::tr("OK"),
QObject::tr("Suppression effectué\n"
             "Click cancel to exit."),QMessageBox::Cancel);
}
else
QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
QObject::tr("Suppression non effectué\n"
             "Click cancel to exit."),QMessageBox::Cancel);

}


void MainWindow::on_pb_modifier_clicked()
{

    QString IDservice = ui->le_ID->text();
    QString serviceName=ui->cb_type->currentText();
    float budget_S = ui->le_budget->text().toDouble();
    QString Dontype = ui->le_name->text();
    int Donquantity=ui->le_qnt->text().toInt();
    QString recherche=ui->le_find->text();

    Service S(IDservice,Dontype,serviceName,budget_S,Donquantity);


    if (S.rechercherID(recherche)->rowCount()!=0 and recherche.length()!=0)
    {
                bool test= S.modifier(recherche);
                               if(test){
                                   MainWindow w;
                               w.show();
                               QMessageBox::information(nullptr, QObject::tr("database is open"),
                                           QObject::tr("Modification effectué.\n"
                                                       "Click Cancel to exit."), QMessageBox::Cancel);
                                  ui->tab_service->setModel(S.afficher());
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


    ui->tab_service->setModel(S.afficher());
     }


void MainWindow::on_pb_recherche_clicked()
{

    Service S;
    QString recherche = ui->le_recherche->text();
    if(recherche.length()!=0)
{

        if(ui->comboBox_recherche->currentIndex()==0){
            ui->recherche->setModel(S.rechercherID(recherche));

        }
        else if (ui->comboBox_recherche->currentIndex()==1)
        {
             ui->recherche->setModel(S.recherchernomS(recherche));


        }
        else if(ui->comboBox_recherche->currentIndex()==2)
        {
            ui->recherche->setModel(S.rechercherDontype(recherche));


    }
    else
    {
       ui->recherche->setModel(S.afficher());
    }
}
}



void MainWindow::on_pb_sort_clicked()
{
    Service S;
        if(ui->comboBox_sort->currentIndex()==0){
            ui->recherche->setModel(S.triIDs());

        }
        else if (ui->comboBox_sort->currentIndex()==1)
        {
            ui->recherche->setModel(S.tridon());

        }
        else if(ui->comboBox_sort->currentIndex()==2)
        {
            ui->recherche->setModel(S.triNomS());

        }
        //else
           // cout << "no combobox" << endl;
}



//export excel




void MainWindow::on_export_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->tab_service);

    //colums to export
    obj.addField(0, "entier", "char(20)");
    obj.addField(1, "reel", "char(20)");
    obj.addField(2, "combobox", "char(20)");
    obj.addField(3, "lineedit", "char(20)");
    obj.addField(4, "textedit", "char(20)");
    obj.addField(5, "dateedit", "char(20)");
    obj.addField(5, "timeedit", "char(20)");


    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}



void MainWindow::on_pb_pdf1_clicked()

 {
     QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");
     if (fileName.isEmpty())
         return;

     QString strStream;
     QTextStream out(&strStream);
     const int rowCount = ui->tab_service->model()->rowCount();
     const int columnCount =ui->tab_service->model()->columnCount();

     out <<  "<html>\n"
             "<head>\n"
             "<meta Content=\"Text/html; charset=Windows-1251\">\n"
             <<  QString("<title>%1</title>\n").arg("eleve")
             <<  "</head>\n"
             "<body bgcolor=#FDFEFE link=#5000A0>\n"
                 "<h1>Liste de Services</h1>"
                 "<table border=1 cellspacing=0 cellpadding=2>\n";

     // headers
     out << "<thead><tr bgcolor=#F5B7B1>";
     for (int column = 0; column < columnCount; column++)
         if (!ui->tab_service->isColumnHidden(column))
             out << QString("<th>%1</th>").arg(ui->tab_service->model()->headerData(column, Qt::Horizontal).toString());
     out << "</tr></thead>\n";

     // data table
     for (int row = 0; row < rowCount; row++) {
         out << "<tr>";
         for (int column = 0; column < columnCount; column++) {
             if (!ui->tab_service->isColumnHidden(column)) {
                 QString data = ui->tab_service->model()->data(ui->tab_service->model()->index(row, column)).toString().simplified();
                 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
             }
         }
         out << "</tr>\n";
     }
     out <<  "</table>\n"
         "</body>\n"
         "</html>\n";

     QTextDocument *document = new QTextDocument();
     document->setHtml(strStream);

     QPrinter printer(QPrinter::PrinterResolution);
     printer.setOutputFormat(QPrinter::PdfFormat);
     printer.setOutputFileName(fileName);
     document->print(&printer);
 }




void MainWindow::on_pb_pdf2_clicked()

 {
     QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");
     if (fileName.isEmpty())
         return;

     QString strStream;
     QTextStream out(&strStream);
     const int rowCount = ui->recherche->model()->rowCount();
     const int columnCount =ui->recherche->model()->columnCount();

     out <<  "<html>\n"
             "<head>\n"
             "<meta Content=\"Text/html; charset=Windows-1251\">\n"
             <<  QString("<title>%1</title>\n").arg("eleve")
             <<  "</head>\n"
             "<body bgcolor=#FDFEFE link=#5000A0>\n"
                 "<h1>Liste des Services recherchés ou triés</h1>"
                 "<table border=1 cellspacing=0 cellpadding=2>\n";

     // headers
     out << "<thead><tr bgcolor=#F5B7B1>";
     for (int column = 0; column < columnCount; column++)
         if (!ui->recherche->isColumnHidden(column))
             out << QString("<th>%1</th>").arg(ui->recherche->model()->headerData(column, Qt::Horizontal).toString());
     out << "</tr></thead>\n";

     // data table
     for (int row = 0; row < rowCount; row++) {
         out << "<tr>";
         for (int column = 0; column < columnCount; column++) {
             if (!ui->recherche->isColumnHidden(column)) {
                 QString data = ui->recherche->model()->data(ui->recherche->model()->index(row, column)).toString().simplified();
                 out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
             }
         }
         out << "</tr>\n";
     }
     out <<  "</table>\n"
         "</body>\n"
         "</html>\n";

     QTextDocument *document = new QTextDocument();
     document->setHtml(strStream);

     QPrinter printer(QPrinter::PrinterResolution);
     printer.setOutputFormat(QPrinter::PdfFormat);
     printer.setOutputFileName(fileName);
     document->print(&printer);
 }




void MainWindow::on_stats_clicked()
{
    Dialog *dialog = new Dialog(this);
    ThemeWidget *themeWidget = new ThemeWidget(dialog);
    dialog->setWindowTitle("Statistics");
    QVBoxLayout *layout = new QVBoxLayout(dialog);
    layout->addWidget(themeWidget);
    dialog->setLayout(layout);
    dialog->setModal(true);
    dialog->exec();
}







void MainWindow::on_stockVerification_clicked()
{

        QString IDservice = ui->le_idss->text(); // assuming the ID is entered in a QLineEdit named serviceID

        // Select the service with the given ID from the Services table
        QSqlQuery query;
        query.prepare("SELECT budget_S FROM Services WHERE IDservice = :IDservice");
        query.bindValue(":IDservice", IDservice);
        query.exec();

        if (query.next()) { // if the service is found
            double budget_S = query.value(0).toDouble();

            // Select the donation amount for the given category
            QString category_name = ui->cbdon->currentText(); // assuming the category is selected from a QComboBox named cb_type
            query.prepare("SELECT amount FROM Donations WHERE category_name = :category_name");
            query.bindValue(":category_name", category_name);
            query.exec();

            if (query.next()) { // if the donation amount for the category is found
                double amount = query.value(0).toDouble();

                if (budget_S <= amount) { // if the budget_S is less than or equal to the donation amount
                    // Show the service in the Stock tableView
                    QSqlQueryModel *model = new QSqlQueryModel();
                    model->setQuery("SELECT * FROM Services WHERE IDservice = " +IDservice);
                    ui->Stock->setModel(model);
                } else {
                    QMessageBox::warning(this, "Warning", "Service is not ready to be posted yet.");
                }
            } else {
                QMessageBox::warning(this, "Warning", "Donation amount for the category not found.");
            }
        } else {
            QMessageBox::warning(this, "Warning", "Service not found.");
        }
    }





