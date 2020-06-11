#include "parserconfig.h"

ParserConfig::ParserConfig()
{

}

QString ParserConfig::GetParam(QByteArray JSONString, QString obj)
{
    QJsonDocument document = QJsonDocument::fromJson(JSONString);
    QJsonObject root = document.object();
    return root.value("methods").toObject().value(obj).toString();
}

int ParserConfig::GetRequestInteraval(QByteArray JSONString)
{
    QJsonDocument document = QJsonDocument::fromJson(JSONString);
    QJsonObject root = document.object();
    return root.value("standbyRequestInterval").toInt();
}

QVariant ParserConfig::GetParamStandby(QByteArray JSONString, QString obj)
{
    QJsonDocument document = QJsonDocument::fromJson(JSONString);
    QJsonObject root = document.object();
    return root.value(obj);
}
