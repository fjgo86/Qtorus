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
    _connection_type = CT_UNK;
    _cur_packet = nullptr;
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
    // Reading the data

    if (_cur_packet == nullptr)
    {
        _buffer = _socket->readAll();
        _cur_packet = static_cast<packet_in*>(PacketFactory::getPacket(_buffer.at(0)));
    }
    else
    {
        _buffer.append(_socket->readAll());
    }

    if (_buffer.size() < _cur_packet->getSize())
    {
        return; // Wait for the rest of the data to be processed
    }
    _cur_packet->setBuffer(_buffer);

    // data readed
    // Now we determinate what to do
    if (_connection_type == CT_UNK) // If there's not a connection type yet...
    {
        LOGIN_STATUS type = get_login_status(_buffer); // get the login status
        switch (type)
        {
        case LOGIN_CONFIRM:
            // TODO: Send login confirmation
            break;
        default:
        case LOGIN_BADUSER:
        case LOGIN_BADPASSWORD:
        case LOGIN_BLOCKED:
            // TODO: decline login request with the status type
            _socket->close();
            break;
        }
        // Wether we accept or reject the connection, it's all we have to do now.
        return;
    }
    else if (_connection_type == CT_LOGIN)  // passed the login checks
    {
        //TODO: Handle server selection screen
        //TODO: Handle char selection/creation screen
        return;
    }

    // _connection_type == CT_GAME
    QString slog("Receiving packet: ");
    slog.append(slog.number((uchar)_cur_packet->getId()));
    slog.append("\n");
    DEBUG_LOG(slog);
    // force a packet_in->read() to interpretate the received data.
    _cur_packet->read();
    delete _cur_packet;   // data readed and executed, delete it
    _cur_packet = nullptr;    // sets the pointer to null for the new incoming packets
}

LOGIN_STATUS ClientSocket::get_login_status(QByteArray &buffer)
{
    _crypto.detect_client_key(buffer);
    if (_crypto.getCliver_major() == 0) // detection failed or we have an unencrypted client.
    {
        // TODO: Unencrypted allowance check in the ini.
        // TODO: AccMgr->check(accname, accpw);
    }
    return LOGIN_CONFIRM;
}
