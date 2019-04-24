#ifndef _INC_CRYPTO_H
#define _INC_CRYPTO_H

#include <QByteArray>

enum CRYPT_TYPE
{
    CRYPT_NONE,     // No encryption
    CRYPT_BFISH,    // Blowfish
    CRYPT_BTFISH,   // Blowfish + Twofish
    CRYPT_TFISH     // Twofish
};


struct Crypt_Keys
{
    uint first;
    uint second;
    CRYPT_TYPE type;
    uint cliver;
};

class crypto
{
private:
    crypto(const crypto &cpy);
    void operator=(const crypto &cpy);

    uint _seed; // Seed sent by the client.
    std::pair<uint, uint> _key; // key.first, key.second (from crypt.ini)

    // Client version = major.minor.revision.prototype, eg 7.0.24.13
    uint _cliver_major;      // Major version
    uint _cliver_minor;      // Minor version
    uint _cliver_revision;   // Revision
    uint _cliver_prototype;  // Prototype

    uint _cliver_full;      // full integer, eg: 702413

    // Connection
    CRYPT_TYPE _crypt_type;         // Encryption type required

public:
    crypto();
    ~crypto();

    /* @brief Detect the client keys for the incoming connection
     *
     * @param buffer The buffer
     *
     * Reads the data inside buffer (sent in packet 0xef) and reads the list of keys
     * to detect the client version trying to connect. buffer has to be used afterwards
     * to read the account name and password so we get a copy here to change it freely.
    */
    void detect_client_key(QByteArray &buffer);

    /*
     * @brief Gets the full client version
     *
     * @return the version
    */
    uint getCliver();
    /*
     * @brief Gets the major client version
     *
     * @return the version
    */
    uint getCliver_major();
    /*
     * @brief Gets the minor client version
     *
     * @return the version
    */
    uint getCliver_minor();
    /*
     * @brief Gets the revision version
     *
     * @return the revision
    */
    uint getCliver_revision();
    /*
     * @brief Gets the prototype version
     *
     * @return the prototype
    */
    uint getCliver_prototype();

    CRYPT_TYPE getCrypt();
};

#endif // _INC_CRYPTO_H
