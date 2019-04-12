#ifndef _INC_NETWORK_H
#define _INC_NETWORK_H

#include <vector>
#include <memory>
#include <QObject>
#include <QTcpServer>
#include "serversocket.h"
#include "clientsocket.h"


class Server;
class Network : public QTcpServer
{
    Q_OBJECT
    std::vector<std::shared_ptr<ClientSocket>> _clients;    ///< vector containing a pointer to all connected clients
    ~Network();
    Network(QObject *parent = 0);
    static Network *_instance; ///< Instance pointer for singleton pattern
    QString _ip;
    int _port;
public:
    static Network *getInstance(); ///< Instance for singleton pattern
    void init();    ///< Initialize configuration
    void start();   ///< start listening
signals:
public slots:
    void acceptClient();
};


#endif //_INC_NETWORK_H
