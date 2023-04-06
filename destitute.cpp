#include "destitute.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>
#include <QSqlError>
#include <QRegularExpression>
#include <QPrinter>
#include <QPdfWriter>
#include <QPainter>
#include <QtSql>
#include <QMessageBox>
//stats
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
//QrCode
#include <QZXing>
#include <QImage>

Destitute::Destitute()
{
    destitute_id="0";
    first_name="";
    last_name="";
    destitute_level=-1;
    contact="";
}

Destitute::Destitute(QString id,QString fn,QString ln,int l,QString c)
{
    destitute_id=id;
    first_name=fn;
    last_name=ln;
    destitute_level=l;
    contact=c;

}

bool Destitute::Add()
{
    QSqlQuery query;
    QString level_string=QString::number(destitute_level);
          query.prepare("INSERT INTO DESTITUE (DESTITUTE_ID, FIRST_NAME, LAST_NAME, DESTITUTE_LEVEL, CONTACT) VALUES (:DESTITUTE_ID, :FIRST_NAME, :LAST_NAME, :DESTITUTE_LEVEL, :CONTACT)");
          query.bindValue(":DESTITUTE_ID", destitute_id);
          query.bindValue(":FIRST_NAME", first_name);
          query.bindValue(":LAST_NAME", last_name);
          query.bindValue(":DESTITUTE_LEVEL",level_string);
          query.bindValue(":CONTACT", contact);
          return query.exec();

}

QSqlQueryModel * Destitute::Show()
{
    QSqlQueryModel * model=new QSqlQueryModel();
          model->setQuery("SELECT * FROM DESTITUE");
     return model;
}


bool Destitute::Delete(QString id)
{
    QSqlQuery query;
    query.prepare("DELETE FROM DESTITUE WHERE DESTITUTE_ID= :id");
    query.bindValue(":id",id);
    return  query.exec();
}

bool Destitute::Update(QString id)
{
    QSqlQuery query;
    QString level_string=QString::number(destitute_level);
          query.prepare(" UPDATE DESTITUE SET FIRST_NAME = :FIRST_NAME, LAST_NAME =:LAST_NAME, DESTITUTE_LEVEL =:DESTITUTE_LEVEL, CONTACT =:CONTACT WHERE DESTITUTE_ID = :DESTITUTE_ID");
          query.bindValue(":DESTITUTE_ID", id);
          query.bindValue(":FIRST_NAME", first_name);
          query.bindValue(":LAST_NAME", last_name);
          query.bindValue(":DESTITUTE_LEVEL",level_string);
          query.bindValue(":CONTACT", contact);
          return query.exec();
}
QSqlQuery Destitute::Edit(QString val)
{
    QSqlQuery query;
    bool test=true; //to be compatible with diffrent type of data :test to transform back to int when needed for the level
    for (const QChar& c: val)
    {
        if(!c.isDigit())
            test =false;
    }
    qDebug()<<"test="<<test;
    if(test)
    {
        int x;
        x=QString(val).toInt();
        query.prepare("SELECT * FROM DESTITUE WHERE ( (DESTITUTE_LEVEL= :val) )");
        query.bindValue(":val",x);
    }
    else
    {
    query.prepare("SELECT * FROM DESTITUE WHERE ((DESTITUTE_ID= :val) OR (FIRST_NAME= :val) OR (LAST_NAME= :val) OR (CONTACT= :val ) )");
    query.bindValue(":val",val);
    }
    return  query;
}

int getmaxId()
{
    QSqlQuery qry;
    qry.prepare(" SELECT MAX (DESTITUTE_ID) FROM DESTITUE ");
/*
    if (query.exec()) {
        if (query.next()) {
            int max = query.value(0).toInt();
            // do something with the max value
            return max;
        }
    } else {
        qDebug() << "Error executing query:" << query.lastError().text();
        return -1;
    }*/

        if (!qry.exec())
        {
            // Error handling
            qDebug() << "Failed to execute query:" << qry.lastError().text();
            return -1;
        }

        // Retrieve the maximum ID value from the query result
        if (qry.next())
        {
            QString lastID = qry.value(0).toString();
            int i = lastID.section(QRegularExpression("[^\\d]+"), 1).toInt();
            //int i=lastID.toInt();
            qDebug() <<"last ID=" <<lastID;
           //qDebug() <<"i=" <<i;
            return i;
        }
        return -1;
}

QSqlQueryModel * Destitute::Search(QString val)
{
    QSqlQuery query;
    QSqlQueryModel * model=new QSqlQueryModel();
          query.prepare("SELECT * FROM DESTITUE WHERE UPPER(CONTACT)= UPPER(:val)");
          query.bindValue(":val",val);
          query.exec();
          model->setQuery(query);
          qDebug()<<"show";
     return model;
}

QSqlQueryModel * Destitute::Sort()
{
    QSqlQuery query;
    QSqlQueryModel * model=new QSqlQueryModel();
          query.prepare("SELECT * FROM DESTITUE ORDER BY DESTITUTE_LEVEL ");
          query.exec();
          model->setQuery(query);
          qDebug()<<"show";
     return model;
}

void Destitute::PDF(QString fileName)
//QSqlQueryModel * Destitute::PDF()
{
    //QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", QDir::homePath(), "PDF files (*.pdf)");

        if (!fileName.isEmpty()) {
    QSqlQueryModel * model=new QSqlQueryModel();
       //QPdfWriter pdfWriter("D:/projet_center/gestion_necessiteus/PDF/fileName.pdf");
    QPdfWriter pdfWriter(fileName );
    pdfWriter.setPageSize(QPageSize(QPageSize::A4));
            pdfWriter.setPageMargins(QMarginsF(10, 10, 10, 10));
            QPainter painter;
            if (!painter.begin(&pdfWriter)) {
                qDebug() << "Failed to open PDF file for writing";
               // return model;
            }

            painter.setRenderHint(QPainter::Antialiasing);
            painter.setRenderHint(QPainter::TextAntialiasing);

            // Set up the font and pen for drawing text
            QFont font("Helvetica", 12);
            QPen pen(Qt::black, 0.5);
            painter.setFont(font);
            painter.setPen(pen);

            // Add the current date to the PDF
                QDateTime currentDateTime = QDateTime::currentDateTime();
                QString dateString = currentDateTime.toString("dd/MM/yyyy hh:mm:ss");
                painter.drawText(7800, 30, dateString);

            painter.drawText(1900,400,"NUMBER OF DESTITUTES ACCORDING TO THEIR CONTACT");
    // Get the number of columns in the query result
    QSqlQuery query;
    query.prepare("SELECT CONTACT , COUNT(*) FROM DESTITUE GROUP BY CONTACT");


    int numRows = query.size();
    qDebug() << "numRows=" << numRows;
    if (!query.exec()) {
        qDebug() << "Failed to execute query";
        QMessageBox::information(nullptr, QObject::tr(":/"),
                    QObject::tr("Problem.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else{
    model->setQuery(query);
    qDebug()<<"pdf:"<<model->rowCount();
    //int numCols = query.record().count();
    // Draw the column headers
    /*       for (int col = 0; col < numCols; col++) {
               QString headerText = query.record().fieldName(col);
               painter.drawText(col * 1000, 900, headerText);
           }
    // Iterate over the rows in the query and draw them onto the PDF

    for (int i = 0; i < model->rowCount(); ++i)
        {
        QModelIndex index = model->index(i, 0); // access the first column of the current row
        QVariant value = model->data(index);
        painter.drawText(1 * 150, 1200 + i * 200, value.toString());
        qDebug() << value.toString(); // print the value

        QModelIndex indexCount = model->index(i, 1); // access the second column of the current row
            QVariant valueCount = model->data(indexCount);
            painter.drawText(5 * 300, 1200 + i * 200, valueCount.toString());
            qDebug() << valueCount.toString(); // print the value
        }*/

    // Create the QTableWidget and set its properties
            QTableWidget *table = new QTableWidget(model->rowCount(), 2);
            table->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            table->setHorizontalHeaderLabels({"CONTACT", "COUNT"});
            table->horizontalHeader()->setStretchLastSection(true);

            // Populate the table with the data from the model
            for (int row = 0; row < model->rowCount(); ++row) {
                QModelIndex index = model->index(row, 0);
                QString contact = model->data(index).toString();

                index = model->index(row, 1);
                QString count = model->data(index).toString();

                table->setItem(row, 0, new QTableWidgetItem(contact));
                table->setItem(row, 1, new QTableWidgetItem(count));
                table->render(&painter, QPoint(2000, 2000));
            }
    QMessageBox::information(nullptr, QObject::tr("OK"),
                         QObject::tr("PDF generated succefully.\n"
                                     "Click Cancel to exit."), QMessageBox::Cancel);
    }

    painter.end();
}
}
QChartView * Destitute::STATS()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    QSqlQuery query;
    query.prepare("SELECT DESTITUTE_LEVEL , COUNT(*) FROM DESTITUE GROUP BY DESTITUTE_LEVEL");

    if (!query.exec()) {
        qDebug() << "Failed to execute query";
        QMessageBox::information(nullptr, QObject::tr(":/"),
                    QObject::tr("Problem.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        QChartView *chartview = new QChartView();
        //chartview->setParent(ui->horizontalFrame);
        return chartview;

    }
    else{
    model->setQuery(query);
    QPieSeries *series = new QPieSeries();
    for (int i = 0; i < model->rowCount(); ++i)
        {
        QModelIndex index = model->index(i, 0); // access the first column of the current row
        QVariant value = model->data(index);
        QString nom=value.toString();
        qDebug() << nom; // print the value

        QModelIndex indexCount = model->index(i, 1); // access the second column of the current row
            QVariant valueCount = model->data(indexCount);
            qreal num =valueCount.toReal();
            qDebug() << num; // print the value
            float val=(num*100)/model->rowCount();
            qDebug() << "%"<<val;
            QString prc=QString::number(val);
            QString aff=nom + "("+prc+"%"+")";
            qDebug() << "msg"<<aff;
            series->append(aff,num);
            //series->setPieSize(0.5);
        }


      /*

    QPieSeries *series = new QPieSeries();
    series->append("level1", 80);
        series->append("level0", 70);
        series->append("level3", 50);
        series->append("level2", 40);
        //series->append("PHP", 30);
*/
        QPieSlice *slice = series->slices().at(1);
            slice->setExploded(true);
            slice->setLabelVisible(true);
            slice->setPen(QPen(Qt::darkGreen, 2));
            slice->setBrush(Qt::green);


            QChart *chart = new QChart();
            chart->addSeries(series);
            chart->setTitle("Destitute level Pie Chart");


            QChartView *chartview = new QChartView(chart);
            //chartview->setParent(ui->horizontalFrame);
            return chartview;


            }
}

QImage  generateQRCode()
{
    qDebug() << "here";
    QZXing qrCode;
    QString data="ghalia chiboub";
        qrCode.setDecoder(QZXing::DecoderFormat_QR_CODE);
        QImage image = qrCode.encodeData(data);
        return image;
}
/*
QImage generateQRCode{
    // Encode text into QR code
    std::wstring wtext = text.toStdWString();
    qrcodegen::QrCode qr = qrcodegen::QrCode::encodeText(wtext.c_str(), qrcodegen::QrCode::Ecc::LOW);

    // Calculate QR code size
    const int s = qr.getSize();
    const int imgSize = 256;
    const double scale = imgSize / static_cast<double>(s);

    // Create image and painter
    QImage image(imgSize, imgSize, QImage::Format_RGB888);
    image.fill(Qt::white);
    QPainter painter(&image);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw QR code
    for (int y = 0; y < s; y++) {
        for (int x = 0; x < s; x++) {
            const bool module = qr.getModule(x, y);
            QRectF r(x * scale, y * scale, scale, scale);
            if (module) {
                painter.fillRect(r, Qt::black);
            }
        }
    }

    return image;
}*/

