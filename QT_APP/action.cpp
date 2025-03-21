#include "action.h"

Action::Action() {}


void Action::close(){
    this->stopWebServer();

    // Wait until the POST request is complete
    QEventLoop loop;
    connect(this, &Action::webServerStopped, &loop, &QEventLoop::quit); // Looping until the signal emit
    loop.exec();

    QCoreApplication::exit();
    
}

void Action::clean(){

    this->close();

    // Dangerous code that removes the git cloned project
    //std::filesystem::remove_all("../../../../QT"); // Works only from build dir
    std::filesystem::remove_all("../QT"); // Works from the project root dir
}

void Action::stopWebServer(){

    // close the web server by sending a POST request

    // Copy paste from main
    // Init manager and request
    QNetworkAccessManager* manager = new QNetworkAccessManager();
    QNetworkRequest request;

    // Configuring the request

    request.setUrl(QUrl("http://127.0.0.1:10000/api/v1/getQML")); // Set url to web server API
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json"); // We want to send json

    // Configure post data request
    QJsonObject json;
    json.insert("action","close");

    QJsonDocument doc(json);
    QByteArray postData = doc.toJson();

    qDebug() << "Sending POST data:" << QString(postData);

    QNetworkReply* reply = manager->post(request, postData); // Sending POST request

    // Emitting webServerStopped when the reply was complete

    QObject::connect(reply, &QNetworkReply::finished, [reply, this]() {
    if (reply->error() == QNetworkReply::NoError) {
        emit webServerStopped();
    }
    });

}
