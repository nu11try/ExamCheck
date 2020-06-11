#include "mainwindow.h"
#include "loginform.h"

#include <QApplication>
#include <QDir>

void CreateDir(QString);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //CreateDir(QString(getenv("AppData")).append("\\ExamCheck"));
    CreateDir(QCoreApplication::applicationDirPath().append("\\image"));

    LoginForm login;
    login.setFixedSize(login.width(), login.height());
    login.show();   

    return a.exec();
}

void CreateDir(QString path) {
    if (!QDir().exists(path)) {
        QDir().mkdir(path);
    }
}
