#include "hardconfigure.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    hardConfigure w;
    w.show();

    return a.exec();
}
