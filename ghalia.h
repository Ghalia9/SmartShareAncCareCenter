#ifndef GHALIA_H
#define GHALIA_H

#include <QDialog>

namespace Ui {
class ghalia;
}

class ghalia : public QDialog
{
    Q_OBJECT

public:
    explicit ghalia(QWidget *parent = nullptr);
    ~ghalia();

private:
    Ui::ghalia *ui;
};

#endif // GHALIA_H
