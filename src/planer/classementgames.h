#ifndef CLASSEMENTGAMES_H
#define CLASSEMENTGAMES_H

#include "basegamehandling.h"
#include "calculateresults.h"

class ClassementGames : public BaseGameHandling
{
    Q_OBJECT
public:
    explicit ClassementGames(Database *db, QStringList *grPrefix);
    ~ClassementGames();

    void setParameters(QString startRound, int lastgameTime, int pauseKrPl, int countSatz, int minSatz, int fieldCount, int teamsCount, int divisionCount, QStringList *fieldNames, int lastRoundNr, int lastGameNr, int bettyspiele);

    void generateClassementGames();

    void finalTournamentResults();

private:
    QStringList generateGamePlan(QTime startRound);
    QStringList createClassement();

    QList<QStringList> krGameResults, plGameResults;
    QList<int> classements;
    QString startRound;
    int prefixCount, fieldCount, teamsCount, gamesCount, divisionCount, bettyspiele;
    int satz, min, pause, lastGameNr, lastRoundNr;
    QStringList *grPrefix, *fieldNames;
};

#endif // CLASSEMENTGAMES_H
