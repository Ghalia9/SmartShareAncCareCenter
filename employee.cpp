#include "employee.h"

employee::employee(QString id,QString first,QString last,QString login,QString mdp,QString fct,QString cntct,float slry,int eff){
    this->id=id;
    this->mdp=mdp;
    this->login=login;
    this->salary=slry;
    this->contact=cntct;
    this->function=fct;
    this->firstname=first;
    this->lastname=last;
    this->efficiency=eff;
}
bool employee::ajouter(){
    QSqlQuery query;
    QString eff = QString::number(efficiency);
    QString slry = QString::number(salary);
    query.prepare("INSERT INTO EMPLOYEES (EMPLOYEE_ID, FIRST_NAME, LAST_NAME, LOGIN, PASSWORD, FUNCTION, SALARY, CONTACT, EFFICIENCY) VALUES (:EMPLOYEE_ID, :FIRST_NAME, :LAST_NAME, :LOGIN, :PASSWORD, :FUNCTION, :SALARY, :CONTACT, :EFFICIENCY)");
    query.bindValue(":EMPLOYEE_ID",id);
    query.bindValue(":FIRST_NAME",firstname);
    query.bindValue(":LAST_NAME",lastname);
    query.bindValue(":LOGIN",login);
    query.bindValue(":PASSWORD",mdp);
    query.bindValue(":FUNCTION",function);
    query.bindValue(":SALARY",slry);
    query.bindValue(":CONTACT",contact);
    query.bindValue(":EFFICIENCY",eff);
    return query.exec();
}
QSqlQueryModel * employee::afficher(){
QSqlQueryModel * model=new QSqlQueryModel();
model->setQuery("SELECT * FROM EMPLOYEES");
//model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
//model->setHeaderData(1,Qt::Horizontal,QObject::tr("First Name"));
//model->setHeaderData(2,Qt::Horizontal,QObject::tr("Last Name"));
//model->setHeaderData(3,Qt::Horizontal,QObject::tr("Login"));
//model->setHeaderData(4,Qt::Horizontal,QObject::tr("Password"));
//model->setHeaderData(5,Qt::Horizontal,QObject::tr("Function"));
//model->setHeaderData(6,Qt::Horizontal,QObject::tr("Salary"));
//model->setHeaderData(7,Qt::Horizontal,QObject::tr("Contact"));
//model->setHeaderData(8,Qt::Horizontal,QObject::tr("Efficiency"));
return model;
}
bool employee::supprimer(QString id){
QSqlQuery query;
query.prepare("DELETE FROM EMPLOYEES WHERE EMPLOYEE_ID = :id");
query.bindValue(":id",id);
return query.exec();
}
