#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "employee.h"
#include <QMessageBox>
#include <QtSql>
#include <QDebug>
#include <cstdlib>
#include <QPrinter>
#include <QPainter>
#include <QPdfWriter>
#include <QTextDocument>
#include <QtPrintSupport>
#include <QtPrintSupport/QPrinter>
#include <QtPrintSupport/QPrintDialog>
#include <QtGui/QPainter>
#include <QImage>
#include <QPixmap>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tableView->setModel(etmp.afficher());
    ui->lineEdit_login->setValidator(new QRegExpValidator (QRegExp("[A-Za-z]+"),this));
    //ui->lineEdit_salary->setValidator(new QRegExpValidator (QRegExp("\d"),this));
    ui->lineEdit_lastname->setValidator(new QRegExpValidator (QRegExp("[A-Za-z]+"),this));
    ui->lineEdit_firstname->setValidator(new QRegExpValidator (QRegExp("[A-Za-z]+"),this));
    //ui->lineEdit_password->setValidator(new QRegExpValidator (QRegExp("^(?=.*[A-Za-z])(?=.*\d)(?=.*[@$!%*#?&])[A-Za-z\d@$!%*#?&]{8,}$"),this));//Minimum eight characters, at least one letter, one number and one special character:
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_6_clicked(){
    //QString id=ui->lineEdit_id->text();
    QString nom=ui->lineEdit_lastname->text();
    QString prenom=ui->lineEdit_firstname->text();
    QString login=ui->lineEdit_login->text();
    QString password=ui->lineEdit_password->text();
    QString function=ui->lineEdit_fucntion->text();
    QString contact=ui->lineEdit_contact->text();
    float salary=ui->lineEdit_salary->text().toFloat();
    int efficiency=0;

    int x=rand()%100;

    QString id="emp"+QString::number(x);
    employee e(id,nom,prenom,login,password,function,contact,salary,efficiency);
bool test=e.ajouter();
if(test)
    {
        //REFRESH
         ui->tableView->setModel(etmp.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Added successfuly.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("NOT ADDED.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_pushButton_5_clicked()
{
    QString id=ui->lineEdit_iddelete->text();
    bool test=etmp.supprimer(id);
    if(test){
        //REFRESH
        ui->tableView->setModel(etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Suppression effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("Suppression non effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_pushButton_edit_clicked()
{
    QString id=ui->lineEdit_id_3->text();
    QString nom=ui->lineEdit_lastname_3->text();
    QString prenom=ui->lineEdit_firstname_3->text();
    QString login=ui->lineEdit_login_3->text();
    QString password=ui->lineEdit_password_3->text();
    QString function=ui->lineEdit_fucntion_3->text();
    QString contact=ui->lineEdit_contact_3->text();
    float salary=ui->lineEdit_salary_3->text().toFloat();
    int efficiency=0;
    employee e(id,nom,prenom,login,password,function,contact,salary,efficiency);
bool test=e.update(id);
if(test)
    {
        //REFRESH
         ui->tableView->setModel(etmp.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Edited successfuly.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("NOT Edited.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void MainWindow::on_tableView_activated(const QModelIndex &index)
{
    QString val=index.sibling(index.row(), index.column()).data().toString();
    QSqlQuery qry;
    employee e;
    qry=e.Edit(val);
    if (qry.exec()){
        while(qry.next()){
        ui->lineEdit_id_3->setText(qry.value(0).toString());
        ui->lineEdit_lastname_3->setText(qry.value(1).toString());
        ui->lineEdit_firstname_3->setText(qry.value(2).toString());
        ui->lineEdit_login_3->setText(qry.value(3).toString());
        ui->lineEdit_password_3->setText(qry.value(4).toString());
        ui->lineEdit_fucntion_3->setText(qry.value(5).toString());
        ui->lineEdit_contact_3->setText(qry.value(6).toString());
        ui->lineEdit_salary_3->setText(qry.value(7).toString());
    }
    }
    else
    {
       // QMessageBox::critical(nullptr, QObject::tr("Not OK"),QObject::tr("Couldn't fill.\n""Click Cancel to exit."),QMessageBox::Cancel);
       qDebug()<<qry.lastError().text();    }

}

void MainWindow::on_pushButton_clicked()
{
  int res=1;
  QString text=ui->lineEdit_search->text();
  Qt::CheckState state=ui->checkBox_name->checkState();
  if (state == Qt::Checked) {
      res=1; //name
  }
  Qt::CheckState state2=ui->checkBox_function->checkState();
  if (state2 == Qt::Checked) {
      res=2; //function
  }
  Qt::CheckState state3=ui->checkBox_salary->checkState();
  if (state3 == Qt::Checked) {
      res=3; //salary
  }

  ui->tableView->setModel(etmp.rechercher(text,res));
}

void MainWindow::on_pushButton_2_clicked()
{
    QString x = ui->comboBox->currentText();
        if (x == "Ascending salary") {
           ui->tableView->setModel(etmp.sort(1));
        } else if (x == "Descending salary") {
           ui->tableView->setModel(etmp.sort(2));
        }

}

void MainWindow::on_pushButton_3_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", "example.pdf", "PDF files (*.pdf)");
            if (fileName.isEmpty()) {
                return;
            }

            QPrinter printer(QPrinter::HighResolution);
            printer.setOutputFormat(QPrinter::PdfFormat);
            printer.setOutputFileName(fileName);

            QPainter painter;
            painter.begin(&printer);
            QString id=ui->lineEdit_iddelete->text();
            QSqlQuery query;
            query.prepare("SELECT FIRST_NAME, FUNCTION, SALARY FROM EMPLOYEES WHERE EMPLOYEE_ID like :id");
            query.bindValue(":id",id);
            query.exec();
            qDebug()<<query.lastError().text();
                while (query.next()) {
                    // Get the values from the current row
                    QString name = query.value("FIRST_NAME").toString();
                    float eff = query.value("SALARY").toFloat();
                    QString function = query.value("FUNCTION").toString();
//image palacement
                    QPixmap image("C:/Users/moham/Desktop/Esprit/2 eme A16/qt/partieismail/employeeprofile.png");
    QPixmap scaledImage = image.scaled(640,640);
                       int pageWidth = printer.width();
                       int imageWidth = scaledImage.width();
                       int xPos = (pageWidth - imageWidth) / 2;
                       int yPos = 0;

                       painter.drawPixmap(xPos, yPos, scaledImage);
                    // Print the values on the PDF

                    painter.drawText(100, 600, "Name: " + name);
                    painter.drawText(100, 800, "Salary: " + QString::number(eff));
                    painter.drawText(100, 1000, "Function: " + function);
                }
            painter.end();
    }


