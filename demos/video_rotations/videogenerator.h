#ifndef VIDEOGENERATOR_H
#define VIDEOGENERATOR_H

#include <QObject>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QTime>
#include <QDebug>

class VideoGenerator : public QObject
{
    Q_OBJECT

private:
    QString m_exec;
    QStringList m_args;
    QString m_val;

    QProcess m_process;
    QTime m_time;
    int m_procTime;
    QString m_out;

public:
    VideoGenerator(QObject *par = nullptr);

    virtual ~VideoGenerator();

    void run();

    void showReport();


public slots:
    void finished();

    void readProcessOutput();
};

#endif // VIDEOGENERATOR_H
