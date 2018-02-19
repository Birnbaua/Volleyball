#include "crossgames.h"

CrossGames::CrossGames(Database *db, QStringList *grPrefix)
    : BaseGameHandling(db, grPrefix)
{
}

CrossGames::~CrossGames()
{
}

// set kreuzspiele params
void CrossGames::setParameters(QString startRound, int lastgameTime, int pauseZwKr, int countSatz, int minSatz, int minPause,
                               int fieldCount, int teamsCount, int divisionCount, QStringList *fieldNames, int lastRoundNr, int lastGameNr,
                               int bettyspiele)
{
    emit logMessages("KREUZSPIELE:: set kreuszpiele params");
    this->startRound = startRound;
    this->satz = countSatz;
    this->min = minSatz;
    this->pause = minPause;
    this->fieldCount = fieldCount;
    this->teamsCount = teamsCount;
    this->divisionCount = divisionCount;
    this->fieldNames = fieldNames;
    this->lastGameNr = lastGameNr;
    this->lastRoundNr = lastRoundNr;
    this->bettyspiele = bettyspiele;

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
    gamesCount = 0;

    execQuerys << generateGamePlan(QTime::fromString(startRound));

    if(bettyspiele == 1)
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
    int addzeit = ((satz * min) + pause) * 60;
    QStringList querys;

    // get list current ranking results
    QList<QList<QStringList> > resultDivisionsZw;
    QList<QStringList*> finalDivisions;
    // help lists
    QStringList divisionA, divisionB, divisionC, divisionD, divisionE, divisionF, divisionG, divisionH, divisionI, divisionJ, divisionK, divisionL;

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
    divisionK = getDivisionTeamNames(&(resultDivisionsZw.at(10)));
    divisionL = getDivisionTeamNames(&(resultDivisionsZw.at(11))); 

    lastRoundNr++;

    if(bettyspiele == 0)
    {
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
            case 55:
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

            case 60:
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
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(11," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',11,'','" + divisionK.at(2) + "','" + divisionL.at(3) + "','" + divisionK.at(3) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',12,'','" + divisionK.at(2) + "','" + divisionL.at(3) + "','" + divisionK.at(3) + "',0,0,0,0,0,0)";

                startRound = startRound.addSecs(addzeit);
                lastRoundNr++; lastGameNr++;

                querys << "INSERT INTO kreuzspiele_spielplan VALUES(13," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',12,'','" + divisionA.at(1) + "','" + divisionB.at(0) + "','" + divisionB.at(1) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(14," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',11,'','" + divisionA.at(3) + "','" + divisionB.at(2) + "','" + divisionB.at(3) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(15," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',10,'','" + divisionC.at(1) + "','" + divisionD.at(0) + "','" + divisionD.at(1) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(16," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',9,'','" + divisionC.at(3) + "','" + divisionD.at(2) + "','" + divisionD.at(3) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(17," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + divisionE.at(1) + "','" + divisionF.at(0) + "','" + divisionF.at(1) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(18," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + divisionE.at(3) + "','" + divisionF.at(2) + "','" + divisionF.at(3) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(19," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + divisionG.at(1) + "','" + divisionH.at(0) + "','" + divisionH.at(1) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(20," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionG.at(3) + "','" + divisionH.at(2) + "','" + divisionH.at(3) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(21," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionI.at(1) + "','" + divisionJ.at(0) + "','" + divisionJ.at(1) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(22," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionI.at(3) + "','" + divisionJ.at(2) + "','" + divisionJ.at(3) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(23," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionK.at(1) + "','" + divisionL.at(0) + "','" + divisionL.at(1) + "',0,0,0,0,0,0)";
                lastGameNr++;
                querys << "INSERT INTO kreuzspiele_spielplan VALUES(24," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionK.at(3) + "','" + divisionL.at(2) + "','" + divisionL.at(3) + "',0,0,0,0,0,0)";
                break;
        }
    }
    else
    {
        if(divisionA.count() > 0)
            finalDivisions.append(&divisionA);

        if(divisionB.count() > 0)
            finalDivisions.append(&divisionB);

        if(divisionC.count() > 0)
            finalDivisions.append(&divisionC);

        if(divisionD.count() > 0)
            finalDivisions.append(&divisionD);

        if(divisionE.count() > 0)
            finalDivisions.append(&divisionE);

        if(divisionF.count() > 0)
            finalDivisions.append(&divisionF);

        if(divisionG.count() > 0)
            finalDivisions.append(&divisionG);

        if(divisionH.count() > 0)
            finalDivisions.append(&divisionH);

        if(divisionI.count() > 0)
            finalDivisions.append(&divisionI);

        if(divisionJ.count() > 0)
            finalDivisions.append(&divisionJ);

        if(divisionK.count() > 0)
            finalDivisions.append(&divisionK);

        if(divisionL.count() > 0)
            finalDivisions.append(&divisionL);

        QList<QList<QStringList>> gameList;
        QStringList refereeList;
        lastGameNr++;

        // create game list
        for(int i = 0; i < divisionCount;)
        {
            if(i + 1 < finalDivisions.count())
            {
                int rest = (finalDivisions.at(i)->count() + finalDivisions.at(i + 1)->count()) % 2;
                int count = (finalDivisions.at(i)->count() + finalDivisions.at(i + 1)->count() - rest) / 2;
                QList<QStringList> games;

                for(int x = 0; x < count; x++)
                {
                    games.append(QStringList() << finalDivisions.at(i)->at(x) << finalDivisions.at(i + 1)->at(x));
                    gamesCount++;
                }

                gameList.append(games);
                i = i + 2;
            }
            else
            {
                break;
            }
        }

        for(int i = 0; i < gameList.count() && i < fieldCount; i++)
        {
            QList<QStringList> refList = gameList.at(i);
            for(int j = 0; j < refList.count(); j++)
            {
                refereeList.append(refList.at(j).at(0));
                refereeList.append(refList.at(j).at(1));
            }
        }

        // generate round starting with last group and last game (worst two teams)
        for(int count = 0, fCount = 1, y = (gameList.count() - 1), startingReferee = 0,
            rowCount = 1, dataRow = gameList.at((gameList.count() - 1)).count() - 1;
            count < gamesCount; rowCount++, lastGameNr++, count++, startingReferee++)
        {
            QString referee = "";
            if(startingReferee < fieldCount)
                referee = refereeList.at(startingReferee);

            querys << "INSERT INTO kreuzspiele_spielplan VALUES("
                      + string(rowCount) + "," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "', " + string(fCount) + ",'','"
                      + gameList.at(y).at(dataRow).at(0) + "','"
                      + gameList.at(y).at(dataRow).at(1) + "','"
                      + referee + "',"
                      + "0,0,0,0,0,0)";

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

            if(dataRow < 1)
            {
                dataRow = gameList.at(y).count() - 1;
                y--;
            }
            else
            {
                dataRow--;
            }
        }
    }

    return querys;
}
