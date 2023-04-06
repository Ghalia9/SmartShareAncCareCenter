#include "donations.h"

donation::donation(int quantity,double amount,QString donation_id,QString category_name,QString name,QString description,QString phone_number)
{
    this->quantity=quantity;
    this->amount=amount;
    this->donation_id=donation_id;
    this->category_name=category_name;
    this->name=name;
    this->description=description;
    this->phone_number=phone_number;


}
bool donation::ajouterD()
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


QSqlQueryModel * donation::afficherD()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from donations ORDER BY CATEGORY_NAME");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("DONATION_ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("CATEGORY_NAME"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NAME"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DESCRIPTION"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("AMOUNT"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("QUANTITY"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("PHONE NUMBER"));

    return model;
}





