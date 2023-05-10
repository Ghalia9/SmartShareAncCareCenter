#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;

//
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("shareandcarecenter");
//db.setUserName("ela2");//inserer nom de l'utilisateur
//db.setPassword("ela2");//inserer mot de passe de cet utilisateur
db.setUserName("eyaa");//inserer nom de l'utilisateur
db.setPassword("esprit23");//inserer mot de passe de cet utilisateur
//db.setUserName("Koussay");//inserer nom de l'utilisateur
//db.setPassword("esprit23");//inserer mot de passe de cet utilisateur
//db.setUserName("ismail2023");//inserer nom de l'utilisateur
//db.setPassword("ismail2023");//inserer mot de passe de cet utilisateur
    if (db.open())
test=true;





    return  test;
}
void Connection::closeconnection(){db.close();}
