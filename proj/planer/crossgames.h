#ifndef CROSSGAMES_H
#define CROSSGAMES_H

#include "basegamehandling.h"

class CrossGames : public BaseGameHandling
{
    Q_OBJECT
public:
    explicit CrossGames(Database *db, QStringList *grPrefix);
    ~CrossGames();

    void setParameters(QString startRound, int lastgameTime, int pauseZwKr, int countSatz, int minSatz, int minPause, int fieldCount, int teamsCount, int divisionCount, QStringList *fieldNames, int lastRoundNr, int lastGameNr, int bettyspiele);

    void generateCrossGames();

private:
    QStringList getDivisionTeamNames(const QList<QStringList> *list);
    QStringList generateGamePlan(QTime startRound);

    QString startRound;
    int prefixCount, fieldCount, teamsCount, divisionCount, gamesCount, bettyspiele;
    int satz, min, pause, lastGameNr, lastRoundNr;
    QStringList *grPrefix, *fieldNames;
};

#endif // CROSSGAMES_H
