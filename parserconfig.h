#ifndef PARSERCONFIG_H
#define PARSERCONFIG_H

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

class ParserConfig
{
public:
    ParserConfig();

public slots:
    QString GetParam(QByteArray, QString);
    QVariant GetParamStandby(QByteArray, QString);
    int GetRequestInteraval(QByteArray);
private:
    QString buf;
};

#endif // PARSERCONFIG_H
