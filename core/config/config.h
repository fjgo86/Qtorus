#ifndef _INC_CONFIG_H
#define _INC_CONFIG_H

#include <QString>
#include "network/crypto.h"

extern class Config
{
    // Network
    QString _servIP;
    uint _servPort;
    Crypt_Keys _crypt_keys;

public:
    Config();
    ~Config();
    QString servIP() const;
    void setServIP(const QString &servIP);
    uint servPort() const;
    void setServPort(const uint &servPort);
} g_Cfg;

#endif // _INC_CONFIG_H
