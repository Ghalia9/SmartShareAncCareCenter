#pragma once

#ifndef DONATION_H
#define DONATION_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class donation
{
    QString donation_id, category_name, name, description, phone_number;
    int quantity;
    double amount;
    public:
    donation(){}
    donation(int,double,QString,QString,QString,QString,QString);

    //Getters
    QString getDonationID(){return donation_id;}
    QString getCategoryName(){return category_name;}
    QString getName(){return name;}
    QString getDescription(){return description;}
    QString getPhoneNumber(){return phone_number;}
    int getQuantity(){return quantity;}
    double getAmount(){return amount;}

    //setters
    void setDonationID(QString donation_id){this->donation_id=donation_id;}
    void setCategoryName(QString cn){category_name=cn;}
    void setName(QString n){name=n;}
    void setDescription(QString d){description=d;}
    void setPhoneNumber(QString ph){phone_number=ph;}
    void setQuantity(int q){this->quantity=q;}
    void setAmount(double a){this->amount=a;}

    QString setDonationID() {return donation_id;};

    //fonctionnalités de base relatives à l'entité Etudiant
    bool ajouterD();
    QSqlQueryModel * afficherD();

};

#endif // DONATION_H
