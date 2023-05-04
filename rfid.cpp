#include "rfid.h"
#include <QDebug>
RFID::RFID()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
SerialBuffer="";
}

QString RFID::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort* RFID::getserial()
{
    qDebug()<<"getting serial now";
    return serial;
}
int RFID::connect_arduino()
{
    // recherche du port sur lequel la carte arduino identifée par arduino uno_vendor_id

    // est connectée

    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){

    if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
        if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier()== arduino_uno_producy_id) {

    arduino_is_available = true;

    arduino_port_name=serial_port_info.portName();
        }}}

    qDebug() << "arduino port_name is :"<< arduino_port_name;

    if(arduino_is_available) { // configuration de la communication (debit...)
   // QSerialPort serial;
       // serial.setPortName(arduino_port_name);
        serial->setPortName("COM5");

    if(serial->open (QSerialPort::ReadWrite)){


        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
    return 0;
}
    return 1;
    }
    return -1;
}

int RFID::close_arduino()
{
    if(serial->isOpen()){
        serial->close();
        return 0;
    }
    return 1;
}




QString RFID::read_from_arduino()
{
    SerialData = serial->readAll();
    SerialBuffer += QString(SerialData).trimmed();
    if (SerialBuffer.length() >= 8) {
        QString completeCardID = SerialBuffer.left(8);
        qDebug() << "Received data: " << completeCardID;
        SerialBuffer.remove(0, 20);
        return completeCardID;
    }
    return "";
}

int RFID::write_to_arduino(QString d)
{
    if(serial->isWritable()){
        QByteArray dataBytes = d.toUtf8();
       serial->write(dataBytes);
    }else{
        qDebug()<<"Couldn't write to serial!";
    }
return 1;
}


