#include "service.h"

Service::Service(QString IDservice,QString Dontype,QString serviceName,int Donquantity,double budget_S)
{
    this->IDservice=IDservice;
    this->Dontype=Dontype;
    this->serviceName=serviceName;
    this->budget_S=budget_S;
    this->Donquantity=Donquantity;
}
bool Service::ajouter()
{
    QSqlQuery query;
    //prepare() prend la requete en parametre pour la preparer à léxecution

    query.prepare("insert into services (IDservice,Dontype, serviceName, Donquantity, budget_S )" "values (:IDservice,:Dontype ,:serviceName, :Donquantity, :budget_S)");
    //creation des variables liees

    query.bindValue(":IDservice", IDservice);
    query.bindValue(":Dontype", Dontype);
    query.bindValue(":serviceName", serviceName);
    query.bindValue(":Donquantity", Donquantity);
    query.bindValue(":budget_S", budget_S);


    //query.exec();
    if(query.exec())
        return true;
    else
        return false;
}


QSqlQueryModel * Service::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from Services");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDservice"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Dontype"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("serviceName"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Donquantity"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("budget_S"));

    return model;
}

QSqlQueryModel * Service::afficherStock(QString IDservice)
{
    QSqlQueryModel * model=new QSqlQueryModel();
    QString queryStr = "SELECT * FROM Services WHERE IDservice = :IDservice";
    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":IDservice", IDservice);
    if(query.exec()){
        model->setQuery(query);
        model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDservice"));
        model->setHeaderData(1,Qt::Horizontal,QObject::tr("Dontype"));
        model->setHeaderData(2,Qt::Horizontal,QObject::tr("serviceName"));
        model->setHeaderData(3,Qt::Horizontal,QObject::tr("Donquantity"));
        model->setHeaderData(4,Qt::Horizontal,QObject::tr("budget_S"));
    }
    return model;
}



bool Service::supprimer(QString IDservice)
{
QSqlQuery query;
query.prepare("Delete from Services where IDservice= :IDservice");
query.bindValue(":IDservice",IDservice);
query.exec();
return query.exec();
}

bool Service :: modifier()
{
    QSqlQuery query;
        query.prepare("UPDATE SERVICES SET IDservice = :IDservice,Dontype = :Dontype, serviceName = :serviceName,  Donquantity = :Donquantity , budget_S = :budget_S WHERE IDservice LIKE '"+IDservice+"%'");
        query.bindValue(":IDservice", IDservice);
        query.bindValue(":Dontype", Dontype);
        query.bindValue(":serviceName", serviceName);
        query.bindValue(":Donquantity", Donquantity);
        query.bindValue(":budget_S", budget_S);
        query.exec();
       return  query.exec();
}
QSqlQueryModel* Service ::rechercherID(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM Services where IDservice LIKE '"+recherche+"%' ");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDservice"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Dontype"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("serviceName"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Donquantity"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("budget_S"));
    return model;
}


QSqlQueryModel* Service::rechercherDontype(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM Services where Dontype LIKE '"+recherche+"%'  OR LOWER(Dontype) LIKE '"+recherche+"%' OR UPPER(Dontype) LIKE '"+recherche+"%'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDservice"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Dontype"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("serviceName"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Donquantity"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("budget_S"));
    return model;
}


QSqlQueryModel* Service::recherchernomS(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM Services where serviceName LIKE '"+recherche+"%'  OR LOWER(serviceName) LIKE '"+recherche+"%' OR UPPER(serviceName) LIKE '"+recherche+"%'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDservice"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Dontype"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("serviceName"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Donquantity"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("budget_S"));
    return model;
}

QSqlQueryModel * Service::triIDs()
{
  QSqlQueryModel* model=new QSqlQueryModel();
  model->setQuery("SELECT * FROM Services order by IDservice");
  model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDservice"));
  model->setHeaderData(1,Qt::Horizontal,QObject::tr("Dontype"));
  model->setHeaderData(2,Qt::Horizontal,QObject::tr("serviceName"));
  model->setHeaderData(3,Qt::Horizontal,QObject::tr("Donquantity"));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("budget_S"));
  return model;

}
/*
QSqlQueryModel * Service::tridon()
{
  QSqlQueryModel* model=new QSqlQueryModel();
  model->setQuery("SELECT * FROM Services order by Donquantity");
  model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDservice"));
  model->setHeaderData(1,Qt::Horizontal,QObject::tr("Dontype"));
  model->setHeaderData(2,Qt::Horizontal,QObject::tr("serviceName"));
  model->setHeaderData(3,Qt::Horizontal,QObject::tr("Donquantity"));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("budget_S"));
  return model;


}
QSqlQueryModel * Service::triNomS()
{
  QSqlQueryModel* model=new QSqlQueryModel();
  model->setQuery("SELECT * FROM Services order by serviceName");
  model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDservice"));
  model->setHeaderData(1,Qt::Horizontal,QObject::tr("Dontype"));
  model->setHeaderData(2,Qt::Horizontal,QObject::tr("serviceName"));
  model->setHeaderData(3,Qt::Horizontal,QObject::tr("Donquantity"));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("budget_S"));
  return model;


}

*/
