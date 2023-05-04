#ifndef COLLECTS_H
#define COLLECTS_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>

class Collects
{
private:
    QString Collect_ID;
    QString Collect_name;
    QString location;
    QDate collect_date;
    double collect_budget;
    double collections;
    QString description_c;


public:
    Collects(){};
    Collects(QString Collect_ID, QString Collect_name, QString location,
             QDate collect_date, double collect_budget, double collections,
             QString description_c);

    QString getCollectID() {return Collect_ID;};
    QString getCollectName() const{return Collect_name;};
    QString getLocation() const{return location;};
    QDate getCollectDate() const{return collect_date;};
    float getCollectBudget() const{return collect_budget;};
    float getCollections() const{return collections;};
    QString getDescription() const{return description_c;};
//    void setID(int id){this->id=id;}

    void setCollectID(QString Collect_ID){this->Collect_ID=Collect_ID;};
    void setCollectName(const QString& Collect_name);
    void setLocation(const QString& location);
    void setCollectDate(const QDate& collect_date);
    void setCollectBudget(float collect_budget);
    void setCollections(float collections);
    void setDescription(const QString& description_c);


    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(QString);
    bool modifier();
    QSqlQueryModel* rechercherID(QString );
    QSqlQueryModel* rechercherDate(QString );
    QSqlQueryModel* rechercherName(QString );
QSqlQueryModel * afficher2();
   QSqlQueryModel * triDate();
   QSqlQueryModel * triCollects();
   QSqlQueryModel * triCosts();
   static QString getLastId();
   QString generateNextId();
   QSqlQuery Edit(QString val);



};
#endif // COLLECTS_H


