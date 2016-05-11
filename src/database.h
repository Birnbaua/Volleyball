/****************************************************************************
**
** Copyright (C) 2015 cfr
** Description: adds database support for sqlite
** Contact:
** Version: 0.4
**
** Version 0.1  database handling for postgres and sqlite,
**              signals for error and log messages
** Version 0.2  add qsqlquerymodel and qsqltablemodel,
**              fix for log msg output if query error.nr = 0
** Version 0.3  use destructor to close database connection,
**              little code updates
** Version 0.4  fixed transaction/commit, added function for commit
**              qsqltablemodel data, add log message if commit fails
**
****************************************************************************/

#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class Database : public QObject
{
    Q_OBJECT
public:
    explicit Database(QString dbname = 0, QObject *parent = 0);
    ~Database();

    bool open();
    void write(QString query);
    QList<QStringList> read(QString query);
    QSqlQueryModel* createSqlQueryModel(QString query);
    QSqlTableModel* createSqlTableModel(QString tableName, QStringList columnName);
    bool commitSqlTableModel(QSqlTableModel *model);

signals:
    void log(QString);

private:
    QSqlDatabase db;
    QSqlQuery *q;
};

#endif // DATABASE_H
