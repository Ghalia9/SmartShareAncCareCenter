/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actiongeneral;
    QAction *actionto_to_list;
    QAction *actionAbout;
    QAction *actionManagments;
    QAction *actionDonations;
    QAction *actionServices;
    QAction *actionEvents;
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGroupBox *groupBox_4;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLineEdit *the_firstname;
    QLineEdit *the_lastname;
    QLineEdit *the_contact;
    QSpinBox *the_level;
    QPushButton *pb_delete;
    QPushButton *pb_update;
    QPushButton *pb_add;
    QGroupBox *groupBox_11;
    QPushButton *pushButton_pdf_4;
    QGroupBox *groupBox_10;
    QLabel *label_19;
    QLineEdit *lineEdit_4;
    QPushButton *pushButton_search_4;
    QLabel *label_20;
    QRadioButton *radioButton_level_4;
    QRadioButton *radioButton_contact_4;
    QListView *listView_5;
    QLabel *label;
    QLineEdit *the_id;
    QGroupBox *groupBox_6;
    QLabel *label_15;
    QLineEdit *lineEdit_2;
    QPushButton *pushButton_search_2;
    QLabel *label_16;
    QRadioButton *radioButton_level_2;
    QRadioButton *radioButton_contact_2;
    QListView *listView_3;
    QGroupBox *groupBox_7;
    QPushButton *pushButton_pdf_2;
    QGroupBox *groupBox_12;
    QLabel *label_21;
    QLineEdit *lineEdit_5;
    QPushButton *pushButton_search_5;
    QLabel *label_22;
    QRadioButton *radioButton_level_5;
    QRadioButton *radioButton_contact_5;
    QTableView *tabDestitute;
    QGroupBox *groupBox_5;
    QPushButton *pushButton_pdf_3;
    QGroupBox *groupBox_stat_2;
    QListView *listView_4;
    QWidget *tab_2;
    QWidget *tab_3;
    QWidget *tab_4;
    QFormLayout *formLayout_2;
    QGroupBox *groupBox_8;
    QFormLayout *formLayout_3;
    QFormLayout *formLayout_4;
    QFormLayout *formLayout;
    QLabel *label_11;
    QLineEdit *lineEdit_FirstName_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_12;
    QLineEdit *lineEdit_Last_Name_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_13;
    QLineEdit *lineEdit_contact_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_14;
    QSpinBox *spinBox_level_3;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_delete_3;
    QPushButton *pushButton_update_3;
    QPushButton *pushButton_add_3;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_3;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_4;
    QMenuBar *menubar;
    QMenu *menuManagments;
    QMenu *menuLogo;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1178, 754);
        QPalette palette;
        QBrush brush(QColor(96, 195, 244, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        MainWindow->setPalette(palette);
        MainWindow->setStyleSheet(QStringLiteral("background-color: rgb(96, 195, 244);"));
        actiongeneral = new QAction(MainWindow);
        actiongeneral->setObjectName(QStringLiteral("actiongeneral"));
        actiongeneral->setCheckable(false);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/Employees.png"), QSize(), QIcon::Normal, QIcon::Off);
        actiongeneral->setIcon(icon);
        QFont font;
        font.setFamily(QStringLiteral("Poppins"));
        font.setPointSize(9);
        actiongeneral->setFont(font);
        actionto_to_list = new QAction(MainWindow);
        actionto_to_list->setObjectName(QStringLiteral("actionto_to_list"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/Destitute.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionto_to_list->setIcon(icon1);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/logo application.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon2);
        actionManagments = new QAction(MainWindow);
        actionManagments->setObjectName(QStringLiteral("actionManagments"));
        actionDonations = new QAction(MainWindow);
        actionDonations->setObjectName(QStringLiteral("actionDonations"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/images/Donations.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDonations->setIcon(icon3);
        actionServices = new QAction(MainWindow);
        actionServices->setObjectName(QStringLiteral("actionServices"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/images/Services.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionServices->setIcon(icon4);
        actionEvents = new QAction(MainWindow);
        actionEvents->setObjectName(QStringLiteral("actionEvents"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/images/Events.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEvents->setIcon(icon5);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 0, 1021, 711));
        QFont font1;
        font1.setFamily(QStringLiteral("Poppins"));
        font1.setPointSize(10);
        tabWidget->setFont(font1);
        tabWidget->setTabPosition(QTabWidget::North);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        groupBox_4 = new QGroupBox(tab);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(20, 10, 481, 351));
        QPalette palette1;
        QBrush brush1(QColor(133, 214, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        groupBox_4->setPalette(palette1);
        groupBox_4->setFont(font1);
        groupBox_4->setStyleSheet(QStringLiteral("background-color: rgb(133, 214, 255);"));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(60, 60, 101, 20));
        label_7->setFont(font1);
        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(60, 120, 91, 20));
        label_8->setFont(font1);
        label_9 = new QLabel(groupBox_4);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(75, 180, 71, 20));
        label_9->setFont(font1);
        label_10 = new QLabel(groupBox_4);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(80, 240, 56, 16));
        label_10->setFont(font1);
        the_firstname = new QLineEdit(groupBox_4);
        the_firstname->setObjectName(QStringLiteral("the_firstname"));
        the_firstname->setGeometry(QRect(210, 60, 113, 22));
        the_firstname->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        the_lastname = new QLineEdit(groupBox_4);
        the_lastname->setObjectName(QStringLiteral("the_lastname"));
        the_lastname->setGeometry(QRect(210, 120, 113, 22));
        the_lastname->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        the_contact = new QLineEdit(groupBox_4);
        the_contact->setObjectName(QStringLiteral("the_contact"));
        the_contact->setGeometry(QRect(210, 180, 113, 22));
        the_contact->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        the_level = new QSpinBox(groupBox_4);
        the_level->setObjectName(QStringLiteral("the_level"));
        the_level->setGeometry(QRect(210, 240, 111, 22));
        the_level->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        the_level->setMaximum(5);
        pb_delete = new QPushButton(groupBox_4);
        pb_delete->setObjectName(QStringLiteral("pb_delete"));
        pb_delete->setGeometry(QRect(20, 300, 93, 28));
        pb_delete->setFont(font1);
        pb_delete->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        pb_update = new QPushButton(groupBox_4);
        pb_update->setObjectName(QStringLiteral("pb_update"));
        pb_update->setGeometry(QRect(190, 300, 93, 28));
        pb_update->setFont(font1);
        pb_update->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"alternate-background-color: rgb(255, 255, 255);"));
        pb_add = new QPushButton(groupBox_4);
        pb_add->setObjectName(QStringLiteral("pb_add"));
        pb_add->setGeometry(QRect(360, 300, 93, 28));
        pb_add->setFont(font1);
        pb_add->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        groupBox_11 = new QGroupBox(groupBox_4);
        groupBox_11->setObjectName(QStringLiteral("groupBox_11"));
        groupBox_11->setGeometry(QRect(540, 520, 471, 121));
        groupBox_11->setStyleSheet(QLatin1String("\n"
"background-color: rgb(133, 214, 255);"));
        pushButton_pdf_4 = new QPushButton(groupBox_11);
        pushButton_pdf_4->setObjectName(QStringLiteral("pushButton_pdf_4"));
        pushButton_pdf_4->setGeometry(QRect(50, 50, 371, 31));
        pushButton_pdf_4->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(255, 255, 255);"));
        pushButton_pdf_4->setCheckable(false);
        groupBox_10 = new QGroupBox(groupBox_4);
        groupBox_10->setObjectName(QStringLiteral("groupBox_10"));
        groupBox_10->setGeometry(QRect(540, -10, 471, 511));
        groupBox_10->setStyleSheet(QLatin1String("\n"
"border-color: rgb(0, 0, 0);\n"
"background-color: rgb(133, 214, 255);"));
        label_19 = new QLabel(groupBox_10);
        label_19->setObjectName(QStringLiteral("label_19"));
        label_19->setGeometry(QRect(60, 30, 56, 16));
        lineEdit_4 = new QLineEdit(groupBox_10);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        lineEdit_4->setGeometry(QRect(150, 30, 161, 22));
        lineEdit_4->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        pushButton_search_4 = new QPushButton(groupBox_10);
        pushButton_search_4->setObjectName(QStringLiteral("pushButton_search_4"));
        pushButton_search_4->setGeometry(QRect(360, 30, 61, 28));
        pushButton_search_4->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label_20 = new QLabel(groupBox_10);
        label_20->setObjectName(QStringLiteral("label_20"));
        label_20->setGeometry(QRect(30, 80, 56, 16));
        radioButton_level_4 = new QRadioButton(groupBox_10);
        radioButton_level_4->setObjectName(QStringLiteral("radioButton_level_4"));
        radioButton_level_4->setGeometry(QRect(100, 110, 97, 20));
        radioButton_contact_4 = new QRadioButton(groupBox_10);
        radioButton_contact_4->setObjectName(QStringLiteral("radioButton_contact_4"));
        radioButton_contact_4->setGeometry(QRect(280, 110, 97, 20));
        listView_5 = new QListView(groupBox_10);
        listView_5->setObjectName(QStringLiteral("listView_5"));
        listView_5->setGeometry(QRect(20, 150, 431, 341));
        listView_5->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label = new QLabel(groupBox_4);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(80, 30, 56, 16));
        the_id = new QLineEdit(groupBox_4);
        the_id->setObjectName(QStringLiteral("the_id"));
        the_id->setGeometry(QRect(210, 30, 113, 22));
        the_id->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        groupBox_6 = new QGroupBox(tab);
        groupBox_6->setObjectName(QStringLiteral("groupBox_6"));
        groupBox_6->setGeometry(QRect(1200, 190, 471, 511));
        groupBox_6->setStyleSheet(QLatin1String("\n"
"border-color: rgb(0, 0, 0);\n"
"background-color: rgb(133, 214, 255);"));
        label_15 = new QLabel(groupBox_6);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setGeometry(QRect(60, 30, 56, 16));
        lineEdit_2 = new QLineEdit(groupBox_6);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        lineEdit_2->setGeometry(QRect(150, 30, 161, 22));
        lineEdit_2->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        pushButton_search_2 = new QPushButton(groupBox_6);
        pushButton_search_2->setObjectName(QStringLiteral("pushButton_search_2"));
        pushButton_search_2->setGeometry(QRect(360, 30, 61, 28));
        pushButton_search_2->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label_16 = new QLabel(groupBox_6);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setGeometry(QRect(30, 80, 56, 16));
        radioButton_level_2 = new QRadioButton(groupBox_6);
        radioButton_level_2->setObjectName(QStringLiteral("radioButton_level_2"));
        radioButton_level_2->setGeometry(QRect(100, 110, 97, 20));
        radioButton_contact_2 = new QRadioButton(groupBox_6);
        radioButton_contact_2->setObjectName(QStringLiteral("radioButton_contact_2"));
        radioButton_contact_2->setGeometry(QRect(280, 110, 97, 20));
        listView_3 = new QListView(groupBox_6);
        listView_3->setObjectName(QStringLiteral("listView_3"));
        listView_3->setGeometry(QRect(20, 150, 431, 341));
        listView_3->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        groupBox_7 = new QGroupBox(tab);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setGeometry(QRect(1200, 720, 471, 121));
        groupBox_7->setStyleSheet(QLatin1String("\n"
"background-color: rgb(133, 214, 255);"));
        pushButton_pdf_2 = new QPushButton(groupBox_7);
        pushButton_pdf_2->setObjectName(QStringLiteral("pushButton_pdf_2"));
        pushButton_pdf_2->setGeometry(QRect(50, 50, 371, 31));
        pushButton_pdf_2->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(255, 255, 255);"));
        pushButton_pdf_2->setCheckable(false);
        groupBox_12 = new QGroupBox(tab);
        groupBox_12->setObjectName(QStringLiteral("groupBox_12"));
        groupBox_12->setGeometry(QRect(520, 10, 471, 511));
        groupBox_12->setFont(font1);
        groupBox_12->setStyleSheet(QLatin1String("\n"
"border-color: rgb(0, 0, 0);\n"
"background-color: rgb(133, 214, 255);"));
        label_21 = new QLabel(groupBox_12);
        label_21->setObjectName(QStringLiteral("label_21"));
        label_21->setGeometry(QRect(55, 30, 61, 20));
        label_21->setFont(font1);
        lineEdit_5 = new QLineEdit(groupBox_12);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        lineEdit_5->setGeometry(QRect(150, 30, 161, 22));
        lineEdit_5->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        pushButton_search_5 = new QPushButton(groupBox_12);
        pushButton_search_5->setObjectName(QStringLiteral("pushButton_search_5"));
        pushButton_search_5->setGeometry(QRect(360, 30, 71, 28));
        pushButton_search_5->setFont(font1);
        pushButton_search_5->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label_22 = new QLabel(groupBox_12);
        label_22->setObjectName(QStringLiteral("label_22"));
        label_22->setGeometry(QRect(30, 80, 61, 16));
        label_22->setFont(font1);
        radioButton_level_5 = new QRadioButton(groupBox_12);
        radioButton_level_5->setObjectName(QStringLiteral("radioButton_level_5"));
        radioButton_level_5->setGeometry(QRect(100, 110, 97, 20));
        radioButton_level_5->setFont(font1);
        radioButton_contact_5 = new QRadioButton(groupBox_12);
        radioButton_contact_5->setObjectName(QStringLiteral("radioButton_contact_5"));
        radioButton_contact_5->setGeometry(QRect(280, 110, 97, 20));
        radioButton_contact_5->setFont(font1);
        tabDestitute = new QTableView(groupBox_12);
        tabDestitute->setObjectName(QStringLiteral("tabDestitute"));
        tabDestitute->setGeometry(QRect(20, 150, 431, 341));
        tabDestitute->setStyleSheet(QLatin1String("\n"
"background-color: rgb(255, 255, 255);"));
        groupBox_5 = new QGroupBox(tab);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setGeometry(QRect(520, 540, 471, 121));
        groupBox_5->setFont(font1);
        groupBox_5->setStyleSheet(QLatin1String("\n"
"background-color: rgb(133, 214, 255);"));
        pushButton_pdf_3 = new QPushButton(groupBox_5);
        pushButton_pdf_3->setObjectName(QStringLiteral("pushButton_pdf_3"));
        pushButton_pdf_3->setGeometry(QRect(50, 50, 371, 31));
        pushButton_pdf_3->setFont(font1);
        pushButton_pdf_3->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"background-color: rgb(255, 255, 255);"));
        pushButton_pdf_3->setCheckable(false);
        groupBox_stat_2 = new QGroupBox(tab);
        groupBox_stat_2->setObjectName(QStringLiteral("groupBox_stat_2"));
        groupBox_stat_2->setGeometry(QRect(20, 380, 481, 281));
        groupBox_stat_2->setFont(font1);
        groupBox_stat_2->setStyleSheet(QLatin1String("\n"
"background-color: rgb(133, 214, 255);"));
        listView_4 = new QListView(groupBox_stat_2);
        listView_4->setObjectName(QStringLiteral("listView_4"));
        listView_4->setGeometry(QRect(20, 40, 431, 221));
        listView_4->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        formLayout_2 = new QFormLayout(tab_4);
        formLayout_2->setObjectName(QStringLiteral("formLayout_2"));
        groupBox_8 = new QGroupBox(tab_4);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        groupBox_8->setPalette(palette2);
        groupBox_8->setStyleSheet(QStringLiteral("background-color: rgb(133, 214, 255);"));
        formLayout_3 = new QFormLayout(groupBox_8);
        formLayout_3->setObjectName(QStringLiteral("formLayout_3"));
        formLayout_4 = new QFormLayout();
        formLayout_4->setObjectName(QStringLiteral("formLayout_4"));
        formLayout = new QFormLayout();
        formLayout->setObjectName(QStringLiteral("formLayout"));
        label_11 = new QLabel(groupBox_8);
        label_11->setObjectName(QStringLiteral("label_11"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_11);

        lineEdit_FirstName_3 = new QLineEdit(groupBox_8);
        lineEdit_FirstName_3->setObjectName(QStringLiteral("lineEdit_FirstName_3"));
        lineEdit_FirstName_3->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit_FirstName_3);


        formLayout_4->setLayout(0, QFormLayout::LabelRole, formLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_12 = new QLabel(groupBox_8);
        label_12->setObjectName(QStringLiteral("label_12"));

        horizontalLayout_2->addWidget(label_12);

        lineEdit_Last_Name_3 = new QLineEdit(groupBox_8);
        lineEdit_Last_Name_3->setObjectName(QStringLiteral("lineEdit_Last_Name_3"));
        lineEdit_Last_Name_3->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        horizontalLayout_2->addWidget(lineEdit_Last_Name_3);


        formLayout_4->setLayout(1, QFormLayout::LabelRole, horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_13 = new QLabel(groupBox_8);
        label_13->setObjectName(QStringLiteral("label_13"));

        horizontalLayout_3->addWidget(label_13);

        lineEdit_contact_3 = new QLineEdit(groupBox_8);
        lineEdit_contact_3->setObjectName(QStringLiteral("lineEdit_contact_3"));
        lineEdit_contact_3->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        horizontalLayout_3->addWidget(lineEdit_contact_3);


        formLayout_4->setLayout(2, QFormLayout::LabelRole, horizontalLayout_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_14 = new QLabel(groupBox_8);
        label_14->setObjectName(QStringLiteral("label_14"));

        horizontalLayout_4->addWidget(label_14);

        spinBox_level_3 = new QSpinBox(groupBox_8);
        spinBox_level_3->setObjectName(QStringLiteral("spinBox_level_3"));
        spinBox_level_3->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        spinBox_level_3->setMaximum(5);

        horizontalLayout_4->addWidget(spinBox_level_3);


        formLayout_4->setLayout(3, QFormLayout::LabelRole, horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        pushButton_delete_3 = new QPushButton(groupBox_8);
        pushButton_delete_3->setObjectName(QStringLiteral("pushButton_delete_3"));
        pushButton_delete_3->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        horizontalLayout_5->addWidget(pushButton_delete_3);

        pushButton_update_3 = new QPushButton(groupBox_8);
        pushButton_update_3->setObjectName(QStringLiteral("pushButton_update_3"));
        pushButton_update_3->setStyleSheet(QLatin1String("background-color: rgb(255, 255, 255);\n"
"alternate-background-color: rgb(255, 255, 255);"));

        horizontalLayout_5->addWidget(pushButton_update_3);

        pushButton_add_3 = new QPushButton(groupBox_8);
        pushButton_add_3->setObjectName(QStringLiteral("pushButton_add_3"));
        pushButton_add_3->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        horizontalLayout_5->addWidget(pushButton_add_3);


        formLayout_4->setLayout(4, QFormLayout::LabelRole, horizontalLayout_5);


        formLayout_3->setLayout(0, QFormLayout::LabelRole, formLayout_4);


        formLayout_2->setWidget(0, QFormLayout::LabelRole, groupBox_8);

        tabWidget->addTab(tab_4, QString());
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout_3 = new QVBoxLayout(layoutWidget);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout_4 = new QVBoxLayout(layoutWidget1);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setEnabled(true);
        menubar->setGeometry(QRect(0, 0, 1178, 26));
        menubar->setStyleSheet(QStringLiteral(""));
        menuManagments = new QMenu(menubar);
        menuManagments->setObjectName(QStringLiteral("menuManagments"));
        menuLogo = new QMenu(menubar);
        menuLogo->setObjectName(QStringLiteral("menuLogo"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        toolBar->setStyleSheet(QLatin1String("\n"
"border-color: rgb(0, 0, 0);\n"
"background-color: rgb(133, 214, 255);"));
        toolBar->setIconSize(QSize(100, 100));
        MainWindow->addToolBar(Qt::LeftToolBarArea, toolBar);

        menubar->addAction(menuManagments->menuAction());
        menubar->addAction(menuLogo->menuAction());
        menuManagments->addAction(actiongeneral);
        menuManagments->addAction(actionto_to_list);
        menuManagments->addAction(actionDonations);
        menuManagments->addAction(actionServices);
        menuManagments->addAction(actionEvents);
        menuLogo->addAction(actionAbout);
        toolBar->addAction(actionAbout);
        toolBar->addAction(actiongeneral);
        toolBar->addSeparator();
        toolBar->addAction(actionto_to_list);
        toolBar->addSeparator();
        toolBar->addAction(actionDonations);
        toolBar->addSeparator();
        toolBar->addAction(actionServices);
        toolBar->addSeparator();
        toolBar->addAction(actionEvents);
        toolBar->addSeparator();

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actiongeneral->setText(QApplication::translate("MainWindow", "Employees", Q_NULLPTR));
        actionto_to_list->setText(QApplication::translate("MainWindow", "Distitutes", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("MainWindow", "logo", Q_NULLPTR));
        actionManagments->setText(QApplication::translate("MainWindow", "Managments", Q_NULLPTR));
        actionDonations->setText(QApplication::translate("MainWindow", "Donations", Q_NULLPTR));
        actionServices->setText(QApplication::translate("MainWindow", "Services", Q_NULLPTR));
        actionEvents->setText(QApplication::translate("MainWindow", "Events", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Add a destitute", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "First Name", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindow", "Last Name", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindow", "Contact", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindow", "Level", Q_NULLPTR));
        pb_delete->setText(QApplication::translate("MainWindow", "Delete", Q_NULLPTR));
        pb_update->setText(QApplication::translate("MainWindow", "Update", Q_NULLPTR));
        pb_add->setText(QApplication::translate("MainWindow", "Add", Q_NULLPTR));
        groupBox_11->setTitle(QApplication::translate("MainWindow", "PDF", Q_NULLPTR));
        pushButton_pdf_4->setText(QApplication::translate("MainWindow", "Generate PDF", Q_NULLPTR));
        groupBox_10->setTitle(QApplication::translate("MainWindow", "Show", Q_NULLPTR));
        label_19->setText(QApplication::translate("MainWindow", "Search:", Q_NULLPTR));
        pushButton_search_4->setText(QApplication::translate("MainWindow", "Search", Q_NULLPTR));
        label_20->setText(QApplication::translate("MainWindow", "Sort by:", Q_NULLPTR));
        radioButton_level_4->setText(QApplication::translate("MainWindow", "Level", Q_NULLPTR));
        radioButton_contact_4->setText(QApplication::translate("MainWindow", "Contact", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "ID", Q_NULLPTR));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "Show", Q_NULLPTR));
        label_15->setText(QApplication::translate("MainWindow", "Search:", Q_NULLPTR));
        pushButton_search_2->setText(QApplication::translate("MainWindow", "Search", Q_NULLPTR));
        label_16->setText(QApplication::translate("MainWindow", "Sort by:", Q_NULLPTR));
        radioButton_level_2->setText(QApplication::translate("MainWindow", "Level", Q_NULLPTR));
        radioButton_contact_2->setText(QApplication::translate("MainWindow", "Contact", Q_NULLPTR));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "PDF", Q_NULLPTR));
        pushButton_pdf_2->setText(QApplication::translate("MainWindow", "Generate PDF", Q_NULLPTR));
        groupBox_12->setTitle(QApplication::translate("MainWindow", "Show", Q_NULLPTR));
        label_21->setText(QApplication::translate("MainWindow", "Search:", Q_NULLPTR));
        pushButton_search_5->setText(QApplication::translate("MainWindow", "Search", Q_NULLPTR));
        label_22->setText(QApplication::translate("MainWindow", "Sort by:", Q_NULLPTR));
        radioButton_level_5->setText(QApplication::translate("MainWindow", "Level", Q_NULLPTR));
        radioButton_contact_5->setText(QApplication::translate("MainWindow", "Contact", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "PDF", Q_NULLPTR));
        pushButton_pdf_3->setText(QApplication::translate("MainWindow", "Generate PDF", Q_NULLPTR));
        groupBox_stat_2->setTitle(QApplication::translate("MainWindow", "Statistics", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "General", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Qr_Code", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainWindow", "Map", Q_NULLPTR));
        groupBox_8->setTitle(QApplication::translate("MainWindow", "Add a destitute", Q_NULLPTR));
        label_11->setText(QApplication::translate("MainWindow", "First Name", Q_NULLPTR));
        label_12->setText(QApplication::translate("MainWindow", "Last Name", Q_NULLPTR));
        label_13->setText(QApplication::translate("MainWindow", "Contact", Q_NULLPTR));
        label_14->setText(QApplication::translate("MainWindow", "Level", Q_NULLPTR));
        pushButton_delete_3->setText(QApplication::translate("MainWindow", "Delete", Q_NULLPTR));
        pushButton_update_3->setText(QApplication::translate("MainWindow", "Update", Q_NULLPTR));
        pushButton_add_3->setText(QApplication::translate("MainWindow", "Add", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainWindow", "Page", Q_NULLPTR));
        menuManagments->setTitle(QApplication::translate("MainWindow", "Managments", Q_NULLPTR));
        menuLogo->setTitle(QApplication::translate("MainWindow", "About", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
