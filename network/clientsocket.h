#ifndef _INC_CLIENTSOCKET_H
#define _INC_CLIENTSOCKET_H

#include <QTcpSocket>
#include <QByteArray>

class ClientSocket : public QObject
{
    Q_OBJECT
    QByteArray _buffer; ///< buffer storing the received data.
    QTcpSocket *_socket; ///< pointer to the socket
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
