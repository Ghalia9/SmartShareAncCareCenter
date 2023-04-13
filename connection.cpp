#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
db = QSqlDatabase::addDatabase("QODBC");
bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("share");
db.setUserName("ela2");//inserer nom de l'utilisateur
db.setPassword("ela2");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;


    return  test;
}

void Connection::closeConnection(){ db.close(); }
