#ifndef donationswindow_H
#define donationswindow_H

#include <QMainWindow>
#include "donation.h"
#include "arduino.h"
namespace Ui {
class donationswindow;
}

class donationswindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit donationswindow(QWidget *parent = nullptr);
    ~donationswindow();

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


    //void on_changeButton_clicked();

    void on_actionemployee_triggered();

    void on_actiondestitutes_triggered();

    void on_actiondonations_triggered();

    void on_actionservices_triggered();

    void on_actionevents_triggered();

    void on_actionabout_this_app_triggered();

    //void on_tab_stock_activated(const QModelIndex &index);

    void on_pb_image_clicked();

    void on_pb_clear_clicked();

private:
    Ui::donationswindow *ui;
    donation Etmp;
    QByteArray data;
    Arduino A;
  //  donation donationObj;

};

#endif // donationswindow_H
