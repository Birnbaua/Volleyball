/****************************************************************************
**
** Copyright (C) 2015 cfeil
** Contact:
**
** Description:
** adds database support for postgres and sqlite
**
** Version:
** v1.0 ... database handling for postgres and sqlite,
**          signals for error and log messages
**
** v1.1 ... add qsqlquerymodel and qsqltablemodel,
**          fix for log msg output if query error.nr = 0
**
** v1.2 ... use destructor to close database connection,
**          little code updates
**
** v1.3 ... fixed transaction/commit, added function for commit
**          qsqltablemodel data, add log message if commit fails
**
****************************************************************************/

#ifndef DATABASE
#define DATABASE

#include <QtSql>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class database : public QObject
{
    Q_OBJECT
public:
    database()
    {
        dbTypChoosen = false;
    }
    ~database()
    {
        db.close();
    }

    // database is postgres
    void dbIsPsql(QString dbName, QString host, QString user, QString pw, int port)
    {
        db = QSqlDatabase::addDatabase("QPSQL");
        db.setDatabaseName(dbName);
        db.setHostName(host);
        db.setUserName(user);
        db.setPassword(pw);
        db.setPort(port);
        dbTypChoosen = true;
    }

    // database is sqlite
    void dbIsSqlite(QString dbName)
    {
        db = QSqlDatabase::addDatabase("QSQLITE");
        db.setDatabaseName(dbName);
        dbTypChoosen = true;
    }

    // open database, return true if db open successfull
    bool openDb()
    {
        // if db type not chosen, don't open db
        if(!dbTypChoosen)
        {
            emit dbError("DB_ERROR:: choose db type before open");;
            return false;
        }

        // try open db
        if(!db.open())
        {
            emit dbError("DB_ERROR:: " + db.lastError().text());
            return false;
        }

        // create sqlquery from db connection
        q = new QSqlQuery(db);

        return true;
    }

    // write statement to db
    void write(QString query)
    {
        // execute statement
        emit dbLog("DB_STATEMENT:: " + query);
        q->exec(query);
        
        // emit error if problems occur
        if(q->lastError().number() > 0)
            emit dbError("DB_ERROR:: " + q->lastError().text());
    }

    // read statement from db, return result as list
    QList<QStringList> read(QString query)
    {
        QList<QStringList> list;

        // execute statement
        emit dbLog("DB_STATEMENT:: " + query);
        q->exec(query);

        // emit error if problems occur
        if(q->lastError().number() > 0)
            emit dbError("DB_ERROR:: " + q->lastError().text());

        // read from result until end
        while(q->next())
        {
            QStringList slist;
            QSqlRecord r = q->record();

            // iterate through all columns and add values to stringlist
            for(int i = 0; i < r.count(); i++)
                slist << r.value(i).toString();

            list.append(slist);
        }

        return list;
    }

    // return sqlquerymodel from statement
    QSqlQueryModel* createSqlQueryModel(QString query)
    {
        QSqlQueryModel *model = new QSqlQueryModel(this);

        // set query
        emit dbLog("DB_STATEMENT:: " + query);
        model->setQuery(query);

        // emit error if problems occur
        if(model->lastError().number() > 0)
            emit dbError("DB_ERROR:: " + model->lastError().text());

        return model;
    }

    // create sqltablemodel from statment and column names
    QSqlTableModel* createSqlTableModel(QString tableName, QStringList columnName)
    {
        int i = 0;
        QSqlTableModel *model = new QSqlTableModel(this);

        // set table, edit strategy to manual submit
        model->setTable(tableName);
        model->setEditStrategy(QSqlTableModel::OnManualSubmit);
        model->select();

        // emit error if problems occur
        if(model->lastError().number() > 0)
            emit dbError("DB_ERROR:: " + model->lastError().text());

        if(!columnName.isEmpty())
        {
            // set column header names
            foreach(QString column, columnName)
            {
                model->setHeaderData(i, Qt::Horizontal, column);
                i++;
            }
        }

        return model;
    }

    // commit sqltablemodel changes to database
    bool commitSqlTableModel(QSqlTableModel *model)
    {
        // because of manual submit use transactions
        model->database().transaction();

        if(model->submitAll())
        {
            model->database().commit();
            return true;
        }

        emit dbError("DB_ERROR:: " + model->lastError().text());
        model->database().rollback();

        return false;
    }

signals:
    // send log msg
    void dbLog(QString);

    // send error msg
    void dbError(QString);

private:
    QSqlDatabase db;
    QSqlQuery *q;
    bool dbTypChoosen;
};
#endif // DATABASE
