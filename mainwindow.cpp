#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "destitute.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->tabDestitute->setModel(De.Show());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::centerAndResize() {

   // get the dimension available on this screen
   QSize availableSize = qApp->desktop()->availableGeometry().size();
   int width = availableSize.width();
   int height = availableSize.height();
   qDebug() << "Available dimensions " << width << "x" << height;
   width *= 0.6; // 90% of the screen size
   height *= 0.74; // 90% of the screen size
   qDebug() << "Computed dimensions " << width << "x" << height;
   QSize newSize( width, height );
   setGeometry(
       QStyle::alignedRect(
           Qt::LeftToRight,
           Qt::AlignCenter,
           newSize,
           qApp->desktop()->availableGeometry()
       )
   );
}

void MainWindow::on_pb_add_clicked()
{
   QString fn=ui->the_firstname->text();
   QString ln=ui->the_lastname->text();
   QString c=ui->the_contact->text();
   int level=ui->the_level->value();
   //int level=1;
   QString id=ui->the_id->text();
    Destitute D(id,fn,ln,level,c);
    bool test=D.Add();
    if(test)
    {
        //REFRESH
        ui->tabDestitute->setModel(De.Show());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Added successfuly.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("NOT ADDED.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}

void MainWindow::on_pb_delete_clicked()
{
    QString id=ui->the_id->text();
    bool test=De.Delete(id);
    if(test)
    {
        //REFRESH
        ui->tabDestitute->setModel(De.Show());
        QMessageBox::information(nullptr, QObject::tr("OK"),
                    QObject::tr("Deleted successfuly.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    }
    else
        QMessageBox::critical(nullptr, QObject::tr("Not OK"),
                    QObject::tr("NOT Deleted.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);


}
