#include "checkstartexam.h"

CheckStartExam::CheckStartExam()
{

}

void CheckStartExam::check()
{
    qDebug() << serverIP + pathRequestInterval;
    QNetworkRequest request(QUrl(serverIP + pathRequestInterval));
    manager = new QNetworkAccessManager(this);
    QByteArray uid = UID.toUtf8();
    request.setRawHeader("Authorization", uid);
    reply = manager->get(request);
    connect(reply, SIGNAL(finished()), SLOT(sendingFinished()));
}

void CheckStartExam::sendingFinished()
{
    QByteArray JSON = reply->readAll();
    bool record = parser->GetParamStandby(JSON, "record").toBool();
    if (record) emit send(record, parser->GetParamStandby(JSON, "snapshotInterval").toDouble(), parser->GetParamStandby(JSON, "screenshotW").toInt());
    else emit send(record, 0.0, 0);
    reply->deleteLater();
    manager->deleteLater();
    emit finished();
}

void CheckStartExam::setData(QString intervalPath, int ms, QString uid, QString serverIP)
{
    this->serverIP = serverIP;
    parser = new ParserConfig();
    pathRequestInterval = intervalPath;
    requestInterval = ms;
    UID = uid;
}

