#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "service.h"
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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


   void on_stockVerification_clicked();


private:
    Ui::MainWindow *ui;
    Service Etmp;
    QByteArray data;


};

#endif // MAINWINDOW_H
