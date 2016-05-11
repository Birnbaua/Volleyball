#ifndef CLASSEMENTGAMES_H
#define CLASSEMENTGAMES_H

#include <QObject>
#include <QTableView>

#include "database.h"
#include "calculateresults.h"

class ClassementGames : public QObject
{
    Q_OBJECT
public:
    explicit ClassementGames(Database *db = 0, QStringList *grPrefix = 0, QObject *parent = 0);
    ~ClassementGames();

    void setParameters(QString startRound, int lastgameTime, int pauseKrPl, int countSatz, int minSatz, int fieldCount, int teamsCount, QStringList *fieldNames, int lastRoundNr, int lastGameNr);
    void clearAllData();
    void generateClassementGames();
    void recalculateTimeSchedule(QTableView *qtv, QSqlTableModel *model);
    void finalTournamentResults();

signals:
    void logMessages(QString);

private:
    QStringList generateGamePlan(QTime startRound, QList<QStringList> *krGameResults);
    QStringList insertFieldNames();
    QStringList createClassement(QList<QStringList> *plGameResults);
    void writeToDb(QStringList *querys);
    QString intToStr(int nbr);

    QList<QList<int> > classements;
    QStringList *grPrefix, *fieldNames, tablesToClear;
    int satz, min, pause, fieldCount, teamsCount, lastGameNr, lastRoundNr;
    QString startRound;
    Database *db;
};

#endif // CLASSEMENTGAMES_H
