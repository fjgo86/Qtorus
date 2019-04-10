#include "gui.h"
#include "console_in.h"
#include "console_out.h"
#include "../logger/logger.h"
#include <QBoxLayout>

gui::gui(QWidget *parent) : QWidget(parent)
{
    mainbox = new QHBoxLayout(this);

    console = new QVBoxLayout();
    mainbox->addLayout(console);

    console_out *consout = console_out::getInstance();
    console_in *consin = console_in::getInstance();
    logger * log = logger::getInstance();

    console->addWidget(consout);
    console->addWidget(consin);
    log->bind(consout);

}
