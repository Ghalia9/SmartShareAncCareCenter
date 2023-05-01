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
#include "QZXing/QZXing.h"
//#include <QZXing>
#include <QImage>
//Map
#include <QtNetwork/QNetworkAccessManager>
#include <QtLocation/QGeoCodingManager>
//#include <QtLocation/QGeoSe>
//#include <QtPositioning/QGeosea>
#include <QtQuick/QQuickItem>
#include <QtLocation>
#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
//
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariantMap>
#include <QVariantList>
#include <QGeoCoordinate>
//#include <QMapboxGL>
//#include <QMapboxGLMap>

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

QImage Destitute::generateQRCode(QString data)
{
    qDebug() << "here";
    QZXing qrCode;
        qrCode.setDecoder(QZXing::DecoderFormat_QR_CODE);
        QImage image = qrCode.encodeData(data);
        return image;
}

QString Destitute::getData(QString id)
{
    qDebug()<<"id="<<id;
    QString result;
    QSqlQuery query;

          query.prepare("SELECT * FROM DESTITUE WHERE ((DESTITUTE_ID= :val) OR (FIRST_NAME= :val) OR (LAST_NAME= :val) OR (CONTACT= :val ) )");
   //       query.prepare("SELECT * FROM DESTITUE WHERE ( (DESTITUTE_ID= :id) )");
          query.bindValue(":val",id);
          query.exec();
          if (!query.exec()) {
              qDebug() << "Failed to execute query";
              }
          else
          {

          while (query.next()) {
              result += "The destitute's name is ";
              result += query.value(1).toString(); // Ajouter la première colonne
              result += " " + query.value(2).toString(); // Ajouter la deuxième colonne
              result += " his/her destitute level is " + query.value(3).toString(); // Ajouter la troisième colonne
              result += " and is located in " + query.value(4).toString();
              // Ajouter d'autres colonnes si nécessaire
          }
          }
          qDebug()<<result;
          return result;
}
/*
void pinLocationOnMap(QString location, QMapboxGLMap *map)
{
    // Step 1: Get the latitude and longitude of the location using Mapbox Geocoding API

    QNetworkAccessManager *manager = new QNetworkAccessManager();
    QUrl url("https://api.mapbox.com/geocoding/v5/mapbox.places/" + location + ".json?access_token=<your_access_token>");
    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QString response = reply->readAll();
            QJsonDocument jsonResponse = QJsonDocument::fromJson(response.toUtf8());
            QJsonObject jsonObject = jsonResponse.object();
            QJsonArray features = jsonObject["features"].toArray();
            if (!features.isEmpty()) {
                QJsonObject geometry = features[0].toObject()["geometry"].toObject();
                double longitude = geometry["coordinates"].toArray()[0].toDouble();
                double latitude = geometry["coordinates"].toArray()[1].toDouble();

                // Step 2: Add a marker at the location on the Mapbox GL map

                map->addMarker(QMapboxGL::MarkerOptions()
                               .setPosition(QGeoCoordinate(latitude, longitude))
                               .setIcon(QIcon(":/marker.png")) // Replace with your marker icon
                               .setAnchor(QPointF(0.5, 1.0))); // Set anchor point to bottom center of marker icon
            }
        } else {
            // Handle the error
        }
        reply->deleteLater();
        manager->deleteLater();
    });
}

*/

void Destitute::pinLocationOnMap(QQuickItem *mapItem, const QString &locationString)
{
    qDebug()<<"hiii";
    // Create a QNetworkAccessManager to perform the HTTP request
    QNetworkAccessManager *manager = new QNetworkAccessManager(mapItem);

    // Create the request URL with the location string
    //QString urlString = QString("https://maps.googleapis.com/maps/api/geocode/json?address=%1").arg(locationString);
    QString urlString = QString("https://maps.googleapis.com/maps/api/geocode/json?address=tunis");

    // Create the HTTP request
    QNetworkRequest request;
    request.setUrl(QUrl(urlString));

    // Perform the HTTP request and connect to the finished() signal to retrieve the result
    QNetworkReply *reply = manager->get(request);
    QObject::connect(reply, &QNetworkReply::finished, [=]() {
        if (reply->error() != QNetworkReply::NoError) {
            qWarning() << "HTTP request error:" << reply->errorString();
            //added
            reply->deleteLater();
            manager->deleteLater();
            return;
        }

        // Parse the JSON response
        QByteArray data = reply->readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        QJsonObject obj = doc.object();

        // Check if the response status is OK
        QString status = obj.value("status").toString();
        if (status != "OK") {
            qWarning() << "Geocoding error:" << status;
            //added
            reply->deleteLater();
            manager->deleteLater();
            return;
        }

        // Retrieve the first result
        QJsonArray results = obj.value("results").toArray();
        if (results.isEmpty()) {
            qWarning() << "No results found for location:" << locationString;
            //added
            reply->deleteLater();
            manager->deleteLater();
            return;
        }
        QJsonObject location = results.at(0).toObject().value("geometry").toObject().value("location").toObject();

        // Retrieve the coordinates of the first result
        double latitude = location.value("lat").toDouble();
        double longitude = location.value("lng").toDouble();
        qDebug() << "Latitude:" << latitude << ", Longitude:" << longitude;

        // Create a new map object and set its properties
        QMetaObject::invokeMethod(mapItem, "addMapItem", Q_ARG(QVariant, latitude),
                                  Q_ARG(QVariant, longitude), Q_ARG(QVariant, locationString),
                                  Q_ARG(QVariant, true));
            //added
        reply->deleteLater();
                manager->deleteLater();
    });
}


/*
void pinAddress(QGeoMap *map, const QString &address, const QString &name)
{
    // Create a geocoding manager
    QGeoServiceProvider provider("osm");
    QGeoCodingManager *manager = provider.geocodingManager();

    // Create a geocoding request for the address
    QGeoAddress geoAddress;
    geoAddress.setCountry("default"); // Set the country to avoid ambiguity
    geoAddress.setText(address);
    QGeoCodeReply *reply = manager->geocode(geoAddress);

    // Connect a slot to handle the geocoding result
    QObject::connect(reply, &QGeoCodeReply::finished, map, [=]() {
        if (reply->error() == QGeoCodeReply::NoError) {
            // Get the first location from the result list
            QGeoLocation location = reply->locations().first();

            // Create a new map item at the location
            QGeoMapItem *item = new QGeoMapItem(location.coordinate());
            item->setLabel(name);

            // Add the item to the map
            map->addMapItem(item);
        }

        // Clean up the reply object
        reply->deleteLater();
    });
}*/
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

