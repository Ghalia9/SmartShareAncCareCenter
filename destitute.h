#ifndef DESTITUTE_H
#define DESTITUTE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>

#include <QImage>
//map
#include <QtNetwork/QNetworkAccessManager>
#include <QtLocation/QGeoCodingManager>
//#include <QtLocation/QGeoSe>
//#include <QtPositioning/QGeosea>
#include <QtQuick/QQuickItem>

#include <QtNetwork/QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
class Destitute
{
    QString destitute_id,first_name,last_name,contact;
    int destitute_level;

public:
    //CONSTRUCTURS
    Destitute();
    Destitute(QString,QString,QString,int,QString);

    //GETTERS
    QString getid(){return destitute_id;}
    QString getfirstname(){return first_name;}
    QString getlastname(){return last_name;}
    QString getcontact(){return contact;}
    int getlevel(){return destitute_level;}

    //SETTERS
    void setid(QString id){destitute_id=id;}
    void setfirstname(QString nom){first_name=nom;}
    void setlastname(QString prenom){last_name=prenom;}
    void setcontact(QString cont){contact=cont;}
    void setlevel(int l){destitute_level=l;}

    //FONCTIONS
    bool Add();
    QSqlQueryModel * Show();
    bool Delete(QString);
    bool Update(QString);
    QSqlQuery Edit(QString);
    int getmaxId();
    QSqlQueryModel * Search(QString);
    QSqlQueryModel * Sort();
    void PDF(QString);
    QChartView * STATS();
    void Clear();
    QImage generateQRCode(QString);
    QString getData(QString);
    void pinLocationOnMap(QQuickItem *mapItem, const QString &locationString);

};

#endif // DESTITUTE_H
