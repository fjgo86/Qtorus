#ifndef _INC_LOGGER_H
#define _INC_LOGGER_H

#include <QObject>
#include <QString>

#define LOG(s) logger::getInstance()->log(logger::LOG_TYPE::LOGT_DEFAULT, s);
#define WARNING_LLOG(s) logger::getInstance()->log(logger::LOG_TYPE::LOGT_WARNING, s);
#define DEBUG_LOG(s) logger::getInstance()->log(logger::LOG_TYPE::LOGT_DEBUG, s);
#define ERROR_LOG(s) logger::getInstance()->log(logger::LOG_TYPE::LOGT_ERROR, s);
#define CRITICAL_LOG(s) logger::getInstance()->log(logger::LOG_TYPE::LOGT_CRITICAL, s);

class console_out;

class logger : public QObject
{
    Q_OBJECT
    static logger *_instance; // Singleton pattern, forbid more than one instance of this class.
    logger();

public:
    ~logger();
    enum LOG_TYPE
    {
        LOGT_DEFAULT,
        LOGT_WARNING,
        LOGT_DEBUG,
        LOGT_ERROR,
        LOGT_CRITICAL
    };
    static logger *getInstance();// retrieves the instance.

    /*
     * @brief Transforms the log into a final string
     *
     * @param type The type of log
     * @param s The log' string
     *
     * Converts the 'type' to a colored string and inserts it as a prefix for the final string
     * then sends the 'log' signal for the console_out to print.
    */
    void log(logger::LOG_TYPE type, QString s);

    /*
     * @brief connect this signal object with it's console_out receiver
     *
     * @param cons the console
     *
     * binds 'add_log' with 'receive_log'
    */
    void bind(console_out *cons);

signals:
    /*
     * @brief Signals the console_out to print some string
     *
     * @param type The type of log
     * @param s The string
    */
    void add_log(logger::LOG_TYPE, QString);
};

#endif // _INC_LOGGER_H
