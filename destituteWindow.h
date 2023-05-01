#ifndef destituteWindow_H
#define destituteWindow_H
#include <QDesktopWidget>
#include <QDebug>
#include <QMainWindow>
#include <destitute.h>
#include <capteur.h>

#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
#include <QBarSet>
#include <QBarSeries>

QT_BEGIN_NAMESPACE
namespace Ui { class destituteWindow; }
QT_END_NAMESPACE

class destituteWindow : public QMainWindow
{
    Q_OBJECT

public:
    destituteWindow(QWidget *parent = nullptr);
    ~destituteWindow();
    void centerAndResize();


private slots:
    void on_pb_add_clicked();

    void on_pb_delete_clicked();

    void on_pb_update_clicked();

    void on_showtab_activated(const QModelIndex &index);

    void on_pb_search_clicked();

    void on_pb_sort_clicked();

    void on_pb_pdf_clicked();

    void on_pb_clear_clicked();

    void on_listQR_activated(const QModelIndex &index);

    void Read();


    void on_actiongeneral_triggered();

    void on_actionDonations_triggered();

    void on_actionServices_triggered();

    void on_actionEvents_triggered();

private:
    Ui::destituteWindow *ui;
    Destitute De;

    QByteArray data;
     Capteur C;
};
#endif // destituteWindow_H
