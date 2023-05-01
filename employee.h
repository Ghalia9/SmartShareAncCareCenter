#ifndef EMPLOYEE_H
#define EMPLOYEE_H
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QString>


class employee
{
    QString id,firstname,lastname,login,mdp,function,contact;
    float salary;
    int efficiency;
public:
    employee(){}
    employee(QString id,QString first,QString last,QString login,QString mdp,QString fct,QString cntct,float slry,int eff);
    //getters
    QString getid(){return id;}
    QString getfirstname(){return firstname;}
    QString getlastname(){return lastname;}
    QString getlogin(){return login;}
    QString getmdp(){return mdp;}
    QString getfunction(){return function;}
    QString getcontact(){return contact;}
    float getsalary(){return salary;}
    int getefficiency(){return efficiency;}
    //setters
    void setid (QString a){id=a;}
    void setfirstname (QString a){firstname=a;}
    void setlastname (QString a){lastname=a;}
    void setlogin (QString a){login=a;}
    void setmdp (QString a){mdp=a;}
    void setfunction (QString a){function=a;}
    void setcontact (QString a){contact=a;}
    void setsalary (float a){salary=a;}
    void setefficiency (int a){efficiency=a;}
    //crud
    bool ajouter();
    QSqlQueryModel * afficher();
    bool supprimer(QString);
    bool update (QString);
    QSqlQuery Edit (QString);
    QSqlQueryModel * rechercher(QString search,int);
    QSqlQueryModel * sort(int);
    QSqlQuery pdf ();
};

#endif // EMPLOYEE_H
