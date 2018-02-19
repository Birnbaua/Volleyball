#ifndef QUALIFYINGGAMES_H
#define QUALIFYINGGAMES_H

#include "basegamehandling.h"

class QualifyingGames : public BaseGameHandling
{
    Q_OBJECT
public:
    explicit QualifyingGames(Database *db, QStringList *grPrefix);
    ~QualifyingGames();

    void setParameters(QString startTurnier, int countSatz, int minSatz,
                   int minPause, int fieldCount, int teamsCount, QStringList *fieldNames);

    void generateGames();

private:
    QList<QStringList> generateDivisionGames(QStringList *divisionList);
    QStringList generateGamePlan(QList<QList<QStringList> > *divisionsGameList, int gamesCount, QTime tournamentStart, int satz, int min, int pause);

    QString startTurnier;
    bool first;
    int prefixCount, fieldCount, teamsCount, gamesCount;
    int satz, min, pause;
    QStringList *grPrefix, *fieldNames;
    QList<QList<int> > firstFourMsDivision, fourMsDivision, fiveMsDivision;
};

#endif // QUALIFYINGGAMES_H
