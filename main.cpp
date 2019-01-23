#include <QCoreApplication>
#include <audio.h>
#include <QThread>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Audio audio;
    audio.queue("medicine.wav");
    audio.queue("weback.wav");
    return a.exec();
}
