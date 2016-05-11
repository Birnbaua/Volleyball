/****************************************************************************
**
** Copyright (C) 2015 cfeil
** Contact:
**
** Description:
** adds log support, write to database or file
**
** Version:
** v1.0 ... write logs to database table
**
** v1.1 ... add file log support, add timestamp
**
** v1.2 ... use destructor to close file if logtyp = file
**          little code updates
**
** v1.3 ... fixed timestamp day and year result,
**          fixed write logstring immediately to file with flush
**
****************************************************************************/

#ifndef LOGGING
#define LOGGING

#include <QTextStream>
#include <QDateTime>
#include <QFile>

#include "database_v1.3.h"

class logging : public QObject
{
    Q_OBJECT
public:
    logging()
    {
        // set type for logging, usually file log is default (false)
        logType = false;
        dbTable = "";
    }
    ~logging()
    {
        if(!logType)
            file.close();
    }

    // set db and table name for log
    bool setDbAsLogTarget(database *m_Db, QString dbTable)
    {
        if(dbTable != "")
        {
            this->m_Db = m_Db;
            this->dbTable = dbTable;
            logType = true;
            return true;
        }

        emit logLog("LOG_ERROR:: no database table defined, string is empty");
        return false;
    }

    // set file for log
    bool setFileAsLogTarget(QString fileName)
    {
        file.setFileName(fileName);

        if(file.open(QIODevice::Append | QIODevice::Text))
        {
            out.setDevice(&file);
            logType = false;
            return true;
        }

        emit logLog("LOG_ERROR:: can't open file to write log");
        return false;
    }

public slots:
    // write log to db or file
    void write(QString msg)
    {
        // logtype = file
        if(!logType)
        {
            // write log to file with current timestamp
            out << dt.currentDateTime().toString("dd.MM.yyyy hh:mm:ss.zzz") + " " << msg << "\n";
            out.flush();
            return;
        }

        // logtype = database
        m_Db->write("INSERT INTO " + dbTable + " VALUES(DEFAULT, CURRENT_TIMESTAMP, '" + msg + "')");
    }

signals:
    // send log msg
    void logLog(QString);

private:
    database *m_Db;
    QTextStream out;
    QFile file;
    QDateTime dt;
    QString dbTable;
    bool logType;
};
#endif // LOGGING
