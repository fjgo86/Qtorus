#include "config.h"



Config::Config()
{
    _servIP = "192.168.1.77";
    _servPort = 2595;
}

Config::~Config()
{

}

uint Config::servPort() const
{
    return _servPort;
}

void Config::setServPort(const uint &servPort)
{
    _servPort = servPort;
}

QString Config::servIP() const
{
    return _servIP;
}

void Config::setServIP(const QString &servIP)
{
    _servIP = servIP;
}
