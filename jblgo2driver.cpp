#include "jblgo2driver.h"
#include <QDebug>

JBLGO2driver::JBLGO2driver() :
    m_player(new QProcess()),
    m_is_running(false),
    m_is_ready(true)
{
    m_player->setWorkingDirectory("/home/pi/Music");
    connect(m_player, &QProcess::readyReadStandardError,
        [=](){
        QByteArray stream_output = m_player->readAllStandardError();
        auto lines = QString(stream_output).split("\n");
        for (auto& line: lines){
            if (line != "")
                qDebug() << "Audio stream: " << line;
        }
    });
    connect(m_player, QOverload<int, QProcess::ExitStatus>::of(&QProcess::finished),
        [=](int exit_code, QProcess::ExitStatus exit_status){
        qDebug() << "Exit status: " << exit_status;
        if (exit_code != 0) {
            qDebug() << "Unexpected error: " << exit_code;
            m_is_running = false;
        }
    });
}

JBLGO2driver::~JBLGO2driver()
{
    m_is_running = false;
    //TODO: Interrupt QWaitCondition to exit run thread
    m_player->waitForFinished();
    m_player->close();
    delete m_player;
    qDebug() << "Driver closed";
}

int num_loops = 0; // TEMP
void JBLGO2driver::run()
{
    m_is_running = true;
    while(m_is_running)
    {
        QString blank_file = "blank.wav";
        QString command = "aplay " + blank_file;
        qDebug() << command;
        m_player->start(command);
        m_player->waitForFinished();

        while(!m_queue.empty())
        {
            QString command = "aplay " + m_queue.front();
            m_queue.pop_front();
            qDebug() << command;
            m_player->start(command);
            m_player->waitForFinished();
        }
        QThread::sleep(600); //TODO: replace with QWaitCondition for clean shut down of thread
    }
    /*
    m_is_running = true;
    while(m_is_running)
    {
        qDebug() << num_loops++ << "Ping speaker";
        QString blank_file = "blank.wav";
        QString ping_bluetooth = "aplay " + blank_file;
        QProcess player;
        player.setWorkingDirectory("/home/pi/Music");
        player.start(ping_bluetooth);
        player.waitForFinished();
        player.close();

        QThread::sleep(600); //TODO: replace with QWaitCondition for clean shut down of thread
    }
    */
}

void JBLGO2driver::play(QString file_name)
{
    m_queue.push_back(file_name);
    //break run thread sleep

    /*
    m_player->waitForFinished();
    QString command = "aplay " + file_name;
    m_player->start(command);
    qDebug() << "play finished";
    */
}
