/*#ifndef _INC_SERVERSOCKET_H
#define _INC_SERVERSOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>


class Network;

class ServerSocket
{
    bool _run;
    struct sockaddr_in _address;
    int _serverSocket;
public:

    ServerSocket();
    ServerSocket(in_addr ip, int port);
    in_addr GetIP()
    {
        return _address.sin_addr;
    }

    int GetPort()
    {
        return _address.sin_port;
    }

    ~ServerSocket();
    void init();
};
#endif // _INC_SERVERSOCKET_H
*/
