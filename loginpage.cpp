#include "loginpage.h"
#include "ghalia.h"
#include "ui_loginpage.h"
#include "employee.h"
#include <QMessageBox>
#include "mainwindow.h"
#include <QCryptographicHash>

loginpage::loginpage(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::loginpage)
{
    ui->setupUi(this);
    QPixmap pix("C:/Users/moham/Desktop/Esprit/2 eme A16/Projet c++/conception/logo application2.png");
    ui->label_pic->setPixmap(pix);
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
