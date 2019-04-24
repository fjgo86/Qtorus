#include "packet.h"
#include "clientsocket.h"
#include "core/logger/logger.h"
#include <QString>


packet *PacketFactory::getPacket(uchar packetid)
{
    return getPacket((PacketId)packetid);
}

packet *PacketFactory::getPacket(PacketId packetid)
{
    switch (packetid)
    {
    case PacketId::PACKET_LOGIN:
        return new PacketLogin();
    default:
        QString slog("Received undefined packet ");
        slog.append(packetid);
        slog.append("\n");
        ERROR_LOG(slog);
                break;
    }
    return nullptr;
}

void packet::setBuffer(QByteArray &buffer)
{
    _buffer = buffer;
}

packet::packet(ClientSocket *socket, uchar id)
{
    _socket = socket;
    _id = id;
}

packet::packet(ClientSocket *socket, PacketId id)
{
    _socket = socket;
    _id = (uchar)id;
}

uchar packet::getId()
{
    return _id;
}


packet_out::packet_out(ClientSocket *target, PacketId id) : packet(target, id)
{

}

void packet_out::reserve_size()
{
    _size_reserved = true;
}

void packet_out::send()
{
    if (_size_reserved == true)
    {
        uchar size = _buffer.size();
        encrypt_value(size);
        _buffer.insert(1, size);
    }
    _socket->getSocket()->write(_buffer);
}

packet_in::packet_in(ClientSocket *socket, PacketId id) : packet(socket, id)
{

}

packet_in::~packet_in()
{

}

PacketLogin::PacketLogin() : packet_in(nullptr, PacketId::PACKET_LOGIN)
{

}

PacketLogin::~PacketLogin()
{

}

void PacketLogin::read()
{

}
