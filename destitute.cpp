#include "destitute.h"
#include <QSqlQuery>
#include <QtDebug>
#include <QObject>

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

