#include "loginpage.h"
//#include "ghalia.h"
#include "rfid.h"
#include "donationswindow.h"
#include "donation.h"
#include "destitute.h"
#include "destituteWindow.h"
#include "ui_loginpage.h"
#include "employee.h"
#include <QMessageBox>
#include "empwindow.h"
#include <QCryptographicHash>
#include "smtp.h"
#include "CollectsMainWindow.h"
#include "sermainwindow.h"
#include <QDebug>
#include <QSqlQuery>
#include <QtSql>
int s=rand()%10000;
bool empwindowshowen=false;
int USER=0;
loginpage::loginpage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginpage)
{
    ui->setupUi(this);
    QPixmap pix("D:/SmartShareAncCareCenter-GestionEmployees/logo application2.png");
    //QPixmap pix("C:/Users/moham/Desktop/Esprit/2 eme A16/Projet c++/conception/logo application2.png");
    ui->label_pic->setPixmap(pix);
    //forgot password ui
    ui->label_3->hide();
    ui->label_4->hide();
    ui->label_5->hide();
    ui->label_6->hide();
    ui->lineEdit->hide();
    ui->lineEdit_password_2->hide();
    ui->lineEdit_code->hide();
    ui->pushButton_2->hide();
    USER=0;

    int ret=C.connect_arduino();
        qDebug() <<"ret="<<ret;
        switch(ret){
        case(0):qDebug()<<"Arduino is available and connected to : "<< C.getarduino_port_name();
            break;
        case(1):qDebug()<<"Arduino is available but not connected to : "<< C.getarduino_port_name();
            break;
        case(-1):qDebug()<<"Arduino is not available ";
        }

        QObject::connect(C.getserial(),SIGNAL(readyRead()),this,SLOT(card()));

}

loginpage::~loginpage()
{
    delete ui;
}


void loginpage::card (){
    int i;
    QString cardid = C.read_from_arduino();

    if (cardid != ""){
    QSqlQuery query;
    query.prepare("SELECT * FROM employees WHERE card_id = :cardid");
    query.bindValue(":cardid", cardid);
    bool success = query.exec();
    if (success && query.next()) {
i = C.write_to_arduino("true");
        this->hide();
        //here we will open window by function
        QString fct =  query.value(5).toString();
        QString name = query.value(3).toString();
        //send to arduino

        i = C.write_to_arduino(name);

        if (fct == "Administrator" && !empwindowshowen){
USER=1;
        empwindow *emp = new empwindow();

        emp->showMaximized();
        empwindowshowen = emp->isVisible();

        qDebug()<<empwindowshowen;}

        else if (fct == "Destitute Manager"){

            destituteWindow *ghaliap = new destituteWindow();
            ghaliap->showMaximized();
        }
       else if (fct == "Donations Manager"){

            donationswindow *eyap = new donationswindow();
            eyap->showMaximized();
        }
        else if (fct == "Events Manager"){
        CollectsMainWindow *koussayp = new CollectsMainWindow();
        koussayp->showMaximized();

        }
        else if (fct == "Services Manager"){

            serMainWindow *elap = new serMainWindow();
             elap->showMaximized();
         }
    } else {
        // Login failed
        i = C.write_to_arduino("false");
        qDebug()<<empwindowshowen;
                  if (!empwindowshowen){
        QMessageBox::warning(this, "Login", "Card not recognized!");
                  }
    }

}
}
void loginpage::on_pushButton__login_clicked()
{
       QString username = ui->lineEdit_login->text();
       QString password = ui->lineEdit_password->text();

       QByteArray input_hashed_password = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256); //decryption
       // Check if the login credentials are correct
       QSqlQuery query;
       query.prepare("SELECT * FROM employees WHERE login = :username AND password = :password");
       qDebug()<<username;
       query.bindValue(":username", username);
       QString pass =input_hashed_password.toHex();
       query.bindValue(":password", pass);
       qDebug()<<pass;
       bool success = query.exec();
       qDebug()<<success;
        qDebug()<<query.lastError().text();
        if (success && query.next() ) {
                   // Login successful
                   //QMessageBox::information(this, "Login", "Login successful!");
                   // Hide the login window and show the main window
                   this->hide();
                   //here we will open window by function
                   QString fct =  query.value(5).toString();
                    qDebug()<<fct;
                   if (fct == "Administrator"){
                   empwindow *emp = new empwindow();
                   emp->showMaximized();
                   empwindowshowen = emp->isVisible();
                   USER=1;

                   }
                   else if (fct == "Destitute Manager"){
                    destituteWindow *ghaliap = new destituteWindow();
                     ghaliap->showMaximized();

                   }
                   else if (fct == "Events Manager"){
                   CollectsMainWindow *koussayp = new CollectsMainWindow();
                   koussayp->showMaximized();

                   }
                   else if (fct == "Donations Manager"){

                        donationswindow *eyap = new donationswindow();
                        eyap->showMaximized();
                    }
                   else if (fct == "Services Manager"){

                       serMainWindow *elap = new serMainWindow();
                        elap->showMaximized();
                    }
               } else {
                   // Login failed

                   QMessageBox::warning(this, "Login", "Invalid login credentials!");

               }
}

void loginpage::on_pushButton_clicked()
{
//    QString username = ui->uname->text();
//         QString password = ui->paswd->text();
//         QString recipient = ui->rcpt->text();
//         QString subject = ui->subject->text();
    QString username = ui->lineEdit_login->text();
    QSqlQuery query;
    query.prepare("SELECT * FROM employees WHERE login = :username");
    query.bindValue(":username", username);
    bool success = query.exec();
    if (success && query.next()) {
    QString recipient =  query.value(7).toString();


//    QString pass =  query.value(4).toString();

//qDebug()<<pass;
//qDebug()<<recipient;
//    QByteArray input_hashed_password = QCryptographicHash::hash(pass.toUtf8(), QCryptographicHash::Sha256);
//qDebug()<<input_hashed_password;
//qDebug()<<pass.toUtf8();
//QString test = input_hashed_password.toHex();
        QString subject = "Password Recovery";
        int x=rand()%10000;

        //QString message = "Your verification code is ";

         Smtp* smtp = new Smtp("mohamedismail.elhedfi@esprit.tn","dooqktpplqzdyxki");
         connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent()));
         QString msg = "Your verification code is "+QString::number(x);
         smtp->sendMail(username, recipient, subject, msg);

         ui->lineEdit_password->setText(QString::number(x));

    }
    ui->label_3->show();
    ui->label_4->show();
    ui->label_5->show();
    ui->label_6->show();
    ui->lineEdit->show();
    ui->lineEdit_password_2->show();
    ui->lineEdit_code->show();
    ui->pushButton_2->show();

    ui->label->hide();
    ui->label_2->hide();
    ui->lineEdit_login->hide();
    ui->lineEdit_password->hide();
    ui->pushButton->hide();
    ui->pushButton__login->hide();






}
void loginpage::mailSent(){

}

void loginpage::on_pushButton_2_clicked()
{
QString code = ui->lineEdit_code->text();
int test= code.toInt();
QString number = ui->lineEdit_password->text();
int num= number.toInt();
if (test==num){
    QString new_pass = ui->lineEdit_password_2->text();
    QString new_pass_comf = ui->lineEdit->text();
    QString login = ui->lineEdit_login->text();
    if (new_pass==new_pass_comf){
        QByteArray hashed_password = QCryptographicHash::hash(new_pass.toUtf8(), QCryptographicHash::Sha256);
        QString hashed_password_string(hashed_password.toHex());

        QSqlQuery query;
        query.prepare("UPDATE EMPLOYEES SET PASSWORD = :PASSWORD WHERE LOGIN LIKE :LOGIN");
        query.bindValue(":LOGIN",login);
        query.bindValue(":PASSWORD",hashed_password_string);
        if (query.exec()){
            ui->label_3->hide();
            ui->label_4->hide();
            ui->label_5->hide();
            ui->label_6->hide();
            ui->lineEdit->hide();
            ui->lineEdit_password_2->hide();
            ui->lineEdit_code->hide();
            ui->pushButton_2->hide();

            ui->label->show();
            ui->label_2->show();
            ui->lineEdit_login->show();
            ui->lineEdit_password->show();
            ui->pushButton->show();
            ui->pushButton__login->show();
            ui->lineEdit_password->setText("");
        }
    }else{
        QMessageBox::warning(nullptr, QObject::tr("Not OK"),
                    QObject::tr("Password confirmation failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

}else{
    QMessageBox::warning(nullptr, QObject::tr("Not OK"),
                QObject::tr("Invalid Verification code.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
}
