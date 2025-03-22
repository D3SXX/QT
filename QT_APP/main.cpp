#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickItem>
#include <QQmlContext>
#include <QAction>

// Needed for QQuickView
#include <QQuickView>

// Needed for fetch POST requests
#include <QtNetwork>

// Needed for timer
#include "timer.h"

// Needed for usb
#include "usb.h"

// Needed for close and cleanup
#include "action.h"

int main(int argc, char *argv[])
{

    // Init app
    QGuiApplication app(argc, argv);

    // Init manager and request
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest request;

    // Init timer

    Timer *timer = new Timer();

    // Init usb (libusb)

    Usb *usb = new Usb();

    // Init action (close and cleanup)

    Action *action = new Action();

    // Configuring the request

    request.setUrl(QUrl("http://127.0.0.1:10000/api/v1/getQML")); // Set url to web server API
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json"); // We want to send json

    // Init qQuickView
    QQuickView *view = new QQuickView;
    view->setResizeMode(QQuickView::SizeRootObjectToView);
    
    // Set the size of the view
    // To fix "QQuickView does not support using a window as a root item." when loading the QML file
    view->setWidth(800);  
    view->setHeight(600);

    // String with filename
    QString filename = "../QT_APP/Main.qml";

    // Configure post data request
    QJsonObject json;
    json.insert("filename",filename);

    QJsonDocument doc(json);
    QByteArray postData = doc.toJson();

    qDebug() << "Sending POST data:" << QString(postData);

    QNetworkReply* reply = manager->post(request, postData); // Sending POST request

    // Connect "finished" signal to a lambda that handles the response
    QObject::connect(reply, &QNetworkReply::finished, [reply, view, timer, usb, action]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray responseData = reply->readAll();
            
            // Create a temporary file to store the QML content
            QTemporaryFile tempFile;
            if (tempFile.open()) {
                tempFile.write(responseData);
                tempFile.close();
                
                view->rootContext()->setContextProperty("timer", timer);
                view->rootContext()->setContextProperty("usb",usb);

                // Load the QML from the tempFile
                view->setSource(QUrl::fromLocalFile(tempFile.fileName()));
                view->show();
                QQuickItem *item = view->rootObject();
                QQuickItem *timerButton = item->findChild<QQuickItem*>("timerButton");
                QQuickItem *exitButton = item->findChild<QQuickItem*>("exitButton");
                QQuickItem *cleanButton = item->findChild<QQuickItem*>("cleanupButton");

                QObject::connect(exitButton, SIGNAL(close()), action, SLOT(close()));
                QObject::connect(cleanButton, SIGNAL(clean()), action, SLOT(clean()));
                QObject::connect(timerButton, SIGNAL(toggleTimer()), timer, SLOT(toggleTimer()));

            }
        } else {
            qDebug() << "Error:" << reply->errorString();
            QCoreApplication::exit(); // exit QT APP
        }
        
        reply->deleteLater(); // delete the reply object
    });



    return app.exec();
}
