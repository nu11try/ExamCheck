#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QThread>
#include <screenshot.h>
#include <QMessageBox>
#include "parserconfig.h"
#include "checkstartexam.h"
#include "uploadimage.h"
#include <QThread>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT    

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void setData(QString, QByteArray, int, QString);
    void startOrStopExam(bool, double, int);
    void postImage(QString, QString, bool);
    void restartCheckServer(bool, double, double);
    void threadStartServer();
    void threadStartScreenShot();

private:    
    Ui::MainWindow *ui;
    int requestInterval;
    double snapshotInterval;
    bool record;
    int widthNew;
    ParserConfig *parser;
    QTimer *timerServer;
    QTimer *timerScreenShot;
    QThread *threadServer;
    QThread *threadScreenShot;
    QThread *threadUploadImage;
    CheckStartExam *startExam;
    ScreenShot *screenShot;
    UploadImage *uploadImage;
    QString UID;
    QByteArray JSONConfigString;
    bool multiScreens = false;
    QString serverIP;
};
#endif // MAINWINDOW_H
