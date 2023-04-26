#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "dialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include "smtp.h"
#include <QMainWindow>
#include "collects.h"
#include "arduino.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
void refreshCalendar();
void showEvents(const QDate& date);


private slots:
     void on_pushButton_ajouter_clicked();

    void on_pushButton_supprimer_clicked();

    void on_pb_modifier_clicked();

    void on_confirm_sort_clicked();

    void on_confirm_search_clicked();

    void on_pdf_clicked();

    void on_stats_clicked();

    //void on_tabWidget_currentChanged(int index);

    void on_tab_read_activated(const QModelIndex &index);

    void on_calendarWidget_clicked(const QDate &date);
void on_arduino1_clicked();
private slots:
    void sendMail();
    void mailSent();
    void on_refresh_clicked();

private:
    Ui::MainWindow *ui;
    Collects Etmp;
   // Dialog *dialog;
    QStringList files;
    Arduino A;

};

#endif // MAINWINDOW_H

