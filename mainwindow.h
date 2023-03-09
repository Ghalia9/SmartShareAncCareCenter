#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDesktopWidget>
#include <QDebug>
#include <QMainWindow>
#include <destitute.h>

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

private:
    Ui::MainWindow *ui;
    Destitute De;
};
#endif // MAINWINDOW_H
