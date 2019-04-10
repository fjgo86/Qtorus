#ifndef _INC_CONSOLE_OUT_H
#define _INC_CONSOLE_OUT_H

#include <QTextEdit>
#include "core/logger/logger.h"

class console_out : public QTextEdit
{
    Q_OBJECT
    static console_out* _instance; // Singleton pattern, keep only one output handler

    console_out();

    void set_type(logger::LOG_TYPE type);
    void add_log(QString s);
    QColor background_color;
    QColor text_color_default;
    QColor text_color_warning;
    QColor text_color_debug;
    QColor text_color_error;
    QColor text_color_critical;

public:
    ~console_out();
    static console_out *getInstance();

signals:
public slots:
    void receive_log(logger::LOG_TYPE type, QString s);
};

#endif // _INC_CONSOLE_OUT_H
