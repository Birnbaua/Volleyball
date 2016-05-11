#ifndef QUALIFYINGGAMES_H
#define QUALIFYINGGAMES_H

#include <QObject>
#include <QTableView>
#include <QTime>

#include "database.h"
#include "calculateresults.h"

class QualifyingGames : public QObject
{
    Q_OBJECT
public:
    explicit QualifyingGames(Database *db, QStringList *grPrefix);
    ~QualifyingGames();

    void setParameters(QString startTurnier, int countSatz, int minSatz,
                   int minPause, int fieldCount, int teamsCount, QStringList *fieldNames);
    void clearAllData();
    void generateGames();
    void calculateResult();
    void recalculateTimeSchedule(QTableView *qtv, QSqlTableModel *model);
    QStringList checkEqualDivisionResults();

signals:
    void logMessages(QString);

private:
    void writeToDb(QStringList *querys);
    QList<QStringList> generateDivisionGames(QStringList *divisionList);
    QStringList generateGamePlan(QList<QList<QStringList> > *divisionsGameList, int gamesCount, QTime tournamentStart, int satz, int min, int pause);
    QStringList insertFieldNr(int gameCount, int fieldCount);
    QStringList insertFieldNames();
    QStringList generateResultTables(QList<QStringList> *divisionsList);

    QString startTurnier;
    bool first;
    int satz, min, pause, fieldCount, teamsCount;
    QStringList *grPrefix, *fieldNames, tablesToClear;
    QList<QList<int> > firstFourMsDivision, fourMsDivision, fiveMsDivision;
    Database *db;
};

#endif // QUALIFYINGGAMES_H
