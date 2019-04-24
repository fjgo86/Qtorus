#ifndef _INC_PACKET_H
#define _INC_PACKET_H

#include <QByteArray>

enum PacketId
{
    PACKET_LOGIN = 239,

};


class ClientSocket;
class packet
{
protected:
    QByteArray _buffer;
    uint _buffer_pos;
    uchar _id;
    ClientSocket *_socket;

    bool _disable_decrypt = true;
public:
    packet(ClientSocket *socket, uchar id);
    packet(ClientSocket *socket, PacketId id);

    virtual int getSize() = 0;
    uchar getId();
    /* @brief sets the buffer for this packet
     *
     * @param buffer the buffer
     *
     * Makes a copy of the buffer from ClientSocket to free that buffer for other packets
    */
    void setBuffer(QByteArray &buffer);

    /* @brief Disables decryption
     *
     * Should only be used for new connections sending the Login Packet
    */
    void disable_decrypt();
    template<typename T>
    /* @brief Decrypts the given value
     *
     * @param &d the value to decrypt
     * @return the new value.
    */
    void decrypt_value(T &d);
    /* @brief Encrypts the given value
     *
     * @param &d the value to encrypt
     * @return the new value.
    */
    template<typename T>
    void encrypt_value(T &d);
    template<typename T>
    friend packet &operator>>(packet& packet, T &d);
    template<typename T>
    friend packet &operator<<(packet& packet, T &d);
};

template<typename T>
void packet::decrypt_value(T& d)
{
    d = d;  // WUNUSED_PARAM
    // TODO: client keys and crypt
}

template<typename T>
void packet::encrypt_value(T& d)
{
    d = d;  // WUNUSED_PARAM
    // TODO: client keys and crypt
}

template<typename T>
packet & operator>>(packet &packet, T &d)
{
    packet._buffer >> decrypted_value(d);
    return packet;
}

template<typename T>
packet & operator<<(packet &packet, T &d)
{
    packet._buffer << encrypted_value(d);
    return packet;
}


struct PacketFactory
{
    static packet * getPacket(uchar packetid);
    static packet * getPacket(PacketId packetid);
};

class packet_out : public packet
{
    bool _size_reserved;
public:
    virtual int getSize() = 0;
    packet_out(ClientSocket *target, PacketId id);
    /* @brief marks the size to be filled later
     *
     * Some packets have an unknown amount of data, this marks the size position
     * in the buffer to be filled after generating all the data sent.
     * If this is set, there's no need to set the size, it will be automatically done before sending.
    */
    void reserve_size();

    void send();
};

class packet_in : public packet
{
public:
    virtual int getSize() = 0;
    packet_in(ClientSocket *socket, PacketId id);
    virtual ~packet_in();
    virtual void read() = 0;
};


class PacketLogin : public packet_in
{
public:
    PacketLogin();
    virtual ~PacketLogin();
    virtual int getSize() override
    {
        return 63;
    }
    virtual void read() override;
};

#endif // _INC_PACKET_H
