#include "login_form.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}


login_form::login_form(QWidget *parent) : QWidget(parent), ui (new)
{

}
