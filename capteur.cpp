#include "capteur.h"
#include <QDebug>
Capteur::Capteur()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
}

QString Capteur::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort* Capteur::getserial()
{
    return serial;
}
int Capteur::connect_arduino()
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
        serial->setPortName(arduino_port_name);

    if(serial->open (QSerialPort::ReadWrite)){

    /*serial.setBaudRate (QSerialPort::Baud9600); // débit: 9680 bits/s

    serial.setDataBits (QSerialPort::Data8); //Longueur des données : 8 bits, serial->setParity (QSerialPort::NoParity); //1 bit de parité optionnel serial->setStopBits (QSerialPort::OneStop); //Nombre de bits de stop: 1 serial->setFlowControl (QSerialPort::NoFlowControl);

    serial.setParity(QSerialPort::NoParity);

    serial.setStopBits(QSerialPort::OneStop);

    serial.setFlowControl(QSerialPort::NoFlowControl);
*/
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

int Capteur::close_arduino()
{
    if(serial->isOpen()){
        serial->close();
        return 0;
    }
    return 1;
}

QByteArray Capteur::read_from_arduino()
{/*
    QSerialPort *serial =getserial();
    qDebug()<<"serial:"<<serial;
    qDebug()<<"haaaaaaaaaaaaaaaaaaa";
    */
    if(serial->isReadable()){
        qDebug()<<"haaaaaaaaaaaaaaaaaaa2";
        data=serial->readAll();
        //data = serial->readLine();
        qDebug()<<"received:"<<data;

        return data;
    }
}

int Capteur::write_to_arduino(QByteArray d)
{
    if(serial->isWritable()){
        serial->write(d);
    }else{
        qDebug()<<"Couldn't write to serial!";
    }

}



