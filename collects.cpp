#include "collects.h"
#include <QSqlQuery>
#include <QtDebug>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
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
    // Get the Collect data from the object's attributes
    QString Collect_ID = this->Collect_ID;
    QString Collect_name = this->Collect_name;
    QString location = this->location;
    QDate collect_date = this->collect_date;
    double collect_budget = this->collect_budget;
    double collections = this->collections;
    QString description_c = this->description_c;

    // Check if there are enough funds for this event
    QSqlQuery query("SELECT TOTAL FROM TOTALDONS WHERE CATEGORY='money'");
    query.next();
    double total = query.value(0).toDouble();
    if (total >= collect_budget) {
        // Subtract the collect_budget from the total and update the TOTALDONS table
        total -= collect_budget;
        QSqlQuery updateQuery;
        updateQuery.prepare("UPDATE TOTALDONS SET TOTAL=:total WHERE CATEGORY='money'");
        updateQuery.bindValue(":total", total);
        updateQuery.exec();

        // Add the collections to the total budget and update the TOTALDONS table
        total += collections;
        updateQuery.prepare("UPDATE TOTALDONS SET TOTAL=:total WHERE CATEGORY='money'");
        updateQuery.bindValue(":total", total);
        updateQuery.exec();

        // Add the Collect to the database
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
        if(query.exec())
            return true;
        else
            return false;
    } else {
        // Show a message box indicating that there are not enough funds for this event
        QMessageBox::critical(nullptr, "Error", "There are not enough funds for this event.");
        return false;
    }
}

QSqlQueryModel * Collects::afficher()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM Collects ORDER BY collect_id ASC");

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
    query.prepare("DELETE FROM Collects WHERE LOWER(COLLECT_ID) = LOWER(:id)");
    query.bindValue(":id", Collect_ID);
    return query.exec();
}


bool Collects :: modifier()
{
    QSqlQuery query;
        query.prepare("UPDATE COLLECTS SET COLLECT_NAME = :collect_name, LOCATION = :location, COLLECT_DATE = :collect_date, COLLECT_BUDGET = :collect_budget, COLLECTIONS = :collections, DESCRIPTION_C = :description_c WHERE COLLECT_ID LIKE '"+Collect_ID+"%'");
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


    model->setQuery("SELECT * FROM Collects where COLLECT_ID LIKE '"+recherche+"%' OR LOWER(COLLECT_ID) LIKE '"+recherche+"%' OR UPPER(COLLECT_ID) LIKE '"+recherche+"%' ");

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
  model->setQuery("SELECT * FROM COLLECTS order by COLLECT_DATE ASC");
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
QString Collects::getLastId()
{
    QSqlQuery query;
    QString lastId = "";

    if(query.exec("SELECT Collect_id FROM COLLECTS ORDER BY Collect_ID DESC LIMIT 1"))
    {
        if(query.next())
        {
            lastId = query.value(0).toString();
        }
    }

    return lastId;
}

QString Collects::generateNextId()
{
    QSqlQuery query;
    QString nextId = "";
    QString lastId = "";

    if(query.exec("SELECT MAX(Collect_id) FROM COLLECTS"))
    {
        if(query.next())
        {
            lastId = query.value(0).toString();
        }
    }

    if(lastId.isEmpty())
    {
        nextId = "COL-001";
    }
    else
    {
        QString lastIdSuffix = lastId.right(3);
        int lastIdSuffixInt = lastIdSuffix.toInt();
        int nextIdSuffixInt = lastIdSuffixInt + 1;
        QString nextIdSuffix = QString::number(nextIdSuffixInt, 10).rightJustified(3, '0');
        nextId = "COL-" + nextIdSuffix;
    }

    return nextId;
}
QSqlQuery Collects::Edit(QString val)
{
    QSqlQuery query;
    bool test=true;
    for (const QChar& c: val)
    {
        if(!c.isDigit())
            test =false;
    }
    qDebug()<<"test="<<test;
    if(test)
    {
        //int x;
      //  x=QString(val).toInt();
        query.prepare("SELECT * FROM COLLECTS WHERE ( (Collect_ID= :val) )");
        //query.bindValue(":val",x);
    }
    else
    {
        bool ok;
        double budget = val.toDouble(&ok);
        if (ok) {
            query.prepare("SELECT * FROM Collects WHERE ((Collect_ID= :val) OR (Collect_name= :val) OR (Collect_date= :val) OR (Collect_budget= :budget ) )");
            query.bindValue(":budget", budget);
        } else {
            query.prepare("SELECT * FROM Collects WHERE ((Collect_ID= :val) OR (Collect_name= :val) OR (Collect_date= :val))");
        }
        query.bindValue(":val",val);
    }
    return  query;
}
QSqlQueryModel * Collects::afficher2()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select contact from Employees ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CONTACT"));


    return model;
}
