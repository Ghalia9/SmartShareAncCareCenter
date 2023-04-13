#ifndef CONNECTION_H
#define CONNECTION_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QSqlQueryModel>
#include <QDebug>
#include <QObject>

class Connection : public QObject
{
    Q_OBJECT
public:
    Connection();
    bool createconnect();
    void closeConnection();

public slots:
    void newCollectAdded();
    void refreshCalendar();

private:
    QSqlDatabase db;
    QObject database; // declare database as a member variable

};

#endif // CONNECTION_H
