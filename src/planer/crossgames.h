#ifndef CROSSGAMES_H
#define CROSSGAMES_H

#include "basegamehandling.h"

class CrossGames : public BaseGameHandling
{
    Q_OBJECT
public:
    explicit CrossGames(Database *db, QStringList *grPrefix);
    ~CrossGames();

    void setParameters(QString startRound, int lastgameTime, int pauseZwKr, int countSatz, int minSatz, int minPause, int fieldCount, int teamsCount, QStringList *fieldNames, int lastRoundNr, int lastGameNr);

    void generateCrossGames();

signals:
    void logMessages(QString);

private:
    QStringList getDivisionTeamNames(const QList<QStringList> *list);
    QStringList generateGamePlan(QTime startRound);

    QString startRound;
    int prefixCount, fieldCount, teamsCount, gamesCount;
    int satz, min, pause, lastGameNr, lastRoundNr;
    QStringList *grPrefix, *fieldNames;
};

#endif // CROSSGAMES_H
