#include "sermainwindow.h"
#include "ui_sermainwindow.h"
#include "service.h"
#include "QtDebug"
#include <QMessageBox>
#include "exportexcelobject.h"
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>
#include "sermainwindow.h"
#include "ui_sermainwindow.h"
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
#include "loginpage.h"
#include "CollectsMainWindow.h"
#include "empwindow.h"
#include "destituteWindow.h"
#include "donationswindow.h"
#include "sermainwindow.h"

serMainWindow::serMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::serMainWindow)
{
    ui->setupUi(this);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
       break;
    case(-1):qDebug() << "arduino is not available";
    }
     QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(affcherRendezvousArduino())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
     ui->tab_service->setModel(Etmp.afficher());
     ui->tab_service2->setModel(Etmp.afficher());
     //ui->le_ID->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{0,255}"), this));
     ui->le_ID->setReadOnly(true);//le slot update_label suite à la reception du signal readyRead (reception des données).

     ui->cb_type->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{0,255}"), this));
     ui->le_name->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{0,255}"), this));
     ui->le_budget->setValidator(new QDoubleValidator(0, 9999999, 3, this));
     ui->le_qnt->setValidator(new QIntValidator(0, 9999999, this));
     ui->le_idsup->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{0,255}"), this));
     //ui->le_find->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{0,255}"), this));

}



serMainWindow::~serMainWindow()
{
    delete ui;
}
/*
void serMainWindow::on_pushButton_ajouter_clicked()
{
    // Generate the next ID
           QSqlQuery query("SELECT MAX(IDservice) FROM Services");
           query.next();
           QString lastId = query.value(0).toString();
           int nextIndex = lastId.isEmpty() ? 1 : lastId.right(3).toInt() + 1;  // extract the numeric part of the ID and increment it
           QString IDservice = "A" + QString("%1").arg(nextIndex, 3, 10, QChar('0')); // create the new ID





//QString IDservice=ui->le_ID->text();
QString Dontype=ui->cb_type->currentText();
QString serviceName=ui->le_name->text();
int Donquantity=ui->le_qnt->text().toInt();
float budget_S = ui->le_budget->text().toDouble();
Service S(IDservice,Dontype,serviceName,Donquantity,budget_S);
if (S.ajouter()) {
    //Refresh (actualiser)
        ui->tab_service->setModel(Etmp.afficher());
        ui->tab_service2->setModel(Etmp.afficher());

    QMessageBox::information(nullptr, QObject::tr("OK"),
    QObject::tr("Ajout effectué\n"
                 "Click cancel to exit."),QMessageBox::Cancel);
    // Update the totaldons table
    QSqlQuery queryUpdateTotal;
    if (Dontype == "money") {
        if (budget_S > 0) {
            queryUpdateTotal.prepare("UPDATE totaldons SET total = total - :budget WHERE category = 'money'");
            queryUpdateTotal.bindValue(":budget", budget_S);
            queryUpdateTotal.exec();
        }
    } else {
        queryUpdateTotal.prepare("UPDATE totaldons SET total = total - :quantity WHERE category = :service");
        queryUpdateTotal.bindValue(":service", Dontype);
        queryUpdateTotal.bindValue(":quantity", Donquantity);
        queryUpdateTotal.exec();
    }
}
    else
    QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
    QObject::tr("Ajout non effectué\n"
                 "Click cancel to exit."),QMessageBox::Cancel);
}
*/

void serMainWindow::on_pushButton_ajouter_clicked()
{
    // Generate the next ID
    QSqlQuery query("SELECT MAX(IDservice) FROM Services");
    query.next();
    QString lastId = query.value(0).toString();
    int nextIndex = lastId.isEmpty() ? 1 : lastId.right(3).toInt() + 1;  // extract the numeric part of the ID and increment it
    QString IDservice = "A" + QString("%1").arg(nextIndex, 3, 10, QChar('0')); // create the new ID

    QString Dontype = ui->cb_type->currentText();
    QString serviceName = ui->le_name->text();
    int Donquantity = ui->le_qnt->text().toInt();
    float budget_S = ui->le_budget->text().toDouble();

    Service S(IDservice, Dontype, serviceName, Donquantity, budget_S);
    if (S.ajouter()) {
        // Refresh (actualiser)
        ui->tab_service->setModel(Etmp.afficher());
        ui->tab_service2->setModel(Etmp.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Ajout effectué\n"
                                             "Click cancel to exit."), QMessageBox::Cancel);

        if (Dontype == "money" && budget_S > 0) {
            // Update the totaldons table
            QSqlQuery queryUpdateTotal;
            queryUpdateTotal.prepare("UPDATE totaldons SET total = total - :budget WHERE category = 'money'");
            queryUpdateTotal.bindValue(":budget", budget_S);
            queryUpdateTotal.exec();

        } else {
            // Update the totaldons table
            QSqlQuery queryUpdateTotal;
            queryUpdateTotal.prepare("UPDATE totaldons SET total = total - :quantity WHERE category = :service");
            queryUpdateTotal.bindValue(":service", Dontype);
            queryUpdateTotal.bindValue(":quantity", Donquantity);
            queryUpdateTotal.exec();
        }
    } else {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
                              QObject::tr("Ajout non effectué\n"
                                          "Click cancel to exit."), QMessageBox::Cancel);
    }
}

void serMainWindow::on_pushButton_supprimer_clicked()
{
QString IDservice=ui->le_idsup->text();
bool test=Etmp.supprimer(IDservice);

if(test)
{

    //Refresh (actualiser)
    ui->tab_service->setModel(Etmp.afficher());
    ui->tab_service2->setModel(Etmp.afficher());

QMessageBox::information(nullptr, QObject::tr("OK"),
QObject::tr("Suppression effectué\n"
             "Click cancel to exit."),QMessageBox::Cancel);
}
else
QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
QObject::tr("Suppression non effectué\n"
             "Click cancel to exit."),QMessageBox::Cancel);

}


void serMainWindow::on_pb_modifier_clicked()
{

    QString IDservice = ui->le_ID->text();
    QString serviceName=ui->cb_type->currentText();
    QString Dontype = ui->le_name->text();
    int Donquantity=ui->le_qnt->text().toInt();
    float budget_S = ui->le_budget->text().toDouble();
   // QString recherche=ui->le_find->text();

    Service S(IDservice,Dontype,serviceName,Donquantity,budget_S);


    bool test = S.modifier();

        if (test){
            QMessageBox::information(nullptr, QObject::tr("database is open"),
                        QObject::tr("Modification effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
            ui->tab_service->setModel(S.afficher());
            ui->tab_service2->setModel(S.afficher());

        }
        else{
            QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                        QObject::tr("Modification non effectué.\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }

        ui->tab_service->setModel(S.afficher());
        ui->tab_service2->setModel(S.afficher());

    }


void serMainWindow::on_pb_recherche_clicked()
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



void serMainWindow::on_pb_sort_clicked()
{
    Service S;
        if(ui->comboBox_sort->currentIndex()==0){
            ui->recherche->setModel(S.triIDs());
        }
        //else
           // cout << "no combobox" << endl;
}



//export excel




void serMainWindow::on_export_excel_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Excel file"), qApp->applicationDirPath (),
                                                    tr("Excel Files (*.xls)"));
    if (fileName.isEmpty())
        return;

    ExportExcelObject obj(fileName, "mydata", ui->tab_service);

    //colums to export
    obj.addField(0, "IDservice", "char(20)");
    obj.addField(1, "Dontype", "char(20)");
    obj.addField(2, "ServiceName", "char(20)");
    obj.addField(3, "Donquantity", "char(20)");
    obj.addField(4, "budget_S", "char(20)");
   // obj.addField(5, "dateedit", "char(20)");
   // obj.addField(5, "timeedit", "char(20)");


    int retVal = obj.export2Excel();
    if( retVal > 0)
    {
        QMessageBox::information(this, tr("Done"),
                                 QString(tr("%1 records exported!")).arg(retVal)
                                 );
    }
}



void serMainWindow::on_pb_pdf1_clicked()

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




void serMainWindow::on_pb_pdf2_clicked()

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




void serMainWindow::on_stats_clicked()
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








void serMainWindow::on_tab_service_activated(const QModelIndex &index)
{
    QString IDservice = ui->tab_service->model()->data(ui->tab_service->model()->index(index.row(), 0)).toString();
            QString Dontype = ui->tab_service->model()->data(ui->tab_service->model()->index(index.row(), 1)).toString();
            QString serviceName = ui->tab_service->model()->data(ui->tab_service->model()->index(index.row(), 2)).toString();
            int Donquantiy = ui->tab_service->model()->data(ui->tab_service->model()->index(index.row(), 3)).toInt();
            double budget_S = ui->tab_service->model()->data(ui->tab_service->model()->index(index.row(), 4)).toDouble();


            ui->le_ID->setText(IDservice);
            ui->cb_type->setCurrentText(Dontype);
            ui->le_name->setText(serviceName);
            ui->le_qnt->setText(QString::number(Donquantiy));
            ui->le_budget->setText(QString::number(budget_S));



}

void serMainWindow::on_pb_arduino_clicked()
{
    // Read the id from the serial port
       QString serviceId = "";
       if (A.getserial()->isOpen() && A.getserial()->isReadable()) {
           QByteArray data = A.getserial()->readLine();
           serviceId = QString::fromUtf8(data).trimmed();
       }

       // Query the SERVICES table to get the budget of the specified service
       QSqlQuery serviceQuery;
       serviceQuery.prepare("SELECT budget_S, serviceName FROM services WHERE service_id = :IDservice");
       serviceQuery.bindValue(":IDservice", serviceId);
       if (serviceQuery.exec() && serviceQuery.next()) {
           double budget = serviceQuery.value(0).toDouble();
           QString serviceName = serviceQuery.value(1).toString();

           if (budget > 0) {
               // Query the DONATIONS table to get the sum of donation amounts
               QSqlQuery donationQuery;
               donationQuery.prepare("SELECT SUM(amount) FROM donations");
               if (donationQuery.exec() && donationQuery.next()) {
                   double donationSum = donationQuery.value(0).toDouble();

                   // Compare the budget to the sum of donation amounts
                   if (budget > donationSum) {
                       // Send "0" to Arduino if the budget is greater than the sum of donations
                       QByteArray data("0");
                       A.write_to_arduino(data);
                   } else {
                       // Send "1" to Arduino if the budget is less than or equal to the sum of donations
                       QByteArray data("1");
                       A.write_to_arduino(data);
                   }
               }
           } else {
               // Query the DONATIONS table to get the sum of donation quantities for the specified service category
               QSqlQuery donationQuery;
               donationQuery.prepare("SELECT SUM(quantity) FROM donations WHERE category_name = :category_name");
               donationQuery.bindValue(":category_name", serviceName);
               if (donationQuery.exec() && donationQuery.next()) {
                   double qdonationSum = donationQuery.value(0).toDouble();

                   // Query the SERVICES table to get the budget of the specified service
                   QSqlQuery serviceQuery;
                   serviceQuery.prepare("SELECT Donquantity FROM services WHERE service_id = :IDservice");
                   serviceQuery.bindValue(":IDservice", serviceId);
                   if (serviceQuery.exec() && serviceQuery.next()) {
                       int don_quantity = serviceQuery.value(0).toDouble();


                   // Compare the service_name to the sum of donation quantities
                   if (don_quantity > qdonationSum) {
                       // Send "0" to Arduino if the service_name is greater than the sum of donation quantities
                       QByteArray data("0");
                       A.write_to_arduino(data);
                   } else {
                       // Send "1" to Arduino if the service_name is less than or equal to the sum of donation quantities
                       QByteArray data("1");
                       A.write_to_arduino(data);
                   }
               }
           }
    }
           }
}




void serMainWindow::on_destitute_triggered()
{
    if (USER==1){
              destituteWindow  *p=new destituteWindow();
        p->showMaximized();
         this->hide();
           }else{
           QMessageBox::critical(nullptr, QObject::tr("Access denied :/"),
                       QObject::tr("You are not allowed to this section you need to login as a Destitute Manager to access it! :/\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
       }
}

void serMainWindow::on_collects_triggered()
{
    if (USER==1){

             CollectsMainWindow  *p=new CollectsMainWindow();
      p->showMaximized();
       this->hide();
          }else{
          QMessageBox::critical(nullptr, QObject::tr("Access denied :/"),
                      QObject::tr("You are not allowed to this section you need to login as an Events Manager to access it! :/\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
      }
}

void serMainWindow::on_employees_triggered()
{
    if (USER==1){
            empwindow *p=new empwindow();
        p->showMaximized();
        this->hide();
        }else{
            QMessageBox::critical(nullptr, QObject::tr("Access denied :/"),
                        QObject::tr("You are not allowed to this section you need to login as an Admin to access it! :/\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
}

void serMainWindow::on_donations_triggered()
{
    if (USER==1){
              donationswindow  *p=new donationswindow();
        p->showMaximized();
         this->hide();
           }else{
           QMessageBox::critical(nullptr, QObject::tr("Access denied :/"),
                       QObject::tr("You are not allowed to this section you need to login as a Donations Manager to access it! :/\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
       }
}

void serMainWindow::on_services_triggered()
{
    if (USER==1){
        serMainWindow  *p=new serMainWindow();
 p->showMaximized();

 this->hide();

    }else{
    QMessageBox::critical(nullptr, QObject::tr("Access denied :/"),
                QObject::tr("You are not allowed to this section you need to login as a Services Manager to access it! :/\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
}

void serMainWindow::on_logo_triggered()
{
    this->hide();
loginpage *l =new  loginpage();
l->show();
}


void serMainWindow::on_refresh_clicked()
{
        ui->le_ID->clear();
        ui->le_name->clear();
        ui->le_budget->clear();
        ui->le_qnt->clear();
}

void serMainWindow::on_stockVerification_clicked()
{
    QString IDservice = ui->le_idss->text();

    QSqlQuery query;
    query.prepare("SELECT budget_S, Donquantity, Dontype FROM Services WHERE IDservice = :IDservice");
    query.bindValue(":IDservice", IDservice);

    if (query.exec() && query.next()) {
        double budget_S = query.value(0).toDouble();
        int Donquantity = query.value(1).toInt();
        QString Dontype = query.value(2).toString();

        QSqlQuery query2;
        query2.prepare("SELECT amount, quantity FROM Donations WHERE category_name = :category_name");
        query2.bindValue(":category_name", Dontype);
        if (query2.exec()) {
            double sumAmounts = 0;
            int quantity = 0;
            while (query2.next()) {
                sumAmounts += query2.value(0).toDouble();
                quantity = query2.value(1).toInt();
            }

            if (Dontype == "blankets" && Donquantity <= quantity) {
                QMessageBox::information(this, tr("Stock Verification"), tr("service verified and ready to be posted"));

                // Show the service in the Stock tableView
                ui->Stock->setModel(Etmp.afficherStock(IDservice));
            } else if (Dontype == "food" && Donquantity <= quantity) {
                QMessageBox::information(this, tr("Stock Verification"), tr("service verified and ready to be posted"));

                // Show the service in the Stock tableView
                ui->Stock->setModel(Etmp.afficherStock(IDservice));
            } else if (Dontype == "money" && budget_S <= sumAmounts) {
                QMessageBox::information(this, tr("Stock Verification"), tr("service verified and ready to be posted"));

                // Show the service in the Stock tableView
                 ui->Stock->setModel(Etmp.afficherStock(IDservice));
            } else if (Dontype == "clothes" && Donquantity <= quantity) {
                QMessageBox::information(this, tr("Stock Verification"), tr("service verified and ready to be posted"));

                // Show the service in the Stock tableView
                ui->Stock->setModel(Etmp.afficherStock(IDservice));


            } else {
                QMessageBox::warning(this, tr("Stock Verification"), tr("Service is not ready to be posted yet."));
            }
        } else {
            QMessageBox::warning(this, tr("Error"), tr("Failed to retrieve donations from donations table."));
        }
    } else {
        QMessageBox::warning(this, tr("Error"), tr("Failed to retrieve service information from services table."));
    }

}
