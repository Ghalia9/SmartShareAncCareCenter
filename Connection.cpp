
#include "Connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
bool test=false;
db.setDatabaseName("shareandcarecenter");
db.setUserName("eyaa");//inserer nom de l'utilisateur
db.setPassword("esprit23");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
void Connection::closeConnection()
{
    db.close();
}
