#pragma once

#ifndef DONATION_H
#define DONATION_H
#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QStackedWidget>


class donation
{
    QString donation_id, category_name, name, description, phone_number;
    int quantity;
    double amount;
    public:
    donation(){}
    donation(QString,QString,QString,QString,int,double,QString);
    //Getters
    QString getDonationID(){return donation_id;}
    QString getCategoryName(){return category_name;}
    QString getName(){return name;}
    QString getDescription(){return description;}
    int getQuantity(){return quantity;}
    double getAmount(){return amount;}
    QString getPhoneNumber(){return phone_number;}
 //   QString getLastId(){return last_id;}


    //setters
   // void setLastId(QString last_id){this->last_id=last_id;}
   // static QString getLastId();

    void setDonationID(QString donation_id){this->donation_id=donation_id;}
    void setCategoryName(QString cn){category_name=cn;}
    void setName(QString n){name=n;}
    void setDescription(QString d){description=d;}
    void setQuantity(int q){this->quantity=q;}
    void setAmount(double a){this->amount=a;}
    void setPhoneNumber(QString ph){phone_number=ph;}

    QString setDonationID() {return donation_id;};
    //fonctionnalités de base relatives à l'entité Etudiant
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);

    bool modifier();
        QSqlQueryModel* rechercherID(QString );

        QSqlQueryModel * sortID();
        QSqlQueryModel * sortCategoryName();

           QSqlQueryModel* rechercherCategoryName(QString recherche);
            QSqlQueryModel* recherchernom(QString );
            QSqlQueryModel* rechercherID2(QString );
             void generateCatalog();
/*
private:
       QStackedWidget *stackedWidget;
       QVBoxLayout *mainLayout;
       QLabel *titleLabel;
       QLabel *pageLabel;
       QLabel *donationLabel;
       QToolButton *prevButton;
       QToolButton *nextButton;
       QList<QLabel *> donationPages;*/

};


#endif // DONATION_H
