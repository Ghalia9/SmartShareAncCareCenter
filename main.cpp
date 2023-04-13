#include "mainwindow.h"
#include "loginpage.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QCoreApplication>
#include <QtSql>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//login window

//  Mainwindow
    Connection c;
    bool test=c.createconnect(); //etablir la connexion
    loginpage l;
    MainWindow w;
    if(test)
    {l.show();
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

}
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

    return a.exec();
}
