#include "employee.h"
#include <QString>
#include <QDebug>
#include <QtSql>
#include <QMessageBox>
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
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("First Name"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Last Name"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Login"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Password"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("Function"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("Salary"));
model->setHeaderData(7,Qt::Horizontal,QObject::tr("Contact"));
model->setHeaderData(8,Qt::Horizontal,QObject::tr("Efficiency"));
return model;
}

bool employee::supprimer(QString id){
QSqlQuery query;
query.prepare("DELETE FROM EMPLOYEES WHERE EMPLOYEE_ID = :id");
query.bindValue(":id",id);
return query.exec();
}

bool employee::update(QString id){
    QSqlQuery query;
    QString eff = QString::number(efficiency);
    QString slry = QString::number(salary);
    query.prepare("UPDATE EMPLOYEES SET FIRST_NAME = :FIRST_NAME, LAST_NAME = :LAST_NAME, LOGIN = :LOGIN, PASSWORD = :PASSWORD, FUNCTION = :FUNCTION, SALARY = :SALARY, CONTACT = :CONTACT, EFFICIENCY = :EFFICIENCY WHERE EMPLOYEE_ID = :EMPLOYEE_ID");
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

QSqlQuery employee::Edit(QString val){
QSqlQuery qry;
bool test=true;
for (const QChar& c: val){
    if (!c.isDigit()){
        test=false;
    }
}
if (test){
    int x;
    x= QString(val).toInt();
    qry.prepare(("SELECT * FROM EMPLOYEES WHERE FUNCTION= :val OR EFFICINECY= :val"));
    qry.bindValue(":val",val);
}else{
qry.prepare("SELECT * FROM EMPLOYEES WHERE (EMPLOYEE_ID= :val) OR (FIRST_NAME = :val) OR (LAST_NAME = :val) OR (LOGIN = :val) OR (PASSWORD = :val) OR (FUNCTION = :val)  OR (CONTACT = :val)");
qry.bindValue(":val",val);
}
return qry;
}

QSqlQueryModel * employee::rechercher(QString search,int res){
    QSqlQueryModel * model=new QSqlQueryModel();
        QSqlQuery query;
        if (res==1){
        query.prepare("SELECT * FROM EMPLOYEES WHERE FIRST_NAME LIKE :search OR LAST_NAME LIKE :search");
        query.bindValue(":search", "%" + search + "%");
        }else if (res==3){
        query.prepare("SELECT * FROM EMPLOYEES WHERE SALARY >= :search");
        query.bindValue(":search",search);
        }else if (res==2){
        query.prepare("SELECT * FROM EMPLOYEES WHERE FUNCTION LIKE :search");
        query.bindValue(":search", "%" + search + "%");
        }
        query.exec();
        qDebug()<<query.lastError().text();
        model->setQuery(query);
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("First Name"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Last Name"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Login"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Password"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("Function"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("Salary"));
model->setHeaderData(7,Qt::Horizontal,QObject::tr("Contact"));
model->setHeaderData(8,Qt::Horizontal,QObject::tr("Efficiency"));
return model;
}
QSqlQueryModel * employee::sort(int x){
QSqlQueryModel * model=new QSqlQueryModel();
if(x==1){//ascending
model->setQuery("SELECT * FROM EMPLOYEES ORDER BY SALARY ASC");
}else if (x==2){//descending
model->setQuery("SELECT * FROM EMPLOYEES ORDER BY SALARY DESC");
}
model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
model->setHeaderData(1,Qt::Horizontal,QObject::tr("First Name"));
model->setHeaderData(2,Qt::Horizontal,QObject::tr("Last Name"));
model->setHeaderData(3,Qt::Horizontal,QObject::tr("Login"));
model->setHeaderData(4,Qt::Horizontal,QObject::tr("Password"));
model->setHeaderData(5,Qt::Horizontal,QObject::tr("Function"));
model->setHeaderData(6,Qt::Horizontal,QObject::tr("Salary"));
model->setHeaderData(7,Qt::Horizontal,QObject::tr("Contact"));
model->setHeaderData(8,Qt::Horizontal,QObject::tr("Efficiency"));
return model;
}
QSqlQuery employee::pdf(){
    QSqlQuery query("SELECT * FROM EMPLOYEES ORDER BY SALARY ASC");
    if (!query.exec()) {
        qDebug() << "Error executing query:" << query.lastError().text();
    }
    return query;
}










