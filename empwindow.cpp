#include "empwindow.h"
#include "ui_empwindow.h"
#include "employee.h"
#include "destituteWindow.h"
#include "loginpage.h"
#include "todolistwidget.h"
#include "rfid.h"
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
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QRegularExpression>
#include <QCryptographicHash>
#include <QThread>
#include <QTimer>
#include "CollectsMainWindow.h"
#include "empwindow.h"
#include "destituteWindow.h"
#include "donationswindow.h"
#include "sermainwindow.h"


empwindow::empwindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::empwindow)
{
    ui->setupUi(this);


    ui->tableView->setModel(etmp.afficher());
    ui->lineEdit_login_4->setValidator(new QRegExpValidator (QRegExp("[A-Za-z]+"),this));
    //ui->lineEdit_salary->setValidator(new QRegExpValidator (QRegExp("\d"),this));
    ui->lineEdit_lastname_4->setValidator(new QRegExpValidator (QRegExp("[A-Za-z]+"),this));
    ui->lineEdit_firstname_4->setValidator(new QRegExpValidator (QRegExp("[A-Za-z]+"),this));
    //ui->lineEdit_password->setValidator(new QRegExpValidator (QRegExp("^(?=.*[A-Za-z])(?=.*\d)(?=.*[@$!%*#?&])[A-Za-z\d@$!%*#?&]{8,}$"),this));//Minimum eight characters, at least one letter, one number and one special character:

    QSqlQuery query("SELECT SALARY , COUNT(*) FROM EMPLOYEES GROUP BY SALARY");
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.35);
    while (query.next()) {
        QString salary = query.value(0).toString();
        int count = query.value(1).toInt();
        series->append(salary, count);
    }
    QChart *chart = new QChart();
    chart->addSeries(series);
    QPieSlice *slice;
    for (int i = 0; i < series->count(); ++i) {
        slice = series->slices().at(i);
        slice->setBrush(QColor::fromHsv(i * 50, 255, 255));
        slice->setLabel(QString("%1: %2").arg(slice->label()).arg(slice->value()));
    }
    chart->setTitle("Employee Salaries");
    chart->setAnimationOptions(QChart::AllAnimations);
    chart->setTheme(QChart::ChartThemeBlueCerulean);
    chart->setAnimationDuration(5000);
    chart->setAnimationEasingCurve(QEasingCurve::OutBounce);
    chart->setMargins(QMargins(20, 20, 20, 20));
    chart->setDropShadowEnabled(true);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setParent(ui->horizontalFrame);

CToDoList* toDoListWidget= new  CToDoList();//creating new instance for the to do list class
ui->tabWidget->addTab(toDoListWidget, "To-Do List");
ui->lineEdit_id_4->hide();
ui->pushButton_clear->hide();


//int ret=C.connect_arduino();
//    qDebug() <<"ret="<<ret;
//    switch(ret){
//    case(0):qDebug()<<"Arduino is available and connected to : "<< C.getarduino_port_name();
//        break;
//    case(1):qDebug()<<"Arduino is available but not connected to : "<< C.getarduino_port_name();
//        break;
//    case(-1):qDebug()<<"Arduino is not available ";
//    }

//    QObject::connect(C.getserial(),SIGNAL(readyRead()),this,SLOT(Read()));


}
void empwindow::Read(){

   Data = C.read_from_arduino();

//   Data = Data.trimmed();
//   Data.replace("\x00","");
//   qDebug()<<"dataaaa:"<<Data;
      //do sthg
}

empwindow::~empwindow()
{
    delete ui;
}


void empwindow::on_pushButton_6_clicked(){


    //QString id=ui->lineEdit_id_4->text();
    QString nom=ui->lineEdit_lastname_4->text();
    QString prenom=ui->lineEdit_firstname_4->text();
    QString login=ui->lineEdit_login_4->text();
    QString password=ui->lineEdit_password_4->text();
    QString function=ui->comboBox_2->currentText();
    QString contact=ui->lineEdit_contact_4->text();
    float salary=ui->doubleSpinBox->text().toFloat();

    QRegularExpression email("[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\\.[a-zA-Z]{2,}");
    if(email.match(contact).hasMatch()){
    int efficiency=0;

    int x=rand()%100;

QByteArray hashed_password = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
QString hashed_password_string(hashed_password.toHex());


QString id="emp"+QString::number(x);
    employee e(id,nom,prenom,login,hashed_password_string,function,contact,salary,efficiency);
bool test=e.ajouter();
if(test)
    {
        //REFRESH
         ui->tableView->setModel(etmp.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Added successfuly.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    ui->pushButton_clear->click();
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("NOT ADDED.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }else{
        QMessageBox::warning(nullptr, QObject::tr("Not OK"),
                    QObject::tr("Invalid email address.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
    }

void empwindow::on_pushButton_5_clicked()
{
    QString id=ui->lineEdit_iddelete->text();
    bool test=etmp.supprimer(id);
    if(test){
        //REFRESH
        ui->tableView->setModel(etmp.afficher());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Suppression effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->pushButton_clear->click();

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("Suppression non effectuée.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}


void empwindow::on_pushButton_edit_clicked()
{
    QString id=ui->lineEdit_id_4->text();
    QString nom=ui->lineEdit_lastname_4->text();
    QString prenom=ui->lineEdit_firstname_4->text();
    QString login=ui->lineEdit_login_4->text();
    QString password=ui->lineEdit_password_4->text();
QString function=ui->comboBox_2->currentText();
QString contact=ui->lineEdit_contact_4->text();
    float salary=ui->doubleSpinBox->text().toFloat();
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
    ui->pushButton_clear->click();

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("NOT Edited.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
}

void empwindow::on_tableView_activated(const QModelIndex &index)
{
    QString val=index.sibling(index.row(), index.column()).data().toString();
    QSqlQuery qry;
    employee e;
    qry=e.Edit(val);
    if (qry.exec()){
        while(qry.next()){
        ui->lineEdit_id_4->setText(qry.value(0).toString());
ui->lineEdit_iddelete->setText(qry.value(0).toString());
ui->lineEdit_idempcard->setText(qry.value(0).toString());
        ui->lineEdit_lastname_4->setText(qry.value(1).toString());
        ui->lineEdit_firstname_4->setText(qry.value(2).toString());
        ui->lineEdit_login_4->setText(qry.value(3).toString());
        ui->lineEdit_password_4->setText(qry.value(4).toString());
        ui->comboBox_2->setCurrentText(qry.value(5).toString());
        ui->lineEdit_contact_4->setText(qry.value(7).toString());
        ui->doubleSpinBox->setValue(qry.value(6).toFloat());
    }
    }
    else
    {
       // QMessageBox::critical(nullptr, QObject::tr("Not OK"),QObject::tr("Couldn't fill.\n""Click Cancel to exit."),QMessageBox::Cancel);
       qDebug()<<qry.lastError().text();    }

}

void empwindow::on_pushButton_clicked()
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

void empwindow::on_pushButton_2_clicked()
{
    QString x = ui->comboBox->currentText();
        if (x == "Ascending salary") {
           ui->tableView->setModel(etmp.sort(1));
        } else if (x == "Descending salary") {
           ui->tableView->setModel(etmp.sort(2));
        }

}

void empwindow::on_pushButton_3_clicked()
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



void empwindow::on_pushButton_clear_clicked()
{
    ui->lineEdit_id_4->clear();
    ui->lineEdit_lastname_4->clear();
    ui->lineEdit_firstname_4->clear();
    ui->lineEdit_login_4->clear();
    ui->lineEdit_password_4->clear();
ui->lineEdit_contact_4->clear();
    ui->doubleSpinBox->clear();
    ui->lineEdit_idempcard->clear();
}

void empwindow::on_pushButton_4_clicked()
{
    QString employeeid=ui->lineEdit_idempcard->text();
    QString cardid=ui->lineEdit_idcard->text();

    QSqlQuery query;
    query.prepare("UPDATE EMPLOYEES SET CARD_ID = :CARDID WHERE EMPLOYEE_ID like :id");
    query.bindValue(":id",employeeid);
    query.bindValue(":CARDID",cardid);
    if (query.exec()){

ui->tableView->setModel(etmp.afficher());
QTimer time;
ui->label_cardadded->setText("Card added successfuly");
time.setSingleShot(true);
QObject::connect(&time, &QTimer::timeout,ui->label_cardadded, &QLabel::clear);
time.start(2000);
    }else{
        qDebug()<<query.lastError().text();
    }

}


void empwindow::on_pushButton_logout_clicked()
{
    this->hide();
//loginpage *l =new  loginpage();
//l->show();
}

void empwindow::on_actionDistitute_triggered()
{
destituteWindow *Dest = new destituteWindow();
Dest->showMaximized();
this->destroy();
this->hide();

}

void empwindow::on_actionAbout_the_app_triggered()
{
    this->hide();
    this->destroy();
    empwindowshowen=false;
loginpage *l =new  loginpage();
l->show();
}

void empwindow::on_actionEmployees_triggered()
{

    empwindow *p=new empwindow();
        p->showMaximized();
        this->hide();
        this->destroy();
}

void empwindow::on_actionDonation_triggered()
{
    donationswindow  *p=new donationswindow();
        p->showMaximized();
         this->hide();
        this->destroy();
}

void empwindow::on_actionServices_triggered()
{
    serMainWindow  *p=new serMainWindow();
         p->showMaximized();
          this->hide();
         this->destroy();
}

void empwindow::on_actionEvents_triggered()
{
    CollectsMainWindow  *p=new CollectsMainWindow();
      p->showMaximized();
       this->hide();
      this->destroy();
}
