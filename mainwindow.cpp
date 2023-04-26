#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "destitute.h"
#include "capteur.h"
#include "donation.h"

#include <QMessageBox>
#include <QSqlError>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
//pdf
#include <QPrinter>
#include <QPainter>
#include <QPdfWriter>
#include <QtSql>
//stats
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
//qrCode
#include<QPixmap>
#include <QImage>
#include "QZXing/QZXing.h"
//Map
#include <QtQuick/QQuickItem>
#include <QQuickView>
#include <QVBoxLayout>
#include <QQuickItem>
#include <QGeoServiceProvider>
//#include <QQuickWidget>
//
#include <openssl/conf.h>
#include <openssl/evp.h>
#include <openssl/err.h>
//web
#include <QApplication>
//#include <QWebEngineView>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->showtab->setModel(De.Show());
    ui->listQR->setModel(De.Show());
    ui->the_firstname->setValidator(new QRegExpValidator( QRegExp("[A-Za-z]+"), this ));
    ui->the_lastname->setValidator(new QRegExpValidator( QRegExp("[A-Za-z]+"), this ));
    De.STATS()->setParent(ui->stats);

    ui->quickWidget->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
    ui->quickWidget->show();

    int ret=C.connect_arduino();
    qDebug() <<"ret="<<ret;
    switch(ret){
    case(0):qDebug()<<"Arduino is available and connected to : "<< C.getarduino_port_name();
        break;
    case(1):qDebug()<<"Arduino is available but not connected to : "<< C.getarduino_port_name();
        break;
    case(-1):qDebug()<<"Arduino is not available ";
    }

    QObject::connect(C.getserial(),SIGNAL(readyRead()),this,SLOT(Read()));



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Read()
{
   data= C.read_from_arduino();//clothes
       if(data=="1")
       {
           C.write_to_arduino("1");
           // Generate the next ID
                   QSqlQuery query("SELECT MAX(donation_id) FROM donations");
                   query.next();
                   QString lastId = query.value(0).toString();
                   int nextIndex = lastId.isEmpty() ? 1 : lastId.right(3).toInt() + 1;  // extract the numeric part of the ID and increment it
                   QString donation_id = "DON" + QString("%1").arg(nextIndex, 3, 10, QChar('0')); // create the new ID


                //setting default values
               double amount=0;
           int quantity=0;
           //ui->le_id->hide();

           //QString donation_id=ui->le_id->text();
           QString category_name = "clothes";
           QString name="Unkown";
           QString phone_number="Unkown";
           QString description="Unkown";

           donation D(donation_id,category_name,name,description,amount,quantity,phone_number);
           bool test=D.ajouter();
           if(test)
           {
               //Refresh (actualiser)
               // ui->tab_donation->setModel(Etmp.afficher());

           //QMessageBox::information(nullptr, QObject::tr("OK"),
          // QObject::tr("Ajout effectué\n"
                       // "Click cancel to exit."),QMessageBox::Cancel);
               qDebug()<<"added";
           }
           else
           QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
           QObject::tr("Ajout non effectué\n"
                        "Click cancel to exit."),QMessageBox::Cancel);
       }
       else
           C.write_to_arduino("0");
       if(data=="2")//food
       {
           // Generate the next ID
                   QSqlQuery query("SELECT MAX(donation_id) FROM donations");
                   query.next();
                   QString lastId = query.value(0).toString();
                   int nextIndex = lastId.isEmpty() ? 1 : lastId.right(3).toInt() + 1;  // extract the numeric part of the ID and increment it
                   QString donation_id = "DON" + QString("%1").arg(nextIndex, 3, 10, QChar('0')); // create the new ID


                //setting default values
               double amount=0;
           int quantity=0;
           //ui->le_id->hide();

           //QString donation_id=ui->le_id->text();
           QString category_name = "food";
           QString name="Unkown";
           QString phone_number="Unkown";
           QString description="Unkown";

           donation D(donation_id,category_name,name,description,amount,quantity,phone_number);
           bool test=D.ajouter();
           if(test)
           {
               //Refresh (actualiser)
               // ui->tab_donation->setModel(Etmp.afficher());

           //QMessageBox::information(nullptr, QObject::tr("OK"),
          // QObject::tr("Ajout effectué\n"
                       // "Click cancel to exit."),QMessageBox::Cancel);
               qDebug()<<"added";
           }
           else
           QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
           QObject::tr("Ajout non effectué\n"
                        "Click cancel to exit."),QMessageBox::Cancel);
       }
  /*
   float value = data.toFloat();
   qDebug()<<"value:"<<value;
   float x=6;//3ordh boite
   if(value<x)
   {
       //add dons
   }*/
}
void MainWindow::centerAndResize() {

   // get the dimension available on this screen
   QSize availableSize = qApp->desktop()->availableGeometry().size();
   int width = availableSize.width();
   int height = availableSize.height();
   qDebug() << "Available dimensions " << width << "x" << height;
   width *= 0.6; // 90% of the screen size
   height *= 0.74; // 90% of the screen size
   qDebug() << "Computed dimensions " << width << "x" << height;
   QSize newSize( width, height );
   setGeometry(
       QStyle::alignedRect(
           Qt::LeftToRight,
           Qt::AlignCenter,
           newSize,
           qApp->desktop()->availableGeometry()
       )
   );
}

void MainWindow::on_pb_add_clicked()
{
   QString fn=ui->the_firstname->text();
   QString ln=ui->the_lastname->text();
   QString c=ui->the_contact->text();
   int level=ui->the_level->value();
   //QString id=ui->the_id->text();
   ui->the_id->setEnabled(false);
   Destitute De;
   // Retrieve the maximum ID value from the query result
   QSqlQuery qry;
       qry.prepare(" SELECT MAX (DESTITUTE_ID) FROM DESTITUE ");

       if (!qry.exec())
       {
           // Error handling
           qDebug() << "Failed to execute query:" << qry.lastError().text();
           QString id="DES"+QString::number(-1);
           qDebug() <<"id=" <<id;
        Destitute D(id,fn,ln,level,c);
       }

       else
       {
          if (qry.next())
          {
              QString lastID = qry.value(0).toString();
           int i = lastID.section(QRegularExpression("[^\\d]+"), 1).toInt();
           //int i=lastID.toInt();
           qDebug() <<"last ID=" <<lastID;
          qDebug() <<"i=" <<i;
          QString id="DES"+QString::number(++i);
          qDebug() <<"id=" <<id;
       Destitute D(id,fn,ln,level,c);
       bool test=D.Add();
       if(test)
       {
           //REFRESH
           ui->showtab->setModel(De.Show());
           ui->listQR->setModel(De.Show());
           QMessageBox::information(nullptr, QObject::tr("OK"),
                       QObject::tr("Added successfuly.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
           MainWindow w;
            ui->pb_clear->click();
          // w.on_pb_clear_clicked();

       }
       else
           QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                       QObject::tr("NOT ADDED.\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);


           //return i;
          }
          else
             { QString id="DES"+QString::number(-1);
              qDebug() <<"id=" <<id;
           Destitute D(id,fn,ln,level,c);
          }

       }

}

void MainWindow::on_pb_delete_clicked()
{
    ui->the_id->setEnabled(true);
    QString id=ui->the_id->text();
    bool test=De.Delete(id);
    if(test)
    {
        //REFRESH
        ui->showtab->setModel(De.Show());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Deleted successfuly.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        MainWindow w;
         ui->pb_clear->click();

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("NOT Deleted.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pb_update_clicked()
{
    QString fn=ui->the_firstname->text();
    QString ln=ui->the_lastname->text();
    QString c=ui->the_contact->text();
    int level=ui->the_level->value();
    QString id=ui->the_id->text();
     Destitute D(id,fn,ln,level,c);
     bool test=D.Update(id);
     if(test)
     {
         //REFRESH
         ui->showtab->setModel(De.Show());
         QMessageBox::information(nullptr, QObject::tr("OK"),
                     QObject::tr("Updated successfuly.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);
         MainWindow w;
          ui->pb_clear->click();

     }
     else
         QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                     QObject::tr("NOT Updated.\n"
                                 "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_showtab_activated(const QModelIndex &index)
{
    ui->the_id->setEnabled(false);
    QString val=ui->showtab->model()->data(index).toString();
     qDebug()<< "VAL= "<<val;
    Destitute D;
    QSqlQuery query;
    query=D.Edit(val);

    if (query.exec())
    {
            while(query.next())
            {
            ui->the_id->setText(query.value(0).toString());
            ui->the_firstname->setText(query.value(1).toString());
            ui->the_lastname->setText(query.value(2).toString());
            ui->the_level->setValue(query.value(3).toInt());
            ui->the_contact->setText(query.value(4).toString());
            }

    }
    else
    {
       // QMessageBox::critical(this, QObject::tr("Not OK"),query.lastError().text());

        qDebug()<< "ERROR: "<<query.lastError().text();
     }

}



void MainWindow::on_pb_search_clicked()
{
    QString val=ui->the_search->text();
    ui->showtab->setModel(De.Search(val));
}

void MainWindow::on_pb_sort_clicked()
{
    ui->showtab->setModel(De.Sort());
}

void MainWindow::on_pb_pdf_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", QDir::homePath(), "PDF files (*.pdf)");
    if (fileName.isEmpty())
                return;
    //De.PDF(fileName);
    QString strStream;
    QTextStream out(&strStream);
    // Add the current date to the PDF
        QDateTime currentDateTime = QDateTime::currentDateTime();
        QString dateString = currentDateTime.toString("dd/MM/yyyy hh:mm:ss");
    out <<  "<html>\n"
                    "<head>\n"
                    "<meta Content=\"Text/html; charset=Windows-1251\">\n"

                    <<  "</head>\n"
                    "<body bgcolor=#FDFEFE link=#5000A0>\n"
                        "<th colspan='2' style='text-align: right;'>Date: " + dateString + "</th>\n"
                                "</tr>\n"
                        "<h2>NUMBER OF DESTITUTES ACCORDING TO THEIR CONTACT</h1>"
                        "<table border=1 cellspacing=0 cellpadding=2>\n";

            // headers

            out << "<thead><tr bgcolor=#F5B7B1>";
                    out << QString("<th>contact</th>");
                    out << QString("<th>number</th>");

             out << "</tr></thead>\n";
            // data table
             QSqlQueryModel * model=new QSqlQueryModel();
             QSqlQuery query;
                 query.prepare("SELECT CONTACT , COUNT(*) FROM DESTITUE GROUP BY CONTACT");
                 if (!query.exec()) {
                     qDebug() << "Failed to execute query";
                 }
                         else
                 {
                 model->setQuery(query);
            for (int row = 0; row < model->rowCount(); row++) {
                out << "<tr>";

                QModelIndex index = model->index(row, 0);
                                QString contact = model->data(index).toString();

                                index = model->index(row, 1);
                                QString count = model->data(index).toString();
                       out << QString("<td bkcolor=0>%1</td>").arg(contact);
                       out << QString("<td bkcolor=0>%1</td>").arg(count);

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
}

void MainWindow::on_pb_clear_clicked()
{
    ui->the_id->clear();
    ui->the_firstname->clear();
    ui->the_lastname->clear();
    ui->the_level->clear();
    ui->the_contact->clear();
}
/*
void MainWindow::on_pushButton_clicked()
{
    QString id=ui->id->text();
    QString data=De.getData(id);
    QImage img=De.generateQRCode(data);
    ui->qr_code->setPixmap(QPixmap::fromImage(img));

}
*/
void MainWindow::on_listQR_activated(const QModelIndex &index)
{
    QString val=ui->listQR->model()->data(index).toString();
     qDebug()<< "VAL= "<<val;
     QString data=De.getData(val);
     QImage img=De.generateQRCode(data);
     ui->qr_code->setPixmap(QPixmap::fromImage(img));
}
