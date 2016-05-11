#include "database.h"

Database::Database(QString dbname, QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(dbname);
}

Database::~Database()
{
    q->finish();
    db.close();
}

bool Database::open()
{
    // try open db
    if(!db.open())
    {
        emit log("DB_ERROR:: " + db.lastError().text());
        return false;
    }

    // create sqlquery from db connection
    q = new QSqlQuery(db);

    return true;
}

void Database::write(QString query)
{
    // execute statement
    emit log("DB_STATEMENT:: " + query);
    q->exec(query);

    // emit error if problems occur
    if(q->lastError().number() > 0)
        emit log("DB_ERROR:: " + q->lastError().text());
}

QList<QStringList> Database::read(QString query)
{
    QList<QStringList> result;

    // execute statement
    emit log("DB_STATEMENT:: " + query);
    q->exec(query);

    // emit error if problems occur
    if(q->lastError().number() > 0)
        emit log("DB_ERROR:: " + q->lastError().text());

    // read from result until end
    while(q->next())
    {
        QStringList slist;
        QSqlRecord r = q->record();

        // iterate through all columns and add values to stringlist
        for(int i = 0; i < r.count(); i++)
            slist << r.value(i).toString();

        result.append(slist);
    }

    return result;
}

QSqlQueryModel *Database::createSqlQueryModel(QString query)
{
    QSqlQueryModel *model = new QSqlQueryModel();

    // set query
    emit log("DB_STATEMENT:: " + query);
    model->setQuery(query);

    // emit error if problems occur
    if(model->lastError().number() > 0)
        emit log("DB_ERROR:: " + model->lastError().text());

    return model;
}

QSqlTableModel* Database::createSqlTableModel(QString tableName, QStringList columnName)
{
    int i = 0;
    QSqlTableModel *model = new QSqlTableModel();

    // set table, edit strategy to manual submit
    model->setTable(tableName);
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->select();

    // emit error if problems occur
    if(model->lastError().number() > 0)
        emit log("DB_ERROR:: " + model->lastError().text());

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

bool Database::commitSqlTableModel(QSqlTableModel *model)
{
    // because of manual submit use transactions
    model->database().transaction();

    if(model->submitAll())
    {
        model->database().commit();
        return true;
    }

    emit log("DB_ERROR:: " + model->lastError().text());
    model->database().rollback();

    return false;
}
