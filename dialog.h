#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    // Declare any private member variables or functions here
};

#endif // DIALOG_H
