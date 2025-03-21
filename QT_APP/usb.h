#ifndef USB_H
#define USB_H

#include <QDebug>
#include <QObject>
#include <QMap>
#include <QVariant>
#include <QVariantList>

// The library that is used for getting usb data
#include <libusb-1.0/libusb.h>


class Usb : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList deviceList READ deviceList NOTIFY deviceListChanged) // Connect QML list to the deviceListChanged signal

public:
    Usb();


public slots:
    void listDevices();
    QVariantList deviceList();

signals:
    void deviceListChanged();

private:
    QVariantList m_deviceList;

};
#endif // USB_H
