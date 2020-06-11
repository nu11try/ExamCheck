#ifndef LOGINFORM_H
#define LOGINFORM_H

#include <QMainWindow>
#include <QString>
#include <QStringList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkAccessManager>
#include <QtNetwork/QNetworkReply>
#include <QThread>
#include "screenscheck.h"
#include "GetConfig.h"
#include "parserconfig.h"
#include "auth.h"
#include "screenshot.h"

namespace Ui {
class LoginForm;
}

class LoginForm : public QMainWindow
{
    Q_OBJECT
public:
    explicit LoginForm(QWidget *parent = nullptr);
    ~LoginForm();    

public slots:
    void on_btn_enter_clicked();    
    void go_in_main_window(QString);
    void get_config_string(QByteArray);

private:
    Ui::LoginForm *ui;
    ParserConfig *parser;
    Auth *auth;
    GetConfigClass *conf;
    QString UID;
    QString Phone;
    QString serverIP;
    QList<QString> pathAndTime;
    QByteArray ConfigStrign;
    QString Token;
    int standbyRequestInterval;
    QThread *threadConf;
    QThread *threadAuth;
};

#endif // LOGINFORM_H
