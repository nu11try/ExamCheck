#include "auth.h"

Auth::Auth()
{

}

void Auth::auth()
{
    reqdata.clear();
    manager = new QNetworkAccessManager(this);
    reqdata.append("phone = " + Phone);
    reqdata.append("&uid = " + UID);
    QUrl url(serverIP + AuthPath);
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
    reply = manager->post(request,reqdata);
    connect(reply, SIGNAL(finished()), SLOT(sendingFinished()));
}

void Auth::sendingFinished()
{    
    emit send(reply->readAll());   
    reply->deleteLater();
    manager->deleteLater();
    emit finished();
}

void Auth::setData(QString phone, QString uid, QString auth_path, QString serverIP)
{
    this->serverIP = serverIP;
    Phone = phone;
    UID = uid;
    AuthPath = auth_path;
}
