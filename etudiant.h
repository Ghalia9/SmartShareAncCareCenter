#ifndef ETUDIANT_H
#define ETUDIANT_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class etudiant
{
    QString nom, prenom;
    int id;
    public:
    etudiant(){}
    etudiant(int,QString,QString);

    //Getters
    QString getNom(){return nom;}
    QString getPreom(){return prenom;}
    int getID(){return id;}

    //setters
    void setNom(QString n){nom=n;}
    void setPrenom(QString p){prenom=p;}
    void setID(int id){this->id=id;}

    //fonctionnalités de base relatives à l'entité Etudiant
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(int);

};

#endif // ETUDIANT_H
