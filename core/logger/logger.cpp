#include "logger.h"
#include "core/gui/console_out.h"

logger * logger::_instance = nullptr;

logger::logger()
{
}

logger::~logger()
{

}

void logger::log(logger::LOG_TYPE type, QString s)
{
    emit add_log(type, s);
}

void logger::bind(console_out *cons){
    connect(this, &logger::add_log, cons, &console_out::receive_log);
}

logger *logger::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new logger();
    }
    return _instance;
}
