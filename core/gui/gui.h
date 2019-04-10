#ifndef _INC_GUI_H
#define _INC_GUI_H

#include <QWidget>

class QHBoxLayout;
class QVBoxLayout;

class gui : public QWidget
{
    Q_OBJECT

    QHBoxLayout *mainbox;
    QVBoxLayout *console;
public:
    gui(QWidget *parent = 0);
    ~gui(){

    }

signals:
public slots:
};

#endif // _INC_GUI_H
