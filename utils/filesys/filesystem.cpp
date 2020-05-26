#include "filesystem.h"

#include <QDir>
#include <QFileInfo>
#include <QStringList>
#include <QDebug>

QString concatPath(QString dir, QString path)
{
    return QDir::cleanPath(QDir(dir).absolutePath())+"/"+path;
}

bool checkFile(QString filename)
{
    return QFileInfo(filename).exists();
}

bool checkDirectory(QString dirname)
{
    return QDir(dirname).exists();
}

void createDirectory(QString dirname)
{
    if (checkDirectory(dirname)) return;
    //
    QDir dir(dirname);
    QStringList dirs = dir.absolutePath().split("/");
    QString curdirstr;
    for ( int i=0; i<dirs.size(); i++ ) {
        if ( dirs[i]!="." && dirs[i].size()>0 ) {
            curdirstr += "/"+dirs[i];
            if ( dirs[i]!=".." ) {
                QString curdirabs = QFileInfo(curdirstr).absoluteFilePath();
                QDir curdir(curdirabs);
                if ( !curdir.exists() ) {
                    qDebug() << "Creating directory:" << QFileInfo(curdirabs).absoluteFilePath();
                    dir.mkdir( QFileInfo(curdirabs).absoluteFilePath() );
                }
            }
        }
    }
}

void checkAndCreateDirectory(QString dirname)
{
    if ( !checkDirectory(dirname) ) {
        createDirectory(dirname);
    }
}


void checkAndCreateFileDir(QString filename)
{
    QFileInfo fi(filename);
    QString dirpath = fi.absoluteDir().absolutePath();
    if ( !checkDirectory(dirpath) ) {
        createDirectory(dirpath);
    }
}

void clearDir(QString dirname)
{
    //TODO
}

QVector<QString> createDirList(QString dirname, QString filter)
{
    QVector<QString> internalDirs;
    QDir dir(dirname);
    QVector<QFileInfo> allfiles = dir.entryInfoList().toVector();
    for ( int i=0; i<allfiles.size(); i++ ) {
        if ( !allfiles[i].isDir() ) continue;
        if ( !allfiles[i].baseName().size() ) continue;
        if (filter.size()==0 || !allfiles[i].baseName().contains(filter) ) {
            internalDirs.append(allfiles[i].absoluteFilePath());
        }
    }
    return internalDirs;
}

QVector<QString> createFileList(QString dirname, QString suffix, QString filter)
{
    QVector<QString> files;
    QDir dir(dirname);
    QVector<QFileInfo> allfiles = dir.entryInfoList().toVector();
    for ( int i=0; i<allfiles.size(); i++ ) {
        if ( allfiles[i].suffix()==suffix && (filter.size()==0 || !allfiles[i].baseName().contains(filter)) ) {
            files.append(allfiles[i].absoluteFilePath());
        }
    }
    return files;
}

QVector<QString> createFileList(QString dirname, QString suffix, QVector<QString> filters)
{
    QVector<QString> files;
    QDir dir(dirname);
    QVector<QFileInfo> allfiles = dir.entryInfoList().toVector();
    for ( int i=0; i<allfiles.size(); i++ ) {
        if ( allfiles[i].suffix()==suffix ) {
            bool insertFile = true;
            for ( int j=0; j<filters.size(); j++ ) {
                if ( allfiles[i].baseName().contains(filters[j]) ) {
                    insertFile = false;
                    break;
                }
            }
            if ( insertFile ) {
                files.append(allfiles[i].absoluteFilePath());
            }
        }
    }
    return files;
}

QVector<QString> createFileList(QString dirname, QVector<QString> suffixes)
{
    QVector<QString> files;
    QDir dir(dirname);
    QVector<QFileInfo> allfiles = dir.entryInfoList().toVector();
    for ( int i=0; i<allfiles.size(); i++ ) {
        if ( suffixes.contains(allfiles[i].suffix()) ) {
            files.append(allfiles[i].absoluteFilePath());
        }
    }
    return files;
}

void scanDir(QString dirname, QVector<QString> &suffixes, QVector<QString> &files)
{
    QDir dir(dirname);
    dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    //qDebug() << "Scanning: " << dir.path();
    QVector<QFileInfo> allfiles = dir.entryInfoList().toVector();
    for ( int i=0; i<allfiles.size(); i++ ) {
        if ( suffixes.contains(allfiles[i].suffix()) ) {
            files.append(allfiles[i].absoluteFilePath());
        }
    }
    dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    QStringList dirList = dir.entryList();
    for ( int i=0; i<dirList.size(); ++i ) {
        QString newPath = concatPath(dir.absolutePath(), dirList.at(i));
        scanDir(newPath, suffixes, files);
    }
}

QVector<QString> createFileListRecursively(QString dirname, QVector<QString> &suffixes)
{
    QVector<QString> files;
    scanDir(dirname, suffixes, files);
    return files;
}
