#ifndef CHECKSTARTEXAM_H
#define CHECKSTARTEXAM_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QThread>
#include "parserconfig.h"
#include <QEventLoop>
#include <QByteArray>

class CheckStartExam : public QObject
{
    Q_OBJECT

public:
    CheckStartExam();

public slots:
    void check();
    void sendingFinished();
    void setData(QString, int, QString, QString);
signals:
    void send(bool, double, int);
    void finished();
private:
    QNetworkReply *reply;
    QNetworkAccessManager *manager;
    QString pathRequestInterval;
    int requestInterval;
    ParserConfig *parser;
    QString UID;
    QString serverIP;
};

#endif // CHECKSTARTEXAM_H
