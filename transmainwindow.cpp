#include "transmainwindow.h"
#include "ui_transmainwindow.h"
#include <QPainter>

transMainWindow::transMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::transMainWindow)
{
    ui->setupUi(this);
}



transMainWindow::~transMainWindow()
{
    delete ui;
}
