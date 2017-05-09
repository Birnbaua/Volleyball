#include "crossgames.h"

CrossGames::CrossGames(Database *db, QStringList *grPrefix)
    : BaseGameHandling(db, grPrefix)
{
}

CrossGames::~CrossGames()
{
}

// set kreuzspiele params
void CrossGames::setParameters(QString startRound, int lastgameTime, int pauseZwKr, int countSatz, int minSatz, int minPause, int fieldCount, int teamsCount, QStringList *fieldNames, int lastRoundNr, int lastGameNr)
{
    emit logMessages("KREUZSPIELE:: set kreuszpiele params");
    this->startRound = startRound;
    this->satz = countSatz;
    this->min = minSatz;
    this->pause = minPause;
    this->fieldCount = fieldCount;
    this->teamsCount = teamsCount;
    this->fieldNames = fieldNames;
    this->lastGameNr = lastGameNr;
    this->lastRoundNr = lastRoundNr;

    setTimeParameters(satz, min, pause);

    QTime time = QTime::fromString(this->startRound, "hh:mm");
    time = time.addSecs((pauseZwKr * 60) + (lastgameTime * 60));
    this->startRound = time.toString("hh:mm");
}

// generate kreuzspiele
void CrossGames::generateCrossGames()
{
    QStringList execQuerys;

    prefixCount = getPrefixCount();

    execQuerys << generateGamePlan(QTime::fromString(startRound));

    execQuerys << insertFieldNames("kreuzspiele_spielplan", fieldNames);

    dbWrite(&execQuerys);
}

// get teamnames from list
QStringList CrossGames::getDivisionTeamNames(const QList<QStringList> *list)
{
    QStringList nameList;

    for(int i = 0; i < list->size(); i++)
        nameList << list->at(i).at(0);

    return nameList;
}

// generate game plan over all divisions
QStringList CrossGames::generateGamePlan(QTime startRound)
{
    int addzeit = ((satz * min) + pause)*60;
    QStringList querys;

    // get list current ranking results
    QList<QList<QStringList> > resultDivisionsZw;

    // help lists
    QStringList divisionA, divisionB, divisionC, divisionD, divisionE, divisionF, divisionG, divisionH, divisionI, divisionJ;

    // read divisional rank results and add to list
    for(int i = 0; i < prefixCount; i++)
        resultDivisionsZw.append(dbRead("select ms, punkte, satz from zwischenrunde_erg_gr" + getPrefix(i) + " order by punkte desc, satz desc"));

    divisionA = getDivisionTeamNames(&(resultDivisionsZw.at(0)));
    divisionB = getDivisionTeamNames(&(resultDivisionsZw.at(1)));
    divisionC = getDivisionTeamNames(&(resultDivisionsZw.at(2)));
    divisionD = getDivisionTeamNames(&(resultDivisionsZw.at(3)));
    divisionE = getDivisionTeamNames(&(resultDivisionsZw.at(4)));
    divisionF = getDivisionTeamNames(&(resultDivisionsZw.at(5)));
    divisionG = getDivisionTeamNames(&(resultDivisionsZw.at(6)));
    divisionH = getDivisionTeamNames(&(resultDivisionsZw.at(7)));
    divisionI = getDivisionTeamNames(&(resultDivisionsZw.at(8)));
    divisionJ = getDivisionTeamNames(&(resultDivisionsZw.at(9)));

    lastRoundNr++;
    switch(teamsCount)
    {
        case 20:
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(1," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA.at(0) + "','" + divisionB.at(1) + "','" + divisionA.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(2," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionA.at(2) + "','" + divisionB.at(3) + "','" + divisionA.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(3," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionC.at(0) + "','" + divisionD.at(1) + "','" + divisionC.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(4," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionC.at(2) + "','" + divisionD.at(3) + "','" + divisionC.at(3) + "',0,0,0,0,0,0)";
            startRound = startRound.addSecs(addzeit);
            lastRoundNr++; lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(5," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA.at(1) + "','" + divisionB.at(0) + "','" + divisionB.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(6," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionA.at(3) + "','" + divisionB.at(2) + "','" + divisionB.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(7," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionC.at(1) + "','" + divisionD.at(0) + "','" + divisionD.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionC.at(3) + "','" + divisionD.at(2) + "','" + divisionD.at(3) + "',0,0,0,0,0,0)";
            break;

        case 25:
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(1," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA.at(0) + "','" + divisionB.at(1) + "','" + divisionA.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(2," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionA.at(2) + "','" + divisionB.at(3) + "','" + divisionA.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(3," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionC.at(0) + "','" + divisionD.at(1) + "','" + divisionC.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(4," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionC.at(2) + "','" + divisionD.at(3) + "','" + divisionC.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(5," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionA.at(1) + "','" + divisionB.at(0) + "','" + divisionB.at(1) + "',0,0,0,0,0,0)";
            startRound = startRound.addSecs(addzeit);
            lastRoundNr++; lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(6," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA.at(3) + "','" + divisionB.at(2) + "','" + divisionB.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(7," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionC.at(1) + "','" + divisionD.at(0) + "','" + divisionD.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionC.at(3) + "','" + divisionD.at(2) + "','" + divisionD.at(3) + "',0,0,0,0,0,0)";
            break;

        case 28:
        case 30:
        case 35:
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(1," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA.at(0) + "','" + divisionB.at(1) + "','" + divisionA.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(2," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionA.at(2) + "','" + divisionB.at(3) + "','" + divisionA.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(3," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionC.at(0) + "','" + divisionD.at(1) + "','" + divisionC.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(4," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionC.at(2) + "','" + divisionD.at(3) + "','" + divisionC.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(5," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionE.at(0) + "','" + divisionF.at(1) + "','" + divisionE.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(6," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + divisionE.at(2) + "','" + divisionF.at(3) + "','" + divisionE.at(3) + "',0,0,0,0,0,0)";
            startRound = startRound.addSecs(addzeit);
            lastRoundNr++; lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(7," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + divisionA.at(1) + "','" + divisionB.at(0) + "','" + divisionB.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionA.at(3) + "','" + divisionB.at(2) + "','" + divisionB.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(9," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionC.at(1) + "','" + divisionD.at(0) + "','" + divisionD.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(10," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionC.at(3) + "','" + divisionD.at(2) + "','" + divisionD.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(11," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionE.at(1) + "','" + divisionF.at(0) + "','" + divisionF.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionE.at(3) + "','" + divisionF.at(2) + "','" + divisionF.at(3) + "',0,0,0,0,0,0)";
            break;

        case 40:
        case 45:
<<<<<<< HEAD
        case 50:
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(1," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA.at(0) + "','" + divisionB.at(1) + "','" + divisionA.at(1) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(2," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionA.at(2) + "','" + divisionB.at(3) + "','" + divisionA.at(3) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(3," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionC.at(0) + "','" + divisionD.at(1) + "','" + divisionC.at(1) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(4," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionC.at(2) + "','" + divisionD.at(3) + "','" + divisionC.at(3) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(5," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionE.at(0) + "','" + divisionF.at(1) + "','" + divisionE.at(1) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(6," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + divisionE.at(2) + "','" + divisionF.at(3) + "','" + divisionE.at(3) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(7," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + divisionG.at(0) + "','" + divisionH.at(1) + "','" + divisionG.at(1) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + divisionG.at(2) + "','" + divisionH.at(3) + "','" + divisionG.at(3) + "',0,0,0,0,0,0)";
                startRound = startRound.addSecs(addzeit);
                lastRoundNr++; lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(9," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + divisionA.at(1) + "','" + divisionB.at(0) + "','" + divisionB.at(1) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(10," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + divisionA.at(3) + "','" + divisionB.at(2) + "','" + divisionB.at(3) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(11," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + divisionC.at(1) + "','" + divisionD.at(0) + "','" + divisionD.at(1) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionC.at(3) + "','" + divisionD.at(2) + "','" + divisionD.at(3) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(13," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionE.at(1) + "','" + divisionF.at(0) + "','" + divisionF.at(1) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(14," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionE.at(3) + "','" + divisionF.at(2) + "','" + divisionF.at(3) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(15," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionG.at(1) + "','" + divisionH.at(0) + "','" + divisionH.at(1) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(16," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionG.at(3) + "','" + divisionH.at(2) + "','" + divisionH.at(3) + "',0,0,0,0,0,0)";
                break;
=======
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(1," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA.at(0) + "','" + divisionB.at(1) + "','" + divisionA.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(2," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionA.at(2) + "','" + divisionB.at(3) + "','" + divisionA.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(3," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionC.at(0) + "','" + divisionD.at(1) + "','" + divisionC.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(4," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionC.at(2) + "','" + divisionD.at(3) + "','" + divisionC.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(5," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionE.at(0) + "','" + divisionF.at(1) + "','" + divisionE.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(6," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + divisionE.at(2) + "','" + divisionF.at(3) + "','" + divisionE.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(7," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + divisionG.at(0) + "','" + divisionH.at(1) + "','" + divisionG.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + divisionG.at(2) + "','" + divisionH.at(3) + "','" + divisionG.at(3) + "',0,0,0,0,0,0)";
            startRound = startRound.addSecs(addzeit);
            lastRoundNr++; lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(9," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + divisionA.at(1) + "','" + divisionB.at(0) + "','" + divisionB.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(10," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + divisionA.at(3) + "','" + divisionB.at(2) + "','" + divisionB.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(11," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + divisionC.at(1) + "','" + divisionD.at(0) + "','" + divisionD.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionC.at(3) + "','" + divisionD.at(2) + "','" + divisionD.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(13," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionE.at(1) + "','" + divisionF.at(0) + "','" + divisionF.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(14," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionE.at(3) + "','" + divisionF.at(2) + "','" + divisionF.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(15," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionG.at(1) + "','" + divisionH.at(0) + "','" + divisionH.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(16," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionG.at(3) + "','" + divisionH.at(2) + "','" + divisionH.at(3) + "',0,0,0,0,0,0)";
            break;

        case 50:
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(1," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA.at(0) + "','" + divisionB.at(1) + "','" + divisionA.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(2," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionA.at(2) + "','" + divisionB.at(3) + "','" + divisionA.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(3," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionC.at(0) + "','" + divisionD.at(1) + "','" + divisionC.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(4," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionC.at(2) + "','" + divisionD.at(3) + "','" + divisionC.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(5," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionE.at(0) + "','" + divisionF.at(1) + "','" + divisionE.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(6," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + divisionE.at(2) + "','" + divisionF.at(3) + "','" + divisionE.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(7," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + divisionG.at(0) + "','" + divisionH.at(1) + "','" + divisionG.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + divisionG.at(2) + "','" + divisionH.at(3) + "','" + divisionG.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(9," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',9,'','" + divisionI.at(0) + "','" + divisionJ.at(1) + "','" + divisionI.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(10," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',10,'','" + divisionI.at(2) + "','" + divisionJ.at(3) + "','" + divisionI.at(3) + "',0,0,0,0,0,0)";
            startRound = startRound.addSecs(addzeit);
            lastRoundNr++; lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(11," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',10,'','" + divisionA.at(1) + "','" + divisionB.at(0) + "','" + divisionB.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',9,'','" + divisionA.at(3) + "','" + divisionB.at(2) + "','" + divisionB.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(13," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + divisionC.at(1) + "','" + divisionD.at(0) + "','" + divisionD.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(14," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + divisionC.at(3) + "','" + divisionD.at(2) + "','" + divisionD.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(15," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + divisionE.at(1) + "','" + divisionF.at(0) + "','" + divisionF.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(16," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionE.at(3) + "','" + divisionF.at(2) + "','" + divisionF.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(17," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionG.at(1) + "','" + divisionH.at(0) + "','" + divisionH.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(18," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionG.at(3) + "','" + divisionH.at(2) + "','" + divisionH.at(3) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(19," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionI.at(1) + "','" + divisionJ.at(0) + "','" + divisionI.at(1) + "',0,0,0,0,0,0)";
            lastGameNr++;
            querys << "INSERT INTO kreuzspiele_spielplan VALUES(20," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionI.at(3) + "','" + divisionJ.at(2) + "','" + divisionI.at(3) + "',0,0,0,0,0,0)";
            break;
>>>>>>> refs/remotes/origin/master
    }

    return querys;
}
