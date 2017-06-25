#ifndef INTERIMGAMES_H
#define INTERIMGAMES_H

#include "basegamehandling.h"

class InterimGames : public BaseGameHandling
{
    Q_OBJECT
public:
    explicit InterimGames(Database *db, QStringList *grPrefix);
    ~InterimGames();

    void setParameters(QString startRound, int pauseVrZw, int countSatz, int minSatz, int minPause,
                       int fieldCount, int teamsCount, int divisionCount, QStringList *fieldNames, int lastRoundNr, int lastGameNr, int bettyspiele);

    bool generateGames();

signals:
    void doubleResultsOverDivisions();

private:
    QStringList generateGamePlan(QList<QList<QStringList> > *divisionsGameList, int gamesCount, QTime startRound, int lastRoundNr, int lastGameNr, int satz, int min, int pause);
    QList<QStringList> generateDivisionGames(QStringList *divisionList);
    QList<QStringList> generateNewDivisions();
    QList<QStringList> getDivisionsClassement(QList<QList<QStringList> > *divisionsClassements, int rank);
    QStringList getTeamList(QList<QStringList> *teamsDivisions);
    bool checkListDoubleResults(QList<QStringList> *list);
    void sortList(QList<QStringList> *sortList);

    QString startRound;
    bool first;
    int prefixCount, fieldCount, teamsCount, gamesCount, divisionCount;
    int satz, min, pause, lastGameNr, lastRoundNr, bettyspiele;
    QStringList *grPrefix, *fieldNames;
    QList<QList<int> > firstFourMsDivision, fourMsDivision, fiveMsDivision;
};

#endif // INTERIMGAMES_H
