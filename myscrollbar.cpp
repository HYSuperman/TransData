#include "myscrollbar.h"
#include "outputdialog.h"
#include <iostream>

myScrollBar::myScrollBar(outPutDialog *opd, QWidget *parent) :
    outputdialog(opd), QScrollBar(parent)
{
}

void myScrollBar::mouseReleaseEvent(QMouseEvent *event){
    if(value()!=maximum())
        outputdialog->isBottom = false;
    else
        outputdialog->isBottom = true;

    QScrollBar::mouseReleaseEvent(event);

}

void myScrollBar::mousePressEvent(QMouseEvent *event){
    outputdialog->isBottom = false;
    QScrollBar::mousePressEvent(event);

}
