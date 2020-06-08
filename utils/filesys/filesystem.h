#ifndef QTUTILS_FILESYSTEM_H
#define QTUTILS_FILESYSTEM_H

#include <QString>
#include <QVector>

QString concatPath(QString dir, QString path);

bool checkFile(QString filename);

bool checkDirectory(QString dirname);
void createDirectory(QString dirname);
void checkAndCreateDirectory(QString dirname);

void checkAndCreateFileDir(QString filename);

void clearDir(QString dirname);

QVector<QString> createDirList(QString dirname, QString filter="");
QVector<QString> createFileList(QString dirname, QString suffix, QString filter="");
QVector<QString> createFileList(QString dirname, QString suffix, QVector<QString> filters);
QVector<QString> createFileList(QString dirname, QVector<QString> suffixes);

QVector<QString> createFileListRecursively(QString dirname, QString suffix);
QVector<QString> createFileListRecursively(QString dirname, QString suffix, QString filter);
QVector<QString> createFileListRecursively(QString dirname, QString suffix, QVector<QString> filters);
QVector<QString> createFileListRecursively(QString dirname, QVector<QString> &suffixes);

#endif // QTUTILS_FILESYSTEM_H
