
QT += location
QT += positioning
QT += quick
QT += widgets
QT += quickwidgets

QT += serialport

QT       += core gui printsupport charts

include(QZXing/QZXing.pri)  #sets up the library for your project.
#LIBS += -L$$PWD/QZXing/ -lqzxing   #adds the library files to the project's library path and links against the "qzxing" library.

#include(qzxing-master/qzxing-master/QZXing.pri)  #sets up the library for your project.
#LIBS += -L$$PWD/qzxing-master/qzxing-master/ -lqzxing   #adds the library files to the project's library path and links against the "qzxing" library.

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets quickwidgets
QT += sql network serialport

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    CollectsMainWindow.cpp \
    arduino.cpp \
    capteur.cpp \
    collects.cpp \
    connection.cpp \
    destitute.cpp \
    destituteWindow.cpp \
    dialog.cpp \
    donation.cpp \
    donationswindow.cpp \
    employee.cpp \
    empwindow.cpp \
    loginpage.cpp \
    main.cpp \
    rfid.cpp \
    smtp.cpp \
    smtpk.cpp \
    themewidget.cpp \
    todolistwidget.cpp

HEADERS += \
    CollectsMainWindow.h \
    RFID_LCD_module.ino \
    arduino.h \
    capteur.h \
    collects.h \
    connection.h \
    destitute.h \
    destituteWindow.h \
    dialog.h \
    donation.h \
    donationswindow.h \
    employee.h \
    empwindow.h \
    loginpage.h \
    rfid.h \
    smtp.h \
    smtpk.h \
    themewidget.h \
    todolistwidget.h

FORMS += \
    CollectsMainWindow.ui \
    destitute.ui \
    destituteWindow.ui \
    dialog.ui \
    donationsmainwindow.ui.autosave \
    donationswindow.ui \
    empwindow.ui \
    loginpage.ui \
    todolistwidget.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qml.qrc \
    qml.qrc \
    qml.qrc \
    res.qrc \
    res.qrc \
    res.qrc \
    resources.qrc \
    resources.qrc \
    resources.qrc

DISTFILES += \
    Destitute.png \
    Donations.png \
    Employees.png \
    Events.png \
    Food-PNG-Image.png \
    Services.png \
    Untitled-1-01.png \
    add.png \
    burger-savoureux-isole-fond-blanc-restauration-rapide-hamburger-frais-du-boeuf-du-fromage.jpg \
    calendar.qml \
    clothes.png \
    employeeprofile.png \
    food.png \
    logo application.png \
    logo application.png \
    main.qml \
    partieismail.pro.user \
    partieismail.pro.user.b8621b6 \
    partieismail.pro.user.f30694c \
    partieismail.pro.user.f76aa42 \
    pates-tagliatelles-aux-tomates-au-poulet.jpg \
    pin.png \
    qsdfg-01.png \
    remove.png \
    sdf1-01.png \
    xxxxxxccccccccccccc-01.png \
    xxxxxxxxx-01.png \
    —Pngtree—hand painted cartoon clothing display_3476811.png
