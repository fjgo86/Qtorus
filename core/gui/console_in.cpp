#include "console_in.h"
#include <QSettings>

console_in *console_in::_instance = nullptr;

console_in::console_in()
{
    // --> Color settings
    // Reading from QSettings
    QSettings settings;
    settings.beginGroup("console_in");
    _background_color = settings.value("background_color",QColor::fromRgb(0,0,0)).value<QColor>();               // Default black background
    _text_color_default = settings.value("text_color_default", QColor::fromRgb(255,255,255)).value<QColor>();    // Default white text color

    // Initial color setup
    QPalette palette;
    palette.setColor(QPalette::Base, _background_color);
    palette.setColor(QPalette::Text, _text_color_default);
    setPalette(palette);

    // Color settings <--
}

console_in::~console_in()
{

}

console_in *console_in::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new console_in();
    }
    return _instance;
}
