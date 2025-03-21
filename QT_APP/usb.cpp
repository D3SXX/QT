#include "usb.h"

Usb::Usb() {

    // Trying to init libusb
    if (libusb_init(nullptr) < 0){
        qDebug() << "Error on initializing libusb";
    }
}

void Usb::listDevices(){
    m_deviceList.clear();
    libusb_device **devices;
    ssize_t count = libusb_get_device_list(nullptr, &devices);

    // Checking either we have any devices connected
    if (count < 0){
        qDebug() << "Error on getting device list";
    }
    for (ssize_t i = 0; i < count; i++) {
        struct libusb_device_descriptor description;
        int result = libusb_get_device_descriptor(devices[i], &description);
        
        if (result < 0) {
            qDebug() << "Failed to get device descriptor";
            continue;
        }
        // Storing all data in QMap
        QVariantMap deviceInfo;

        // https://libusb.sourceforge.io/api-1.0/structlibusb__device__descriptor.html
        // collect model (iManufacturer), vendor (iProduct), and location (bus, address and port)
        deviceInfo["Product"] = QString::number(description.iProduct, 8);
        deviceInfo["VID"] = QString::number(description.idVendor, 16);
        
        // Getting location
        deviceInfo["Location"] = QString("Bus: %1, Address: %2, Port: %3")
                                     .arg(libusb_get_bus_number(devices[i]))
                                     .arg(libusb_get_device_address(devices[i]))
                                     .arg(libusb_get_port_number(devices[i]));
        
        // Getting the rest

        libusb_device_handle *handle;
        result = libusb_open(devices[i], &handle); // Will only work if the root rights are present

        if (result >= 0){
            unsigned char string[256]; // needed for libusb_get_string_descriptor_ascii

            // Get manufacturer (vendor) name
            if (description.iManufacturer > 0) {
                result = libusb_get_string_descriptor_ascii(handle,
                                                            description.iManufacturer, string, sizeof(string));
                if (result > 0) {
                    deviceInfo["Vendor"] = QString::fromUtf8((char*)string);
                } else {
                    deviceInfo["Vendor"] = QString("Vendor %1").arg(QString::number(description.idVendor, 16));
                }
            } else {
                deviceInfo["Vendor"] = QString("Vendor %1").arg(QString::number(description.idVendor, 16));
            }

            // Get product (model) name
            if (description.iProduct > 0) {
                result = libusb_get_string_descriptor_ascii(handle,
                                                            description.iProduct, string, sizeof(string));
                if (result > 0) {
                    deviceInfo["Model"] =  QString::fromUtf8((char*)string);
                }
            }

            libusb_close(handle);
        }else { // In case we don't have root rights
            // use idVendor and idProduct as model and vendor
            deviceInfo["Vendor"] = QString::number(description.idVendor, 16);
            deviceInfo["Model"] = QString::number(description.idProduct, 16);
        }

        deviceInfo["VID"] = QString::number(description.idVendor, 16);
        deviceInfo["PID"] = QString::number(description.idProduct, 16);

        m_deviceList.append(QVariant::fromValue(deviceInfo));


    }
    // Cleaning up
    libusb_free_device_list(devices, 1);

    // Emit signal
    emit deviceListChanged();

}


QVariantList Usb::deviceList(){
    return m_deviceList;
}
