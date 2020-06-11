#ifndef SCREENSHOT_H
#define SCREENSHOT_H

#include <QObject>
#include <QVector>
#include <QPixmap>
#include <QApplication>
#include <QDesktopWidget>
#include <QScreen>
#include <QDebug>
#include <QFile>
#include <QDateTime>
#include <QTime>
#include <QTextStream>
#include <QBuffer>
#include <QByteArray>
#include <QGuiApplication>
#include <QtConcurrent/QtConcurrentRun>

class ScreenShot : public QObject
{
    Q_OBJECT

public:
    ScreenShot();


public slots:
    void makeScreenshots();
    void setWidth(double);

signals:
    void send(QString, QString, bool);
    void finished();

private:
    QString mainPath;
    double widthWindow;
};

#endif // SCREENSHOT_H
