#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    parser = new ParserConfig();
    timerServer = new QTimer(this);
    timerScreenShot = new QTimer(this);

    record = false;
    snapshotInterval = 0;
    widthNew = 0;

    connect(timerServer, SIGNAL(timeout()), this, SLOT(threadStartServer()));
    connect(timerScreenShot, SIGNAL(timeout()), this, SLOT(threadStartScreenShot()));    

    screenShot = new ScreenShot();
    uploadImage = new UploadImage();
    startExam = new CheckStartExam();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setData(QString UIDGet, QByteArray JSONConfig, int standbyRequestInterval, QString serverIP)
{
    this->serverIP = serverIP;
    UID = UIDGet;    
    JSONConfigString = JSONConfig;
    requestInterval = standbyRequestInterval;

    threadServer = new QThread(this);
    startExam->moveToThread(threadServer);
    connect(threadServer, SIGNAL(started()), startExam, SLOT(check()));
    connect(startExam, SIGNAL(send(bool, double, int)), this, SLOT(startOrStopExam(bool, double, int)));
    connect(startExam, SIGNAL(finished()), threadServer, SLOT(quit()));
    startExam->setData(parser->GetParam(JSONConfigString, "standby"), requestInterval, UID, serverIP);
    threadServer->start();

    threadScreenShot = new QThread(this);
    screenShot->moveToThread(threadScreenShot);
    connect(threadScreenShot, SIGNAL(started()), screenShot, SLOT(makeScreenshots()));
    connect(screenShot, SIGNAL(finished()), threadScreenShot, SLOT(quit()));
    connect(screenShot, SIGNAL(send(QString, QString, bool)), this, SLOT(postImage(QString, QString, bool)));

    threadUploadImage = new QThread(this);
    uploadImage->moveToThread(threadUploadImage);
    connect(threadUploadImage, SIGNAL(started()), uploadImage, SLOT(upload()));
    connect(uploadImage, SIGNAL(finished()), threadUploadImage, SLOT(quit()));
    connect(uploadImage, SIGNAL(restart(bool, double, double)), this, SLOT(restartCheckServer(bool, double, double)));

    timerServer->start(requestInterval);
}

void MainWindow::startOrStopExam(bool startRecord, double interval, int width)
{          
    if (startRecord) {
        timerServer->stop();
        ui->label->setText("Идет экзамен!");
        if (record != startRecord || snapshotInterval != interval || widthNew != width)// || (record && !timerScreenShot->isActive()))
        {
            widthNew = width;
            record = startRecord;
            snapshotInterval = interval;
            timerScreenShot->start(snapshotInterval);
        }
    } else {
        if (ui->label->text() != "Экзамен не идет!")
            ui->label->setText("Экзамен не идет!");
    }
}

void MainWindow::postImage(QString time, QString filePath, bool multi)
{
    multiScreens = multi;

    uploadImage->setData(multiScreens, parser->GetParamStandby(JSONConfigString, "image").toString(), UID, time, filePath, serverIP);
    threadUploadImage->start();
}

void MainWindow::restartCheckServer(bool record, double interval, double width)
{    
    this->record = record;
    snapshotInterval = interval;
    widthNew = width;

    if (!record) {
        timerScreenShot->stop();
        timerServer->start(requestInterval);        
    } else {
        timerServer->stop();
        timerScreenShot->start(snapshotInterval);
    }
}

void MainWindow::threadStartServer()
{
    threadServer->start();
}

void MainWindow::threadStartScreenShot()
{    
    screenShot->setWidth(widthNew);
    threadScreenShot->start();
}
