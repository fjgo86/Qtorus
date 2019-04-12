#include <QApplication>
#include "core/gui/gui.h"
#include "core/logger/logger.h"
#include "server/server.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    gui * pgui = new gui();

    pgui->show();

    Server *serv = new Server();
    serv->run();

    return a.exec();
}
