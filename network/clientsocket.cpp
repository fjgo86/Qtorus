#include "clientsocket.h"
#include "core/logger/logger.h"
#include <QHostAddress>

QTcpSocket *ClientSocket::getSocket()
{
    return _socket;
}

ClientSocket::ClientSocket(QTcpSocket *socket)
{
    _socket = socket;
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    QString slog;
    slog.append("Client connecting from ");
    slog.append(_socket->peerAddress().toString());
    slog.append("\n");
    LOG(slog);
}

ClientSocket::~ClientSocket()
{

}


void ClientSocket::readyRead()
{
    _buffer = _socket->readAll();

    QString slog("Receiving packet: ");
    slog.append(slog.number((uchar)_buffer.at(0)));
    slog.append("\n");
    DEBUG_LOG(slog);
}
