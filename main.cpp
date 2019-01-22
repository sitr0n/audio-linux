#include <QCoreApplication>
#include <audio.h>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Audio audio;
    audio.play();
    audio.play();
    return a.exec();
}
