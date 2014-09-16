#include <QProcess>
#include <iostream>
#include "outputdialog.h"
#include "hardconfigure.h"
#include "myscrollbar.h"
#include "unistd.h"

outPutDialog::outPutDialog(hardConfigure *configure,QWidget *parent) :
    QMainWindow(parent)
{
    mac_phy_Process = configure->mac_phy_Process;
    outPutWindow = new QTextEdit;
    //QProgressBar *transProgress = new QProgressBar;
    //QLabel *pictureLabel = new QLabel;
    //QSplitter *hSplitter = new QSplitter(Qt::Horizontal);
    //hSplitter->addWidget(outPutWindow);


    //QPixmap *pixmap = new QPixmap(300, 300);
    //pixmap->load("1.jpg");
    //pictureLabel->setPixmap(*pixmap);
    //pixmap->scaledToHeight(400);
    //pixmap->scaledToWidth(400);
    //hSplitter->addWidget(pictureLabel);
   // hSplitter->setStretchFactor(0, 1);
    //QSplitter *splitter = new QSplitter(Qt::Vertical);
    //splitter->addWidget(hSplitter);
    //splitter->addWidget(splitter);
    setCentralWidget(outPutWindow);
    //setGeometry(100, 100, 1500, 800);
    //setMinimumSize(1500, 800);


   // addDockWidget(Qt::RightDockWidgetArea,pictureArea);


    setWindowTitle("output from low_mac");
    setGeometry(300,300,800,500);

    outPutWindow->setReadOnly(true);
    scrollBar = new myScrollBar(this);
    outPutWindow->setVerticalScrollBar(scrollBar);
    scrollBar->setValue(scrollBar->maximum());
    isBottom = true;

    connect(mac_phy_Process, SIGNAL(readyReadStandardOutput()), this, SLOT(updateOutPutEdit()));
    connect(mac_phy_Process, SIGNAL(readyReadStandardError()), this, SLOT(updateOutPutError()));
    connect(mac_phy_Process, SIGNAL(finished(int,QProcess::ExitStatus)), this, SLOT(processFinished(int,QProcess::ExitStatus)));
}
/*
void outPutDialog::updateBar(){
    int num = 10000;
    //centralWidget()->children().at(1)->setRange(0, 10000);
    QSplitter *a = centralWidget();
    QProgressBar *b = a->widget(1);
    b->setRange(0, 10000);
    for(int i = 0;i < num;i++){
        usleep(1000);
        b->setValue(i);
}

}
*/
void outPutDialog::closeEvent(QCloseEvent *event){
    if(okToContinue()){
        mac_phy_Process->close();
        event->accept();
    }
    else
        event->ignore();
}

bool outPutDialog::okToContinue(){
    int r = QMessageBox::warning(this, tr("Warning"),
                            tr("Mac_main program is stilling running\n"
                               "Do you want to leave?"),
                            QMessageBox::Yes | QMessageBox::No);
            if (r == QMessageBox::Yes) {
                return true;
            } else {
                return false;
            }
}

void outPutDialog::updateOutPutEdit(){
    QByteArray newData = mac_phy_Process->readAllStandardOutput();
    QString text = QString::fromLocal8Bit(newData);
    outPutWindow->insertPlainText(text);
    if(isBottom && (scrollBar->minimum() != scrollBar->maximum()))
        scrollBar->setValue(scrollBar->maximum());
}

void outPutDialog::updateOutPutError(){
    QByteArray newData = mac_phy_Process->readAllStandardError();
    //QString text = outPutWindow->toPlainText()+QString::fromLocal8Bit(newData);
    QString text = QString::fromLocal8Bit(newData);
    outPutWindow->insertPlainText(text);
    if(scrollBar->value() == scrollBar->maximum())
    scrollBar->setValue(scrollBar->maximum());
}

void outPutDialog::processFinished(int exitCode, QProcess::ExitStatus exitStatus){
    if(exitStatus == QProcess::CrashExit){
        outPutWindow->append(tr("low_mac program crashed"));
    }else if(exitCode != 0){
        outPutWindow->append(tr("low_mac failed"));
    }else{
        outPutWindow->append(tr("succeed!"));
    }
}

