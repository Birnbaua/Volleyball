#ifndef BASEGAMEHANDLING_H
#define BASEGAMEHANDLING_H

#include <QObject>
#include <QTableView>
#include <QTime>

#include "database.h"
#include "calculateresults.h"

class BaseGameHandling : public QObject
{
    Q_OBJECT
public:
    explicit BaseGameHandling(Database *db, QStringList *grPrefix);
    ~BaseGameHandling();

    void clearAllData(QStringList tables);

    QStringList insertFieldNr(QString round, int gameCount, int fieldCount);

    QStringList insertFieldNames(QString round, QStringList *fieldnames);

    QStringList generateResultTables(QString round, QList<QStringList> *divisionsList);

    void recalculateTimeSchedule(QTableView *qtv, QSqlTableModel *model);

    QStringList checkEqualDivisionResults(QString round, QString resultTableName);

    void calculateResult(QString round, QString resultTableName);

    QList<QStringList> dbRead(QString query);

    void dbWrite(QStringList *querys);

    QString getPrefix(int index);

    int getPrefixCount();

signals:
    void logMessages(QString);

private:
    Database *db;
    QString startRound;
    int satz, min, pause;
    QStringList *grPrefix;
};

#endif // BASEGAMEHANDLING_H
