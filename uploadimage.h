#ifndef UPLOADIMAGE_H
#define UPLOADIMAGE_H

#include <QObject>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QUrlQuery>
#include <QBuffer>
#include <QHttpMultiPart>
#include <QFile>
#include <QEventLoop>
#include <QJsonObject>
#include <QJsonDocument>
#include "parserconfig.h"
#include "screenshot.h"

class UploadImage: public QObject
{
    Q_OBJECT
public:
    UploadImage();

public slots:
    void upload();    
    void restartServer();
    void setData(bool, QString, QString, QString, QString, QString);
signals:
    void restart(bool, double, double);
    void finished();
private:
    QNetworkReply *reply;
    QNetworkRequest request;
    QNetworkAccessManager *manager;
    bool multi;
    QString path;
    QString fileName;
    QString time;
    QString UID;
    QString serverIP;
    QEventLoop loop;
};

#endif // UPLOADIMAGE_H
