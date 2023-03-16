#ifndef COLLECTS_H
#define COLLECTS_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDate>

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
    QString getCollectName() const;
    QString getLocation() const;
    QDate getCollectDate() const;
    float getCollectBudget() const;
    float getCollections() const;
    QString getDescription() const;
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
    bool modifier(QString Collect_ID);
    QSqlQueryModel* rechercherID(QString );
    QSqlQueryModel* rechercherDate(QString );
    QSqlQueryModel* rechercherName(QString );

   QSqlQueryModel * triDate();
   QSqlQueryModel * triCollects();
   QSqlQueryModel * triCosts();


};
#endif // COLLECTS_H


