#ifndef _INC_SERVER_H
#define _INC_SERVER_H

#include <QThread>
#include <QObject>
#include <QMutex>

class Server : public QThread
{
    Q_OBJECT
    bool _run;
    QMutex _mutex;
    ~Server();
public:
    void run() override;
    Server(QObject *parent = 0);

signals:
    void emitStop(QObject *obj);
private slots:
    void stop();
};

#endif // _INC_SERVER_H
