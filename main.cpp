#include <QApplication>
#include "core/gui/gui.h"
#include "core/logger/logger.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    gui * pgui = new gui();

    pgui->show();

    return a.exec();
}
