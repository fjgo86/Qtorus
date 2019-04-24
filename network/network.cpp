#include "network.h"
#include "server/server.h"
#include "core/config/config.h"
#include "core/logger/logger.h"
#include <QSettings>

Network *Network::_instance = nullptr;

Network::Network(QObject *parent) : QTcpServer(parent)
{
}

Network::~Network()
{
    _clients.clear();
}

void Network::start()
{
    QString slog;
    QHostAddress ip(_ip);
    QString sip(_ip);
    sip.append(":");
    sip.append(sip.number(_port));

    if (!listen( ip, _port))
    {
        slog.append("Server failed to listen to");
        slog.append(sip);
        slog.append("\n");
        ERROR_LOG(slog);
        return;
    }
    slog.append("Server listening to ");
    slog.append(sip);
    slog.append("\n");
    LOG(slog);
    connect(this, SIGNAL(newConnection()), this, SLOT(acceptClient()));
}

void Network::init()
{
    _ip = g_Cfg.servIP();
    _port = g_Cfg.servPort();
}

Network *Network::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new Network();
    }
    return _instance;
}

void Network::acceptClient()
{
    std::shared_ptr<ClientSocket> client(new ClientSocket(nextPendingConnection()));
    _clients.push_back(client);
}
