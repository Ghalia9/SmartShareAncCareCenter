#include "donation.h"
#include <QPrinter>
#include <QTextDocument>
#include <QSqlRecord>
#include <QTextCursor>
#include <QDebug>
#include <QPainter>
#include <QMessageBox>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QToolButton>








donation::donation(QString donation_id,QString category_name,QString name,QString description,int quantity,double amount,QString phone_number)
{
    this->donation_id=donation_id;
    this->category_name=category_name;
    this->name=name;
    this->description=description;
    this->quantity=quantity;
    this->amount=amount;
    this->phone_number=phone_number;


}
bool donation::ajouter()
{
    QSqlQuery query;
    QString res = QString::number(quantity);
    QString res1 = QString::number(amount);

    //prepare() prend la requete en parametre pour la preparer à léxecution

    query.prepare("insert into donations (quantity,amount,donation_id,category_name,name,description,phone_number)" "values (:quantity,:amount,:donation_id,:category_name,:name,:description,:phone_number)");
    //creation des variables liees

    query.bindValue(":quantity",res);
    query.bindValue(":amount",res1);
    query.bindValue(":donation_id",donation_id);
    query.bindValue(":category_name",category_name);
    query.bindValue(":name",name);
    query.bindValue(":description",description);
    query.bindValue(":phone_number",phone_number);


    return query.exec(); //exec() envoie la requete pour l'execution
}


QSqlQueryModel * donation::afficher()
{
    QSqlQueryModel * model=new QSqlQueryModel();
    model->setQuery("select * from donations ORDER BY CATEGORY_NAME");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("DONATION_ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("CATEGORY_NAME"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("NAME"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("DESCRIPTION"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("QUANTITY"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("AMOUNT"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("PHONE NUMBER"));

    return model;
}


bool donation::supprimer(QString donation_id)
{
QSqlQuery query;
query.prepare("Delete from donations where donation_id= :donation_id");
query.bindValue(":donation_id",donation_id);
query.exec();
return query.exec();
}


bool donation :: modifier()
{
    QSqlQuery query;
    query.prepare("UPDATE DONATIONS SET DONATION_ID = :donation_id, CATEGORY_NAME = :category_name, NAME = :name, DESCRIPTION = :description,  QUANTITY = :quantity, AMOUNT = :amount,PHONE_NUMBER = :phone_number WHERE DONATION_ID LIKE '"+donation_id+"%'");

        query.bindValue(":donation_id", donation_id);
        query.bindValue(":category_name", category_name);
        query.bindValue(":name",name );
        query.bindValue(":description", description);
        query.bindValue(":quantity", quantity);
        query.bindValue(":amount", amount);
        query.bindValue(":phone_number", phone_number);
      query.exec();
       return  query.exec();
}
QSqlQueryModel* donation ::rechercherID(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM donations" );
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("donation_id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("category_name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("description"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("quantity"));

    model->setHeaderData(5, Qt::Horizontal, QObject::tr("amount"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("phone_number"));

    return model;
}


QSqlQueryModel * donation::sortID()
{
  QSqlQueryModel* model=new QSqlQueryModel();
  model->setQuery("SELECT * FROM donations order by DONATION_ID ASC");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("donation_id"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("category_name"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("name"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("description"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("quantity"));

  model->setHeaderData(5, Qt::Horizontal, QObject::tr("amount"));
  model->setHeaderData(6, Qt::Horizontal, QObject::tr("phone_number"));
  return model;

}
QSqlQueryModel * donation::sortCategoryName()
{
  QSqlQueryModel* model=new QSqlQueryModel();
  model->setQuery("SELECT * FROM donations order by CATEGORY_NAME ASC");
  model->setHeaderData(0, Qt::Horizontal, QObject::tr("donation_id"));
  model->setHeaderData(1, Qt::Horizontal, QObject::tr("category_name"));
  model->setHeaderData(2, Qt::Horizontal, QObject::tr("name"));
  model->setHeaderData(3, Qt::Horizontal, QObject::tr("description"));
  model->setHeaderData(4, Qt::Horizontal, QObject::tr("quantity"));

  model->setHeaderData(5, Qt::Horizontal, QObject::tr("amount"));
  model->setHeaderData(6, Qt::Horizontal, QObject::tr("phone_number"));
  return model;


}

QSqlQueryModel* donation::rechercherCategoryName(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM donations where CATEGORY_NAME LIKE '"+recherche+"%' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("donation_id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("category_name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("description"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("quantity"));

    model->setHeaderData(5, Qt::Horizontal, QObject::tr("amount"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("phone_number"));
    return model;
}
QSqlQueryModel* donation::recherchernom(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM DONATIONS where NAME LIKE '"+recherche+"%' ");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("donation_id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("category_name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("description"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("quantity"));

    model->setHeaderData(5, Qt::Horizontal, QObject::tr("amount"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("phone_number"));
    return model;
}

QSqlQueryModel* donation ::rechercherID2(QString recherche)
{
    QSqlQueryModel* model=new QSqlQueryModel();


    model->setQuery("SELECT * FROM donations where DONATION_ID LIKE '"+recherche+"%'" );

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("donation_id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("category_name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("name"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("description"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("quantity"));

    model->setHeaderData(5, Qt::Horizontal, QObject::tr("amount"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("phone_number"));
    return model;
}
/*
void donation::generateCatalog()
{
    // Create a printer object and set its properties
    QPrinter printer;
    printer.setPageSize(QPrinter::A4);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("donation_catalog.pdf");

    // Create a QTextDocument object to hold the catalog
    QTextDocument doc;

    // Set the document properties
    doc.setPageSize(printer.pageRect().size());

    // Create a QSqlQueryModel object and populate it with the donations
    QSqlQueryModel *model = afficher();

    // Loop through each donation in the model
    for (int i = 0; i < model->rowCount(); i++) {
        // Get the donation details
        QString category = model->record(i).value("CATEGORY_NAME").toString();
        QString name = model->record(i).value("NAME").toString();
        QString description = model->record(i).value("DESCRIPTION").toString();
        QString amount = model->record(i).value("AMOUNT").toString();
        QString quantity = model->record(i).value("QUANTITY").toString();
        QString phone = model->record(i).value("PHONE NUMBER").toString();

        // Create a QTextCursor object to add text to the document
        QTextCursor cursor(&doc);

        // Insert the donation details into the document
        cursor.insertText("Category: " + category + "\n");
        cursor.insertText("Name: " + name + "\n");
        cursor.insertText("Description: " + description + "\n");
        cursor.insertText("Amount: " + amount + "\n");
        cursor.insertText("Quantity: " + quantity + "\n");
        cursor.insertText("Phone number: " + phone + "\n");

        // Insert a page break
        if (i != model->rowCount() - 1) {
            cursor.insertPageBreak();
        }
    }

    // Print the document to the printer
    doc.print(&printer);
}*/
/*
void donation::generateCatalog()
{
    // Create a printer object
    QPrinter printer(QPrinter::PrinterResolution);

    // Set printer properties
    printer.setPaperSize(QPrinter::A4);
    printer.setOrientation(QPrinter::Portrait);
    printer.setFullPage(true);

    // Create a text document
    QTextDocument doc;

    // Set document properties
    doc.setPageSize(printer.pageRect().size());
    doc.setDocumentMargin(50);

    // Create a text cursor
    QTextCursor cursor(&doc);

    // Execute the SQL query
    QSqlQuery query("SELECT * FROM donations ORDER BY CATEGORY_NAME");

    // Iterate over the results and add to document
    while (query.next()) {
        // Add donation details to document
        QString category = query.value("CATEGORY_NAME").toString();
        QString name = query.value("NAME").toString();
        QString description = query.value("DESCRIPTION").toString();
        double amount = query.value("AMOUNT").toDouble();
        int quantity = query.value("QUANTITY").toInt();
        QString phoneNumber = query.value("PHONE_NUMBER").toString();

        QString html = QString("<h1>%1</h1><br><b>Name:</b> %2<br><b>Description:</b> %3<br><b>Amount:</b> %4<br><b>Quantity:</b> %5<br><b>Phone Number:</b> %6")
            .arg(category)
            .arg(name)
            .arg(description)
            .arg(amount)
            .arg(quantity)
            .arg(phoneNumber);

        cursor.insertHtml(html);

        // Insert a page break after each donation's details
        cursor.insertHtml("<br><br><hr>");
        cursor.insertHtml("<p style=\"page-break-after: always;\">&nbsp;</p>");
    }

    // Print the document
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("catalogue.pdf");
    doc.print(&printer);
}*/


/*
void donation::generateCatalog()
{
    // Retrieve the list of donations from the database
    QSqlQueryModel *model = afficher();
    int rowCount = model->rowCount();
    qDebug() << "Number of donations:" << rowCount;

    // Set up the printer
    QPrinter printer;
    printer.setOutputFileName("catalog.pdf");
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageMargins(QMarginsF(10, 10, 10, 10), QPageLayout::Millimeter);
    QPainter painter;

    // Set up the text document
    QTextDocument doc;
    QTextCursor cursor(&doc);
    QTextOption option;
    option.setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    doc.setDefaultTextOption(option);
    QFont font("Arial", 16, QFont::Bold);
    cursor.insertText("Donation Catalog", font);
    cursor.insertBlock();

    // Iterate over the list of donations and add them to the text document
    for (int i = 0; i < rowCount; i++) {
        QSqlRecord record = model->record(i);
        QString categoryName = record.value("CATEGORY_NAME").toString();
        QString name = record.value("NAME").toString();
        QString description = record.value("DESCRIPTION").toString();
        int amount = record.value("AMOUNT").toInt();
        int quantity = record.value("QUANTITY").toInt();
        QString phoneNumber = record.value("PHONE_NUMBER").toString();
        cursor.insertText(QString("Category: %1\nName: %2\nDescription: %3\nAmount: %4\nQuantity: %5\nPhone Number: %6\n\n")
                          .arg(categoryName).arg(name).arg(description).arg(amount).arg(quantity).arg(phoneNumber));
        cursor.insertPageBreak();
    }

    // Print the text document to the PDF file
    doc.print(&painter, &printer);
    qDebug() << "Catalog generated";
}*/

/*
void donation::generateCatalog()
{
    // Create a new QTextDocument
    QTextDocument doc;

    // Set up the QTextCursor
    QTextCursor cursor(&doc);

    // Set the font
    QFont font("Arial", 16);
    cursor.insertHtml(QString("<span style=\"font-family:'%1'; font-size:%2pt;\">")
                      .arg(font.family()).arg(font.pointSize()));

    // Set the title
    cursor.insertHtml("<h1>Donations Catalog</h1>");

    // Set the table style
    cursor.insertHtml("<style>table, th, td { border: 1px solid black; border-collapse: collapse; }</style>");

    // Set the table header
    cursor.insertHtml("<table><thead><tr><th>Donation ID</th><th>Category</th><th>Name</th><th>Description</th><th>Amount</th><th>Quantity</th><th>Phone Number</th></tr></thead>");

    // Get the data from the database
    QSqlQuery query;
    query.prepare("SELECT * FROM donations ORDER BY CATEGORY_NAME");
    query.exec();

    // Set the table data
    cursor.insertHtml("<tbody>");
    while (query.next()) {
        QString donationID = query.value(0).toString();
        QString category = query.value(1).toString();
        QString name = query.value(2).toString();
        QString description = query.value(3).toString();
        QString amount = query.value(4).toString();
        QString quantity = query.value(5).toString();
        QString phone = query.value(6).toString();

        QString row = QString("<tr><td>%1</td><td>%2</td><td>%3</td><td>%4</td><td>%5</td><td>%6</td><td>%7</td></tr>")
                      .arg(donationID).arg(category).arg(name).arg(description).arg(amount).arg(quantity).arg(phone);
        cursor.insertHtml(row);

        // Insert a page break after each row
        cursor.insertHtml("<p style=\"page-break-after:always;\">&nbsp;</p>");
    }
    cursor.insertHtml("</tbody></table>");

    // Print the document
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("catalog.pdf");
    doc.print(&printer);

    // Display a message box
    QMessageBox::information(0, "Catalog Generated", "The catalog has been generated and saved as 'catalog.pdf'.");
}
*/

/*
void donation::generateCatalog()
{
    // Retrieve the donations from the database
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM donations ORDER BY CATEGORY_NAME");

    // Create a stacked widget to hold the pages
    QStackedWidget *pages = new QStackedWidget();

    // Create a widget for each donation and add it to the stacked widget
    for (int i = 0; i < model->rowCount(); i++) {
        QWidget *page = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout(page);

        // Retrieve the donation data
        int donationId = model->record(i).value("DONATION_ID").toInt();
        QString categoryName = model->record(i).value("CATEGORY_NAME").toString();
        QString name = model->record(i).value("NAME").toString();
        QString description = model->record(i).value("DESCRIPTION").toString();
        int amount = model->record(i).value("AMOUNT").toInt();
        int quantity = model->record(i).value("QUANTITY").toInt();
        QString phoneNumber = model->record(i).value("PHONE NUMBER").toString();

        // Create a QLabel for each piece of data and add it to the layout
        QLabel *donationIdLabel = new QLabel(QString("Donation ID: %1").arg(donationId));
        layout->addWidget(donationIdLabel);

        QLabel *categoryNameLabel = new QLabel(QString("Category Name: %1").arg(categoryName));
        layout->addWidget(categoryNameLabel);

        QLabel *nameLabel = new QLabel(QString("Name: %1").arg(name));
        layout->addWidget(nameLabel);

        QLabel *descriptionLabel = new QLabel(QString("Description: %1").arg(description));
        layout->addWidget(descriptionLabel);

        QLabel *amountLabel = new QLabel(QString("Amount: %1").arg(amount));
        layout->addWidget(amountLabel);

        QLabel *quantityLabel = new QLabel(QString("Quantity: %1").arg(quantity));
        layout->addWidget(quantityLabel);

        QLabel *phoneNumberLabel = new QLabel(QString("Phone Number: %1").arg(phoneNumber));
        layout->addWidget(phoneNumberLabel);

        // Add the page to the stacked widget
        pages->addWidget(page);
    }

    // Create the previous and next buttons and add them to a horizontal layout
    QToolButton *previousButton = new QToolButton();
    previousButton->setText("Previous");
    QToolButton *nextButton = new QToolButton();
    nextButton->setText("Next");
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(previousButton);
    buttonLayout->addStretch();
    buttonLayout->addWidget(nextButton);

    // Create a main layout for the dialog and add the stacked widget and button layout to it
    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(pages);
    mainLayout->addLayout(buttonLayout);

    // Create a dialog to display the catalog
    QDialog *catalogDialog = new QDialog();
    catalogDialog->setLayout(mainLayout);

    // Connect the previous and next buttons to the stacked widget's previous and next functions
    stackedWidget->setCurrentIndex(stackedWidget->currentIndex() - 1);
    stackedWidget->setCurrentIndex(stackedWidget->currentIndex() + 1);

    // Show the dialog
    catalogDialog->exec();
}
*/






