#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QDialog>
#include "smtp.h"
namespace Ui {
class loginpage;
}

class loginpage : public QDialog
{
    Q_OBJECT

public:
    explicit loginpage(QWidget *parent = nullptr);

    ~loginpage();

private slots:
    void on_pushButton__login_clicked();

    void on_pushButton_clicked();
    void mailSent ();

    void on_pushButton_2_clicked();

private:
    Ui::loginpage *ui;
};

#endif // LOGINPAGE_H
