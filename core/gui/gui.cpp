#include "gui.h"
#include "console_in.h"
#include "console_out.h"
#include "../logger/logger.h"
#include <QBoxLayout>
#include <QSettings>

gui::gui(QWidget *parent) : QWidget(parent)
{
    // <-- Window settings
    QSettings settings;
    settings.beginGroup("gui");

    // Restoring window size
    int width = settings.value("width", 1024).value<int>();
    int height = settings.value("height", 768).value<int>();

    // setting window size
    QSize size(width, height);
    resize(size);
    // Window settings -->

    // <-- Creating main layouts
    _mainbox = new QHBoxLayout(this);
    _console = new QVBoxLayout();
    _mainbox->addLayout(_console);
    // main layouts <--

    // <-- Initializing & configuring consoles
    console_out *consout = console_out::getInstance();
    console_in *consin = console_in::getInstance();
    logger * log = logger::getInstance();

    _console->addWidget(consout);
    _console->addWidget(consin);
    log->bind(consout);

    // consoles -->

    // class' data:
    _isInitialized = false;
    connect(&_resizeTimer, SIGNAL(timeout()), this, SLOT(resizeDone()));

}

void gui::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    if (_isInitialized == false) // resize is called once in start
    {
        _isInitialized = true;  // once called, reflect it
        return;                 // and return
    }
    _resizeTimer.start(500);    // starts the timer or resets it until the resize has finished.
}

void gui::resizeDone()
{
    QSettings settings;
    settings.beginGroup("gui");
    settings.setValue("height", QWidget::height());
    settings.setValue("width", QWidget::width());
    settings.sync();
}
