#ifndef INTERIMGAMES_H
#define INTERIMGAMES_H

#include <QObject>
#include <QTableView>
#include <QTime>

#include "database.h"
#include "calculateresults.h"

class InterimGames : public QObject
{
    Q_OBJECT
public:
    explicit InterimGames(Database *db, QStringList *grPrefix);
    ~InterimGames();

    void setParameters(QString startRound, int pauseVrZw, int countSatz, int minSatz, int minPause,
                       int fieldCount, int teamsCount, QStringList *fieldNames, int lastRoundNr, int lastGameNr);
    void clearAllData();
    bool generateGames();
    void calculateResult();
    void recalculateTimeSchedule(QTableView *qtv, QSqlTableModel *model);
    QStringList checkEqualDivisionResults();

signals:
    void logMessages(QString);
    void doubleResultsOverDivisions();

private:
    void writeToDb(QStringList *querys);
    QStringList generateResultTables(QList<QStringList> *divisionsList);
    QStringList insertFieldNames();
    QStringList insertFieldNr(int gameCount, int fieldCount);
    QStringList generateGamePlan(QList<QList<QStringList> > *divisionsGameList, int gamesCount, QTime startRound, int lastRoundNr, int lastGameNr, int satz, int min, int pause);
    QList<QStringList> generateDivisionGames(QStringList *divisionList);
    QList<QStringList> generateNewDivisions();
    QList<QStringList> getDivisionsClassement(QList<QList<QStringList> > *divisionsClassements, int rank);
    QStringList getTeamList(QList<QStringList> *teamsDivisions);
    bool checkListDoubleResults(QList<QStringList> *list);
    void sortList(QList<QStringList> *sortList);

    QString startRound;
    bool first;
    int satz, min, pause, fieldCount, teamsCount, lastGameNr, lastRoundNr;
    QStringList *grPrefix, *fieldNames, tablesToClear;
    QList<QList<int> > firstFourMsDivision, fourMsDivision, fiveMsDivision;
    Database *db;
};

#endif // INTERIMGAMES_H
