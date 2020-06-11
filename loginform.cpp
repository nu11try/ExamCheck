#include "loginform.h"
#include "ui_loginform.h"
#include "mainwindow.h"

LoginForm::LoginForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginForm)
{    
    ui->setupUi(this);

    serverIP = "http://127.0.0.1:3000";

    parser = new ParserConfig();

    threadConf = new QThread(this);
    threadAuth = new QThread(this);

    conf = new GetConfigClass();
    auth = new Auth();

    conf->moveToThread(threadConf);
    conf->setData(serverIP);
    connect(conf, SIGNAL(send(QByteArray)), this, SLOT(get_config_string(QByteArray)));
    connect(threadConf, SIGNAL(started()), conf, SLOT(GetConfig()));
    connect(conf, SIGNAL(finished()), threadConf, SLOT(quit()));
    threadConf->start();

    auth->moveToThread(threadAuth);
    connect(auth, SIGNAL(send(QString)), this, SLOT(go_in_main_window(QString)));
    connect(threadAuth, SIGNAL(started()), auth, SLOT(auth()));
    connect(auth, SIGNAL(finished()), threadAuth, SLOT(quit()));
}

LoginForm::~LoginForm()
{
    delete ui;
}

void LoginForm::on_btn_enter_clicked()
{
    UID = ui->edt_uid->text();
    Phone = ui->edt_tel->text();

    if(UID == "" || Phone == "")
        QMessageBox::warning(0, "Пустые данные", "Не все данные указаны!");
    else {
        standbyRequestInterval = parser->GetRequestInteraval(ConfigStrign);
        auth->setData(Phone, UID, parser->GetParam(ConfigStrign, "auth"), serverIP);
        threadAuth->start();
    }
}

void LoginForm::go_in_main_window(QString response)
{   
    Token = response;
    if (Token != "no") {        
        MainWindow *w = new MainWindow();
        w->setAttribute(Qt::WA_DeleteOnClose, true);
        w->setFixedSize(w->width(), w->height());
        w->show();
        emit w->setData(Token, ConfigStrign, standbyRequestInterval, serverIP);
        this->close();
    }else{
        QMessageBox::warning(0, "Неверные данные", "Введенные данные неверны!");
    }
}

void LoginForm::get_config_string(QByteArray param)
{
    ConfigStrign = param;
}
