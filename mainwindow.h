#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDesktopWidget>
#include <QDebug>
#include <QMainWindow>
#include <destitute.h>

#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
#include <QBarSet>
#include <QBarSeries>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
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

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Destitute De;
};
#endif // MAINWINDOW_H
