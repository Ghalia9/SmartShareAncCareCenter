#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "donation.h"
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

private slots:
     void on_pb_ajouter_clicked();

    void on_pb_supprimer_clicked();

    // void on_pb_ajouter_clicked();


    void on_pb_modifier_clicked();

    void on_pb_sort_clicked();

    void on_pb_search_clicked();

    void on_pdf_clicked();

    void on_tab_donation_activated(const QModelIndex &index);

    void on_le_invoice_clicked();

    void on_btn_print_clicked();
    void keyPressEvent(QKeyEvent *event); // Function declaration


    void on_stats_clicked();

    void on_pb_catalogue_clicked();

    void on_pushButton5_clicked();

private:
    Ui::MainWindow *ui;
    donation Etmp;
    QByteArray data;
    Arduino A;
  //  donation donationObj;

};

#endif // MAINWINDOW_H
