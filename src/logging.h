/****************************************************************************
**
** Copyright (C) 2015 cfr
** Description: adds log support, write to file
** Contact:
** Version: 0.4
**
** Version 0.1  write logs to database table
** Version 0.2  add file log support, add timestamp
** Version 0.3  use destructor to close file if logtyp = file
**              little code updates
** Version 0.4  fixed timestamp day and year result,
**              fixed write logstring immediately to file with flush
**
****************************************************************************/

#ifndef LOGGING_H
#define LOGGING_H

#include <QObject>
#include <QTextStream>
#include <QDateTime>
#include <QFile>

class Logging : public QObject
{
    Q_OBJECT
public:
    explicit Logging(QString filename = 0, QObject *parent = 0);
    ~Logging();

public slots:
    void write(QString message);

signals:
    void log(QString);

private:
    QTextStream out;
    QFile file;
    QDateTime dt;
};

#endif // LOGGING_H
