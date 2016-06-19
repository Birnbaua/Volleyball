#ifndef BASEGAMEHANDLING_H
#define BASEGAMEHANDLING_H

#include <QObject>
#include <QTableView>
#include <QTime>

#include "database.h"

class BaseGameHandling : public QObject
{
    Q_OBJECT
public:
    explicit BaseGameHandling(Database *db,
                              QStringList *grPrefix,
                              QStringList *fieldNames,
                              int fieldcount,
                              int teamsCount);

    void clearAllData(QStringList tables);
    QStringList insertFieldNr(QString round, int gameCount);
    QStringList insertFieldNames(QString round);
    QStringList generateResultTables(QString round, QList<QStringList> *divisionsList);
    void writeToDB(QStringList *querys);
    void recalculateTimeSchedule(QTableView *qtv, QSqlTableModel *model);
    QStringList checkEqualDivisionResults(QString round, QString resultTableName);

signals:
    void logMessages(QString);

private:
    Database *db;
    QString startRound;
    int satz, min, pause, fieldCount, teamsCount;
    QStringList *grPrefix, *fieldNames, tablesToClear;
};

#endif // BASEGAMEHANDLING_H
