#ifndef CROSSGAMES_H
#define CROSSGAMES_H

#include <QObject>
#include <QTableView>

#include "database.h"

class CrossGames : public QObject
{
    Q_OBJECT
public:
    explicit CrossGames(Database *db, QStringList *grPrefix = 0, QObject *parent = 0);
    ~CrossGames();

    void setParameters(QString startRound, int lastgameTime, int pauseZwKr, int countSatz, int minSatz, int minPause, int fieldCount, int teamsCount, QStringList *fieldNames, int lastRoundNr, int lastGameNr);
    void clearAllData();
    void generateCrossGames();
    void recalculateTimeSchedule(QTableView *qtv, QSqlTableModel *model);

signals:
    void logMessages(QString);

private:
    void writeToDb(QStringList *querys);
    QString intToStr(int nbr);
    QStringList insertFieldNames();
    QStringList getDivisionTeamNames(const QList<QStringList> *list);
    QStringList generateGamePlan(QTime startRound);

    QStringList *grPrefix, *fieldNames, tablesToClear;
    int satz, min, pause, fieldCount, teamsCount, lastGameNr, lastRoundNr;
    QString startRound;
    Database *db;
};

#endif // CROSSGAMES_H
