#include "etudiant.h"

etudiant::etudiant(int id,QString nom,QString prenom)
{
    this->id=id;
    this->nom=nom;
    this->prenom=prenom;
}
bool etudiant::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(id);
    //prepare() prend la requete en parametre pour la preparer à léxecution

    query.prepare("insert into etudiant (id, nom, prenom)" "values (:id, :nom, :prenom)");
    //creation des variables liees

    query.bindValue(":id",res);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);

    return query.exec(); //exec() envoie la requete pour l'execution
}


QSqlQueryModel * etudiant::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from etudiant");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Nom"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));

    return model;
}


bool etudiant::supprimer(int id)
{
QSqlQuery query;
QString res=QString::number(id);
query.prepare("Delete from etudiant where ID= :id");
query.bindValue(":id",res);
return query.exec();
}
