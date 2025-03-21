#ifndef ACTION_H
#define ACTION_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QCoreApplication>
#include <filesystem>

class Action:public QObject{

    Q_OBJECT

public:
    Action();

public slots:
    void close();
    void clean();

signals:
    void webServerStopped();

private:
    void stopWebServer();
};
#endif // ACTION_H

