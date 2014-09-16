#ifndef TRANSMAINWINDOW_H
#define TRANSMAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class transMainWindow;
}

class transMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit transMainWindow(QWidget *parent = 0);
    ~transMainWindow();

private:
    Ui::transMainWindow *ui;
};

#endif // TRANSMAINWINDOW_H
