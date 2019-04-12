#include "console_out.h"
#include <QString>
#include <QSettings>

console_out *console_out::_instance = nullptr;

console_out::console_out()
{

    // --> Color settings

    // Reading from QSettings
    QSettings settings;
    settings.beginGroup("console_out");
    _background_color = settings.value("background_color",QColor::fromRgb(0,0,0)).value<QColor>();               // Default black background
    _text_color_default = settings.value("text_color_default", QColor::fromRgb(255,255,255)).value<QColor>();    // Default white text color
    _text_color_warning = settings.value("text_color_warning", QColor::fromRgb(0,255,0)).value<QColor>();
    _text_color_debug = settings.value("text_color_debug", QColor::fromRgb(0,255,255)).value<QColor>();
    _text_color_error = settings.value("text_color_error", QColor::fromRgb(255,255,0)).value<QColor>();
    _text_color_critical = settings.value("text_color_critical", QColor::fromRgb(255,0,0)).value<QColor>();

    // Initial color setup
    set_type(logger::LOG_TYPE::LOGT_DEFAULT);   // Setting default text color
    QPalette palette;
    palette.setColor(QPalette::Base, _background_color);
    setPalette(palette);    // Setting default background color
    // Color settings <--

    // --> QTextEdit settings
    setReadOnly(true); // Disable writing
    // QTextEdit settings <--
}

console_out::~console_out()
{

}

void console_out::set_type(logger::LOG_TYPE type)
{
    switch (type)
    {
        case logger::LOG_TYPE::LOGT_ERROR:
            setTextColor(_text_color_error);
            break;
        case logger::LOG_TYPE::LOGT_CRITICAL:
        setTextColor(_text_color_critical);
            break;
        case logger::LOG_TYPE::LOGT_WARNING:
        setTextColor(_text_color_warning);
            break;
        case logger::LOG_TYPE::LOGT_DEBUG:
        setTextColor(_text_color_debug);
            break;
        default:
        case logger::LOG_TYPE::LOGT_DEFAULT:
        setTextColor(_text_color_default);
            break;
    }
}

void console_out::add_log(QString s)
{
    insertPlainText(s);
}

console_out * console_out::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new console_out();
    }
    return _instance;
}

void console_out::receive_log(logger::LOG_TYPE type, QString s)
{
    set_type(type);
    QString typestr;
    switch (type)
    {
    case logger::LOG_TYPE::LOGT_WARNING:
        typestr.append("Warning: ");
    break;
    case logger::LOG_TYPE::LOGT_DEBUG:
        typestr.append("Debug: ");
    break;
    case logger::LOG_TYPE::LOGT_ERROR:
        typestr.append("Error: ");
    break;
    case logger::LOG_TYPE::LOGT_CRITICAL:
        typestr.append("Critical: ");
    break;
    default:
    case logger::LOG_TYPE::LOGT_DEFAULT:
    break;
    }
    add_log(typestr);
    set_type(logger::LOG_TYPE::LOGT_DEFAULT);
    add_log(s);

}
