#include "service.h"

Service::Service(QString IDservice,QString Dontype,QString serviceName,double budget_S,int Donquantity)
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

    query.prepare("insert into services (IDservice, serviceName, budget_S, Dontype, Donquantity )" "values (:IDservice, :serviceName, :budget_S, :Dontype, :Donquantity)");
    //creation des variables liees

    query.bindValue(":IDservice", IDservice);
    query.bindValue(":serviceName", serviceName);
    query.bindValue(":budget_S", budget_S);
    query.bindValue(":Dontype", Dontype);
    query.bindValue(":Donquantity", Donquantity);


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
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("serviceName"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("budget_S"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Dontype"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Donquantity"));

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

bool Service :: modifier(QString recherche)
{
    QSqlQuery query;
        query.prepare("UPDATE SERVICES SET IDservice = :IDservice, serviceName = :serviceName, budget_S = :budget_S, Dontype = :Dontype, Donquantity = :Donquantity WHERE IDservice LIKE '"+recherche+"%'");
        query.bindValue(":IDservice", IDservice);
        query.bindValue(":serviceName", serviceName);
        query.bindValue(":budget_S", budget_S);
        query.bindValue(":Dontype", Dontype);
        query.bindValue(":Donquantity", Donquantity);
        query.exec();
       return  query.exec();
}
QSqlQueryModel* Service ::rechercherID(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM Services where IDservice LIKE '"+recherche+"%' ");

    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDservice"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("serviceName"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("budget_S"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Dontype"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Donquantity"));
    return model;
}


QSqlQueryModel* Service::rechercherDontype(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM Services where Dontype LIKE '"+recherche+"%'  OR LOWER(Dontype) LIKE '"+recherche+"%' OR UPPER(Dontype) LIKE '"+recherche+"%'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDservice"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("serviceName"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("budget_S"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Dontype"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Donquantity"));
    return model;
}


QSqlQueryModel* Service::recherchernomS(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM Services where serviceName LIKE '"+recherche+"%'  OR LOWER(serviceName) LIKE '"+recherche+"%' OR UPPER(serviceName) LIKE '"+recherche+"%'");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDservice"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("serviceName"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("budget_S"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Dontype"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Donquantity"));
    return model;
}

QSqlQueryModel * Service::triIDs()
{
  QSqlQueryModel* model=new QSqlQueryModel();
  model->setQuery("SELECT * FROM Services order by IDservice");
  model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDservice"));
  model->setHeaderData(2,Qt::Horizontal,QObject::tr("serviceName"));
  model->setHeaderData(3,Qt::Horizontal,QObject::tr("budget_S"));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("Dontype"));
  model->setHeaderData(5,Qt::Horizontal,QObject::tr("Donquantity"));
  return model;

}

QSqlQueryModel * Service::tridon()
{
  QSqlQueryModel* model=new QSqlQueryModel();
  model->setQuery("SELECT * FROM Services order by Donquantity");
  model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDservice"));
  model->setHeaderData(2,Qt::Horizontal,QObject::tr("serviceName"));
  model->setHeaderData(3,Qt::Horizontal,QObject::tr("budget_S"));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("Dontype"));
  model->setHeaderData(5,Qt::Horizontal,QObject::tr("Donquantity"));
  return model;


}
QSqlQueryModel * Service::triNomS()
{
  QSqlQueryModel* model=new QSqlQueryModel();
  model->setQuery("SELECT * FROM Services order by serviceName");
  model->setHeaderData(0,Qt::Horizontal,QObject::tr("IDservice"));
  model->setHeaderData(2,Qt::Horizontal,QObject::tr("serviceName"));
  model->setHeaderData(3,Qt::Horizontal,QObject::tr("budget_S"));
  model->setHeaderData(4,Qt::Horizontal,QObject::tr("Dontype"));
  model->setHeaderData(5,Qt::Horizontal,QObject::tr("Donquantity"));
  return model;


}

