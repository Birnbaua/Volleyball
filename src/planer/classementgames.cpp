#include "classementgames.h"

ClassementGames::ClassementGames(Database *db, QStringList *grPrefix)
    : BaseGameHandling(db, grPrefix)
{
}

ClassementGames::~ClassementGames()
{
}

// set platzspiele params
void ClassementGames::setParameters(QString startRound, int lastgameTime, int pauseKrPl,
                                    int countSatz, int minSatz, int fieldCount, int teamsCount,
                                    QStringList *fieldNames, int lastRoundNr, int lastGameNr)
{
    emit logMessages("PLATZSPIELE:: set platzspiele params");
    this->startRound = startRound;
    this->satz = countSatz;
    this->min = minSatz;
    this->pause = 0;
    this->fieldCount = fieldCount;
    this->teamsCount = teamsCount;
    this->fieldNames = fieldNames;
    this->lastGameNr = lastGameNr;
    this->lastRoundNr = lastRoundNr;

    setTimeParameters(satz, min, pause);

    QTime time = QTime::fromString(this->startRound, "hh:mm");
    time = time.addSecs((pauseKrPl * 60) + (lastgameTime * 60));
    this->startRound = time.toString("hh:mm");

    switch(teamsCount)
    {
        case 20:
        case 25: classements = QList<int>()
                             << 9 << 10 << 19 << 20
                             << 7 << 8 << 17 << 18
                             << 5 << 6 << 15 << 16
                             << 3 << 4 << 13 << 14 << 23 << 24
                             << 11 << 12 << 21 << 22
                             << 1 << 2;
            break;

        case 28: classements = QList<int>()
                             << 9 << 10 << 19 << 20
                             << 7 << 8 << 17 << 18 << 27 << 28
                             << 5 << 6 << 15 << 16 << 25 << 26
                             << 3 << 4 << 13 << 14 << 23 << 24
                             << 11 << 12 << 21 << 22
                             << 1 << 2;
            break;

        case 30:
        case 35: classements = QList<int>()
                             << 9 << 10 << 19 << 20 << 29 << 30
                             << 7 << 8 << 17 << 18 << 27 << 28
                             << 5 << 6 << 15 << 16 << 25 << 26
                             << 3 << 4 << 13 << 14 << 23 << 24
                             << 11 << 12 << 21 << 22
                             << 1 << 2;
            break;

        case 40:
        case 45: classements = QList<int>()
                             << 9 << 10 << 19 << 20 << 29 << 30 << 39 << 40
                             << 7 << 8 << 17 << 18 << 27 << 28 << 37 << 38
                             << 5 << 6 << 15 << 16 << 25 << 26 << 35 << 36
                             << 3 << 4 << 13 << 14 << 23 << 24 << 33 << 34
                             << 11 << 12 << 21 << 22 << 31 << 32
                             << 1 << 2;
            break;

        case 50: classements = QList<int>()
                         << 9 << 10 << 19 << 20 << 29 << 30 << 39 << 40 << 49 << 50
                         << 7 << 8 << 17 << 18 << 27 << 28 << 37 << 38 << 47 << 48
                         << 5 << 6 << 15 << 16 << 25 << 26 << 35 << 36 << 45 << 46
                         << 3 << 4 << 13 << 14 << 23 << 24 << 33 << 34 << 43 << 44
                         << 11 << 12 << 21 << 22 << 31 << 32 << 41 << 42
                         << 1 << 2;
            break;

        case 55: classements = QList<int>()
                         << 9 << 10 << 19 << 20 << 29 << 30 << 39 << 40 << 49 << 50
                         << 7 << 8 << 17 << 18 << 27 << 28 << 37 << 38 << 47 << 48
                         << 5 << 6 << 15 << 16 << 25 << 26 << 35 << 36 << 45 << 46
                         << 3 << 4 << 13 << 14 << 23 << 24 << 33 << 34 << 43 << 44
                         << 11 << 12 << 21 << 22 << 31 << 32 << 41 << 42
                         << 1 << 2;
            break;

        case 60: classements = QList<int>()
                         << 9 << 10 << 19 << 20 << 29 << 30 << 39 << 40 << 49 << 50
                         << 7 << 8 << 17 << 18 << 27 << 28 << 37 << 38 << 47 << 48
                         << 5 << 6 << 15 << 16 << 25 << 26 << 35 << 36 << 45 << 46
                         << 3 << 4 << 13 << 14 << 23 << 24 << 33 << 34 << 43 << 44
                         << 11 << 12 << 21 << 22 << 31 << 32 << 41 << 42
                         << 1 << 2;
            break;
    }
}

// generate platzspiele
void ClassementGames::generateClassementGames()
{
    QList<QStringList> krGameResults;
    QStringList execQuerys;

    prefixCount = getPrefixCount();

    QList<QStringList> krGames = dbRead("SELECT spiel, ms_a, ms_b, satz1a, satz1b, satz2a, satz2b, satz3a, satz3b FROM kreuzspiele_Spielplan ORDER BY id ASC");

    foreach(QStringList krGame, krGames)
        krGameResults << CalculateResults::getResultsKrPl(krGame);

    execQuerys << generateGamePlan(QTime::fromString(startRound), &krGameResults);

    execQuerys << insertFieldNames("platzspiele_spielplan", fieldNames);

    dbWrite(&execQuerys);
}

// tournament results
void ClassementGames::finalTournamentResults()
{
    QList<QStringList> plGameResults;
    QStringList execQuerys;

    QList<QStringList> plGames = dbRead("SELECT spiel, ms_a, ms_b, satz1a, satz1b, satz2a, satz2b, satz3a, satz3b FROM platzspiele_Spielplan ORDER BY id ASC");

    foreach(QStringList plGame, plGames)
        plGameResults << CalculateResults::getResultsKrPl(plGame);

    dbWrite("DELETE FROM platzierungen");

    execQuerys << createClassement(&plGameResults);

    dbWrite(&execQuerys);
}

// generate game plan over all divisions
QStringList ClassementGames::generateGamePlan(QTime startRound, QList<QStringList> *krGameResults)
{
    int addzeit = ((satz * min) + pause) * 60;
    QStringList querys;

    // get list current ranking results
    QList<QStringList> resultDivisionsZw;

    // help lists
    const QStringList *divisionA, *divisionB, *divisionC, *divisionD, *divisionE, *divisionF,
            *divisionG, *divisionH, *divisionI, *divisionJ, *divisionK, *divisionL;

    // read divisional rank results and add to list
    for(int i = 0; i < prefixCount; i++)
    {
        QStringList resultEdit;
        QList<QStringList> divisionResult = dbRead("select ms, punkte, satz from zwischenrunde_erg_gr" + getPrefix(i) + " order by punkte desc, satz desc");

        foreach(QStringList team, divisionResult)
            resultEdit << team.at(0);

        resultDivisionsZw << resultEdit;
    }

    divisionA = &(resultDivisionsZw.at(0));
    divisionB = &(resultDivisionsZw.at(1));
    divisionC = &(resultDivisionsZw.at(2));
    divisionD = &(resultDivisionsZw.at(3));
    divisionE = &(resultDivisionsZw.at(4));
    divisionF = &(resultDivisionsZw.at(5));
    divisionG = &(resultDivisionsZw.at(6));
    divisionH = &(resultDivisionsZw.at(7));
    divisionI = &(resultDivisionsZw.at(8));
    divisionJ = &(resultDivisionsZw.at(9));
    divisionK = &(resultDivisionsZw.at(10));
    divisionL = &(resultDivisionsZw.at(11));

    lastRoundNr++;

    switch(teamsCount)
    {
        case 20:
        case 25:
            // spiel um platz 9
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(1," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA->at(4) + "','" + divisionB->at(4) + "','" + divisionA->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 7
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(2," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults->at(1).at(2) + "','" + krGameResults->at(5).at(2) + "','" + divisionB->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 19
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(3," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionC->at(4) + "','" + divisionD->at(4) + "','" + divisionC->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 17
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(4," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults->at(3).at(2) + "','" + krGameResults->at(7).at(2) + "','" + divisionD->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 5
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(5," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults->at(1).at(1) + "','" + krGameResults->at(5).at(1) + "','" + divisionA->at(4) + "',0,0,0,0,0,0)";

            startRound = startRound.addSecs(addzeit);
            lastRoundNr++;
            // spiel um platz 3
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(6," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults->at(0).at(2) + "','" + krGameResults->at(4).at(2) + "','" + divisionB->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 15
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(7," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults->at(3).at(1) + "','" + krGameResults->at(7).at(1) + "','" + divisionC->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 13
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults->at(2).at(2) + "','" + krGameResults->at(6).at(2) + "','" + divisionD->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 11
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(9," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults->at(2).at(1) + "','" + krGameResults->at(6).at(1) + "','" + divisionC->at(3) + "',0,0,0,0,0,0)";

            startRound = startRound.addSecs(addzeit);
            lastRoundNr++;
            // spiel um platz 1
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(10," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults->at(0).at(1) + "','" + krGameResults->at(4).at(1) + "','" + divisionA->at(3) + "',0,0,0,0,0,0)";
            break;

        case 28:
            // spiel um platz 7
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(1," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults->at(1).at(2) + "','" + krGameResults->at(7).at(2) + "','" + divisionB->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 19
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(2," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionC->at(4) + "','" + divisionD->at(4) + "','" + divisionC->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 17
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(3," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults->at(3).at(2) + "','" + krGameResults->at(9).at(2) + "','" + divisionD->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 27
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(4," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionE->at(4) + "','" + divisionF->at(4) + "','" + divisionE->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 25
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(5," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults->at(5).at(2) + "','" + krGameResults->at(11).at(2) + "','" + divisionF->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 5
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(6," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults->at(1).at(1) + "','" + krGameResults->at(7).at(2) + "','" + krGameResults->at(1).at(2) + "',0,0,0,0,0,0)";
            // spiel um platz 3
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(7," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults->at(0).at(2) + "','" + krGameResults->at(6).at(2) + "','" + krGameResults->at(7).at(2) + "',0,0,0,0,0,0)";

            startRound = startRound.addSecs(addzeit);
            lastRoundNr++;
            // spiel um platz 15
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults->at(3).at(1) + "','" + krGameResults->at(9).at(1) + "','" + divisionC->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 13
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(9," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults->at(2).at(2) + "','" + krGameResults->at(8).at(2) + "','" + divisionD->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 23
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(10," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults->at(5).at(1) + "','" + krGameResults->at(11).at(1) + "','" + divisionE->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 9
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(11," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults->at(4).at(2) + "','" + krGameResults->at(10).at(2) + "','" + divisionF->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 21
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults->at(4).at(1) + "','" + krGameResults->at(10).at(1) + "','" + divisionE->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 11
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(13," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults->at(2).at(1) + "','" + krGameResults->at(8).at(1) + "','" + divisionC->at(4) + "',0,0,0,0,0,0)";

            startRound = startRound.addSecs(addzeit);
            lastRoundNr++;
            // spiel um platz 1
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(14," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults->at(0).at(1) + "','" + krGameResults->at(6).at(1) + "','" + divisionA->at(3) + "',0,0,0,0,0,0)";
            break;

        case 30:
        case 35:
            // spiel um platz 9
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(1," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA->at(4) + "','" + divisionB->at(4) + "','" + divisionA->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 19
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(2," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionC->at(4) + "','" + divisionD->at(4) + "','" + divisionC->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 29
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(3," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionE->at(4) + "','" + divisionF->at(4) + "','" + divisionE->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 7
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(4," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults->at(1).at(2) + "','" + krGameResults->at(7).at(2) + "','" + divisionB->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 17
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(5," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults->at(3).at(2) + "','" + krGameResults->at(9).at(2) + "','" + divisionD->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 27
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(6," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults->at(5).at(2) + "','" + krGameResults->at(11).at(2) + "','" + divisionF->at(1) + "',0,0,0,0,0,0)";

            startRound = startRound.addSecs(addzeit);
            lastRoundNr++;
            // spiel um platz 5
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(7," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults->at(1).at(1) + "','" + krGameResults->at(7).at(1) + "','" + divisionA->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 15
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(9," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults->at(3).at(1) + "','" + krGameResults->at(9).at(1) + "','" + divisionC->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 25
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(11," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults->at(5).at(1) + "','" + krGameResults->at(11).at(1) + "','" + divisionE->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 3
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults->at(0).at(2) + "','" + krGameResults->at(6).at(2) + "','" + divisionB->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 13
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(10," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults->at(2).at(2) + "','" + krGameResults->at(8).at(2) + "','" + divisionD->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 23
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults->at(4).at(2) + "','" + krGameResults->at(10).at(2) + "','" + divisionF->at(4) + "',0,0,0,0,0,0)";

            startRound = startRound.addSecs(addzeit);
            lastRoundNr++;
            // spiel um platz 21
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(13," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults->at(2).at(1) + "','" + krGameResults->at(8).at(1) + "','" + divisionA->at(3) + "',0,0,0,0,0,0)";
            // spiel um platz 11
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(14," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults->at(4).at(1) + "','" + krGameResults->at(10).at(1) + "','" + divisionB->at(3) + "',0,0,0,0,0,0)";

            startRound = startRound.addSecs(addzeit);
            lastRoundNr++;
            // spiel um platz 1
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(15," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults->at(0).at(1) + "','" + krGameResults->at(6).at(1) + "','" + divisionA->at(3) + "',0,0,0,0,0,0)";
            break;

        case 40:
        case 45:
            // spiel um platz 9
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(1," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA->at(4) + "','" + divisionB->at(4) + "','" + divisionA->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 19
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(2," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionC->at(4) + "','" + divisionD->at(4) + "','" + divisionC->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 29
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(3," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionE->at(4) + "','" + divisionF->at(4) + "','" + divisionE->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 39
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(4," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionG->at(4) + "','" + divisionH->at(4) + "','" + divisionG->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 7
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(5," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults->at(1).at(2) + "','" + krGameResults->at(9).at(2) + "','" + divisionB->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 17
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(6," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults->at(3).at(2) + "','" + krGameResults->at(11).at(2) + "','" + divisionD->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 27
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(7," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + krGameResults->at(5).at(2) + "','" + krGameResults->at(13).at(2) + "','" + divisionF->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 37
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults->at(7).at(2) + "','" + krGameResults->at(15).at(2) + "','" + divisionH->at(1) + "',0,0,0,0,0,0)";

            startRound = startRound.addSecs(addzeit);
            lastRoundNr++;
            // spiel um platz 5
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(9," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults->at(1).at(1) + "','" + krGameResults->at(9).at(1) + "','" + divisionA->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 15
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(10," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults->at(3).at(1) + "','" + krGameResults->at(11).at(1) + "','" + divisionC->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 25
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(11," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults->at(5).at(1) + "','" + krGameResults->at(13).at(1) + "','" + divisionE->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 35
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults->at(7).at(1) + "','" + krGameResults->at(15).at(1) + "','" + divisionG->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 3
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(13," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults->at(0).at(2) + "','" + krGameResults->at(8).at(2) + "','" + divisionB->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 13
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(14," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults->at(2).at(2) + "','" + krGameResults->at(10).at(2) + "','" + divisionD->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 23
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(15," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + krGameResults->at(4).at(2) + "','" + krGameResults->at(12).at(2) + "','" + divisionF->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 33
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(16," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults->at(6).at(2) + "','" + krGameResults->at(14).at(2) + "','" + divisionH->at(4) + "',0,0,0,0,0,0)";

            startRound = startRound.addSecs(addzeit);
            lastRoundNr++;
            // spiel um platz 11
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(17," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults->at(2).at(1) + "','" + krGameResults->at(10).at(1) + "','" + divisionA->at(3) + "',0,0,0,0,0,0)";
            // spiel um platz 21
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(18," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults->at(4).at(1) + "','" + krGameResults->at(12).at(1) + "','" + divisionB->at(3) + "',0,0,0,0,0,0)";
            // spiel um platz 31
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(19," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults->at(6).at(1) + "','" + krGameResults->at(14).at(1) + "','" + divisionC->at(3) + "',0,0,0,0,0,0)";

            startRound = startRound.addSecs(addzeit);
            lastRoundNr++;
            // spiel um platz 1
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(20," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults->at(0).at(1) + "','" + krGameResults->at(8).at(1) + "','',0,0,0,0,0,0)";
            break;

        case 50:
            // spiel um platz 9
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(1," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA->at(4) + "','" + divisionB->at(4) + "','" + divisionA->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 19
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(2," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionC->at(4) + "','" + divisionD->at(4) + "','" + divisionC->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 29
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(3," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionE->at(4) + "','" + divisionF->at(4) + "','" + divisionE->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 39
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(4," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionG->at(4) + "','" + divisionH->at(4) + "','" + divisionG->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 49
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(4," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionG->at(4) + "','" + divisionH->at(4) + "','" + divisionG->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 7
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(5," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults->at(1).at(2) + "','" + krGameResults->at(9).at(2) + "','" + divisionB->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 17
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(6," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults->at(3).at(2) + "','" + krGameResults->at(11).at(2) + "','" + divisionD->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 27
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(7," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + krGameResults->at(5).at(2) + "','" + krGameResults->at(13).at(2) + "','" + divisionF->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 37
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults->at(7).at(2) + "','" + krGameResults->at(15).at(2) + "','" + divisionH->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 47
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults->at(7).at(2) + "','" + krGameResults->at(15).at(2) + "','" + divisionH->at(1) + "',0,0,0,0,0,0)";

            startRound = startRound.addSecs(addzeit);
            lastRoundNr++;
            // spiel um platz 5
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(9," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults->at(1).at(1) + "','" + krGameResults->at(9).at(1) + "','" + divisionA->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 15
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(10," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults->at(3).at(1) + "','" + krGameResults->at(11).at(1) + "','" + divisionC->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 25
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(11," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults->at(5).at(1) + "','" + krGameResults->at(13).at(1) + "','" + divisionE->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 35
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults->at(7).at(1) + "','" + krGameResults->at(15).at(1) + "','" + divisionG->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 45
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults->at(7).at(1) + "','" + krGameResults->at(15).at(1) + "','" + divisionG->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 3
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(13," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults->at(0).at(2) + "','" + krGameResults->at(8).at(2) + "','" + divisionB->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 13
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(14," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults->at(2).at(2) + "','" + krGameResults->at(10).at(2) + "','" + divisionD->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 23
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(15," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + krGameResults->at(4).at(2) + "','" + krGameResults->at(12).at(2) + "','" + divisionF->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 33
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(16," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults->at(6).at(2) + "','" + krGameResults->at(14).at(2) + "','" + divisionH->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 43
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(16," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults->at(6).at(2) + "','" + krGameResults->at(14).at(2) + "','" + divisionH->at(4) + "',0,0,0,0,0,0)";

            startRound = startRound.addSecs(addzeit);
            lastRoundNr++;
            // spiel um platz 11
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(17," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults->at(2).at(1) + "','" + krGameResults->at(10).at(1) + "','" + divisionA->at(3) + "',0,0,0,0,0,0)";
            // spiel um platz 21
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(18," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults->at(4).at(1) + "','" + krGameResults->at(12).at(1) + "','" + divisionB->at(3) + "',0,0,0,0,0,0)";
            // spiel um platz 31
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(19," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults->at(6).at(1) + "','" + krGameResults->at(14).at(1) + "','" + divisionC->at(3) + "',0,0,0,0,0,0)";
            // spiel um platz 41
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(20," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults->at(6).at(1) + "','" + krGameResults->at(14).at(1) + "','" + divisionC->at(3) + "',0,0,0,0,0,0)";

            startRound = startRound.addSecs(addzeit);
            lastRoundNr++;
            // spiel um platz 1
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(20," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults->at(0).at(1) + "','" + krGameResults->at(8).at(1) + "','',0,0,0,0,0,0)";
            break;

        case 55:
            // spiel um platz 9
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(1," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA->at(4) + "','" + divisionB->at(4) + "','" + divisionA->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 19
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(2," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionC->at(4) + "','" + divisionD->at(4) + "','" + divisionC->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 29
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(3," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionE->at(4) + "','" + divisionF->at(4) + "','" + divisionE->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 39
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(4," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionG->at(4) + "','" + divisionH->at(4) + "','" + divisionG->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 49
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(4," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionG->at(4) + "','" + divisionH->at(4) + "','" + divisionG->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 7
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(5," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults->at(1).at(2) + "','" + krGameResults->at(9).at(2) + "','" + divisionB->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 17
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(6," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults->at(3).at(2) + "','" + krGameResults->at(11).at(2) + "','" + divisionD->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 27
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(7," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + krGameResults->at(5).at(2) + "','" + krGameResults->at(13).at(2) + "','" + divisionF->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 37
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults->at(7).at(2) + "','" + krGameResults->at(15).at(2) + "','" + divisionH->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 47
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults->at(7).at(2) + "','" + krGameResults->at(15).at(2) + "','" + divisionH->at(1) + "',0,0,0,0,0,0)";

            startRound = startRound.addSecs(addzeit);
            lastRoundNr++;
            // spiel um platz 5
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(9," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults->at(1).at(1) + "','" + krGameResults->at(9).at(1) + "','" + divisionA->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 15
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(10," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults->at(3).at(1) + "','" + krGameResults->at(11).at(1) + "','" + divisionC->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 25
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(11," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults->at(5).at(1) + "','" + krGameResults->at(13).at(1) + "','" + divisionE->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 35
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults->at(7).at(1) + "','" + krGameResults->at(15).at(1) + "','" + divisionG->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 45
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults->at(7).at(1) + "','" + krGameResults->at(15).at(1) + "','" + divisionG->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 3
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(13," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults->at(0).at(2) + "','" + krGameResults->at(8).at(2) + "','" + divisionB->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 13
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(14," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults->at(2).at(2) + "','" + krGameResults->at(10).at(2) + "','" + divisionD->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 23
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(15," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + krGameResults->at(4).at(2) + "','" + krGameResults->at(12).at(2) + "','" + divisionF->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 33
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(16," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults->at(6).at(2) + "','" + krGameResults->at(14).at(2) + "','" + divisionH->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 43
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(16," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults->at(6).at(2) + "','" + krGameResults->at(14).at(2) + "','" + divisionH->at(4) + "',0,0,0,0,0,0)";

            startRound = startRound.addSecs(addzeit);
            lastRoundNr++;
            // spiel um platz 11
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(17," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults->at(2).at(1) + "','" + krGameResults->at(10).at(1) + "','" + divisionA->at(3) + "',0,0,0,0,0,0)";
            // spiel um platz 21
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(18," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults->at(4).at(1) + "','" + krGameResults->at(12).at(1) + "','" + divisionB->at(3) + "',0,0,0,0,0,0)";
            // spiel um platz 31
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(19," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults->at(6).at(1) + "','" + krGameResults->at(14).at(1) + "','" + divisionC->at(3) + "',0,0,0,0,0,0)";
            // spiel um platz 41
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(20," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults->at(6).at(1) + "','" + krGameResults->at(14).at(1) + "','" + divisionC->at(3) + "',0,0,0,0,0,0)";

            startRound = startRound.addSecs(addzeit);
            lastRoundNr++;
            // spiel um platz 1
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(20," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults->at(0).at(1) + "','" + krGameResults->at(8).at(1) + "','',0,0,0,0,0,0)";
            break;

        case 60:
            // spiel um platz 9
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(1," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA->at(4) + "','" + divisionB->at(4) + "','" + divisionA->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 19
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(2," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionC->at(4) + "','" + divisionD->at(4) + "','" + divisionC->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 29
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(3," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionE->at(4) + "','" + divisionF->at(4) + "','" + divisionE->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 39
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(4," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionG->at(4) + "','" + divisionH->at(4) + "','" + divisionG->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 49
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(4," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionG->at(4) + "','" + divisionH->at(4) + "','" + divisionG->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 7
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(5," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults->at(1).at(2) + "','" + krGameResults->at(9).at(2) + "','" + divisionB->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 17
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(6," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults->at(3).at(2) + "','" + krGameResults->at(11).at(2) + "','" + divisionD->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 27
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(7," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + krGameResults->at(5).at(2) + "','" + krGameResults->at(13).at(2) + "','" + divisionF->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 37
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults->at(7).at(2) + "','" + krGameResults->at(15).at(2) + "','" + divisionH->at(1) + "',0,0,0,0,0,0)";
            // spiel um platz 47
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults->at(7).at(2) + "','" + krGameResults->at(15).at(2) + "','" + divisionH->at(1) + "',0,0,0,0,0,0)";

            startRound = startRound.addSecs(addzeit);
            lastRoundNr++;
            // spiel um platz 5
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(9," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults->at(1).at(1) + "','" + krGameResults->at(9).at(1) + "','" + divisionA->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 15
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(10," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults->at(3).at(1) + "','" + krGameResults->at(11).at(1) + "','" + divisionC->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 25
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(11," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults->at(5).at(1) + "','" + krGameResults->at(13).at(1) + "','" + divisionE->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 35
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults->at(7).at(1) + "','" + krGameResults->at(15).at(1) + "','" + divisionG->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 45
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults->at(7).at(1) + "','" + krGameResults->at(15).at(1) + "','" + divisionG->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 3
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(13," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults->at(0).at(2) + "','" + krGameResults->at(8).at(2) + "','" + divisionB->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 13
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(14," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults->at(2).at(2) + "','" + krGameResults->at(10).at(2) + "','" + divisionD->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 23
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(15," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + krGameResults->at(4).at(2) + "','" + krGameResults->at(12).at(2) + "','" + divisionF->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 33
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(16," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults->at(6).at(2) + "','" + krGameResults->at(14).at(2) + "','" + divisionH->at(4) + "',0,0,0,0,0,0)";
            // spiel um platz 43
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(16," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults->at(6).at(2) + "','" + krGameResults->at(14).at(2) + "','" + divisionH->at(4) + "',0,0,0,0,0,0)";

            startRound = startRound.addSecs(addzeit);
            lastRoundNr++;
            // spiel um platz 11
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(17," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults->at(2).at(1) + "','" + krGameResults->at(10).at(1) + "','" + divisionA->at(3) + "',0,0,0,0,0,0)";
            // spiel um platz 21
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(18," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults->at(4).at(1) + "','" + krGameResults->at(12).at(1) + "','" + divisionB->at(3) + "',0,0,0,0,0,0)";
            // spiel um platz 31
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(19," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults->at(6).at(1) + "','" + krGameResults->at(14).at(1) + "','" + divisionC->at(3) + "',0,0,0,0,0,0)";
            // spiel um platz 41
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(20," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults->at(6).at(1) + "','" + krGameResults->at(14).at(1) + "','" + divisionC->at(3) + "',0,0,0,0,0,0)";

            startRound = startRound.addSecs(addzeit);
            lastRoundNr++;
            // spiel um platz 1
            lastGameNr++;
            querys << "INSERT INTO platzspiele_spielplan VALUES(20," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults->at(0).at(1) + "','" + krGameResults->at(8).at(1) + "','',0,0,0,0,0,0)";
            break;
    }

    return querys;
}

// create classement
QStringList ClassementGames::createClassement(QList<QStringList> *plGameResults)
{
    QStringList querys;
    QList<QStringList> bottomRankings;
    int rowid = 0, id = 0;

    for(int i = 0, x = 0; i < plGameResults->size(); i++)
    {
        QStringList plGame = plGameResults->at(i);
        querys << "INSERT INTO platzierungen VALUES(" + string(id++) + "," + string(classements.at(x++)) + ",'" + plGame.at(1) + "')";
        querys << "INSERT INTO platzierungen VALUES(" + string(id++) + "," + string(classements.at(x++)) + ",'" + plGame.at(2) + "')";
    }

    // rest of classement, teams which played vorrunde and zwischenrunde
    switch(teamsCount)
    {
        case 25:
            bottomRankings = dbRead("SELECT ms FROM zwischenrunde_gre_view");
            id++; rowid = id + 1;
            querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(rowid) + ",'" + bottomRankings.at(0).at(0) + "')";
            id++; rowid = id + 1;
            querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(rowid) + ",'" + bottomRankings.at(1).at(0) + "')";
            id++; rowid = id + 1;
            querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(rowid) + ",'" + bottomRankings.at(2).at(0) + "')";
            id++; rowid = id + 1;
            querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(rowid) + ",'" + bottomRankings.at(3).at(0) + "')";
            id++; rowid = id + 1;
            querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(rowid) + ",'" + bottomRankings.at(4).at(0) + "')";
            break;

        case 35:
            bottomRankings = dbRead("SELECT ms FROM zwischenrunde_grg_view");
            id++; rowid = id + 1;
            querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(rowid) + ",'" + bottomRankings.at(0).at(0) + "')";
            id++; rowid = id + 1;
            querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(rowid) + ",'" + bottomRankings.at(1).at(0) + "')";
            id++; rowid = id + 1;
            querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(rowid) + ",'" + bottomRankings.at(2).at(0) + "')";
            id++; rowid = id + 1;
            querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(rowid) + ",'" + bottomRankings.at(3).at(0) + "')";
            id++; rowid = id + 1;
            querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(rowid) + ",'" + bottomRankings.at(4).at(0) + "')";
            break;

        case 45:
            bottomRankings = dbRead("SELECT ms FROM zwischenrunde_gri_view");
            id++; rowid = id + 1;
            querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(rowid) + ",'" + bottomRankings.at(0).at(0) + "')";
            id++; rowid = id + 1;
            querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(rowid) + ",'" + bottomRankings.at(1).at(0) + "')";
            id++; rowid = id + 1;
            querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(rowid) + ",'" + bottomRankings.at(2).at(0) + "')";
            id++; rowid = id + 1;
            querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(rowid) + ",'" + bottomRankings.at(3).at(0) + "')";
            id++; rowid = id + 1;
            querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(rowid) + ",'" + bottomRankings.at(4).at(0) + "')";
            break;

        case 55:
            bottomRankings = dbRead("SELECT ms FROM zwischenrunde_grk_view");
            id++; rowid = id + 1;
            querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(rowid) + ",'" + bottomRankings.at(0).at(0) + "')";
            id++; rowid = id + 1;
            querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(rowid) + ",'" + bottomRankings.at(1).at(0) + "')";
            id++; rowid = id + 1;
            querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(rowid) + ",'" + bottomRankings.at(2).at(0) + "')";
            id++; rowid = id + 1;
            querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(rowid) + ",'" + bottomRankings.at(3).at(0) + "')";
            id++; rowid = id + 1;
            querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(rowid) + ",'" + bottomRankings.at(4).at(0) + "')";
            break;
    }

    return querys;
}
