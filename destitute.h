#ifndef DESTITUTE_H
#define DESTITUTE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Destitute
{
    QString destitute_id,first_name,last_name,contact;
    int destitute_level;

public:
    //CONSTRUCTURS
    Destitute();
    Destitute(QString,QString,QString,int,QString);

    //GETTERS
    QString getid(){return destitute_id;}
    QString getfirstname(){return first_name;}
    QString getlastname(){return last_name;}
    QString getcontact(){return contact;}
    int getlevel(){return destitute_level;}

    //SETTERS
    void setid(QString id){destitute_id=id;}
    void setfirstname(QString nom){first_name=nom;}
    void setlastname(QString prenom){last_name=prenom;}
    void setcontact(QString cont){contact=cont;}
    void setlevel(int l){destitute_level=l;}

    //FONCTIONS
    bool Add();
    QSqlQueryModel * Show();
    bool Delete(QString);



};

#endif // DESTITUTE_H
