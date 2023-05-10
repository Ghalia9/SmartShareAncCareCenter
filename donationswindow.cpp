#include "donationswindow.h"
#include "ui_donationswindow.h"
#include "donation.h"
#include "QtDebug"
#include <QMessageBox>
#include <QIntValidator>
#include <iostream>
#include <QTextDocument>
#include <QTextStream>
#include <QPrinter>
#include <QPrintDialog>
#include <QFileDialog>
#include <QChart>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include <QtCharts>
#include <QtGui>
#include <QSqlError>
#include <QApplication>
#include <QScreen>
#include <QPixmap>
#include <QKeySequence>
#include <QKeyEvent>
#include <QtNetwork>
#include "themewidget1.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <dialog.h>
#include <QPropertyAnimation>
#include "arduino.h"
#include "loginpage.h"
#include "CollectsMainWindow.h"
#include "empwindow.h"
#include "destituteWindow.h"
#include "donationswindow.h"
#include "sermainwindow.h"
#include <QtWidgets>
#include <QtCharts>
#include <QtSql>





donationswindow::donationswindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::donationswindow)
{
    ui->setupUi(this);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
        switch(ret){
        case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
            break;
        case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
           break;
        case(-1):qDebug() << "arduino is not available";
        }
         //QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer

        ui->tab_stock->setModel(Etmp.afficher2());
          ui->tab_stock->resizeColumnsToContents();
    ui->le_image->setReadOnly(true);
    ui->le_id->setReadOnly(true);//le slot update_label suite à la reception du signal readyRead (reception des données).
    ui->tab_donation->setModel(Etmp.afficher());
    ui->le_amount->setValidator(new QDoubleValidator(0, 9999999, 3, this));
    ui->le_quantity->setValidator(new QIntValidator(0, 9999999, this));
    ui->le_phonenumber->setMaxLength(8);
    ui->le_phonenumber->setValidator(new QRegExpValidator(QRegExp("\\d{8}"), this));

    //donationObj = *new donation();


}

donationswindow::~donationswindow()
{
    delete ui;
}

void donationswindow::on_pb_ajouter_clicked()
{
    // Generate the next ID
    QSqlQuery query("SELECT MAX(donation_id) FROM donations");
    query.next();
    QString lastId = query.value(0).toString();
    int nextIndex = lastId.isEmpty() ? 1 : lastId.right(3).toInt() + 1;  // extract the numeric part of the ID and increment it
    QString donation_id = "DON" + QString("%1").arg(nextIndex, 3, 10, QChar('0')); // create the new ID

    double amount = ui->le_amount->text().toDouble();
    int quantity = ui->le_quantity->text().toInt();
    QString category_name = ui->le_categoryname->currentText();
    QString name = ui->le_name->text();
    QString phone_number = ui->le_phonenumber->text();
    QString description = ui->le_description->text();
    QString image = ui->le_image->text();

    donation D(donation_id, category_name, name, description, amount, quantity, phone_number,image);
    bool test = D.ajouter();

    if (test) {
        //Refresh (actualiser)
        ui->tab_donation->setModel(Etmp.afficher());

        QMessageBox::information(nullptr, QObject::tr("OK"), QObject::tr("Ajout effectué\n" "Click cancel to exit."), QMessageBox::Cancel);

        // Check if category is "money" and update totaldons table
        if (category_name == "money") {
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE totaldons SET total = total + :amount WHERE category = 'money'");
            updateQuery.bindValue(":amount", amount);
            updateQuery.exec();
        }
        else {
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE totaldons SET total = total + :quantity WHERE category = :category_name");
            updateQuery.bindValue(":quantity", quantity);
            updateQuery.bindValue(":category_name", category_name);
            updateQuery.exec();
            if (amount != 0) {
                   QSqlQuery updateMoneyQuery;
                   updateMoneyQuery.prepare("UPDATE totaldons SET total = total + :amount WHERE category = 'money'");
                   updateMoneyQuery.bindValue(":amount", amount);
                   updateMoneyQuery.exec();
               }
        }

    }
    else {
        QMessageBox::critical(nullptr, QObject::tr("NOT OK"), QObject::tr("Ajout non effectué\n" "Click cancel to exit."), QMessageBox::Cancel);
    }
}





void donationswindow::on_pb_supprimer_clicked()
{
donation D1;
D1.setDonationID(ui->le_id->text());
bool test=Etmp.supprimer(D1.getDonationID());

if(test)
{

    //Refresh (actualiser)
    ui->tab_donation->setModel(Etmp.afficher());

QMessageBox::information(nullptr, QObject::tr("OK"),
QObject::tr("Suppression effectué\n"
             "Click cancel to exit."),QMessageBox::Cancel);
}
else
QMessageBox::critical(nullptr, QObject::tr("NOT OK"),
QObject::tr("Suppression non effectué\n"
             "Click cancel to exit."),QMessageBox::Cancel);

}
void donationswindow::on_pb_modifier_clicked()
{
    QString donation_id=ui->le_id->text();
    QString category_name = ui->le_categoryname->currentText();
    QString name=ui->le_name->text();
    QString description=ui->le_description->text();
    double amount=ui->le_amount->text().toDouble();
    int quantity=ui->le_quantity->text().toInt();
    QString phone_number=ui->le_phonenumber->text();
    QString image=ui->le_image->text();



//QString category_name=ui->le_categoryname->text();

donation D(donation_id,category_name,name,description,amount,quantity,phone_number,image);

    bool test = D.modifier();

    if (test){
        QMessageBox::information(nullptr, QObject::tr("database is open"),
                    QObject::tr("Modification effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
        ui->tab_donation->setModel(D.afficher());
    }
    else{
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                    QObject::tr("Modification non effectué.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    ui->tab_donation->setModel(D.afficher());
}
void donationswindow::on_pb_sort_clicked()
{

    donation D;
        if(ui->sortbox->currentIndex()==0){
            ui->tab_donation->setModel(D.sortID());

        }
        else if (ui->sortbox->currentIndex()==1)
        {
           ui->tab_donation->setModel(D.sortCategoryName());

        }

        else
           std::cout << "no combobox" << std::endl;
}

void donationswindow::on_pb_search_clicked()
{

    donation d1;
    QString recherche = ui->le_search->text();
    if(recherche.length()!=0)
{
        if(ui->searchbox->currentIndex()==0){
            ui->tab_donation->setModel(d1.rechercherCategoryName(recherche));

        }
        else if (ui->searchbox->currentIndex()==1)
        {
            ui->tab_donation->setModel(d1.rechercherID2(recherche));

        }
        else if(ui->searchbox->currentIndex()==2)
        {
            ui->tab_donation->setModel(d1.recherchernom(recherche));
    }
    else
    {
       ui->tab_donation->setModel(d1.afficher());
    }
}
}

void donationswindow::on_pdf_clicked()
    {
        QString fileName = QFileDialog::getSaveFileName(this, "Save PDF", "", "PDF Files (*.pdf)");
        if (fileName.isEmpty())
            return;

        QString strStream;
        QTextStream out(&strStream);
        const int rowCount = ui->tab_donation->model()->rowCount();
        const int columnCount =ui->tab_donation->model()->columnCount();

        out <<  "<html>\n"
                "<head>\n"
                "<meta Content=\"Text/html; charset=Windows-1251\">\n"
                <<  QString("<title>%1</title>\n").arg("eleve")
                <<  "</head>\n"
                "<body bgcolor=#FDFEFE link=#5000A0>\n"
                    "<h1>List of donations</h1>"
                    "<table border=1 cellspacing=0 cellpadding=2>\n";

        // headers
        out << "<thead><tr bgcolor=#F5B7B1>";
        for (int column = 0; column < columnCount; column++)
            if (!ui->tab_donation->isColumnHidden(column))
                out << QString("<th>%1</th>").arg(ui->tab_donation->model()->headerData(column, Qt::Horizontal).toString());
        out << "</tr></thead>\n";

        // data table
        for (int row = 0; row < rowCount; row++) {
            out << "<tr>";
            for (int column = 0; column < columnCount; column++) {
                if (!ui->tab_donation->isColumnHidden(column)) {
                    QString data = ui->tab_donation->model()->data(ui->tab_donation->model()->index(row, column)).toString().simplified();
                    out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
                }
            }
            out << "</tr>\n";
        }
        out <<  "</table>\n"
            "</body>\n"
            "</html>\n";

        QTextDocument *document = new QTextDocument();
        document->setHtml(strStream);

        QPrinter printer(QPrinter::PrinterResolution);
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName(fileName);
        document->print(&printer);
    }


void donationswindow::on_tab_donation_activated(const QModelIndex &index)
{
    QString donation_id = ui->tab_donation->model()->data(ui->tab_donation->model()->index(index.row(), 0)).toString();
        QString category_name = ui->tab_donation->model()->data(ui->tab_donation->model()->index(index.row(), 1)).toString();
        QString name = ui->tab_donation->model()->data(ui->tab_donation->model()->index(index.row(), 2)).toString();
        QString description = ui->tab_donation->model()->data(ui->tab_donation->model()->index(index.row(), 3)).toString();
        int quantiy = ui->tab_donation->model()->data(ui->tab_donation->model()->index(index.row(), 4)).toInt();
        double amount = ui->tab_donation->model()->data(ui->tab_donation->model()->index(index.row(), 5)).toDouble();
        QString phone_number = ui->tab_donation->model()->data(ui->tab_donation->model()->index(index.row(), 6)).toString();
        QString image = ui->tab_donation->model()->data(ui->tab_donation->model()->index(index.row(), 7)).toString();



        ui->le_id->setText(donation_id);
        ui->le_name->setText(name);
        ui->le_categoryname->setCurrentText(category_name);
        ui->le_quantity->setText(QString::number(quantiy));
        ui->le_amount->setText(QString::number(amount));
        ui->le_description->setText(description);
        ui->le_phonenumber->setText(phone_number);
        ui->le_image->setText(image);
}


void donationswindow::on_le_invoice_clicked()
{

    QSqlQuery query;
    double total_donations = 0.0, total_collections = 0.0, total_service_budgets = 0.0 , total_collect_budgets = 0.0;

    // Get total donations
    if (query.exec("SELECT SUM(amount) FROM donations")) {
        if (query.next()) {
            total_donations = query.value(0).toDouble();
        }
    } else {
        qDebug() << "Error getting total donations: " << query.lastError().text();
    }

    // Get total collections
    if (query.exec("SELECT SUM(collect_budget) FROM collects")) {
        if (query.next()) {
            total_collections = query.value(0).toDouble();
        }
    } else {
        qDebug() << "Error getting total collections: " << query.lastError().text();
    }

    // Get total service budgets
    if (query.exec("SELECT SUM(BUDGET_S) FROM services")) {
        if (query.next()) {
            total_service_budgets = query.value(0).toDouble();
        }
    } else {
        qDebug() << "Error getting total service budgets: " << query.lastError().text();
    }

    if (query.exec("SELECT SUM(collect_budget) FROM collects")) {
        if (query.next()) {
            total_collect_budgets = query.value(0).toDouble();
        }
    } else {
        qDebug() << "Error getting total collect budgets: " << query.lastError().text();
    }

     double net_money =  total_donations+total_collections-total_service_budgets-total_collect_budgets;

    // Display totals in labels
    ui->lbl_total_donations->setText(QString("%1").arg(total_donations));
    ui->lbl_total_collections->setText(QString("%1").arg(total_collections));
    ui->lbl_total_service_budgets->setText(QString("%1").arg(total_service_budgets));
    ui->lbl_total_collect_budgets->setText(QString("%1").arg(total_collect_budgets));
    ui->lbl_net->setText(QString("%1").arg(net_money));


}




void donationswindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_S)
    {
        // Get the primary screen
        QScreen *screen = QGuiApplication::primaryScreen();

        // Capture a screenshot
        QPixmap screenshot = screen->grabWindow(QApplication::desktop()->winId());

        // Ask the user to choose a file path to save the screenshot
        QString filePath = QFileDialog::getSaveFileName(this, tr("Save Screenshot"), "", tr("PNG Images (*.png);;All Files (*)"));

        // Save the screenshot to the chosen file path
        if (!filePath.isEmpty())
        {
            screenshot.save(filePath, "PNG");
            QMessageBox::information(this, tr("Screenshot"), tr("Screenshot saved to %1").arg(filePath));
        }
    }
    else
    {
        QMainWindow::keyPressEvent(event);
    }
}




void donationswindow::on_btn_print_clicked()
{
    QPrinter printer;
    QPrintDialog *printDialog = new QPrintDialog(&printer, this);

    if (printDialog->exec() == QDialog::Accepted) {
        QTextDocument document;
        QTextCursor cursor(&document);

        // Set the font and font size for the document
        QFont font("Arial", 12);
        document.setDefaultFont(font);

        // Add the invoice header
        cursor.insertHtml("<center><h1><font color='red'>Invoice</font></h1><br>");

        // Add the total donations
        QTextBlockFormat leftFormat;
               leftFormat.setAlignment(Qt::AlignLeft);
               cursor.setBlockFormat(leftFormat);
        cursor.insertHtml("<p><strong>Total Donations:</strong></p><p>" + ui->lbl_total_donations->text() + "</p><br>");

        // Add the total collections
        cursor.insertHtml("<p><strong>Total Collections:</strong></p><p>" + ui->lbl_total_collections->text() + "</p><br>");

        // Add the total service budgets
        cursor.insertHtml("<p><strong>Total Service Budgets:</strong></p><p>" + ui->lbl_total_service_budgets->text() + "</p><br>");

        // Add the total collect budgets
        cursor.insertHtml("<p><strong>Total Collect Budgets:</strong></p><p>" + ui->lbl_total_collect_budgets->text() + "</p><br>");

        // Add the net money
        cursor.insertHtml("<p><strong>Net Money:</strong></p><p>" + ui->lbl_net->text() + "</p><br>");

        // Print the document
        printer.setPageMargins(20, 20, 20, 20, QPrinter::Millimeter);
        document.print(&printer);
    }

    delete printDialog;
}




void donationswindow::on_stats_clicked()
{
   Dialog *dialog = new Dialog(this);
   ThemeWidget1 *themeWidget1 = new ThemeWidget1(dialog);
   dialog->setWindowTitle("Statistics");
   QVBoxLayout *layout = new QVBoxLayout(dialog);
   layout->addWidget(themeWidget1);
   dialog->setLayout(layout);
   dialog->setModal(true);

   // Set the dialog size to 500 x 300 pixels
   dialog->setFixedSize(1000, 500);

   dialog->exec();
}




/*
void donationswindow::on_pb_catalogue_clicked()
{
    // Create a new window for the donation catalog
        QDialog *donationCatalog = new QDialog(this);
        donationCatalog->setWindowTitle("Donation Catalog");

        // Set the default size of the dialog to be bigger
            donationCatalog->resize(QSize(800, 600));

        // Create a stacked widget to hold the pages of donations
        QStackedWidget *stackedWidget = new QStackedWidget(donationCatalog);

        // Query the donations from the database
        QSqlQuery query;
        query.prepare("SELECT * FROM donations");
        query.exec();

        // Create a page for each set of donations
        const int pageSize = 1; // Change this to control the number of donations per page
        int currentPage = 0;
        while (query.next()) {
            // Create a new widget to hold the donations on this page
            QWidget *pageWidget = new QWidget(stackedWidget);

            // Create labels to display the donation information
            QLabel *IDLabel = new QLabel(pageWidget);
            IDLabel->setText("Category: " + query.value("DONATION_ID").toString());
            QLabel *categoryLabel = new QLabel(pageWidget);
            categoryLabel->setText("Category: " + query.value("CATEGORY_NAME").toString());
            QLabel *nameLabel = new QLabel(pageWidget);
            nameLabel->setText("Name: " + query.value("NAME").toString());
            QLabel *descriptionLabel = new QLabel(pageWidget);
            descriptionLabel->setText("Description: " + query.value("DESCRIPTION").toString());
            QLabel *amountLabel = new QLabel(pageWidget);
            amountLabel->setText("Amount: $" + QString::number(query.value("AMOUNT").toDouble()));
            QLabel *quantityLabel = new QLabel(pageWidget);
            quantityLabel->setText("Quantity: " + QString::number(query.value("QUANTITY").toInt()));
            QLabel *phoneNumberLabel = new QLabel(pageWidget);
            phoneNumberLabel->setText("Phone Number: " + query.value("PHONE_NUMBER").toString());

            // Lay out the labels
            QVBoxLayout *layout = new QVBoxLayout(pageWidget);
            layout->addWidget(IDLabel);
            layout->addWidget(categoryLabel);
            layout->addWidget(nameLabel);
            layout->addWidget(descriptionLabel);
            layout->addWidget(amountLabel);
            layout->addWidget(quantityLabel);
            layout->addWidget(phoneNumberLabel);

            // Add the page to the stacked widget
            stackedWidget->addWidget(pageWidget);

            // Check if we have reached the end of a page
            if ((currentPage + 1) * pageSize == stackedWidget->count()) {
                currentPage++;
            }
        }

        // Create buttons to navigate between pages
        QPushButton *previousButton = new QPushButton("Previous", donationCatalog);
        QPushButton *nextButton = new QPushButton("Next", donationCatalog);

        // Lay out the stacked widget and navigation buttons
        QVBoxLayout *layout = new QVBoxLayout(donationCatalog);
        layout->addWidget(stackedWidget);
        QHBoxLayout *buttonLayout = new QHBoxLayout();
        buttonLayout->addWidget(previousButton);
        buttonLayout->addStretch();
        buttonLayout->addWidget(nextButton);
        layout->addLayout(buttonLayout);

        // Connect the navigation buttons to slots that change the page
        connect(previousButton, &QPushButton::clicked, [=]() {
            int newIndex = stackedWidget->currentIndex() - 1;
            if (newIndex >= 0) {
                stackedWidget->setCurrentIndex(newIndex);
            }
        });
        connect(nextButton, &QPushButton::clicked, [=]() {
            int newIndex = stackedWidget->currentIndex() + 1;
            if (newIndex < stackedWidget->count()) {
                stackedWidget->setCurrentIndex(newIndex);
            }
        });

        // Show the donation catalog window
        stackedWidget->setCurrentIndex(0);
        donationCatalog->show();
}*/

void donationswindow::on_pb_catalogue_clicked()
{
    // Create a new window for the donation catalog
    QDialog *donationCatalog = new QDialog(this);
    donationCatalog->setWindowTitle("Donation Catalog");

    // Set the default size of the dialog to be bigger
        donationCatalog->resize(QSize(800, 600));

    // Create a stacked widget to hold the pages of donations
    QStackedWidget *stackedWidget = new QStackedWidget(donationCatalog);


    // Query the donations from the database
    QSqlQuery query;
    query.prepare("SELECT * FROM donations ORDER BY CATEGORY_NAME");
    query.exec();

    QPropertyAnimation *animation = new QPropertyAnimation(stackedWidget, "currentIndex");
    animation->setDuration(100); // set the duration of the animation to 500 ms

    // Create a page for each set of donations
    const int pageSize = 1; // Change this to control the number of donations per page
    int currentPage = 0;
    while (query.next()) {
        // Create a new widget to hold the donations on this page
        QWidget *pageWidget = new QWidget(stackedWidget);
     //yellow
       pageWidget->setStyleSheet("background-color: #FDE3A7;");
        //navy blue
//        pageWidget->setStyleSheet("background-color: navy;");
        //pink
     //   pageWidget->setStyleSheet("background-color: #ffd1dc;");



  // Create labels to display the donation information
        QLabel *IDLabel = new QLabel(pageWidget);
        IDLabel->setText("<html><b><font color='red' size='+2'>Donation ID:</font></b> <font size='+2'>" + query.value("DONATION_ID").toString() + "</font></html>");
        QLabel *categoryLabel = new QLabel(pageWidget);
        categoryLabel->setText("<html><b><font color='red' size='+2'>Category:</font></b> <font size='+2'>" + query.value("CATEGORY_NAME").toString() + "</font></html>");
        QLabel *nameLabel = new QLabel(pageWidget);
        nameLabel->setText("<html><b><font color='red' size='+2'>Name:</font></b> <font size='+2'>" + query.value("NAME").toString() + "</font></html>");
        QLabel *descriptionLabel = new QLabel(pageWidget);
        descriptionLabel->setText("<html><b><font color='red' size='+2'>Description:</font></b> <font size='+2'>" + query.value("DESCRIPTION").toString() + "</font></html>");
        QLabel *amountLabel = new QLabel(pageWidget);
        amountLabel->setText("<html><b><font color='red' size='+2'>Amount:</font></b> <font size='+2'>$" + QString::number(query.value("AMOUNT").toDouble()) + "</font></html>");
        QLabel *quantityLabel = new QLabel(pageWidget);
        quantityLabel->setText("<html><b><font color='red' size='+2'>Quantity:</font></b> <font size='+2'>" + QString::number(query.value("QUANTITY").toInt()) + "</font></html>");
        QLabel *phoneNumberLabel = new QLabel(pageWidget);
        phoneNumberLabel->setText("<html><b><font color='red' size='+2'>Phone Number:</font></b> <font size='+2'>" + query.value("PHONE_NUMBER").toString() + "</font></html>");


        // Add an image to the top right corner according to the ID
        QString ID = query.value("DONATION_ID").toString();
        QLabel *imageLabel = new QLabel(pageWidget);

        // Query the image path based on the donation_id
        QSqlQuery imageQuery;
        imageQuery.prepare("SELECT image FROM donations WHERE donation_id = :donation_id");
        imageQuery.bindValue(":donation_id", ID);
        imageQuery.exec();

        if (imageQuery.next()) {
            QString imagePath = imageQuery.value("image").toString();
            QPixmap donationImage(imagePath);
            if (!donationImage.isNull()) {
                QPixmap scaledImage = donationImage.scaled(250, 250, Qt::KeepAspectRatio);
                imageLabel->setPixmap(scaledImage);
            }
        }
        imageLabel->setAlignment(Qt::AlignTop | Qt::AlignRight);
        // Lay out the labels
        QVBoxLayout *layout = new QVBoxLayout(pageWidget);
        layout->addWidget(IDLabel);
        layout->addWidget(categoryLabel);
        layout->addWidget(nameLabel);
        layout->addWidget(descriptionLabel);
        layout->addWidget(amountLabel);
        layout->addWidget(quantityLabel);
        layout->addWidget(phoneNumberLabel);
        layout->addWidget(imageLabel);

        // Add the page to the stacked widget
        stackedWidget->addWidget(pageWidget);

        // Check if we have reached the end of a page
        if ((currentPage + 1) * pageSize == stackedWidget->count()) {
            currentPage++;
        }
    }
    // Create buttons to navigate between pages
    QPushButton *previousButton = new QPushButton("Previous", donationCatalog);
    QPushButton *nextButton = new QPushButton("Next", donationCatalog);

    // Lay out the stacked widget and navigation buttons
    QVBoxLayout *layout = new QVBoxLayout(donationCatalog);
    layout->addWidget(stackedWidget);
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(previousButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(nextButton);
    layout->addLayout(buttonLayout);



    // Connect the navigation buttons to slots that change the page
    connect(previousButton, &QPushButton::clicked, [=]() {
        int newIndex = stackedWidget->currentIndex() - 1;
        if (newIndex >= 0) {
            // stackedWidget->setCurrentIndex(newIndex);

            animation->setStartValue(stackedWidget->currentIndex());
            animation->setEndValue(newIndex);
            animation->start();
        }

    });
    connect(nextButton, &QPushButton::clicked, [=]() {
        int newIndex = stackedWidget->currentIndex() + 1;
        if (newIndex < stackedWidget->count()) {
          //  stackedWidget->setCurrentIndex(newIndex);
            animation->setStartValue(stackedWidget->currentIndex());
            animation->setEndValue(newIndex);
            animation->start();
        }
    });

    // Show the donation catalog window
    stackedWidget->setCurrentIndex(0);
    donationCatalog->show();
}



void donationswindow::on_actionemployee_triggered()
{  if (USER==1){
        empwindow *p=new empwindow();
    p->showMaximized();
    this->hide();
    }else{
        QMessageBox::critical(nullptr, QObject::tr("Access denied :/"),
                    QObject::tr("You are not allowed to this section you need to login as an Admin to access it! :/\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void donationswindow::on_actiondestitutes_triggered()
{
    if (USER==1){
             destituteWindow  *p=new destituteWindow();
       p->showMaximized();
        this->hide();
          }else{
          QMessageBox::critical(nullptr, QObject::tr("Access denied :/"),
                      QObject::tr("You are not allowed to this section you need to login as a Destitute Manager to access it! :/\n"
                                  "Click Cancel to exit."), QMessageBox::Cancel);
      }
}

void donationswindow::on_actiondonations_triggered()
{
    if (USER==1){
               donationswindow  *p=new donationswindow();
         p->showMaximized();
          this->hide();
            }else{
            QMessageBox::critical(nullptr, QObject::tr("Access denied :/"),
                        QObject::tr("You are not allowed to this section you need to login as a Donations Manager to access it! :/\n"
                                    "Click Cancel to exit."), QMessageBox::Cancel);
        }
}

void donationswindow::on_actionservices_triggered()
{
    if (USER==1){
               serMainWindow  *p=new serMainWindow();
        p->showMaximized();
         this->hide();
           }else{
           QMessageBox::critical(nullptr, QObject::tr("Access denied :/"),
                       QObject::tr("You are not allowed to this section you need to login as a Services Manager to access it! :/\n"
                                   "Click Cancel to exit."), QMessageBox::Cancel);
       }
}

void donationswindow::on_actionevents_triggered()
{
    if (USER==1){

           CollectsMainWindow  *p=new CollectsMainWindow();
    p->showMaximized();
     this->hide();
        }else{
        QMessageBox::critical(nullptr, QObject::tr("Access denied :/"),
                    QObject::tr("You are not allowed to this section you need to login as an Events Manager to access it! :/\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }
}

void donationswindow::on_actionabout_this_app_triggered()
{

    this->hide();
loginpage *l =new  loginpage();
l->show();
}


void donationswindow::on_pb_image_clicked()
{
    qDebug() << "Button clicked"; // Debug statement to check if the button is clicked

    QString imagePath = QFileDialog::getOpenFileName(this, tr("Select Image"), "", tr("Image Files (*.png *.jpg *.jpeg)"));

       if (!imagePath.isEmpty()) {
           ui->le_image->setText(imagePath);
       }
}

void donationswindow::on_pb_clear_clicked()
{
        ui->le_id->clear();
        ui->le_name->clear();
        ui->le_description->clear();
        ui->le_amount->clear();
        ui->le_quantity->clear();
        ui->le_phonenumber->clear();
        ui->le_image->clear();

}

