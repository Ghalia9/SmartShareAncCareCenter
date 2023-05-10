#ifndef SERVICE_H
#define SERVICE_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class Service
{
    QString IDservice,Dontype,serviceName;
    int Donquantity;
    double budget_S;
    public:
    Service(){}
    Service(QString,QString,QString,int,double);

    //Getters
    QString getIDservice(){return IDservice;}
    QString getDontype(){return Dontype;}
    QString getserviceName(){return serviceName;}
    int getDonquantity(){return Donquantity;}
    double getbudget_S(){return budget_S;}

    //setters
    void setIDservice(QString id){IDservice=id;}
    void setDontype(QString t){Dontype=t;}
    void setserviceName(QString n){serviceName=n;}
    void setDonquantity(int Donquantity){this->Donquantity=Donquantity;}
    void setbudget_S(double budget_S){this->budget_S=budget_S;}

    //fonctionnalités de base relatives à l'entité Service
    bool ajouter();
    QSqlQueryModel * afficher();
    QSqlQueryModel * afficherStock(QString IDservice);
    bool supprimer(QString);
    bool modifier();
    QSqlQueryModel* rechercherID(QString);
    QSqlQueryModel* rechercherDontype(QString recherche);
    QSqlQueryModel* recherchernomS(QString );
    QSqlQueryModel * triIDs();
    //QSqlQueryModel * tridon();
   // QSqlQueryModel * triNomS();




};

#endif // ETUDIANT_H
