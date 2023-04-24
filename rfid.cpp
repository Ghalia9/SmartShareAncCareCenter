#include "rfid.h"
#include <QDebug>
RFID::RFID()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
}

QString RFID::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort* RFID::getserial()
{
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

int RFID::close_arduino()
{
    if(serial->isOpen()){
        serial->close();
        return 0;
    }
    return 1;
}


/*
QByteArray Capteur::read_from_arduino()
{
    qDebug()<<"d5allllllll";
   // if(serial->isReadable()){
        qDebug()<<"1111111111111111111111";
        // Send request to Arduino to get variable value
                QByteArray request = "GET_dist"; // Replace with your custom request command
                serial->write(request);
                qDebug() << "Request sent:" << request;

                // Read response from Arduino
                while (serial->waitForReadyRead()) {
                    QByteArray responseData = serial->readAll();
                    qDebug() << "Received data:" << responseData;
                    return responseData;
                }
        data=serial->readAll();
        qDebug()<<"data="<<data;
        return data;
   // }
  //  }

}
*/
//chat
/*
QByteArray Capteur::read_from_arduino()
{
    QSerialPort serial;
    serial.setPortName("COM3"); // replace with the name of your serial port
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);

    if (!serial.open(QIODevice::ReadWrite)) {
        qWarning() << "Failed to open serial port";
        return QByteArray();
    }

    QByteArray data = serial.readAll();
    while (!data.isEmpty()) {
        // do something with the received data
        qDebug() << "Received data:" << data;
        data = serial.readAll();
    }

    serial.close();
    return data;
}
*/

QByteArray RFID::read_from_arduino()
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
int RFID::write_to_arduino(QByteArray d)
{
    if(serial->isWritable()){
        serial->write(d);
    }else{
        qDebug()<<"Couldn't write to serial!";
    }

}
/*
QString Capteur::getarduino_port_name()
{
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){

    if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
        if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier()== arduino_uno_producy_id) {

    arduino_is_available = true;

    arduino_port_name=serial_port_info.portName();
        }}}

    return arduino_port_name;
}
*/
/*
QSerialPort * Capteur::getserial()
{
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){

    if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
        if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier()== arduino_uno_producy_id) {

    arduino_is_available = true;

    arduino_port_name=serial_port_info.portName();
        }}}

    qDebug() << "arduino port_name is :"<< arduino_port_name;

    if(arduino_is_available) { // configuration de la communication (debit...)
    QSerialPort serial;
        serial.setPortName(arduino_port_name);
    if(serial.open (QSerialPort::ReadWrite)){

    serial.setBaudRate (QSerialPort::Baud9600); // débit: 9680 bits/s

    serial.setDataBits (QSerialPort::Data8); //Longueur des données : 8 bits, serial->setParity (QSerialPort::NoParity); //1 bit de parité optionnel serial->setStopBits (QSerialPort::OneStop); //Nombre de bits de stop: 1 serial->setFlowControl (QSerialPort::NoFlowControl);

    serial.setParity(QSerialPort::NoParity);

    serial.setStopBits(QSerialPort::OneStop);

    serial.setFlowControl(QSerialPort::NoFlowControl);

    return &serial;
}
    }}
*/
/*
QSerialPort* Capteur::getserial()
{
    QSerialPort *serial = new QSerialPort();

    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
        if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
            if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier()== arduino_uno_producy_id) {
                arduino_is_available = true;
                arduino_port_name = serial_port_info.portName();
                qDebug() << "Arduino port_name is: " << arduino_port_name;
            }
        }
    }

    if(arduino_is_available) {
        // Configuration de la communication (débit...)
        serial->setPortName(arduino_port_name);
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);
        return serial;

        if(serial->open(QSerialPort::ReadWrite)){
            return serial;
        }
        else {
            qDebug() << "Failed to open serial port.";
            delete serial;
            return nullptr;
        }
    }
    else {
        qDebug() << "Could not find Arduino port.";
        delete serial;
        return nullptr;
    }
}
*/
