#include "GetConfig.h"

GetConfigClass::GetConfigClass(QObject *parent) : QObject(parent)
{    
}
void GetConfigClass::GetConfig() {
    QNetworkRequest request(QUrl(serverIP + "/config"));
    mngr = new QNetworkAccessManager(this);
    reply = mngr->get(request);
    connect(reply, SIGNAL(finished()), SLOT(sendingFinished()));
}

void GetConfigClass::sendingFinished()
{
    emit send(reply->readAll());
    reply->deleteLater();
    mngr->deleteLater();
    emit finished();
}

void GetConfigClass::setData(QString serverIP)
{
    this->serverIP = serverIP;
}
