#ifndef OUTPUTDIALOG_H
#define OUTPUTDIALOG_H

#include <QMainWindow>
#include <QtGui>


class QProcess;
class hardConfigure;
class myScrollBar;


class outPutDialog : public QMainWindow
{
    Q_OBJECT
public:
    explicit outPutDialog(hardConfigure *configure, QWidget *parent = 0);
    QTextEdit *outPutWindow;
    myScrollBar *scrollBar;
    bool isBottom;
    //void updateBar();
protected:
    void closeEvent(QCloseEvent *event);

signals:

private slots:
    void updateOutPutEdit();
    void updateOutPutError();
    void processFinished(int exitCode, QProcess::ExitStatus exitStatus);

private:
    bool okToContinue();
    QProcess *mac_phy_Process;

};

#endif // OUTPUTDIALOG_H
