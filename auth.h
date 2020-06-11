#ifndef AUTH_H
#define AUTH_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>

class Auth : public QObject
{
    Q_OBJECT
public:
    explicit Auth();

public slots:
    void auth();
    void sendingFinished();
    void setData(QString, QString, QString, QString);
signals:
    void send(QString);
    void finished();
private:
    QString name;
    QString serverIP;
    QNetworkReply *reply;
    QNetworkAccessManager *manager;
    QByteArray reqdata;
    QNetworkRequest request;
    QString Phone;
    QString UID;
    QString AuthPath;
};

#endif // AUTH_H
