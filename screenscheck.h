#ifndef SCREENSCHECK_H
#define SCREENSCHECK_H

#include <QObject>
#include <QGuiApplication>
#include <QDebug>
#include <QThread>

class ScreensCheck : public QObject
{
    Q_OBJECT

public:
    ScreensCheck(QObject *parent = 0);    

public slots:
    void check();
signals:
    // true, если несклько мониторов
    void send(bool);

};

#endif // SCREENSCHECK_H
