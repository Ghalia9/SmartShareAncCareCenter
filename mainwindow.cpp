#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "destitute.h"
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

/*
    // Create a QQuickView to display the QML content
        QQuickView *view = new QQuickView();
        view->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
       // view.show();
        if (view->status() == QQuickView::Error) {
            qDebug() << "Error loading QML file:" << view->errors();
        } else {
             qDebug() << "QML file loaded";
        // Create a widget to contain the QQuickView
        QWidget *container = QWidget::createWindowContainer(view, this);

        // Create a layout for the container widget
        QVBoxLayout *layout = new QVBoxLayout(ui->centalWidgetM);
        layout->addWidget(container);

}*/
   // ui->quickMap->setSource(QUrl(QStringLiteral("qrc:/main.qml")));
   // ui->quickMap->show();
   // ui->map->show();
    /*QQuickView view;
        view.setResizeMode(QQuickView::SizeRootObjectToView);
        view.setSource(QUrl("qrc:/main.qml"));
        view.show();


        // Get a pointer to the map item
            QQuickItem *mapItem = view.rootObject()->findChild<QQuickItem*>("mapItem");
      //  QtQuick::QQuickItem *mapItem = view.rootObject()->findChild<QtQuick::QQuickItem*>("mapItem");

            // Pin a location on the map
            QString locationString = "Paris, France";
            De.pinLocationOnMap(mapItem, locationString);
            */
/*
    QPieSeries *series = new QPieSeries();
        series->setHoleSize(0.35);
        series->append("Protein 4.28%", 4.28);
        QPieSlice *slice = series->append("Fat 15.6%", 15.6);

        slice->setExploded();
        slice->setLabelVisible();
        series->append("Other 23.8%", 23.8);
        series->append("Other 56.4%", 56.4);


        QChart *chart = new QChart();
        chart->addSeries(series);
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->setTitle("Donut Chart Example");
        chart->setTheme(QChart::ChartThemeBlueCerulean);


        QChartView *chartview = new QChartView(chart);
        chartview->setRenderHint(QPainter::Antialiasing);

        chartview->setParent(ui->stats);
        */
}

MainWindow::~MainWindow()
{
    delete ui;
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
