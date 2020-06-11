#include "uploadimage.h"

UploadImage::UploadImage()
{
}

void UploadImage::upload()
{
    manager = new QNetworkAccessManager(this);
    QJsonObject data;
    //data.insert("authId",UID);
    data.insert("time",time);
    data.insert("multipleMonitors",multi);

    QJsonDocument doc(data);
    QString strJson(doc.toJson(QJsonDocument::Compact));

    QFile file(fileName);
    file.open(QIODevice::ReadOnly);

    request.setRawHeader("Host", "localhost");
    request.setUrl(QUrl("http://localhost/upload.php"));
    //request.setUrl(QUrl(serverIP + path));
    request.setRawHeader("Content-Type", "multipart/form-data; boundary=---------------------------200242615429510");
    QByteArray uid = UID.toUtf8();
    request.setRawHeader("Authorization", uid);

    QByteArray array;
    array.append("-----------------------------200242615429510\r\n");
    array.append("Content-disposition: ");
    array.append("form-data; name=\"method\"\r\n");
    array.append("\r\n");
    array.append("post");
    array.append("\r\n");
    array.append("-----------------------------200242615429510\r\n");
    array.append("Content-disposition: ");
    array.append("form-data; name=\"key\"\r\n");
    array.append("\r\n");
    array.append("a1683bc4jhkjhkhkgutiuftsdrsr62dkiu");
    array.append("\r\n");
    array.append("-----------------------------200242615429510\r\n");
    array.append("Content-disposition: ");
    array.append("form-data; name=\"data\"\r\n");
    array.append("\r\n");
    array.append(strJson);
    array.append("\r\n");
    array.append("-----------------------------200242615429510\r\n");
    array.append("Content-disposition: ");
    array.append("form-data; name=\"file\"; filename=\"fg.jpg\"\r\n");
    array.append("Content-Type: image/png");
    array.append("\r\n");
    array.append("\r\n");
    array.append(file.readAll());
    array.append("\r\n");
    array.append("-----------------------------200242615429510--");

    reply = manager->post(request, array);
    connect(reply, SIGNAL(finished()), this, SLOT(restartServer()));    
}

void UploadImage::restartServer()
{
    ParserConfig *parser = new ParserConfig();
    QByteArray JSONConfigString = reply->readAll();
    reply->deleteLater();    
    manager->deleteLater();
    QFile(fileName).remove();
    emit restart(parser->GetParamStandby(JSONConfigString, "record").toBool(), parser->GetParamStandby(JSONConfigString, "snapshotInterval").toDouble(), parser->GetParamStandby(JSONConfigString, "screenshotW").toDouble());
    emit finished();
}

void UploadImage::setData(bool mlS, QString server, QString uid, QString time, QString fileName, QString serverIP)
{
    this->serverIP = serverIP;
    multi = mlS;
    path = server;
    UID = uid;
    this->fileName = fileName;
    this->time = time;
}

