#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    bool test=false;
    db.setDatabaseName("shareandcarecenter");
    db.setUserName("Koussay");//inserer nom de l'utilisateur
    db.setPassword("esprit23");//inserer mot de passe de cet utilisateur

    if (db.open())
        test=true;

    connect(&database, SIGNAL(newCollectAdded()), this, SLOT(newCollectAdded()));

    return  test;
}

void Connection::closeConnection()
{
    db.close();
}

void Connection::newCollectAdded()
{
    refreshCalendar();
}

void Connection::refreshCalendar()
{
    // code for refreshing the calendar
}

