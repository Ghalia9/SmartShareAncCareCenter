#include "donation.h"
#include <QPrinter>
#include <QTextDocument>
#include <QSqlRecord>
#include <QTextCursor>
#include <QDebug>
#include <QPainter>
#include <QMessageBox>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QToolButton>








donation::donation(QString donation_id,QString category_name,QString name,QString description,double amount,int quantity,QString phone_number)
{
    this->donation_id=donation_id;
    this->category_name=category_name;
    this->name=name;
    this->description=description;
    this->amount=amount;
    this->quantity=quantity;
    this->phone_number=phone_number;


}
bool donation::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(quantity);
    QString res1 = QString::number(amount);

    //prepare() prend la requete en parametre pour la preparer à léxecution

    query.prepare("insert into donations (quantity,amount,donation_id,category_name,name,description,phone_number)" "values (:quantity,:amount,:donation_id,:category_name,:name,:description,:phone_number)");
    //creation des variables liees

    query.bindValue(":quantity",res);
    query.bindValue(":amount",res1);
    query.bindValue(":donation_id",donation_id);
    query.bindValue(":category_name",category_name);
    query.bindValue(":name",name);
    query.bindValue(":description",description);
    query.bindValue(":phone_number",phone_number);


    return query.exec(); //exec() envoie la requete pour l'execution
}


QSqlQueryModel * donation::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from donations ORDER BY CATEGORY_NAME");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("DONATION_ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("CATEGORY_NAME"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NAME"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DESCRIPTION"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("QUANTITY"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("AMOUNT"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("PHONE NUMBER"));

    return model;
}


bool donation::supprimer(QString donation_id)
{
QSqlQuery query;
query.prepare("Delete from donations where donation_id= :donation_id");
query.bindValue(":donation_id",donation_id);
query.exec();
return query.exec();
}


bool donation :: modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE DONATIONS SET DONATION_ID = :donation_id, CATEGORY_NAME = :category_name, NAME = :name, DESCRIPTION = :description,  QUANTITY = :quantity, AMOUNT = :amount,PHONE_NUMBER = :phone_number WHERE DONATION_ID LIKE '"+donation_id+"%'");

        query.bindValue(":donation_id", donation_id);
        query.bindValue(":category_name", category_name);
        query.bindValue(":name",name );
        query.bindValue(":description", description);
        query.bindValue(":quantity", quantity);
        query.bindValue(":amount", amount);
        query.bindValue(":phone_number", phone_number);
      query.exec();
       return  query.exec();
}
QSqlQueryModel* donation ::rechercherID(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM donations" );
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("donation_id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("category_name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("description"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("quantity"));

    model->setHeaderData(4, Qt::Horizontal, QObject::tr("amount"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("phone_number"));

    return model;
}


QSqlQueryModel * donation::sortID()
{
  QSqlQueryModel* model=new QSqlQueryModel();
  model->setQuery("SELECT * FROM donations order by DONATION_ID ASC");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("donation_id"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("category_name"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("name"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("description"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("quantity"));

  model->setHeaderData(4, Qt::Horizontal, QObject::tr("amount"));
  model->setHeaderData(6, Qt::Horizontal, QObject::tr("phone_number"));
  return model;

}
QSqlQueryModel * donation::sortCategoryName()
{
  QSqlQueryModel* model=new QSqlQueryModel();
  model->setQuery("SELECT * FROM donations order by CATEGORY_NAME ASC");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("donation_id"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("category_name"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("name"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("description"));
  model->setHeaderData(5, Qt::Horizontal, QObject::tr("quantity"));

  model->setHeaderData(4, Qt::Horizontal, QObject::tr("amount"));
  model->setHeaderData(6, Qt::Horizontal, QObject::tr("phone_number"));
  return model;


}

QSqlQueryModel* donation::rechercherCategoryName(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM donations where CATEGORY_NAME LIKE '"+recherche+"%' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("donation_id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("category_name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("description"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("quantity"));

    model->setHeaderData(4, Qt::Horizontal, QObject::tr("amount"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("phone_number"));
    return model;
}
QSqlQueryModel* donation::recherchernom(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM DONATIONS where NAME LIKE '"+recherche+"%' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("donation_id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("category_name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("description"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("quantity"));

    model->setHeaderData(4, Qt::Horizontal, QObject::tr("amount"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("phone_number"));
    return model;
}

QSqlQueryModel* donation ::rechercherID2(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM donations where DONATION_ID LIKE '"+recherche+"%'" );

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("donation_id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("category_name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("description"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("quantity"));

    model->setHeaderData(4, Qt::Horizontal, QObject::tr("amount"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("phone_number"));
    return model;
}
QSqlQueryModel * donation::afficher2()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from totaldons ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CATEGORY"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("TOTAL"));


    return model;
}
