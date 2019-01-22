#ifndef JBLGO2DRIVER_H
#define JBLGO2DRIVER_H

#include <QObject>
#include <QThread>
#include <QProcess>
#include <QVector>

class JBLGO2driver : public QThread
{
    Q_OBJECT
public:
    JBLGO2driver();
    ~JBLGO2driver();
    void play(QString file_name);

protected:
    virtual void run();

private:
    QProcess* m_player;
    bool m_is_running;
    bool m_is_ready;
    QVector<QString> m_queue;
signals:

public slots:

};

#endif // JBLGO2DRIVER_H
