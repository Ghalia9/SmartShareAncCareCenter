#ifndef DESTITUTE_H
#define DESTITUTE_H

#include <QDialog>

namespace Ui {
class Destitute;
}

class Destitute : public QDialog
{
    Q_OBJECT

public:
    explicit Destitute(QWidget *parent = nullptr);
    ~Destitute();

private:
    Ui::Destitute *ui;
};

#endif // DESTITUTE_H
