#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "employee.h"
#include "rfid.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool showen = false;

private slots:
    void on_pushButton_6_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_edit_clicked();

    void on_tableView_activated(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clear_clicked();

    void on_pushButton_4_clicked();

    void Read();

    void on_pushButton_logout_clicked();

private:
    Ui::MainWindow *ui;
    employee etmp;

    QString Data;
    RFID C;
};
#endif // MAINWINDOW_H
