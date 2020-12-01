#include "logginghome.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoggingHome w;
    w.show();
    return a.exec();
}
