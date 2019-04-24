#ifndef _INC_CLIENTSOCKET_H
#define _INC_CLIENTSOCKET_H

#include <QTcpSocket>
#include <QByteArray>
#include "crypto.h"
#include "packet.h"

enum LOGIN_STATUS
{
    LOGIN_CONFIRM,      // Everything OK
    LOGIN_BADUSER,      // Bad user entered
    LOGIN_BADPASSWORD,  // Wrong password used
    LOGIN_BLOCKED       // Blocked account
};

enum CONNECT_TYPE
{
    CT_UNK,     // Uknown, the client may have just connected and it's waiting for the crypt setup and connect confirmation.
    CT_LOGIN,   // Login mode, connect has been confirmated. This covers server selection and player creation/selection screens.
    CT_GAME     // Client connected to the world with a character.
};

class ClientSocket : public QObject
{
    Q_OBJECT
    QByteArray _buffer; ///< buffer storing the received data.
    QTcpSocket *_socket; ///< pointer to the socket
    CONNECT_TYPE _connection_type;  // Connection mode
    packet_in * _cur_packet;

    crypto _crypto; // The crypto handler.

    /* @brief Checks the connection and retrieves it's status.
     *
     * @return the login status.
     *
     * This involves the crypto initial checks and user/password confirmation.
    */
    LOGIN_STATUS get_login_status(QByteArray &buffer);
public:
    QTcpSocket *getSocket();
    ClientSocket(QTcpSocket *socket);
    ~ClientSocket();

signals:
private slots:
    /* @brief New data ready to be readed
     *
    */
    void readyRead();
public slots:
};

#endif // _INC_CLIENTSOCKET_H
