#ifndef _INC_GUI_H
#define _INC_GUI_H

#include <QWidget>
#include <QResizeEvent>
#include <QTimer>

class QHBoxLayout;
class QVBoxLayout;

class gui : public QWidget
{
    Q_OBJECT

    QHBoxLayout *_mainbox;
    QVBoxLayout *_console;

    QTimer _resizeTimer;
    bool _isInitialized;
public:
    gui(QWidget *parent = 0);
    ~gui(){

    }
protected:
    /*
     * @brief overriden resizeEvent
     *
     * @param * the QResizeEvent handler
     *
     * This method overrides default resize event to allow the new size to be saved with QSettings
    */
    virtual void resizeEvent(QResizeEvent *) override;

signals:
private slots:
    void resizeDone();
};

#endif // _INC_GUI_H
