#include "crypto.h"
#include "core/logger/logger.h"
#include <QDataStream>

crypto::crypto()
{
    _cliver_major = 0;
    _cliver_minor = 0;
    _cliver_revision = 0;
    _cliver_prototype = 0;
    _cliver_full = 0;

    _seed = 0;
    _crypt_type = CRYPT_NONE;
}

crypto::~crypto()
{

}

void crypto::detect_client_key(QByteArray &buffer)
{
    QDataStream stream(buffer);
    stream >> _seed;
    QString slog;
    slog.append(slog.number(_seed));
    LOG(slog);
}

uint crypto::getCliver()
{
    return _cliver_full;
}

uint crypto::getCliver_major()
{
    return _cliver_major;
}

uint crypto::getCliver_minor()
{
    return _cliver_minor;
}

uint crypto::getCliver_revision()
{
    return _cliver_revision;
}

uint crypto::getCliver_prototype()
{
    return _cliver_prototype;
}
