#ifndef AUDIO_H
#define AUDIO_H

#include <QObject>
#include <jblgo2driver.h>

class Audio
{
    //Q_OBJECT
public:
    Audio();
    void play();

private:
    JBLGO2driver speaker;

signals:

public slots:
};

#endif // AUDIO_H
