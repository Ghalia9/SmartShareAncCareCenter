#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "service.h"
#include "arduino.h"
#include <QFileDialog>

namespace Ui {
class serMainWindow;
}

class serMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit serMainWindow(QWidget *parent = nullptr);
    ~serMainWindow();

private slots:
     void on_pushButton_ajouter_clicked();

     void on_pushButton_supprimer_clicked();

   void on_pb_modifier_clicked();

   void on_pb_recherche_clicked();

   void on_pb_sort_clicked();

   void on_export_excel_clicked();

   void on_pb_pdf1_clicked();

   void on_pb_pdf2_clicked();

   void on_stats_clicked();


//   void on_stockVerification_clicked();


   void on_tab_service_activated(const QModelIndex &index);

   void on_pb_arduino_clicked();

   void on_collects_triggered();

   void on_destitute_triggered();

   void on_employees_triggered();

   void on_donations_triggered();

   void on_services_triggered();

   void on_logo_triggered();

  // void on_arduino1_clicked();

   void on_refresh_clicked();

   void on_stockVerification_clicked();

private:
    Ui::serMainWindow *ui;
    Service Etmp;
    QByteArray data;
    Arduino A; //objet temporaire

};

#endif // MAINWINDOW_H
