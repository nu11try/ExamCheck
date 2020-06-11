#ifndef SERVERCONNECTOR_H
#define SERVERCONNECTOR_H

#include <QObject>
#include <QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QEventLoop>
#include <QTextCodec>
#include <QUrlQuery>

class GetConfigClass : public QObject
{
    Q_OBJECT


public:
    GetConfigClass(QObject *parent = 0);

public slots:
    void GetConfig();
    void sendingFinished();
    void setData(QString);

signals:
    void send(QByteArray);
    void finished();

private:
    QNetworkAccessManager *mngr;
    QNetworkReply *reply;
    QList<QString> buf;
    QEventLoop loop;
    QString serverIP;
};

#endif // SERVERCONNECTOR_H
