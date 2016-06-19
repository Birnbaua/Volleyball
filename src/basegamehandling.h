#ifndef BASEGAMEHANDLING_H
#define BASEGAMEHANDLING_H

#include <QObject>

#include "database.h"

class BaseGameHandling : public QObject
{
    Q_OBJECT
public:
    explicit BaseGameHandling(QObject *parent = 0);

    void clearAllData(QStringList tables);
    void insertFieldNr(int gameCount, int fieldCount);
    void insertFieldNames();
    void generateResultTables(QList<QStringList> *divisionsList);
    void writeToDB(QStringList *querys);

private:
    Database *db;
    QString startRound;
    int satz, min, pause, fieldCount, teamsCount;
    QStringList *grPrefix, *fieldNames, tablesToClear;
};

#endif // BASEGAMEHANDLING_H
