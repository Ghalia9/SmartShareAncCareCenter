#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
db = QSqlDatabase::addDatabase("QODBC");
bool test=false;

db.setDatabaseName("shareandcarecenter");
db.setUserName("Ghalia");//inserer nom de l'utilisateur
db.setPassword("ghalia9");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
void Connection::closeConnection(){db.close();}
