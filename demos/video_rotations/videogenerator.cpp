#include "videogenerator.h"

#include <QDir>


VideoGenerator::VideoGenerator(QObject *par)
    : QObject(par)
{
    QObject::connect(&m_process, SIGNAL(finished(int,QProcess::ExitStatus)),
                     this, SLOT(finished()));
    QObject::connect(&m_process, SIGNAL(readyReadStandardOutput()),
                     this, SLOT(readProcessOutput()));
    //
    m_exec = "/usr/local/bin/ffmpeg";
    m_args = QStringList( { "-r", "5", "-i",
                            QDir::toNativeSeparators("out/%03d.png"),
                            "-c:v",
                            "libx264", "-vf", "fps=25", "-pix_fmt",
                            "yuv420p", "-y",
                            QDir::toNativeSeparators("out/out.mp4") } );
}

VideoGenerator::~VideoGenerator(){

}

void VideoGenerator::run() {
    m_time.start();
    m_process.start(m_exec, m_args, QIODevice::ReadWrite);
    m_process.waitForFinished(-1);
}

void VideoGenerator::showReport() {
    qDebug() << "Process name:" << m_exec;
    qDebug() << "Process args:" << m_args;
    qDebug() << "Processing time:" << m_procTime;
    qDebug() << "Process output: "<< m_out;
    qDebug() << "Output validtion: " << (m_out==m_val);
}

void VideoGenerator::finished() {
    m_procTime = m_time.elapsed();
}

void VideoGenerator::readProcessOutput() {
    m_out = QString(m_process.readAllStandardOutput());
}
