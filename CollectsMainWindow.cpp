#include "CollectsMainWindow.h"
#include "ui_CollectsMainWindow.h"
#include "collects.h"
#include "QtDebug"
#include "connection.h"
#include "loginpage.h"
#include <QMessageBox>
#include<iostream>
#include <QTextDocument>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>
#include <QFileDialog>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QtCharts>
#include <QtNetwork>
#include <QtGui>
#include "themewidget.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include "dialog.h"
#include <QUrl>
#include "arduino.h"
#include <QSslSocket>
#include <QSslConfiguration>
#include <QAuthenticator>
#include <QtSerialPort/QSerialPort>
#include "smtpk.h"
#include "CollectsMainWindow.h"
#include "empwindow.h"
#include "destituteWindow.h"
#include "donationswindow.h"
#include "sermainwindow.h"




CollectsMainWindow::CollectsMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::CollectsMainWindow)
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
        //QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(koussay())); // permet de lancer
     //le slot update_label suite à la reception du signal readyRead (reception des données).
        ui->tab_mails->setModel(Etmp.afficher2());
            ui->tab_mails->resizeColumnsToContents();


    ui->tab_read->setModel(Etmp.afficher());
    ui->le_budget->setValidator(new QDoubleValidator(0, 9999999, 3, this));
     ui->le_collect->setValidator(new QDoubleValidator(0, 9999999, 3, this));
  //   ui->le_date->setMinimumDate(QDate::currentDate());
   //  ui->le_date->setMinimumDateTime(QDateTime::currentDateTime());
     ui->le_ID->setReadOnly(true);//le slot update_label suite à la reception du signal readyRead (reception des données).
    ui->le_location->setValidator(new QRegExpValidator(QRegExp("[A-Za-z ]{0,255}"), this));
   //  ui->le_des->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9 ]{0,255}"), this));

    // ui->le_IDS->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]{0,255}"), this));
      //  connect(ui->pdf, &QPushButton::clicked, this, &CollectsMainWindow::on_pdf_clicked);
     //connect(ui->calendarWidget, &QCalendarWidget::clicked, this, &CollectsMainWindow::showEvents);
     connect(ui->sendBtn, SIGNAL(clicked()),this, SLOT(sendMail()));


           // Query the database for dates
           QSqlQuery query;
           query.exec("SELECT COLLECT_DATE FROM COLLECTS");

           // Create a QCalendarWidget
           ui->calendarWidget->setGridVisible(true);
           ui->calendarWidget->setNavigationBarVisible(true);

           // Set the text format for each date in the database
           while (query.next()) {
               QDate date = query.value(0).toDate();
               QTextCharFormat format;
               format.setBackground(Qt::green);
               ui->calendarWidget->setDateTextFormat(date, format);

           }
           connect(ui->calendarWidget, &QCalendarWidget::clicked, this, &CollectsMainWindow::on_calendarWidget_clicked);

           refreshCalendar();


}

CollectsMainWindow::~CollectsMainWindow()
{
    delete ui;
}
void CollectsMainWindow::koussay()
{
    qDebug()<<"pop:22";

    //The Serial library provides functions for sending and receiving data over the serial connection
      // Read the id from the serial port
      QString serviceId = "";
//      if (A.getserial()->isOpen() && A.getserial()->isReadable()) {
//          QByteArray data = A.getserial()->readLine();
//          serviceId = QString::fromUtf8(data).trimmed();
//          qDebug()<<serviceId;
//      }
      serviceId=A.read_from_arduino();
      qDebug()<<"pop:"<<serviceId;

      // Check if the service ID exists in the database
      QSqlQuery idQuery;
      idQuery.prepare("SELECT COUNT(*) FROM services WHERE service_id = :id");
      idQuery.bindValue(":id", serviceId);
      if (idQuery.exec() && idQuery.next() && idQuery.value(0).toInt() > 0) {
          // Query the SERVICES table to get the budget of the specified service
          QSqlQuery serviceQuery;
          serviceQuery.prepare("SELECT budget, service_name FROM services WHERE service_id = :id");
          serviceQuery.bindValue(":id", serviceId);
          if (serviceQuery.exec() && serviceQuery.next()) {
              double budget = serviceQuery.value(0).toDouble();
              QString service_name = serviceQuery.value(1).toString();

              if (budget > 0) {
                  // Query the DONATIONS table to get the sum of donation amounts
                  QSqlQuery donationQuery;
                  donationQuery.prepare("SELECT SUM(amount) FROM donations");
                  if (donationQuery.exec() && donationQuery.next()) {
                      double donationSum = donationQuery.value(0).toDouble();

                      // Compare the budget to the sum of donation amounts
                      if (budget > donationSum) {
                         /* // Send "0" to Arduino if the budget is greater than the sum of donations
                          QByteArray data("0");
                          A.write_to_arduino(data);*/
                          // Send "0" to Arduino if the budget is greater than the sum of donations
                                                        QByteArray data("0");
                                                        A.write_to_arduino(data);

                                                        // Ask the user if they want to delete or modify the budget of the service
                                                        QMessageBox msgBox;
                                                        msgBox.setText("Budget is greater than sum of donations");
                                                        msgBox.setInformativeText("Do you want to delete the service or no ?");
                                                        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                                                        msgBox.setDefaultButton(QMessageBox::No);
                                                        int ret = msgBox.exec();
                                                        if (ret == QMessageBox::Yes) {
                                                            // Delete the service from the database
                                                            QSqlQuery deleteQuery;
                                                            deleteQuery.prepare("DELETE FROM services WHERE service_id = :id");
                                                            deleteQuery.bindValue(":id", serviceId);
                                                            deleteQuery.exec();
                                                        } else {
                                                            msgBox.done(QDialog::Rejected);
                                                        }

                                                            // Send "0" to Arduino if the budget is greater than the sum of donations
                      } else {
                          // Send "1" to Arduino if the budget is less than or equal to the sum of donations
                          QByteArray data("1");
                          qDebug()<<"approved";
                          A.write_to_arduino(data);
                      }
                  }
              } else {
                  // Query the DONATIONS table to get the sum of donation quantities for the specified service category
                  QSqlQuery donationQuery;
                  donationQuery.prepare("SELECT SUM(quantity) FROM donations WHERE category_name = :category");
                  donationQuery.bindValue(":category", service_name);
                  if (donationQuery.exec() && donationQuery.next()) {
                      double qdonationSum = donationQuery.value(0).toDouble();

                      // Query the SERVICES table to get the budget of the specified service
                      QSqlQuery serviceQuery;
                      serviceQuery.prepare("SELECT don_quantity FROM services WHERE service_id = :id");
                      serviceQuery.bindValue(":id", serviceId);
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
      } else {
          // Send "3" to Arduino if the service ID is not found in the database
          //qDebug()<<idQuery.lastError();
          QByteArray data("3");
          A.write_to_arduino(data);
      }
      qDebug()<<"end fct";
}

void CollectsMainWindow::on_pushButton_ajouter_clicked()
{
    QString Collect_name = ui->le_name->text();
    QString location = ui->le_location->text();
    QDate collect_date = ui->le_date->date();
    double collect_budget = ui->le_budget->text().toDouble();
    double collections = ui->le_collect->text().toDouble();
    QString description_c = ui->le_des->toPlainText(); // Retrieve the text from the QTextEdit widget

    // Generate the next ID
    QSqlQuery query("SELECT MAX(Collect_Id) FROM Collects");
    query.next();
    QString lastId = query.value(0).toString();
    int nextIndex = lastId.isEmpty() ? 1 : lastId.right(3).toInt() + 1;  // extract the numeric part of the ID and increment it
    QString Collect_ID = "COL" + QString("%1").arg(nextIndex, 3, 10, QChar('0')); // create the new ID

    Collects newCollect(Collect_ID, Collect_name, location, collect_date, collect_budget, collections, description_c);

    if (newCollect.ajouter()) {
        QMessageBox::information(this, "Success", "Collect added successfully.");
        ui->tab_read->setModel(Etmp.afficher());

        ui->le_name->clear();
        ui->le_location->clear();
        ui->le_date->setDate(QDate::currentDate());
        ui->le_budget->clear();
        ui->le_collect->clear();
        ui->le_des->clear();
        refreshCalendar();
    }
}


void CollectsMainWindow::refreshCalendar()
{
    // Query the database for dates
    QSqlQuery query;
    query.exec("SELECT COLLECT_DATE FROM COLLECTS");

    // Clear the existing text formats on the calendar
    ui->calendarWidget->setDateTextFormat(QDate(), QTextCharFormat());

    // Set the text format for each date in the database
    while (query.next()) {
        QDate date = query.value(0).toDate();
        QTextCharFormat format;
        format.setBackground(Qt::green);
        ui->calendarWidget->setDateTextFormat(date, format);
    }
}



void CollectsMainWindow::on_pushButton_supprimer_clicked()
{

        Collects E1;
        E1.setCollectID(ui->le_IDS->text());

        bool test = false;

        if (Etmp.rechercherID(E1.getCollectID())->rowCount() > 0) {
            test = Etmp.supprimer(E1.getCollectID());
        }

        if(test)
        {
            // (actualiser)
            ui->tab_read->setModel(Etmp.afficher());

            QMessageBox::information(nullptr, QObject::tr("OK"),
            QObject::tr("Suppression effectué\n"
                         "Click cancel to exit."),QMessageBox::Cancel);
            ui->le_IDS->clear();
            refreshCalendar();

        }
        else if (E1.getCollectID().isEmpty())
        {
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
            QObject::tr("L'ID est vide.\n"
                         "Click cancel to exit."),QMessageBox::Cancel);
        }
        else
        {
            QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
            QObject::tr("L'ID entré n'existe pas dans la base de données.\n"
                         "Click cancel to exit."),QMessageBox::Cancel);
        }


}

void CollectsMainWindow::on_pb_modifier_clicked()
{

    QString Collect_ID = ui->le_ID->text();
    QString Collect_name = ui->le_name->text();
    QString location = ui->le_location->text();
    QDate collect_date = ui->le_date->date();
    double collect_budget = ui->le_budget->text().toDouble();
    double collections = ui->le_collect->text().toDouble();
    QString description_c = ui->le_des->toPlainText(); // Retrieve the text from the QTextEdit widget

    Collects newCollect(Collect_ID, Collect_name, location, collect_date, collect_budget, collections, description_c);

    bool test = newCollect.modifier();

    if (test){
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("Modification effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_read->setModel(newCollect.afficher());
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("Modification non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    ui->tab_read->setModel(newCollect.afficher());
    refreshCalendar();

}




void CollectsMainWindow::on_confirm_sort_clicked()
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

void CollectsMainWindow::on_confirm_search_clicked()
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


   void CollectsMainWindow::on_pdf_clicked()
    {
        QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");
        if (fileName.isEmpty())
            return;

        QString strStream;
        QTextStream out(&strStream);
        const int rowCount = ui->tab_read->model()->rowCount();
        const int columnCount =ui->tab_read->model()->columnCount();

        out <<  "<html>\n"
                "<head>\n"
                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                <<  QString("<title>%1</title>\n").arg("eleve")
                <<  "</head>\n"
                "<body bgcolor=#FDFEFE link=#5000A0>\n"
                    "<h1>Liste de Events</h1>"
                    "<table border=1 cellspacing=0 cellpadding=2>\n";

        // headers
        out << "<thead><tr bgcolor=#A8C807>";
        for (int column = 0; column < columnCount; column++)
            if (!ui->tab_read->isColumnHidden(column))
                out << QString("<th>%1</th>").arg(ui->tab_read->model()->headerData(column, Qt::Horizontal).toString());
        out << "</tr></thead>\n";

        // data table
        for (int row = 0; row < rowCount; row++) {
            out << "<tr>";
            for (int column = 0; column < columnCount; column++) {
                if (!ui->tab_read->isColumnHidden(column)) {
                    QString data = ui->tab_read->model()->data(ui->tab_read->model()->index(row, column)).toString().simplified();
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

   void CollectsMainWindow::on_stats_clicked()
   {
      Dialog *dialog = new Dialog(this);
      ThemeWidget *themeWidget = new ThemeWidget(dialog);
      dialog->setWindowTitle("Statistics");
      QVBoxLayout *layout = new QVBoxLayout(dialog);
      layout->addWidget(themeWidget);
      dialog->setLayout(layout);
      dialog->setModal(true);

      dialog->setFixedSize(1000, 500);

      dialog->exec();
   }

 void CollectsMainWindow::on_tab_read_activated(const QModelIndex &index)
{
    QString Collect_ID = ui->tab_read->model()->data(ui->tab_read->model()->index(index.row(), 0)).toString();
    QString Collect_name = ui->tab_read->model()->data(ui->tab_read->model()->index(index.row(), 1)).toString();
    QString Collect_location = ui->tab_read->model()->data(ui->tab_read->model()->index(index.row(), 2)).toString();
    QDate Collect_date = ui->tab_read->model()->data(ui->tab_read->model()->index(index.row(), 3)).toDate();
    double Collect_budget = ui->tab_read->model()->data(ui->tab_read->model()->index(index.row(), 4)).toDouble();
    double Collections = ui->tab_read->model()->data(ui->tab_read->model()->index(index.row(), 5)).toDouble();
    QString Collect_des = ui->tab_read->model()->data(ui->tab_read->model()->index(index.row(), 6)).toString();

    ui->le_ID->setText(Collect_ID);
    ui->le_name->setText(Collect_name);
    ui->le_location->setText(Collect_location);
    ui->le_date->setDate(Collect_date);
    ui->le_budget->setText(QString::number(Collect_budget));
    ui->le_collect->setText(QString::number(Collections));
    ui->le_des->setText(Collect_des);
}



 void CollectsMainWindow::on_calendarWidget_clicked(const QDate &date)
 {
     // Prepare the query
     QSqlQuery query;
     query.prepare("SELECT * FROM Collects WHERE TO_CHAR(Collect_Date, 'DD-MM-YYYY') = :date");
     query.bindValue(":date", date.toString("dd-MM-yyyy"));


     // Execute the query
     if (!query.exec()) {
         qDebug() << "Failed to execute query";
         return;
     }

     // show the event
     if (query.next()) {
         QString name = query.value("Collect_name").toString();
         QString location = query.value("Location").toString();
         QString budget = QString::number(query.value("Collect_budget").toDouble());
         QString collections = QString::number(query.value("Collections").toDouble());
         QString description = query.value("Description_C").toString();

         QString eventText = QString("Collect name: %1   \nLocation: %2     \nBudget: %3     \nCollections: %4      \nDescription: %5")
                                 .arg(name, location, budget, collections, description);
         ui->eventLineEdit->setText(eventText);
     } else {
         ui->eventLineEdit->clear();
     }
 }
 void CollectsMainWindow::sendMail()
 {
     QString username = ui->uname->text();
     QString password = ui->paswd->text();
     QString recipient = ui->rcpt->text();
     QString subject = ui->subject->text();
     QString message = ui->msg->toPlainText();

     SMTPK* smtp = new SMTPK(ui->uname->text(), ui->paswd->text());
     connect(smtp, &SMTPK::status, this, &CollectsMainWindow::mailSent);

     smtp->sendMail(username, recipient, subject, message);
 }


 void CollectsMainWindow::mailSent()
 {
   //  if(status == "Message sent")
      //   QMessageBox::warning( 0, tr( "Qt Simple SMTP client" ), tr( "Message sent!\n\n" ) );

 }


void CollectsMainWindow::on_refresh_clicked()
{   ui->le_ID->clear();
    ui->le_name->clear();
    ui->le_location->clear();
    ui->le_date->setDate(QDate::currentDate());
    ui->le_budget->clear();
    ui->le_collect->clear();
    ui->le_des->clear();
}
void CollectsMainWindow::on_arduino1_clicked()
{   //The Serial library provides functions for sending and receiving data over the serial connection
    // Read the id from the serial port
    QString serviceId = "";
    if (A.getserial()->isOpen() && A.getserial()->isReadable()) {
        QByteArray data = A.getserial()->readLine();
        serviceId = QString::fromUtf8(data).trimmed();
    }

    // Check if the service ID exists in the database
    QSqlQuery idQuery;
    idQuery.prepare("SELECT COUNT(*) FROM services WHERE service_id = :id");
    idQuery.bindValue(":id", serviceId);
    if (idQuery.exec() && idQuery.next() && idQuery.value(0).toInt() > 0) {
        // Query the SERVICES table to get the budget of the specified service
        QSqlQuery serviceQuery;
        serviceQuery.prepare("SELECT budget, service_name FROM services WHERE service_id = :id");
        serviceQuery.bindValue(":id", serviceId);
        if (serviceQuery.exec() && serviceQuery.next()) {
            double budget = serviceQuery.value(0).toDouble();
            QString service_name = serviceQuery.value(1).toString();

            if (budget > 0) {
                // Query the DONATIONS table to get the sum of donation amounts
                QSqlQuery donationQuery;
                donationQuery.prepare("SELECT SUM(amount) FROM donations");
                if (donationQuery.exec() && donationQuery.next()) {
                    double donationSum = donationQuery.value(0).toDouble();

                    // Compare the budget to the sum of donation amounts
                    if (budget > donationSum) {
                       /* // Send "0" to Arduino if the budget is greater than the sum of donations
                        QByteArray data("0");
                        A.write_to_arduino(data);*/
                        // Send "0" to Arduino if the budget is greater than the sum of donations
                                                      QByteArray data("0");
                                                      A.write_to_arduino(data);
                                                      // Ask the user if they want to delete or modify the budget of the service
                                                      QMessageBox msgBox;
                                                      msgBox.setText("Budget is greater than sum of donations");
                                                      msgBox.setInformativeText("Do you want to delete the service or no ?");
                                                      msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                                                      msgBox.setDefaultButton(QMessageBox::No);
                                                      int ret = msgBox.exec();
                                                      if (ret == QMessageBox::Yes) {
                                                          // Delete the service from the database
                                                          QSqlQuery deleteQuery;
                                                          deleteQuery.prepare("DELETE FROM services WHERE service_id = :id");
                                                          deleteQuery.bindValue(":id", serviceId);
                                                          deleteQuery.exec();
                                                      } else {
                                                          msgBox.done(QDialog::Rejected);
                                                      }

                                                          // Send "0" to Arduino if the budget is greater than the sum of donations
                    } else {
                        // Send "1" to Arduino if the budget is less than or equal to the sum of donations
                        QByteArray data("1");
                        A.write_to_arduino(data);
                    }
                }
            } else {
                // Query the DONATIONS table to get the sum of donation quantities for the specified service category
                QSqlQuery donationQuery;
                donationQuery.prepare("SELECT SUM(quantity) FROM donations WHERE category_name = :category");
                donationQuery.bindValue(":category", service_name);
                if (donationQuery.exec() && donationQuery.next()) {
                    double qdonationSum = donationQuery.value(0).toDouble();

                    // Query the SERVICES table to get the budget of the specified service
                    QSqlQuery serviceQuery;
                    serviceQuery.prepare("SELECT don_quantity FROM services WHERE service_id = :id");
                    serviceQuery.bindValue(":id", serviceId);
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
    } else {
        // Send "3" to Arduino if the service ID is not found in the database
        QByteArray data("3");
        A.write_to_arduino(data);
    }
}

/*
void CollectsMainWindow::on_arduino1_clicked()
{
    // Read the id from the serial port
        QString serviceId = "";
        if (A.getserial()->isOpen() && A.getserial()->isReadable()) {
            QByteArray data = A.getserial()->readLine();
            serviceId = QString::fromUtf8(data).trimmed();
        }
        // Check if the service ID exists in the database
        QSqlQuery idQuery;
        idQuery.prepare("SELECT COUNT(*) FROM services WHERE service_id = :id");
        idQuery.bindValue(":id", serviceId);
        if (idQuery.exec() && idQuery.next() && idQuery.value(0).toInt() > 0) {
            // Query the SERVICES table to get the budget of the specified service
            QSqlQuery serviceQuery;
            serviceQuery.prepare("SELECT budget, service_name FROM services WHERE service_id = :id");
            serviceQuery.bindValue(":id", serviceId);
            if (serviceQuery.exec() && serviceQuery.next()) {
                double budget = serviceQuery.value(0).toDouble();
                QString service_name = serviceQuery.value(1).toString();

        // Check if the service ID exists in the database
        QSqlQuery idQuery;
        idQuery.prepare("SELECT COUNT(*) FROM services WHERE service_id = :id");
        idQuery.bindValue(":id", serviceId);
        if (idQuery.exec() && idQuery.next() && idQuery.value(0).toInt() > 0) {
            // Query the SERVICES table to get the budget of the specified service
            QSqlQuery serviceQuery;
            serviceQuery.prepare("SELECT budget, service_name FROM services WHERE service_id = :id");
            serviceQuery.bindValue(":id", serviceId);
            if (serviceQuery.exec() && serviceQuery.next()) {
                double budget = serviceQuery.value(0).toDouble();
                QString service_name = serviceQuery.value(1).toString();

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
                            // Ask the user if they want to delete or modify the budget of the service
                            QMessageBox msgBox;
                            msgBox.setText("Budget is greater than sum of donations");
                            msgBox.setInformativeText("Do you want to delete the service or modify its budget?");
                            msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
                            msgBox.setDefaultButton(QMessageBox::No);
                            int ret = msgBox.exec();
                            if (ret == QMessageBox::Yes) {
                                // Delete the service from the database
                                QSqlQuery deleteQuery;
                                deleteQuery.prepare("DELETE FROM services WHERE service_id = :id");
                                deleteQuery.bindValue(":id", serviceId);
                                deleteQuery.exec();
                            } else {
                                msgBox.done(QDialog::Rejected);
                            }

                                // Send "0" to Arduino if the budget is greater than the sum of donations



                        } else {
                            // Send "1" to Arduino if the budget is less than or equal to the sum of donations
                            QByteArray data("1");
                            A.write_to_arduino(data);
                        }
                    }
                    }
                }  else {
                // Query the DONATIONS table to get the sum of donation quantities for the specified service category
                QSqlQuery donationQuery;
                donationQuery.prepare("SELECT SUM(quantity) FROM donations WHERE category_name = :category");
                donationQuery.bindValue(":category", service_name);
                if (donationQuery.exec() && donationQuery.next()) {
                    double qdonationSum = donationQuery.value(0).toDouble();

                    // Query the SERVICES table to get the budget of the specified service
                    QSqlQuery serviceQuery;
                    serviceQuery.prepare("SELECT don_quantity FROM services WHERE service_id = :id");
                    serviceQuery.bindValue(":id", serviceId);
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

         else {
            // Send "3" to Arduino if the service ID is not found in the database
            QByteArray data("3");
            A.write_to_arduino(data);
        }
            }
        }
}
*/

void CollectsMainWindow::on_actionemployees_triggered()
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

void CollectsMainWindow::on_actionservices_triggered()
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

void CollectsMainWindow::on_actiondonations_triggered()
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

void CollectsMainWindow::on_actioncollects_triggered()
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

void CollectsMainWindow::on_actiondestitutes_triggered()
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

void CollectsMainWindow::on_actionlogo_triggered()
{

    this->hide();

loginpage *l =new  loginpage();
l->show();
}
