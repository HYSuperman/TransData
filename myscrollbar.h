#ifndef MYSCROLLBAR_H
#define MYSCROLLBAR_H

#include <QScrollBar>

class outPutDialog;

class myScrollBar : public QScrollBar
{
    Q_OBJECT
public:
    explicit myScrollBar(outPutDialog *opd, QWidget *parent = 0);

private:
    outPutDialog *outputdialog;

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:

public slots:

};

#endif // MYSCROLLBAR_H
