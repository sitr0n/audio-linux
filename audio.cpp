#include "audio.h"
#include <QDebug>

Audio::Audio()
{
    qDebug() << "Audio started";
    speaker.start();
}

void Audio::play()
{
    speaker.play("blank.wav");
}
