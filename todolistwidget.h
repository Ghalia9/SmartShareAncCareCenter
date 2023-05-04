#ifndef TODOLISTWIDGET_H
#define TODOLISTWIDGET_H

#include <QWidget>

#include <QMainWindow>
#include <QListView>
#include <QStringListModel>

class CToDoList : public QMainWindow
{
    Q_OBJECT
public:
    CToDoList();

protected slots:
    void onAdd();
    void onRemove();

private:
    QListView* m_pwPending = nullptr;
    QListView* m_pwCompleted = nullptr;

    QAction* m_pActAdd = nullptr;
    QAction* m_pActRemove = nullptr;
};


#endif // TODOLISTWIDGET_H
