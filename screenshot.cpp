#include "screenshot.h"
#include "uploadimage.h"

ScreenShot::ScreenShot()
{
    // Определение путей к сохранению скринов
    mainPath = QCoreApplication::applicationDirPath().append("/image/");
}

void ScreenShot::setWidth(double width)
{
    widthWindow = width;
}

void ScreenShot::makeScreenshots()
{
    QString timeNameFile = QString("%1.%2.%3.%4").arg(QTime::currentTime().hour())
            .arg(QTime::currentTime().minute()).arg(QTime::currentTime().second()).arg(QTime::currentTime().msec());
    QString filePath = QString("%1%2.jpg").arg(mainPath).arg(timeNameFile);

    QFile fileSaveScreen(filePath);
    fileSaveScreen.open(QIODevice::ReadWrite);

    QDesktopWidget *desktop = QApplication::desktop();
    QRect geo = QGuiApplication::screens().first()->geometry();

    QScreen *primaryScreen = QApplication::primaryScreen();
    QFuture<QPixmap> future;
    future = QtConcurrent::run(primaryScreen, &QScreen::grabWindow,
            desktop->winId(),
            geo.left(), geo.top(),
            geo.width(), geo.height());
    future.waitForFinished();
    QPixmap screenshot = future.result();    
    screenshot.save(&fileSaveScreen, "JPG");
    fileSaveScreen.close();
    int height = (QImage(filePath).size().height() * widthWindow) / QImage(filePath).size().width();
    QImage(filePath).scaled(widthWindow, height).save(filePath);

    qint32 ScreenCount = QGuiApplication::screens().length();
    if (ScreenCount > 1) emit send(timeNameFile, filePath, true);
    else emit send(timeNameFile, filePath, false);

    emit finished();
}
