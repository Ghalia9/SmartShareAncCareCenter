#include "collects.h"
#include <QSqlQuery>
#include <QtDebug>

Collects::Collects(QString Collect_ID, QString Collect_name, QString location,QDate collect_date, double collect_budget, double collections,QString description_c)
{
    this->Collect_ID = Collect_ID;
    this->Collect_name = Collect_name;
    this->location = location;
    this->collect_date = collect_date;
    this->collect_budget = collect_budget;
    this->collections = collections;
    this->description_c = description_c;
}

bool Collects::ajouter()
{

    QSqlQuery query;
       query.prepare("INSERT INTO Collects (COLLECT_ID, COLLECT_NAME, LOCATION, COLLECT_DATE, COLLECT_BUDGET, COLLECTIONS, DESCRIPTION_C) "
                     "VALUES (:Collect_ID, :Collect_name, :location, :collect_date, :collect_budget, :collections, :description_c)");
       query.bindValue(":Collect_ID", Collect_ID);
       query.bindValue(":Collect_name", Collect_name);
       query.bindValue(":location", location);
       query.bindValue(":collect_date", collect_date);
       query.bindValue(":collect_budget", collect_budget);
       query.bindValue(":collections", collections);
       query.bindValue(":description_c", description_c);
    //    query.exec();
       if(query.exec())
           return true;
       else
           return false;

}


QSqlQueryModel * Collects::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
 model->setQuery("SELECT * FROM Collects");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Collect ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Collect name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Location"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Collect date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Collect budget"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Collections"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Description"));


    return model;
}


bool Collects::supprimer(QString Collect_ID)
{
QSqlQuery query;
query.prepare("Delete from Collects where COLLECT_ID= :id");
query.bindValue(":id",Collect_ID);
query.exec();
return query.exec();
}

bool Collects :: modifier(QString recherche)
{
    QSqlQuery query;
        query.prepare("UPDATE COLLECTS SET COLLECT_ID = :collect_id, COLLECT_NAME = :collect_name, LOCATION = :location, COLLECT_DATE = :collect_date, COLLECT_BUDGET = :collect_budget, COLLECTIONS = :collections, DESCRIPTION_C = :description_c WHERE COLLECT_ID LIKE '"+recherche+"%'");
        query.bindValue(":collect_id", Collect_ID);
        query.bindValue(":collect_name", Collect_name);
        query.bindValue(":location", location);
        query.bindValue(":collect_date", collect_date);
        query.bindValue(":collect_budget", collect_budget);
        query.bindValue(":collections", collections);
        query.bindValue(":description_c", description_c);
        query.exec();
       return  query.exec();
}
QSqlQueryModel* Collects ::rechercherID(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM Collects where COLLECT_ID LIKE '"+recherche+"%' ");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Collect ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Collect name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Location"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Collect date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Collect budget"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Collections"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Description"));
    return model;
}
QSqlQueryModel * Collects::triDate()
{
  QSqlQueryModel* model=new QSqlQueryModel();
  model->setQuery("SELECT * FROM COLLECTS order by COLLECT_DATE DESC");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("Collect ID"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("Collect name"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("Location"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("Collect date"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("Collect budget"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("Collections"));
  model->setHeaderData(6, Qt::Horizontal, QObject::tr("Description"));
     return model;


}
QSqlQueryModel * Collects::triCollects()
{
  QSqlQueryModel* model=new QSqlQueryModel();
  model->setQuery("SELECT * FROM COLLECTS order by COLLECTIONS DESC");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("Collect ID"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("Collect name"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("Location"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("Collect date"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("Collect budget"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("Collections"));
  model->setHeaderData(6, Qt::Horizontal, QObject::tr("Description"));
     return model;


}
QSqlQueryModel * Collects::triCosts()
{
  QSqlQueryModel* model=new QSqlQueryModel();
  model->setQuery("SELECT * FROM COLLECTS order by COLLECT_BUDGET DESC");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("Collect ID"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("Collect name"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("Location"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("Collect date"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("Collect budget"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("Collections"));
  model->setHeaderData(6, Qt::Horizontal, QObject::tr("Description"));
     return model;


}
QSqlQueryModel* Collects::rechercherDate(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();


        model->setQuery("SELECT * FROM Collects WHERE COLLECT_DATE LIKE '%" + recherche + "%'");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Collect ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Collect name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Location"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Collect date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Collect budget"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Collections"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Description"));
    return model;
}
QSqlQueryModel* Collects::rechercherName(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM Collects where COLLECT_NAME LIKE '"+recherche+"%' OR LOWER(COLLECT_NAME) LIKE '"+recherche+"%' OR UPPER(COLLECT_NAME) LIKE '"+recherche+"%'");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Collect ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Collect name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Location"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Collect date"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Collect budget"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Collections"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Description"));
    return model;
}
