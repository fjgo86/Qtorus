#ifndef _INC_CONSOLE_IN_H
#define _INC_CONSOLE_IN_H

#include <QLineEdit>
#include <QColor>

/*
 * @brief Handles the keyboard input
*/

class console_in : public QLineEdit
{
    Q_OBJECT
    static console_in *_instance; // Sinleton pattern, only one instance can exist.
    console_in();

    QColor background_color;
    QColor text_color_default;
public:
    ~console_in();
    static console_in *getInstance(); // retrieves the instance.
    //bind(server *serv); // TODO: Binds this console handler to the main server to send and interpret the data written.

signals:
public slots:
};


#endif // _INC_CONSOLE_IN_H
