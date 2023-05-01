
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
    capteur.cpp \
    connection.cpp \
    destitute.cpp \
    destituteWindow.cpp \
    donation.cpp \
    employee.cpp \
    empwindow.cpp \
    loginpage.cpp \
    main.cpp \
    rfid.cpp \
    smtp.cpp \
    todolistwidget.cpp

HEADERS += \
    capteur.h \
    connection.h \
    destitute.h \
    destituteWindow.h \
    donation.h \
    employee.h \
    empwindow.h \
    loginpage.h \
    rfid.h \
    smtp.h \
    todolistwidget.h

FORMS += \
    destituteWindow.ui \
    empwindow.ui \
    loginpage.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    qml.qrc \
    res.qrc \
    resources.qrc
