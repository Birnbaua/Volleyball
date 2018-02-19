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
    QSqlTableModel* createSqlTableModel(QString tableName, QStringList *columnName);
    bool commitSqlTableModel(QSqlTableModel *model);

signals:
    void log(QString);

private:
    QSqlDatabase db;
    QSqlQuery *q;
};

#endif // DATABASE_H
