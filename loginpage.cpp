#include "loginpage.h"
#include "ghalia.h"
#include "ui_loginpage.h"
#include "employee.h"
#include <QMessageBox>
#include "mainwindow.h"
#include <QCryptographicHash>
#include "smtp.h"
#include <QDebug>
#include <QSqlQuery>
int s=rand()%10000;
loginpage::loginpage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginpage)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/moham/Desktop/Esprit/2 eme A16/Projet c++/conception/logo application2.png");
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



}

loginpage::~loginpage()
{
    delete ui;
}

void loginpage::on_pushButton__login_clicked()
{
       QString username = ui->lineEdit_login->text();
       QString password = ui->lineEdit_password->text();

       QByteArray input_hashed_password = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256); //decryption
       // Check if the login credentials are correct
       QSqlQuery query;
       query.prepare("SELECT * FROM employees WHERE login = :username AND password = :password");
       query.bindValue(":username", username);
       QString pass =input_hashed_password.toHex();
       query.bindValue(":password", pass);
       bool success = query.exec();
       if (success && query.next()) {
           // Login successful
           //QMessageBox::information(this, "Login", "Login successful!");
           // Hide the login window and show the main window
           this->hide();
           //here we will open window by function
           QString fct =  query.value(5).toString();
           if (fct == "Administrator"){
           MainWindow *mainWindow = new MainWindow();
           mainWindow->showMaximized();}
           else if (fct == "Destitute Manager"){
ghalia *ghaliap = new ghalia();
ghaliap->showMaximized();

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
        //int x=rand()%10000;
        //QString message = "Your verification code is ";

         Smtp* smtp = new Smtp("mohamedismail.elhedfi@esprit.tn","dooqktpplqzdyxki");
         connect(smtp, SIGNAL(status(QString)), this, SLOT(mailSent()));
         QString msg = "Your verification code is "+QString::number(s);
         smtp->sendMail(username, recipient, subject, msg);

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
if (test==s){
    QString new_pass = ui->lineEdit_password_2->text();
    QString new_pass_comf = ui->lineEdit->text();
    if (new_pass==new_pass_comf){
        QSqlQuery query;
        query.prepare("UPDATE EMPLOYEES SET PASSWORD = :PASSWORD WHERE EMPLOYEE_ID LIKE :ID ");
    }else{

    }

}else{
    QMessageBox::warning(nullptr, QObject::tr("Not OK"),
                QObject::tr("Invalid Verification code.\n"
                            "Click Cancel to exit."), QMessageBox::Cancel);
}
}
