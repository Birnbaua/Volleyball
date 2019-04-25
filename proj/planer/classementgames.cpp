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
                                    int countSatz, int minSatz, int fieldCount, int teamsCount, int divisionCount,
                                    QStringList *fieldNames, int lastRoundNr, int lastGameNr, int bettyspiele)
{
    emit logMessages("PLATZSPIELE:: set platzspiele params");
    this->startRound = startRound;
    this->satz = countSatz;
    this->min = minSatz;
    this->pause = 0;
    this->fieldCount = fieldCount;
    this->teamsCount = teamsCount;
    this->divisionCount = divisionCount;
    this->fieldNames = fieldNames;
    this->lastGameNr = lastGameNr;
    this->lastRoundNr = lastRoundNr;
    this->bettyspiele = bettyspiele;
    setTimeParameters(satz, min, pause);

    QTime time = QTime::fromString(this->startRound, "hh:mm");
    time = time.addSecs((pauseKrPl * 60) + (lastgameTime * 60));
    this->startRound = time.toString("hh:mm");

    if(bettyspiele == 0)
    {
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
}

// generate platzspiele
void ClassementGames::generateClassementGames()
{
    QStringList execQuerys;

    krGameResults.clear();
    prefixCount = getPrefixCount();

    QList<QStringList> krGames = dbRead("SELECT spiel, ms_a, ms_b, satz1a, satz1b, satz2a, satz2b, satz3a, satz3b FROM kreuzspiele_Spielplan ORDER BY id ASC");

    foreach(QStringList krGame, krGames)
        krGameResults << CalculateResults::getResultsKrPl(krGame);

    execQuerys << generateGamePlan(QTime::fromString(startRound));

    execQuerys << insertFieldNames("platzspiele_spielplan", fieldNames);

    dbWrite(&execQuerys);
}

// tournament results
void ClassementGames::finalTournamentResults()
{
    QStringList execQuerys;

    if(krGameResults.count() == 0)
    {
        QList<QStringList> krGames = dbRead("SELECT spiel, ms_a, ms_b, satz1a, satz1b, satz2a, satz2b, satz3a, satz3b FROM kreuzspiele_Spielplan ORDER BY id ASC");

        foreach(QStringList krGame, krGames)
            krGameResults << CalculateResults::getResultsKrPl(krGame);
    }

    plGameResults.clear();

    QList<QStringList> plGames = dbRead("SELECT spiel, ms_a, ms_b, satz1a, satz1b, satz2a, satz2b, satz3a, satz3b FROM platzspiele_Spielplan ORDER BY id ASC");

    foreach(QStringList plGame, plGames)
        plGameResults << CalculateResults::getResultsKrPl(plGame);

    dbWrite("DELETE FROM platzierungen");

    execQuerys << createClassement();

    dbWrite(&execQuerys);
}

// generate game plan over all divisions
QStringList ClassementGames::generateGamePlan(QTime startRound)
{
    int addzeit = ((satz * min) + pause) * 60;
    QStringList querys;

    // get list current ranking results
    QList<QStringList> resultDivisionsZw;

    // help lists
    const QStringList *divisionA = nullptr,
            *divisionB = nullptr,
            *divisionC = nullptr,
            *divisionD = nullptr,
            *divisionE = nullptr,
            *divisionF = nullptr,
            *divisionG = nullptr,
            *divisionH = nullptr,
            *divisionI = nullptr,
            *divisionJ = nullptr,
            *divisionK = nullptr,
            *divisionL = nullptr;
    QList<const QStringList*> helpLists;
    helpLists << divisionA << divisionB << divisionC << divisionD << divisionE << divisionF << divisionG << divisionH << divisionI << divisionJ << divisionK << divisionL;


    // read divisional rank results and add to list
    for(int i = 0; i < prefixCount; i++)
    {
        QStringList resultEdit;
        QList<QStringList> divisionResult = dbRead("select ms, punkte, satz from zwischenrunde_erg_gr" + getPrefix(i) + " order by punkte desc, satz desc");

        foreach(QStringList team, divisionResult)
            resultEdit << team.at(0);

        resultDivisionsZw << resultEdit;
    }

    for(int x = 0; x < helpLists.count(); x++)
    {
        if(resultDivisionsZw.at(x).count() > 0)
            helpLists[x] = &(resultDivisionsZw.at(x));
    }

    lastRoundNr++;

    if(bettyspiele == 0)
    {
        switch(teamsCount)
        {
            case 20:
            case 25:
                // spiel um platz 9
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(1," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA->at(4) + "','" + divisionB->at(4) + "','" + divisionA->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 7
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(2," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(1).at(2) + "','" + krGameResults.at(5).at(2) + "','" + divisionB->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 19
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(3," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionC->at(4) + "','" + divisionD->at(4) + "','" + divisionC->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 17
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(4," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(3).at(2) + "','" + krGameResults.at(7).at(2) + "','" + divisionD->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 5
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(5," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults.at(1).at(1) + "','" + krGameResults.at(5).at(1) + "','" + divisionA->at(4) + "',0,0,0,0,0,0)";

                startRound = startRound.addSecs(addzeit);
                lastRoundNr++;
                // spiel um platz 3
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(6," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults.at(0).at(2) + "','" + krGameResults.at(4).at(2) + "','" + divisionB->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 15
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(7," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(3).at(1) + "','" + krGameResults.at(7).at(1) + "','" + divisionC->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 13
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults.at(2).at(2) + "','" + krGameResults.at(6).at(2) + "','" + divisionD->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 11
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(9," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(2).at(1) + "','" + krGameResults.at(6).at(1) + "','" + divisionC->at(3) + "',0,0,0,0,0,0)";

                startRound = startRound.addSecs(addzeit);
                lastRoundNr++;
                // spiel um platz 1
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(10," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(0).at(1) + "','" + krGameResults.at(4).at(1) + "','" + divisionA->at(3) + "',0,0,0,0,0,0)";
                break;

            case 28:
                // spiel um platz 7
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(1," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(1).at(2) + "','" + krGameResults.at(7).at(2) + "','" + divisionB->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 19
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(2," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionC->at(4) + "','" + divisionD->at(4) + "','" + divisionC->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 17
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(3," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults.at(3).at(2) + "','" + krGameResults.at(9).at(2) + "','" + divisionD->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 27
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(4," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionE->at(4) + "','" + divisionF->at(4) + "','" + divisionE->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 25
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(5," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(5).at(2) + "','" + krGameResults.at(11).at(2) + "','" + divisionF->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 5
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(6," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults.at(1).at(1) + "','" + krGameResults.at(7).at(2) + "','" + krGameResults.at(1).at(2) + "',0,0,0,0,0,0)";
                // spiel um platz 3
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(7," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults.at(0).at(2) + "','" + krGameResults.at(6).at(2) + "','" + krGameResults.at(7).at(2) + "',0,0,0,0,0,0)";

                startRound = startRound.addSecs(addzeit);
                lastRoundNr++;
                // spiel um platz 15
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(3).at(1) + "','" + krGameResults.at(9).at(1) + "','" + divisionC->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 13
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(9," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(2).at(2) + "','" + krGameResults.at(8).at(2) + "','" + divisionD->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 23
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(10," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(5).at(1) + "','" + krGameResults.at(11).at(1) + "','" + divisionE->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 9
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(11," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(4).at(2) + "','" + krGameResults.at(10).at(2) + "','" + divisionF->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 21
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults.at(4).at(1) + "','" + krGameResults.at(10).at(1) + "','" + divisionE->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 11
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(13," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(2).at(1) + "','" + krGameResults.at(8).at(1) + "','" + divisionC->at(4) + "',0,0,0,0,0,0)";

                startRound = startRound.addSecs(addzeit);
                lastRoundNr++;
                // spiel um platz 1
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(14," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(0).at(1) + "','" + krGameResults.at(6).at(1) + "','" + divisionA->at(3) + "',0,0,0,0,0,0)";
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
                querys << "INSERT INTO platzspiele_spielplan VALUES(4," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(1).at(2) + "','" + krGameResults.at(7).at(2) + "','" + divisionB->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 17
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(5," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults.at(3).at(2) + "','" + krGameResults.at(9).at(2) + "','" + divisionD->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 27
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(6," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults.at(5).at(2) + "','" + krGameResults.at(11).at(2) + "','" + divisionF->at(1) + "',0,0,0,0,0,0)";

                startRound = startRound.addSecs(addzeit);
                lastRoundNr++;
                // spiel um platz 5
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(7," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(1).at(1) + "','" + krGameResults.at(7).at(1) + "','" + divisionA->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 15
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(9," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(3).at(1) + "','" + krGameResults.at(9).at(1) + "','" + divisionC->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 25
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(11," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults.at(5).at(1) + "','" + krGameResults.at(11).at(1) + "','" + divisionE->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 3
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(0).at(2) + "','" + krGameResults.at(6).at(2) + "','" + divisionB->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 13
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(10," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults.at(2).at(2) + "','" + krGameResults.at(8).at(2) + "','" + divisionD->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 23
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults.at(4).at(2) + "','" + krGameResults.at(10).at(2) + "','" + divisionF->at(4) + "',0,0,0,0,0,0)";

                startRound = startRound.addSecs(addzeit);
                lastRoundNr++;
                // spiel um platz 21
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(13," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(2).at(1) + "','" + krGameResults.at(8).at(1) + "','" + divisionA->at(3) + "',0,0,0,0,0,0)";
                // spiel um platz 11
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(14," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(4).at(1) + "','" + krGameResults.at(10).at(1) + "','" + divisionB->at(3) + "',0,0,0,0,0,0)";

                startRound = startRound.addSecs(addzeit);
                lastRoundNr++;
                // spiel um platz 1
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(15," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(0).at(1) + "','" + krGameResults.at(6).at(1) + "','" + divisionA->at(3) + "',0,0,0,0,0,0)";
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
                querys << "INSERT INTO platzspiele_spielplan VALUES(5," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults.at(1).at(2) + "','" + krGameResults.at(9).at(2) + "','" + divisionB->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 17
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(6," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults.at(3).at(2) + "','" + krGameResults.at(11).at(2) + "','" + divisionD->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 27
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(7," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + krGameResults.at(5).at(2) + "','" + krGameResults.at(13).at(2) + "','" + divisionF->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 37
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults.at(7).at(2) + "','" + krGameResults.at(15).at(2) + "','" + divisionH->at(1) + "',0,0,0,0,0,0)";

                startRound = startRound.addSecs(addzeit);
                lastRoundNr++;
                // spiel um platz 5
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(9," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(1).at(1) + "','" + krGameResults.at(9).at(1) + "','" + divisionA->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 15
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(10," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(3).at(1) + "','" + krGameResults.at(11).at(1) + "','" + divisionC->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 25
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(11," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults.at(5).at(1) + "','" + krGameResults.at(13).at(1) + "','" + divisionE->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 35
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(7).at(1) + "','" + krGameResults.at(15).at(1) + "','" + divisionG->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 3
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(13," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults.at(0).at(2) + "','" + krGameResults.at(8).at(2) + "','" + divisionB->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 13
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(14," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults.at(2).at(2) + "','" + krGameResults.at(10).at(2) + "','" + divisionD->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 23
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(15," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + krGameResults.at(4).at(2) + "','" + krGameResults.at(12).at(2) + "','" + divisionF->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 33
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(16," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults.at(6).at(2) + "','" + krGameResults.at(14).at(2) + "','" + divisionH->at(4) + "',0,0,0,0,0,0)";

                startRound = startRound.addSecs(addzeit);
                lastRoundNr++;
                // spiel um platz 11
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(17," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(2).at(1) + "','" + krGameResults.at(10).at(1) + "','" + divisionA->at(3) + "',0,0,0,0,0,0)";
                // spiel um platz 21
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(18," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(4).at(1) + "','" + krGameResults.at(12).at(1) + "','" + divisionB->at(3) + "',0,0,0,0,0,0)";
                // spiel um platz 31
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(19," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults.at(6).at(1) + "','" + krGameResults.at(14).at(1) + "','" + divisionC->at(3) + "',0,0,0,0,0,0)";

                startRound = startRound.addSecs(addzeit);
                lastRoundNr++;
                // spiel um platz 1
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(20," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(0).at(1) + "','" + krGameResults.at(8).at(1) + "','',0,0,0,0,0,0)";
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
                querys << "INSERT INTO platzspiele_spielplan VALUES(5," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionG->at(4) + "','" + divisionH->at(4) + "','" + divisionG->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 7
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(6," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults.at(1).at(2) + "','" + krGameResults.at(9).at(2) + "','" + divisionB->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 17
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(7," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + krGameResults.at(3).at(2) + "','" + krGameResults.at(11).at(2) + "','" + divisionD->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 27
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults.at(5).at(2) + "','" + krGameResults.at(13).at(2) + "','" + divisionF->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 37
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(9," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',9,'','" + krGameResults.at(7).at(2) + "','" + krGameResults.at(15).at(2) + "','" + divisionH->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 47
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(10," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',10,'','" + krGameResults.at(9).at(2) + "','" + krGameResults.at(15).at(2) + "','" + divisionH->at(1) + "',0,0,0,0,0,0)";

                startRound = startRound.addSecs(addzeit);
                lastRoundNr++;
                // spiel um platz 5
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(11," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(1).at(1) + "','" + krGameResults.at(9).at(1) + "','" + divisionA->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 15
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(3).at(1) + "','" + krGameResults.at(11).at(1) + "','" + divisionC->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 25
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(13," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults.at(5).at(1) + "','" + krGameResults.at(13).at(1) + "','" + divisionE->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 35
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(14," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(7).at(1) + "','" + krGameResults.at(15).at(1) + "','" + divisionG->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 45
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(15," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults.at(7).at(1) + "','" + krGameResults.at(15).at(1) + "','" + divisionG->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 3
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(16," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults.at(0).at(2) + "','" + krGameResults.at(8).at(2) + "','" + divisionB->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 13
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(17," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + krGameResults.at(2).at(2) + "','" + krGameResults.at(10).at(2) + "','" + divisionD->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 23
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(18," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults.at(4).at(2) + "','" + krGameResults.at(12).at(2) + "','" + divisionF->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 33
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(19," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',9,'','" + krGameResults.at(6).at(2) + "','" + krGameResults.at(14).at(2) + "','" + divisionH->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 43
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(20," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',10,'','" + krGameResults.at(6).at(2) + "','" + krGameResults.at(14).at(2) + "','" + divisionH->at(4) + "',0,0,0,0,0,0)";

                startRound = startRound.addSecs(addzeit);
                lastRoundNr++;
                // spiel um platz 11
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(21," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(2).at(1) + "','" + krGameResults.at(10).at(1) + "','" + divisionA->at(3) + "',0,0,0,0,0,0)";
                // spiel um platz 21
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(22," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(4).at(1) + "','" + krGameResults.at(12).at(1) + "','" + divisionB->at(3) + "',0,0,0,0,0,0)";
                // spiel um platz 31
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(23," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults.at(6).at(1) + "','" + krGameResults.at(14).at(1) + "','" + divisionC->at(3) + "',0,0,0,0,0,0)";
                // spiel um platz 41
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(24," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(6).at(1) + "','" + krGameResults.at(14).at(1) + "','" + divisionC->at(3) + "',0,0,0,0,0,0)";

                startRound = startRound.addSecs(addzeit);
                lastRoundNr++;
                // spiel um platz 1
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(20," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(0).at(1) + "','" + krGameResults.at(8).at(1) + "','',0,0,0,0,0,0)";
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
                querys << "INSERT INTO platzspiele_spielplan VALUES(5," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults.at(1).at(2) + "','" + krGameResults.at(9).at(2) + "','" + divisionB->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 17
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(6," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults.at(3).at(2) + "','" + krGameResults.at(11).at(2) + "','" + divisionD->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 27
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(7," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + krGameResults.at(5).at(2) + "','" + krGameResults.at(13).at(2) + "','" + divisionF->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 37
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults.at(7).at(2) + "','" + krGameResults.at(15).at(2) + "','" + divisionH->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 47
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults.at(7).at(2) + "','" + krGameResults.at(15).at(2) + "','" + divisionH->at(1) + "',0,0,0,0,0,0)";

                startRound = startRound.addSecs(addzeit);
                lastRoundNr++;
                // spiel um platz 5
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(9," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(1).at(1) + "','" + krGameResults.at(9).at(1) + "','" + divisionA->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 15
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(10," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(3).at(1) + "','" + krGameResults.at(11).at(1) + "','" + divisionC->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 25
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(11," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults.at(5).at(1) + "','" + krGameResults.at(13).at(1) + "','" + divisionE->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 35
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(7).at(1) + "','" + krGameResults.at(15).at(1) + "','" + divisionG->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 45
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(7).at(1) + "','" + krGameResults.at(15).at(1) + "','" + divisionG->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 3
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(13," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults.at(0).at(2) + "','" + krGameResults.at(8).at(2) + "','" + divisionB->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 13
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(14," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults.at(2).at(2) + "','" + krGameResults.at(10).at(2) + "','" + divisionD->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 23
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(15," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + krGameResults.at(4).at(2) + "','" + krGameResults.at(12).at(2) + "','" + divisionF->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 33
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(16," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults.at(6).at(2) + "','" + krGameResults.at(14).at(2) + "','" + divisionH->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 43
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(16," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults.at(6).at(2) + "','" + krGameResults.at(14).at(2) + "','" + divisionH->at(4) + "',0,0,0,0,0,0)";

                startRound = startRound.addSecs(addzeit);
                lastRoundNr++;
                // spiel um platz 11
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(17," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(2).at(1) + "','" + krGameResults.at(10).at(1) + "','" + divisionA->at(3) + "',0,0,0,0,0,0)";
                // spiel um platz 21
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(18," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(4).at(1) + "','" + krGameResults.at(12).at(1) + "','" + divisionB->at(3) + "',0,0,0,0,0,0)";
                // spiel um platz 31
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(19," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults.at(6).at(1) + "','" + krGameResults.at(14).at(1) + "','" + divisionC->at(3) + "',0,0,0,0,0,0)";
                // spiel um platz 41
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(20," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(6).at(1) + "','" + krGameResults.at(14).at(1) + "','" + divisionC->at(3) + "',0,0,0,0,0,0)";

                startRound = startRound.addSecs(addzeit);
                lastRoundNr++;
                // spiel um platz 1
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(20," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(0).at(1) + "','" + krGameResults.at(8).at(1) + "','',0,0,0,0,0,0)";
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
                querys << "INSERT INTO platzspiele_spielplan VALUES(5," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults.at(1).at(2) + "','" + krGameResults.at(9).at(2) + "','" + divisionB->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 17
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(6," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults.at(3).at(2) + "','" + krGameResults.at(11).at(2) + "','" + divisionD->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 27
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(7," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + krGameResults.at(5).at(2) + "','" + krGameResults.at(13).at(2) + "','" + divisionF->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 37
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults.at(7).at(2) + "','" + krGameResults.at(15).at(2) + "','" + divisionH->at(1) + "',0,0,0,0,0,0)";
                // spiel um platz 47
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults.at(7).at(2) + "','" + krGameResults.at(15).at(2) + "','" + divisionH->at(1) + "',0,0,0,0,0,0)";

                startRound = startRound.addSecs(addzeit);
                lastRoundNr++;
                // spiel um platz 5
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(9," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(1).at(1) + "','" + krGameResults.at(9).at(1) + "','" + divisionA->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 15
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(10," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(3).at(1) + "','" + krGameResults.at(11).at(1) + "','" + divisionC->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 25
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(11," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults.at(5).at(1) + "','" + krGameResults.at(13).at(1) + "','" + divisionE->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 35
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(7).at(1) + "','" + krGameResults.at(15).at(1) + "','" + divisionG->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 45
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(7).at(1) + "','" + krGameResults.at(15).at(1) + "','" + divisionG->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 3
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(13," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults.at(0).at(2) + "','" + krGameResults.at(8).at(2) + "','" + divisionB->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 13
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(14," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults.at(2).at(2) + "','" + krGameResults.at(10).at(2) + "','" + divisionD->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 23
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(15," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + krGameResults.at(4).at(2) + "','" + krGameResults.at(12).at(2) + "','" + divisionF->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 33
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(16," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults.at(6).at(2) + "','" + krGameResults.at(14).at(2) + "','" + divisionH->at(4) + "',0,0,0,0,0,0)";
                // spiel um platz 43
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(16," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults.at(6).at(2) + "','" + krGameResults.at(14).at(2) + "','" + divisionH->at(4) + "',0,0,0,0,0,0)";

                startRound = startRound.addSecs(addzeit);
                lastRoundNr++;
                // spiel um platz 11
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(17," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(2).at(1) + "','" + krGameResults.at(10).at(1) + "','" + divisionI->at(3) + "',0,0,0,0,0,0)";
                // spiel um platz 21
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(18," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(4).at(1) + "','" + krGameResults.at(12).at(1) + "','" + divisionJ->at(3) + "',0,0,0,0,0,0)";
                // spiel um platz 31
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(19," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults.at(6).at(1) + "','" + krGameResults.at(14).at(1) + "','" + divisionK->at(3) + "',0,0,0,0,0,0)";
                // spiel um platz 41
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(20," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(6).at(1) + "','" + krGameResults.at(14).at(1) + "','" + divisionL->at(3) + "',0,0,0,0,0,0)";

                startRound = startRound.addSecs(addzeit);
                lastRoundNr++;
                // spiel um platz 1
                lastGameNr++;
                querys << "INSERT INTO platzspiele_spielplan VALUES(20," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(0).at(1) + "','" + krGameResults.at(8).at(1) + "','',0,0,0,0,0,0)";
                break;
        }
    }
    else
    {
        QStringList referees;
        QList<QStringList> krGameResultsCopy = krGameResults;
        int resultDivisionsZwCountKorrigiert = resultDivisionsZw.count();

        // if 55 teams, remove the first 5 kr game results, because this teams do not play any classement games
        if(teamsCount == 55)
        {
            for(int t = 0; t < 5; t++)
                krGameResultsCopy.removeFirst();

            resultDivisionsZwCountKorrigiert--;
        }

        // get as many referees as needed for first round
        for(int z = 0; referees.count() < fieldCount; z++)
        {
            for(int k = 0; k < resultDivisionsZw.at(z).count() && referees.count() < fieldCount; k++)
                referees.append(resultDivisionsZw.at(z).at(k));
        }

        // generate games
        for(int i = 0, x = resultDivisionsZwCountKorrigiert - 1, y = ((resultDivisionsZw.at(x).count()
                            + resultDivisionsZw.at(x - 1).count()) / 2) - 1,
            startingReferee = 0, id = 1, fCount = 1; (i + 5) < krGameResultsCopy.count(); id++, lastGameNr++, startingReferee++)
        {
            QString referee1 = "", referee2 = "";

            // get the referee for the looser game
            if(startingReferee < fieldCount)
            {
                referee1 = referees.at(startingReferee);
                startingReferee++;
            }

            // check if there is a next referee for the winner game
            if(startingReferee < fieldCount)
                referee2 = referees.at(startingReferee);

            // get winner and looser for the next related games
            QString winner1 = krGameResultsCopy.at(i).at(1);
            QString looser1 = krGameResultsCopy.at(i).at(2);

            QString winner2 = krGameResultsCopy.at(i + 5).at(1);
            QString looser2 = krGameResultsCopy.at(i + 5).at(2);

            // create looser query
            querys << "INSERT INTO platzspiele_spielplan VALUES(" + string(id) + "," + string(lastRoundNr) + "," + string(lastGameNr) + ",'"
                      + startRound.toString("hh:mm") + "'," + string(fCount) + ",'','"
                      + looser1 + "','" + looser2 + "','" + referee1 + "',0,0,0,0,0,0)";

            if(fCount >= fieldCount)
            {
                fCount = 1;
                lastRoundNr++;
                startRound = startRound.addSecs(addzeit);
            }
            else
            {
                fCount++;
            }

            id++; lastGameNr++;

            // create winner query
            querys << "INSERT INTO platzspiele_spielplan VALUES(" + string(id) + "," + string(lastRoundNr) + "," + string(lastGameNr) + ",'"
                      + startRound.toString("hh:mm") + "'," + string(fCount) + ",'','"
                      + winner1 + "','" + winner2 + "','" + referee2 + "',0,0,0,0,0,0)";

            if(fCount >= fieldCount)
            {
                fCount = 1;
                lastRoundNr++;
                startRound = startRound.addSecs(addzeit);
            }
            else
            {
                fCount++;
            }

            if(i < y)
            {
                i++;
            }
            else
            {
                x = x - 2;
                int toAdd = resultDivisionsZw.at(x).count() + resultDivisionsZw.at(x - 1).count();
                y = y + toAdd;
                i = i + (toAdd / 2);
                i++;
            }
        }
    }

    return querys;
}

// create classement
QStringList ClassementGames::createClassement()
{
    QStringList querys;
    QList<QStringList> bottomRankings;
    int rowid = 0, id = 0;

    // rest of classement, teams which played vorrunde and zwischenrunde
    if(bettyspiele == 0)
    {
        for(int i = 0, x = 0; i < plGameResults.size(); i++)
        {
            QStringList plGame = plGameResults.at(i);
            querys << "INSERT INTO platzierungen VALUES(" + string(id++) + "," + string(classements.at(x++)) + ",'" + plGame.at(1) + "')";
            querys << "INSERT INTO platzierungen VALUES(" + string(id++) + "," + string(classements.at(x++)) + ",'" + plGame.at(2) + "')";
        }

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
    }
    else
    {
        int classement = teamsCount;

        switch(teamsCount)
        {
            case 55:
                // create the classements for the worst teams
                bottomRankings = dbRead("SELECT ms FROM zwischenrunde_grk_view");
                for(int i = 4; i >= 0; i--)
                {
                    querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(classement) + ",'" + bottomRankings.at(i).at(0) + "')";
                    id++; classement--;
                }

                // create the classements for teams that played cross game
                for(int i = 0; i < 5; i++, id++, classement--)
                {
                   // generate looser query
                    querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(classement) + ",'" + krGameResults.at(i).at(2) + "')";

                    id++; classement--;

                    // generate winner query
                    querys << "INSERT INTO platzierungen VALUES(" + string(id) + "," + string(classement) + ",'" + krGameResults.at(i).at(1) + "')";
                }

                // create the next classements for teams that played classement game
                for(int i = 0, x = classement; x > 0; i++, id++, x--)
                {
                    QStringList plGame = plGameResults.at(i);
                    // generate looser query
                    querys << "INSERT INTO platzierungen VALUES(" + string(id++) + "," + string(x) + ",'" + plGame.at(2) + "')";

                    id++; x--;

                    // generate winner query
                    querys << "INSERT INTO platzierungen VALUES(" + string(id++) + "," + string(x) + ",'" + plGame.at(1) + "')";
                }
                break;

            case 60:
                for(int i = 0, x = classement; x > 0; i++, id++, x--)
                {
                    // generate looser query
                    querys << "INSERT INTO platzierungen VALUES(" + string(id++) + "," + string(x) + ",'" + plGameResults.at(i).at(2) + "')";

                    id++; x--;

                    // generate winner query
                    querys << "INSERT INTO platzierungen VALUES(" + string(id++) + "," + string(x) + ",'" + plGameResults.at(i).at(1) + "')";
                }
                break;
        }
    }

    return querys;
}
