#include "server.h"
#include "core/logger/logger.h"
#include "network/network.h"


Server::Server(QObject *parent) : QThread(parent)
{
}

Server::~Server()
{
    qDebug("closing server");
}

void Server::run()
{
    LOG("Starting server...\n");
    _run = true;
    Network *net = Network::getInstance();
    net->init(this);
    connect(this, SIGNAL(finished()), this, SLOT(stop()));   // Handles any stop signal and call stop

    if (_run == true)
    {
        try
        {
            net->start();
        }
        catch(...)
        {
            QString err;
            err.append("server::onTick error: ");
            err.append(strerror(errno));
            err.append("\n");
            ERROR_LOG(err);
            quit();
        }
    }
    else
    {
        quit(); //
    }
}


void Server::stop()
{
    emit emitStop(this);
}
