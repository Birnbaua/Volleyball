#include "interimgames.h"

InterimGames::InterimGames(Database *db, QStringList *grPrefix)
    : BaseGameHandling(db, grPrefix)
{
    first = true;

    // game plan for 4 teams in division
    firstFourMsDivision.append(QList<int>() << 0 << 1 << 2);
    firstFourMsDivision.append(QList<int>() << 2 << 3 << 1);
    firstFourMsDivision.append(QList<int>() << 999 << 999 << 999);
    firstFourMsDivision.append(QList<int>() << 1 << 2 << 3);
    firstFourMsDivision.append(QList<int>() << 999 << 999 << 999);
    firstFourMsDivision.append(QList<int>() << 0 << 3 << 1);
    firstFourMsDivision.append(QList<int>() << 999 << 999 << 999);
    firstFourMsDivision.append(QList<int>() << 1 << 3 << 0);
    firstFourMsDivision.append(QList<int>() << 999 << 999 << 999);
    firstFourMsDivision.append(QList<int>() << 0 << 2 << 3);

    // game plan for 4 teams in division
    fourMsDivision.append(QList<int>() << 0 << 1 << 2);
    fourMsDivision.append(QList<int>() << 999 << 999 << 999);
    fourMsDivision.append(QList<int>() << 2 << 3 << 1);
    fourMsDivision.append(QList<int>() << 999 << 999 << 999);
    fourMsDivision.append(QList<int>() << 1 << 2 << 3);
    fourMsDivision.append(QList<int>() << 999 << 999 << 999);
    fourMsDivision.append(QList<int>() << 0 << 3 << 1);
    fourMsDivision.append(QList<int>() << 999 << 999 << 999);
    fourMsDivision.append(QList<int>() << 1 << 3 << 0);
    fourMsDivision.append(QList<int>() << 0 << 2 << 3);

    // game plan for 5 teams in division
    fiveMsDivision.append(QList<int>() << 0 << 2 << 3);
    fiveMsDivision.append(QList<int>() << 1 << 3 << 4);
    fiveMsDivision.append(QList<int>() << 2 << 4 << 1);
    fiveMsDivision.append(QList<int>() << 0 << 3 << 2);
    fiveMsDivision.append(QList<int>() << 1 << 4 << 0);
    fiveMsDivision.append(QList<int>() << 2 << 3 << 1);
    fiveMsDivision.append(QList<int>() << 0 << 4 << 3);
    fiveMsDivision.append(QList<int>() << 1 << 2 << 0);
    fiveMsDivision.append(QList<int>() << 3 << 4 << 2);
    fiveMsDivision.append(QList<int>() << 0 << 1 << 4);
}

InterimGames::~InterimGames()
{
}

// set vorrunde params
void InterimGames::setParameters(QString startRound, int pauseVrZw, int countSatz, int minSatz, int minPause,
                                 int fieldCount, int teamsCount, int divisionCount, QStringList *fieldNames, int lastRoundNr, int lastGameNr,
                                 int bettyspiele)
{
    emit logMessages("ZWISCHENRUNDE:: set zwischenrunde params");
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
    time = time.addSecs(pauseVrZw * 60);
    this->startRound = time.toString("hh:mm");
}

// generate zwischenrunde
bool InterimGames::generateGames()
{
    QList<QStringList> divisionsList;
    QList<QList<QStringList> > divisionsGameList;
    QStringList execQuerys;

    prefixCount = getPrefixCount();
    gamesCount = 0;

    divisionsList = generateNewDivisions();

    if(divisionsList.count() == 0)
        return false;

    // generate games for each division
    foreach(QStringList divisionList, divisionsList)
        divisionsGameList.append(generateDivisionGames(&divisionList));

    // count games in divisions
    foreach(QList<QStringList> divisionGameList, divisionsGameList)
        gamesCount += divisionGameList.count();

    // generate game plan over all divisonal games
    execQuerys << generateGamePlan(&divisionsGameList, gamesCount, QTime::fromString(startRound), lastRoundNr, lastGameNr, satz, min, pause);

    // insert field numbers
    execQuerys << insertFieldNr("zwischenrunde_spielplan", gamesCount, fieldCount);

    // insert field names
    execQuerys << insertFieldNames("zwischenrunde_spielplan", fieldNames);

    // generate vorrunde divisions result tables
    execQuerys << generateResultTables("zwischenrunde_erg_gr", &divisionsList);

    // execute all statements to database
    dbWrite(&execQuerys);

    return true;
}

// sort qlist<qstringlist>
void InterimGames::sortList(QList<QStringList> *sortList)
{
    for(int x = sortList->count() - 1; x > 0; x--)
    {
        for (int y = 0; y < x; y++)
        {
            if(sortList->at(y).at(1) < sortList->at(y + 1).at(1))
            {
                QStringList saveList = sortList->at(y);
                sortList->replace(y, sortList->at(y + 1));
                sortList->replace(y + 1, saveList);
            }

            if(sortList->at(y).at(1).toInt() == sortList->at(y + 1).at(1).toInt()
                    && sortList->at(y).at(2).toInt() < sortList->at(y + 1).at(2).toInt())
            {
                QStringList saveList = sortList->at(y);
                sortList->replace(y, sortList->at(y + 1));
                sortList->replace(y + 1, saveList);
            }
            else if(sortList->at(y).at(1).toInt() == sortList->at(y + 1).at(1).toInt()
                    && sortList->at(y).at(2).toInt() == sortList->at(y + 1).at(2).toInt()
                    && sortList->at(y).at(4).toInt() > sortList->at(y + 1).at(4).toInt())
            {
                QStringList saveList = sortList->at(y);
                sortList->replace(y, sortList->at(y + 1));
                sortList->replace(y + 1, saveList);
            }
        }
    }
}

bool InterimGames::checkListDoubleResults(QList<QStringList> *list)
{
    for(int i = 0; i < list->size(); i++)
    {
        QStringList team1 = list->at(i);
        for(int x = 0; x < list->size(); x++)
        {
            QStringList team2 = list->at(x);
            if(team1.at(0) != team2.at(0))
            {
                if(team1.at(1) == team2.at(1) && team1.at(2) == team2.at(2) && team1.at(4) == team2.at(4))
                    return true;
            }
        }
    }
    return false;
}

// get divisions classmenet => all divisions first, ...
QList<QStringList> InterimGames::getDivisionsClassement(QList<QList<QStringList> > *divisionsClassements, int rank)
{
    QList<QStringList> result;

    if(rank == 0)
        return QList<QStringList>();

    for(int i = 0; i < divisionsClassements->size(); i++)
        result.append(divisionsClassements->at(i).at(rank - 1));

    return result;
}

// create team list
QStringList InterimGames::getTeamList(QList<QStringList> *teamsDivisions)
{
    QStringList result;

    for(int i = 0; i < teamsDivisions->size(); i++)
        result.append(teamsDivisions->at(i).at(0));

    return result;
}

// generate new divisions
QList<QStringList> InterimGames::generateNewDivisions()
{
    // help lists
    QList<QStringList> divisionsFirst, divisionsSecond, divisionsThird, divisionsFourth, divisionsFifth;
    QStringList divisionsFirstNames, divisionsSecondNames, divisionsThirdNames, divisionsFourthNames, divisionsFifthNames;

    // get list current ranking results
    QList<QList<QStringList> > resultDivisionsVr;

    // new list for new divisions by rank result
    QList<QStringList> newDivisionsZw;

    // read divisional rank results and add to list
    for(int i = 0; i < divisionCount; i++)
        resultDivisionsVr.append(dbRead("select ms, punkte, satz, intern, extern from vorrunde_erg_gr" + getPrefix(i) + " order by punkte desc, satz desc, intern asc"));

    divisionsFirst = getDivisionsClassement(&resultDivisionsVr, 1);
    divisionsSecond = getDivisionsClassement(&resultDivisionsVr, 2);
    divisionsThird = getDivisionsClassement(&resultDivisionsVr, 3);
    divisionsFourth = getDivisionsClassement(&resultDivisionsVr, 4);
    divisionsFifth = getDivisionsClassement(&resultDivisionsVr, 5);

    emit logMessages("INFO: teams count=" + QString::number(teamsCount) + ", bettyspielplan=" + QString::number(bettyspiele));

    if(bettyspiele == 0)
    {
        switch(teamsCount)
        {
            case 20:
                // make ranking of all divisions thrid teams
                sortList(&divisionsThird);

                if(checkListDoubleResults(&divisionsThird))
                    return QList<QStringList>();

                divisionsFirstNames = getTeamList(&divisionsFirst);
                divisionsSecondNames = getTeamList(&divisionsSecond);
                divisionsThirdNames = getTeamList(&divisionsThird);
                divisionsFourthNames = getTeamList(&divisionsFourth);
                divisionsFifthNames = getTeamList(&divisionsFifth);

                // create divisions with max 5 teams from helpList(can contain teams up to 6)
                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(0)
                                        << divisionsFirstNames.at(1)
                                        << divisionsSecondNames.at(2)
                                        << divisionsSecondNames.at(3)
                                        << divisionsThirdNames.at(0));

                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(0)
                                        << divisionsSecondNames.at(1)
                                        << divisionsFirstNames.at(2)
                                        << divisionsFirstNames.at(3)
                                        << divisionsThirdNames.at(1));

                newDivisionsZw.append(QStringList()
                                        << divisionsThirdNames.at(2)
                                        << divisionsFourthNames.at(0)
                                        << divisionsFourthNames.at(1)
                                        << divisionsFifthNames.at(2)
                                        << divisionsFifthNames.at(3));

                newDivisionsZw.append(QStringList()
                                        << divisionsThirdNames.at(3)
                                        << divisionsFifthNames.at(0)
                                        << divisionsFifthNames.at(1)
                                        << divisionsFourthNames.at(2)
                                        << divisionsFourthNames.at(3));
                break;

            case 25:
                divisionsFirstNames = getTeamList(&divisionsFirst);
                divisionsSecondNames = getTeamList(&divisionsSecond);
                divisionsThirdNames = getTeamList(&divisionsThird);
                divisionsFourthNames = getTeamList(&divisionsFourth);
                divisionsFifthNames = getTeamList(&divisionsFifth);

                newDivisionsZw.append(divisionsFirstNames);
                newDivisionsZw.append(divisionsSecondNames);
                newDivisionsZw.append(divisionsThirdNames);
                newDivisionsZw.append(divisionsFourthNames);
                newDivisionsZw.append(divisionsFifthNames);
                break;

            case 28:
                // make ranking of all divisions second teams
                sortList(&divisionsSecond);

                if(checkListDoubleResults(&divisionsSecond))
                    return QList<QStringList>();

                divisionsFirstNames = getTeamList(&divisionsFirst);
                divisionsSecondNames = getTeamList(&divisionsSecond);
                divisionsThirdNames = getTeamList(&divisionsThird);
                divisionsFourthNames = getTeamList(&divisionsFourth);
                divisionsFifthNames = getTeamList(&divisionsFifth);

                // create divisions with max 5 teams from helpList(can contain teams up to 6)
                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(0)
                                        << divisionsFirstNames.at(1)
                                        << divisionsFirstNames.at(2)
                                        << divisionsSecondNames.at(0));

                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(3)
                                        << divisionsFirstNames.at(4)
                                        << divisionsFirstNames.at(5)
                                        << divisionsSecondNames.at(1));

                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(2)
                                        << divisionsSecondNames.at(5)
                                        << divisionsThirdNames.at(0)
                                        << divisionsThirdNames.at(1)
                                        << divisionsThirdNames.at(2));

                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(3)
                                        << divisionsSecondNames.at(4)
                                        << divisionsThirdNames.at(3)
                                        << divisionsThirdNames.at(4)
                                        << divisionsThirdNames.at(5));

                newDivisionsZw.append(QStringList()
                                        << divisionsFourthNames.at(0)
                                        << divisionsFourthNames.at(1)
                                        << divisionsFourthNames.at(2)
                                        << divisionsFifthNames.at(2)
                                        << divisionsFifthNames.at(3));

                newDivisionsZw.append(QStringList()
                                        << divisionsFourthNames.at(3)
                                        << divisionsFourthNames.at(4)
                                        << divisionsFourthNames.at(5)
                                        << divisionsFifthNames.at(0)
                                        << divisionsFifthNames.at(1));
                break;

            case 30:
                // make ranking of all divisions second teams
                sortList(&divisionsSecond);

                if(checkListDoubleResults(&divisionsSecond))
                    return QList<QStringList>();

                // make ranking of all divisions fourth teams
                sortList(&divisionsFourth);

                if(checkListDoubleResults(&divisionsFourth))
                    return QList<QStringList>();

                divisionsFirstNames = getTeamList(&divisionsFirst);
                divisionsSecondNames = getTeamList(&divisionsSecond);
                divisionsThirdNames = getTeamList(&divisionsThird);
                divisionsFourthNames = getTeamList(&divisionsFourth);
                divisionsFifthNames = getTeamList(&divisionsFifth);

                // create divisions with max 5 teams from helpList(can contain teams up to 6)
                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(0)
                                        << divisionsFirstNames.at(1)
                                        << divisionsFirstNames.at(2)
                                        << divisionsSecondNames.at(0)
                                        << divisionsSecondNames.at(3));

                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(3)
                                        << divisionsFirstNames.at(4)
                                        << divisionsFirstNames.at(5)
                                        << divisionsSecondNames.at(1)
                                        << divisionsSecondNames.at(2));

                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(4)
                                        << divisionsThirdNames.at(0)
                                        << divisionsThirdNames.at(1)
                                        << divisionsThirdNames.at(2)
                                        << divisionsFourthNames.at(1));

                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(5)
                                        << divisionsThirdNames.at(3)
                                        << divisionsThirdNames.at(4)
                                        << divisionsThirdNames.at(5)
                                        << divisionsFourthNames.at(0));

                newDivisionsZw.append(QStringList()
                                        << divisionsFourthNames.at(2)
                                        << divisionsFourthNames.at(5)
                                        << divisionsFifthNames.at(0)
                                        << divisionsFifthNames.at(1)
                                        << divisionsFifthNames.at(2));

                newDivisionsZw.append(QStringList()
                                        << divisionsFourthNames.at(3)
                                        << divisionsFourthNames.at(4)
                                        << divisionsFifthNames.at(3)
                                        << divisionsFifthNames.at(4)
                                        << divisionsFifthNames.at(5));
                break;

            case 35:
                // make ranking of all divisions second teams
                sortList(&divisionsSecond);

                if(checkListDoubleResults(&divisionsFourth))
                    return QList<QStringList>();

                // make ranking of all divisions third teams
                sortList(&divisionsThird);

                if(checkListDoubleResults(&divisionsThird))
                    return QList<QStringList>();

                // make ranking of all divisions fourth teams
                sortList(&divisionsFourth);

                if(checkListDoubleResults(&divisionsFourth))
                    return QList<QStringList>();

                // make ranking of all divisions fifth teams
                sortList(&divisionsFifth);

                if(checkListDoubleResults(&divisionsFifth))
                    return QList<QStringList>();

                // get team names from divisions
                divisionsFirstNames = getTeamList(&divisionsFirst);
                divisionsSecondNames = getTeamList(&divisionsSecond);
                divisionsThirdNames = getTeamList(&divisionsThird);
                divisionsFourthNames = getTeamList(&divisionsFourth);
                divisionsFifthNames = getTeamList(&divisionsFifth);

                // create divisions with max 5 teams from helpList(can contain teams up to 6)
                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(0)
                                        << divisionsFirstNames.at(1)
                                        << divisionsFirstNames.at(2)
                                        << divisionsFirstNames.at(3)
                                        << divisionsSecondNames.at(1));

                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(4)
                                        << divisionsFirstNames.at(5)
                                        << divisionsFirstNames.at(6)
                                        << divisionsSecondNames.at(0)
                                        << divisionsSecondNames.at(2));

                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(3)
                                        << divisionsSecondNames.at(5)
                                        << divisionsThirdNames.at(0)
                                        << divisionsThirdNames.at(2)
                                        << divisionsThirdNames.at(4));

                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(4)
                                        << divisionsSecondNames.at(6)
                                        << divisionsThirdNames.at(1)
                                        << divisionsThirdNames.at(3)
                                        << divisionsThirdNames.at(5));

                newDivisionsZw.append(QStringList()
                                        << divisionsThirdNames.at(6)
                                        << divisionsFourthNames.at(1)
                                        << divisionsFourthNames.at(3)
                                        << divisionsFourthNames.at(5)
                                        << divisionsFifthNames.at(0));

                newDivisionsZw.append(QStringList()
                                        << divisionsFourthNames.at(0)
                                        << divisionsFourthNames.at(2)
                                        << divisionsFourthNames.at(4)
                                        << divisionsFourthNames.at(6)
                                        << divisionsFifthNames.at(1));

                newDivisionsZw.append(QStringList()
                                        << divisionsFifthNames.at(2)
                                        << divisionsFifthNames.at(3)
                                        << divisionsFifthNames.at(4)
                                        << divisionsFifthNames.at(5)
                                        << divisionsFifthNames.at(6));
                break;

            case 40:
                // make ranking of all divisions second teams
                sortList(&divisionsSecond);

                if(checkListDoubleResults(&divisionsSecond))
                    return QList<QStringList>();

                // make ranking of all divisions third teams
                sortList(&divisionsThird);

                if(checkListDoubleResults(&divisionsThird))
                    return QList<QStringList>();

                // make ranking of all divisions fourth teams
                sortList(&divisionsFourth);

                if(checkListDoubleResults(&divisionsFourth))
                    return QList<QStringList>();

                // make ranking of all divisions fifth teams
                sortList(&divisionsFifth);

                if(checkListDoubleResults(&divisionsFifth))
                    return QList<QStringList>();

                // get team names from divisions
                divisionsFirstNames = getTeamList(&divisionsFirst);
                divisionsSecondNames = getTeamList(&divisionsSecond);
                divisionsThirdNames = getTeamList(&divisionsThird);
                divisionsFourthNames = getTeamList(&divisionsFourth);
                divisionsFifthNames = getTeamList(&divisionsFifth);

                // create divisions with max 5 teams from helpList(can contain teams up to 5)
                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(0)
                                        << divisionsFirstNames.at(1)
                                        << divisionsFirstNames.at(2)
                                        << divisionsFirstNames.at(3)
                                        << divisionsSecondNames.at(0));

                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(4)
                                        << divisionsFirstNames.at(5)
                                        << divisionsFirstNames.at(6)
                                        << divisionsFirstNames.at(7)
                                        << divisionsSecondNames.at(1));

                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(2)
                                        << divisionsSecondNames.at(3)
                                        << divisionsSecondNames.at(4)
                                        << divisionsThirdNames.at(0)
                                        << divisionsThirdNames.at(2));

                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(5)
                                        << divisionsSecondNames.at(6)
                                        << divisionsSecondNames.at(7)
                                        << divisionsThirdNames.at(1)
                                        << divisionsThirdNames.at(3));

                newDivisionsZw.append(QStringList()
                                        << divisionsThirdNames.at(4)
                                        << divisionsThirdNames.at(6)
                                        << divisionsFourthNames.at(0)
                                        << divisionsFourthNames.at(2)
                                        << divisionsFourthNames.at(4));

                newDivisionsZw.append(QStringList()
                                        << divisionsThirdNames.at(5)
                                        << divisionsThirdNames.at(7)
                                        << divisionsFourthNames.at(1)
                                        << divisionsFourthNames.at(3)
                                        << divisionsFourthNames.at(5));

                newDivisionsZw.append(QStringList()
                                        << divisionsFourthNames.at(6)
                                        << divisionsFifthNames.at(0)
                                        << divisionsFifthNames.at(2)
                                        << divisionsFifthNames.at(4)
                                        << divisionsFifthNames.at(6));
                newDivisionsZw.append(QStringList()
                                        << divisionsFourthNames.at(7)
                                        << divisionsFifthNames.at(1)
                                        << divisionsFifthNames.at(3)
                                        << divisionsFifthNames.at(5)
                                        << divisionsFifthNames.at(7));
                break;

            case 45:
                // make ranking of all divisions second teams
                sortList(&divisionsSecond);

                if(checkListDoubleResults(&divisionsSecond))
                    return QList<QStringList>();

                // make ranking of all divisions third teams
                sortList(&divisionsThird);

                if(checkListDoubleResults(&divisionsThird))
                    return QList<QStringList>();

                // make ranking of all divisions fourth teams
                sortList(&divisionsFourth);

                if(checkListDoubleResults(&divisionsFourth))
                    return QList<QStringList>();

                // make ranking of all divisions fifth teams
                sortList(&divisionsFifth);

                if(checkListDoubleResults(&divisionsFifth))
                    return QList<QStringList>();

                // get team names from divisions
                divisionsFirstNames = getTeamList(&divisionsFirst);
                divisionsSecondNames = getTeamList(&divisionsSecond);
                divisionsThirdNames = getTeamList(&divisionsThird);
                divisionsFourthNames = getTeamList(&divisionsFourth);
                divisionsFifthNames = getTeamList(&divisionsFifth);

                // create divisions with max 5 teams from helpList(can contain teams up to 5)
                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(0)
                                        << divisionsFirstNames.at(1)
                                        << divisionsFirstNames.at(2)
                                        << divisionsFirstNames.at(3)
                                        << divisionsFirstNames.at(4));

                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(5)
                                        << divisionsFirstNames.at(6)
                                        << divisionsFirstNames.at(7)
                                        << divisionsFirstNames.at(8)
                                        << divisionsSecondNames.at(0));

                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(1)
                                        << divisionsSecondNames.at(2)
                                        << divisionsSecondNames.at(3)
                                        << divisionsSecondNames.at(4)
                                        << divisionsThirdNames.at(0));

                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(5)
                                        << divisionsSecondNames.at(6)
                                        << divisionsSecondNames.at(7)
                                        << divisionsSecondNames.at(8)
                                        << divisionsThirdNames.at(1));

                newDivisionsZw.append(QStringList()
                                        << divisionsThirdNames.at(2)
                                        << divisionsThirdNames.at(4)
                                        << divisionsThirdNames.at(6)
                                        << divisionsThirdNames.at(8)
                                        << divisionsFourthNames.at(0));

                newDivisionsZw.append(QStringList()
                                        << divisionsThirdNames.at(3)
                                        << divisionsThirdNames.at(5)
                                        << divisionsThirdNames.at(7)
                                        << divisionsFourthNames.at(1)
                                        << divisionsFourthNames.at(2));

                newDivisionsZw.append(QStringList()
                                        << divisionsFourthNames.at(4)
                                        << divisionsFourthNames.at(6)
                                        << divisionsFourthNames.at(8)
                                        << divisionsFifthNames.at(0)
                                        << divisionsFifthNames.at(2));

                newDivisionsZw.append(QStringList()
                                        << divisionsFourthNames.at(3)
                                        << divisionsFourthNames.at(5)
                                        << divisionsFourthNames.at(7)
                                        << divisionsFifthNames.at(1)
                                        << divisionsFifthNames.at(3));

                newDivisionsZw.append(QStringList()
                                        << divisionsFifthNames.at(4)
                                        << divisionsFifthNames.at(5)
                                        << divisionsFifthNames.at(6)
                                        << divisionsFifthNames.at(7)
                                        << divisionsFifthNames.at(8));
                break;

            case 50:
                // get team names from divisions
                divisionsFirstNames = getTeamList(&divisionsFirst);
                divisionsSecondNames = getTeamList(&divisionsSecond);
                divisionsThirdNames = getTeamList(&divisionsThird);
                divisionsFourthNames = getTeamList(&divisionsFourth);
                divisionsFifthNames = getTeamList(&divisionsFifth);

                // create divisions with max 5 teams from helpList(can contain teams up to 5)
                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(0)
                                        << divisionsFirstNames.at(1)
                                        << divisionsFirstNames.at(2)
                                        << divisionsFirstNames.at(3)
                                        << divisionsFirstNames.at(4));

                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(5)
                                        << divisionsFirstNames.at(6)
                                        << divisionsFirstNames.at(7)
                                        << divisionsFirstNames.at(8)
                                        << divisionsFirstNames.at(9));

                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(0)
                                        << divisionsSecondNames.at(1)
                                        << divisionsSecondNames.at(2)
                                        << divisionsSecondNames.at(3)
                                        << divisionsSecondNames.at(4));

                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(5)
                                        << divisionsSecondNames.at(6)
                                        << divisionsSecondNames.at(7)
                                        << divisionsSecondNames.at(8)
                                        << divisionsSecondNames.at(9));

                newDivisionsZw.append(QStringList()
                                        << divisionsThirdNames.at(0)
                                        << divisionsThirdNames.at(1)
                                        << divisionsThirdNames.at(2)
                                        << divisionsThirdNames.at(3)
                                        << divisionsThirdNames.at(4));

                newDivisionsZw.append(QStringList()
                                        << divisionsThirdNames.at(5)
                                        << divisionsThirdNames.at(6)
                                        << divisionsThirdNames.at(7)
                                        << divisionsThirdNames.at(8)
                                        << divisionsThirdNames.at(9));

                newDivisionsZw.append(QStringList()
                                        << divisionsFourthNames.at(0)
                                        << divisionsFourthNames.at(1)
                                        << divisionsFourthNames.at(2)
                                        << divisionsFourthNames.at(3)
                                        << divisionsFourthNames.at(4));

                newDivisionsZw.append(QStringList()
                                        << divisionsFourthNames.at(5)
                                        << divisionsFourthNames.at(6)
                                        << divisionsFourthNames.at(7)
                                        << divisionsFourthNames.at(8)
                                        << divisionsFourthNames.at(9));

                newDivisionsZw.append(QStringList()
                                        << divisionsFifthNames.at(0)
                                        << divisionsFifthNames.at(1)
                                        << divisionsFifthNames.at(2)
                                        << divisionsFifthNames.at(3)
                                        << divisionsFifthNames.at(4));

                newDivisionsZw.append(QStringList()
                                        << divisionsFifthNames.at(5)
                                        << divisionsFifthNames.at(6)
                                        << divisionsFifthNames.at(7)
                                        << divisionsFifthNames.at(8)
                                        << divisionsFifthNames.at(9));
                break;

            case 55:
                // make ranking of all divisions second teams
                sortList(&divisionsFirst);

                if(checkListDoubleResults(&divisionsFirst))
                    return QList<QStringList>();

                // make ranking of all divisions second teams
                sortList(&divisionsSecond);

                if(checkListDoubleResults(&divisionsSecond))
                    return QList<QStringList>();

                // make ranking of all divisions third teams
                sortList(&divisionsThird);

                if(checkListDoubleResults(&divisionsThird))
                    return QList<QStringList>();

                // make ranking of all divisions fourth teams
                sortList(&divisionsFourth);

                if(checkListDoubleResults(&divisionsFourth))
                    return QList<QStringList>();

                // make ranking of all divisions fifth teams
                sortList(&divisionsFifth);

                if(checkListDoubleResults(&divisionsFifth))
                    return QList<QStringList>();

                // get team names from divisions
                divisionsFirstNames = getTeamList(&divisionsFirst);
                divisionsSecondNames = getTeamList(&divisionsSecond);
                divisionsThirdNames = getTeamList(&divisionsThird);
                divisionsFourthNames = getTeamList(&divisionsFourth);
                divisionsFifthNames = getTeamList(&divisionsFifth);

                // profi
                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(0)
                                        << divisionsFirstNames.at(2)
                                        << divisionsFirstNames.at(4)
                                        << divisionsFirstNames.at(6)
                                        << divisionsFirstNames.at(8));

                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(1)
                                        << divisionsFirstNames.at(3)
                                        << divisionsFirstNames.at(5)
                                        << divisionsFirstNames.at(7)
                                        << divisionsFirstNames.at(9));

                // hobby a
                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(10)
                                        << divisionsSecondNames.at(0)
                                        << divisionsSecondNames.at(2)
                                        << divisionsSecondNames.at(4)
                                        << divisionsSecondNames.at(6));

                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(1)
                                        << divisionsSecondNames.at(3)
                                        << divisionsSecondNames.at(5)
                                        << divisionsSecondNames.at(7)
                                        << divisionsSecondNames.at(8));

                // hobby b
                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(9)
                                        << divisionsThirdNames.at(0)
                                        << divisionsThirdNames.at(2)
                                        << divisionsThirdNames.at(4)
                                        << divisionsThirdNames.at(6));

                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(10)
                                        << divisionsThirdNames.at(1)
                                        << divisionsThirdNames.at(3)
                                        << divisionsThirdNames.at(5)
                                        << divisionsThirdNames.at(7));

                // hobby c
                newDivisionsZw.append(QStringList()
                                        << divisionsThirdNames.at(8)
                                        << divisionsThirdNames.at(10)
                                        << divisionsFourthNames.at(0)
                                        << divisionsFourthNames.at(2)
                                        << divisionsFourthNames.at(4));

                newDivisionsZw.append(QStringList()
                                        << divisionsThirdNames.at(9)
                                        << divisionsFourthNames.at(1)
                                        << divisionsFourthNames.at(3)
                                        << divisionsFourthNames.at(5)
                                        << divisionsFourthNames.at(6));

                // hobby d
                newDivisionsZw.append(QStringList()
                                        << divisionsFourthNames.at(8)
                                        << divisionsFourthNames.at(10)
                                        << divisionsFifthNames.at(0)
                                        << divisionsFifthNames.at(2)
                                        << divisionsFifthNames.at(4));

                newDivisionsZw.append(QStringList()
                                        << divisionsFourthNames.at(7)
                                        << divisionsFourthNames.at(9)
                                        << divisionsFifthNames.at(1)
                                        << divisionsFifthNames.at(3)
                                        << divisionsFifthNames.at(5));

                newDivisionsZw.append(QStringList()
                                        << divisionsFifthNames.at(6)
                                        << divisionsFifthNames.at(7)
                                        << divisionsFifthNames.at(8)
                                        << divisionsFifthNames.at(9)
                                        << divisionsFifthNames.at(10));
                break;

            case 60:
                // make ranking of all divisions second teams
                sortList(&divisionsSecond);

                if(checkListDoubleResults(&divisionsSecond))
                    return QList<QStringList>();

                // make ranking of all divisions third teams
                sortList(&divisionsThird);

                if(checkListDoubleResults(&divisionsThird))
                    return QList<QStringList>();

                // make ranking of all divisions fourth teams
                sortList(&divisionsFourth);

                if(checkListDoubleResults(&divisionsFourth))
                    return QList<QStringList>();

                // make ranking of all divisions fifth teams
                sortList(&divisionsFifth);

                if(checkListDoubleResults(&divisionsFifth))
                    return QList<QStringList>();

                // get team names from divisions
                divisionsFirstNames = getTeamList(&divisionsFirst);
                divisionsSecondNames = getTeamList(&divisionsSecond);
                divisionsThirdNames = getTeamList(&divisionsThird);
                divisionsFourthNames = getTeamList(&divisionsFourth);
                divisionsFifthNames = getTeamList(&divisionsFifth);

                // profi
                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(0)
                                        << divisionsFirstNames.at(1)
                                        << divisionsFirstNames.at(2)
                                        << divisionsFirstNames.at(3)
                                        << divisionsFirstNames.at(4));

                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(5)
                                        << divisionsFirstNames.at(6)
                                        << divisionsFirstNames.at(7)
                                        << divisionsFirstNames.at(8)
                                        << divisionsFirstNames.at(9));

                // hobby a
                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(10)
                                        << divisionsSecondNames.at(0)
                                        << divisionsSecondNames.at(1)
                                        << divisionsSecondNames.at(2)
                                        << divisionsSecondNames.at(3));

                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(11)
                                        << divisionsSecondNames.at(4)
                                        << divisionsSecondNames.at(5)
                                        << divisionsSecondNames.at(6)
                                        << divisionsSecondNames.at(7));

                // hobby b
                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(8)
                                        << divisionsSecondNames.at(9)
                                        << divisionsThirdNames.at(0)
                                        << divisionsThirdNames.at(2)
                                        << divisionsThirdNames.at(4));

                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(10)
                                        << divisionsSecondNames.at(11)
                                        << divisionsThirdNames.at(1)
                                        << divisionsThirdNames.at(3)
                                        << divisionsThirdNames.at(5));

                // hobby c
                newDivisionsZw.append(QStringList()
                                        << divisionsThirdNames.at(6)
                                        << divisionsThirdNames.at(8)
                                        << divisionsThirdNames.at(10)
                                        << divisionsFourthNames.at(0)
                                        << divisionsFourthNames.at(1));

                newDivisionsZw.append(QStringList()
                                        << divisionsThirdNames.at(7)
                                        << divisionsThirdNames.at(9)
                                        << divisionsThirdNames.at(11)
                                        << divisionsFourthNames.at(2)
                                        << divisionsFourthNames.at(3));

                // hobby d
                newDivisionsZw.append(QStringList()
                                        << divisionsFourthNames.at(4)
                                        << divisionsFourthNames.at(6)
                                        << divisionsFourthNames.at(8)
                                        << divisionsFourthNames.at(10)
                                        << divisionsFifthNames.at(0));

                newDivisionsZw.append(QStringList()
                                        << divisionsFourthNames.at(5)
                                        << divisionsFourthNames.at(7)
                                        << divisionsFourthNames.at(9)
                                        << divisionsFourthNames.at(11)
                                        << divisionsFifthNames.at(1));

                // hobby e
                newDivisionsZw.append(QStringList()
                                        << divisionsFifthNames.at(2)
                                        << divisionsFifthNames.at(4)
                                        << divisionsFifthNames.at(6)
                                        << divisionsFifthNames.at(8)
                                        << divisionsFifthNames.at(10));

                newDivisionsZw.append(QStringList()
                                        << divisionsFifthNames.at(3)
                                        << divisionsFifthNames.at(5)
                                        << divisionsFifthNames.at(7)
                                        << divisionsFifthNames.at(9)
                                        << divisionsFifthNames.at(11));

                break;

            default: logMessages("ZWISCHENRUNDE_ERROR:: team count not correct");
        }
    }
    else
    {
        switch(teamsCount)
        {
            case 50:
                // get team names from divisions
                divisionsFirstNames = getTeamList(&divisionsFirst);
                divisionsSecondNames = getTeamList(&divisionsSecond);
                divisionsThirdNames = getTeamList(&divisionsThird);
                divisionsFourthNames = getTeamList(&divisionsFourth);
                divisionsFifthNames = getTeamList(&divisionsFifth);

                // profi
                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(0)
                                        << divisionsFirstNames.at(1)
                                        << divisionsSecondNames.at(2)
                                        << divisionsSecondNames.at(3)
                                        << divisionsSecondNames.at(4));

                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(2)
                                        << divisionsFirstNames.at(3)
                                        << divisionsSecondNames.at(5)
                                        << divisionsSecondNames.at(6)
                                        << divisionsSecondNames.at(7));

                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(4)
                                        << divisionsFirstNames.at(5)
                                        << divisionsFirstNames.at(6)
                                        << divisionsSecondNames.at(8)
                                        << divisionsSecondNames.at(9));

                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(7)
                                        << divisionsFirstNames.at(8)
                                        << divisionsFirstNames.at(9)
                                        << divisionsSecondNames.at(0)
                                        << divisionsSecondNames.at(1));

                // hobby a
                newDivisionsZw.append(QStringList()
                                        << divisionsThirdNames.at(0)
                                        << divisionsThirdNames.at(1)
                                        << divisionsFourthNames.at(2)
                                        << divisionsFourthNames.at(3)
                                        << divisionsFourthNames.at(4));

                newDivisionsZw.append(QStringList()
                                        << divisionsThirdNames.at(2)
                                        << divisionsThirdNames.at(3)
                                        << divisionsFourthNames.at(5)
                                        << divisionsFourthNames.at(6)
                                        << divisionsFourthNames.at(7));

                newDivisionsZw.append(QStringList()
                                        << divisionsThirdNames.at(4)
                                        << divisionsThirdNames.at(5)
                                        << divisionsThirdNames.at(6)
                                        << divisionsFourthNames.at(8)
                                        << divisionsFourthNames.at(9));

                newDivisionsZw.append(QStringList()
                                        << divisionsThirdNames.at(7)
                                        << divisionsThirdNames.at(8)
                                        << divisionsThirdNames.at(9)
                                        << divisionsFourthNames.at(0)
                                        << divisionsFourthNames.at(1));

                // hobby b
                newDivisionsZw.append(QStringList()
                                        << divisionsFifthNames.at(0)
                                        << divisionsFifthNames.at(1)
                                        << divisionsFifthNames.at(2)
                                        << divisionsFifthNames.at(3)
                                        << divisionsFifthNames.at(4));

                newDivisionsZw.append(QStringList()
                                        << divisionsFifthNames.at(5)
                                        << divisionsFifthNames.at(6)
                                        << divisionsFifthNames.at(7)
                                        << divisionsFifthNames.at(8)
                                        << divisionsFifthNames.at(9));
                break;

            case 55:
                // make ranking of all divisions second teams
                sortList(&divisionsSecond);

                if(checkListDoubleResults(&divisionsSecond))
                    return QList<QStringList>();

                // make ranking of all divisions second teams
                sortList(&divisionsFourth);

                if(checkListDoubleResults(&divisionsFourth))
                    return QList<QStringList>();

                // make ranking of all divisions second teams
                sortList(&divisionsFifth);

                if(checkListDoubleResults(&divisionsFifth))
                    return QList<QStringList>();

                // get team names from divisions
                divisionsFirstNames = getTeamList(&divisionsFirst);
                divisionsSecondNames = getTeamList(&divisionsSecond);
                divisionsThirdNames = getTeamList(&divisionsThird);
                divisionsFourthNames = getTeamList(&divisionsFourth);
                divisionsFifthNames = getTeamList(&divisionsFifth);

                // profi
                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(0)
                                        << divisionsFirstNames.at(1)
                                        << divisionsFirstNames.at(2)
                                        << divisionsSecondNames.at(3)
                                        << divisionsSecondNames.at(7));

                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(3)
                                        << divisionsFirstNames.at(4)
                                        << divisionsFirstNames.at(5)
                                        << divisionsSecondNames.at(2)
                                        << divisionsSecondNames.at(6));

                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(6)
                                        << divisionsFirstNames.at(7)
                                        << divisionsFirstNames.at(8)
                                        << divisionsSecondNames.at(1)
                                        << divisionsSecondNames.at(5));

                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(9)
                                        << divisionsFirstNames.at(10)
                                        << divisionsSecondNames.at(0)
                                        << divisionsSecondNames.at(4)
                                        << divisionsSecondNames.at(8));

                // hobby a
                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(9)
                                        << divisionsThirdNames.at(6)
                                        << divisionsThirdNames.at(7)
                                        << divisionsThirdNames.at(8)
                                        << divisionsFourthNames.at(6));

                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(10)
                                        << divisionsThirdNames.at(9)
                                        << divisionsThirdNames.at(10)
                                        << divisionsFourthNames.at(0)
                                        << divisionsFourthNames.at(5));

                newDivisionsZw.append(QStringList()
                                        << divisionsThirdNames.at(0)
                                        << divisionsThirdNames.at(1)
                                        << divisionsThirdNames.at(2)
                                        << divisionsFourthNames.at(1)
                                        << divisionsFourthNames.at(4));

                newDivisionsZw.append(QStringList()
                                        << divisionsThirdNames.at(3)
                                        << divisionsThirdNames.at(4)
                                        << divisionsThirdNames.at(5)
                                        << divisionsFourthNames.at(2)
                                        << divisionsFourthNames.at(3));

                // hobby b
                newDivisionsZw.append(QStringList()
                                        << divisionsFourthNames.at(7)
                                        << divisionsFourthNames.at(10)
                                        << divisionsFifthNames.at(0)
                                        << divisionsFifthNames.at(3)
                                        << divisionsFifthNames.at(4));

                newDivisionsZw.append(QStringList()
                                        << divisionsFourthNames.at(8)
                                        << divisionsFourthNames.at(9)
                                        << divisionsFifthNames.at(1)
                                        << divisionsFifthNames.at(2)
                                        << divisionsFifthNames.at(5));

                // hobby c
                newDivisionsZw.append(QStringList()
                                        << divisionsFifthNames.at(6)
                                        << divisionsFifthNames.at(7)
                                        << divisionsFifthNames.at(8)
                                        << divisionsFifthNames.at(9)
                                        << divisionsFifthNames.at(10));

                break;

            case 60:
                // make ranking of all divisions second teams
                sortList(&divisionsSecond);

                if(checkListDoubleResults(&divisionsSecond))
                    return QList<QStringList>();

                // make ranking of all divisions second teams
                sortList(&divisionsFourth);

                if(checkListDoubleResults(&divisionsFourth))
                    return QList<QStringList>();

                // get team names from divisions
                divisionsFirstNames = getTeamList(&divisionsFirst);
                divisionsSecondNames = getTeamList(&divisionsSecond);
                divisionsThirdNames = getTeamList(&divisionsThird);
                divisionsFourthNames = getTeamList(&divisionsFourth);
                divisionsFifthNames = getTeamList(&divisionsFifth);

                // profi
                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(0)
                                        << divisionsFirstNames.at(1)
                                        << divisionsFirstNames.at(2)
                                        << divisionsSecondNames.at(0)
                                        << divisionsSecondNames.at(7));

                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(3)
                                        << divisionsFirstNames.at(4)
                                        << divisionsFirstNames.at(5)
                                        << divisionsSecondNames.at(1)
                                        << divisionsSecondNames.at(6));

                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(6)
                                        << divisionsFirstNames.at(7)
                                        << divisionsFirstNames.at(8)
                                        << divisionsSecondNames.at(2)
                                        << divisionsSecondNames.at(5));

                newDivisionsZw.append(QStringList()
                                        << divisionsFirstNames.at(9)
                                        << divisionsFirstNames.at(10)
                                        << divisionsFirstNames.at(11)
                                        << divisionsSecondNames.at(3)
                                        << divisionsSecondNames.at(4));

                // hobby a
                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(8)
                                        << divisionsThirdNames.at(0)
                                        << divisionsThirdNames.at(1)
                                        << divisionsThirdNames.at(2)
                                        << divisionsFourthNames.at(3));

                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(9)
                                        << divisionsThirdNames.at(3)
                                        << divisionsThirdNames.at(4)
                                        << divisionsThirdNames.at(5)
                                        << divisionsFourthNames.at(2));

                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(10)
                                        << divisionsThirdNames.at(6)
                                        << divisionsThirdNames.at(7)
                                        << divisionsThirdNames.at(8)
                                        << divisionsFourthNames.at(1));

                newDivisionsZw.append(QStringList()
                                        << divisionsSecondNames.at(11)
                                        << divisionsThirdNames.at(9)
                                        << divisionsThirdNames.at(10)
                                        << divisionsThirdNames.at(11)
                                        << divisionsFourthNames.at(0));

                // hobby b
                newDivisionsZw.append(QStringList()
                                        << divisionsFourthNames.at(4)
                                        << divisionsFourthNames.at(11)
                                        << divisionsFifthNames.at(0)
                                        << divisionsFifthNames.at(1)
                                        << divisionsFifthNames.at(2));

                newDivisionsZw.append(QStringList()
                                        << divisionsFourthNames.at(5)
                                        << divisionsFourthNames.at(10)
                                        << divisionsFifthNames.at(3)
                                        << divisionsFifthNames.at(4)
                                        << divisionsFifthNames.at(5));

                newDivisionsZw.append(QStringList()
                                        << divisionsFourthNames.at(6)
                                        << divisionsFourthNames.at(9)
                                        << divisionsFifthNames.at(6)
                                        << divisionsFifthNames.at(7)
                                        << divisionsFifthNames.at(8));

                newDivisionsZw.append(QStringList()
                                        << divisionsFourthNames.at(7)
                                        << divisionsFourthNames.at(8)
                                        << divisionsFifthNames.at(9)
                                        << divisionsFifthNames.at(10)
                                        << divisionsFifthNames.at(11));
                break;

            default: logMessages("ZWISCHENRUNDE_ERROR:: team count not correct");
        }
    }

    return newDivisionsZw;
}

// generate divisional game plan, use game sequence defined in constructor
QList<QStringList> InterimGames::generateDivisionGames(QStringList *divisionList)
{
    QList<QStringList> result;

    // four teams in division
    if(divisionList->count() == 4)
    {
        if(first)
        {
            foreach(QList<int> game, firstFourMsDivision)
            {
                if(game.at(0) != 999)
                {
                    result.append(QStringList() << divisionList->at(game.at(0)) << divisionList->at(game.at(1)) << divisionList->at(game.at(2)));
                }
                else
                {
                    result.append(QStringList() << "---" << "---" << "---");
                }
            }
            first = false;
        }
        else
        {
            foreach(QList<int> game, fourMsDivision)
            {
                if(game.at(0) != 999)
                {
                    result.append(QStringList() << divisionList->at(game.at(0)) << divisionList->at(game.at(1)) << divisionList->at(game.at(2)));
                }
                else
                {
                    result.append(QStringList() << "---" << "---" << "---");
                }
            }
            first = true;
        }
    }

    if(divisionList->count() == 5)
    {
        // five teams in division
        foreach(QList<int> game, fiveMsDivision)
            result.append(QStringList() << divisionList->at(game.at(0)) << divisionList->at(game.at(1)) << divisionList->at(game.at(2)));
    }

    return result;
}

// generate game plan over all divisions
QStringList InterimGames::generateGamePlan(QList<QList<QStringList> > *divisionsGameList, int gamesCount, QTime startRound, int lastRoundNr, int lastGameNr, int satz, int min, int pause)
{
    QStringList querys;
    int addzeit = ((satz * min) + pause) * 60;
    lastRoundNr++;

    for(int divisionCount = 0, rowCount = 1, dataRow = 0, roundCount = lastRoundNr; rowCount <= gamesCount; divisionCount++)
    {
        if(divisionCount >= divisionsGameList->count())
        {
            divisionCount = 0;
            dataRow++;
            roundCount++;
            startRound = startRound.addSecs(addzeit);
        }

        if(dataRow < divisionsGameList->at(divisionCount).count())
        {
            QList<QStringList> divisionGameList = divisionsGameList->at(divisionCount);
            querys << "INSERT INTO zwischenrunde_spielplan VALUES(" + QString::number(rowCount) + "," + QString::number(roundCount) + "," + QString::number(rowCount + lastGameNr) + ",'" + startRound.toString("hh:mm") + "',0,'','" + divisionGameList.at(dataRow).at(0) + "','" + divisionGameList.at(dataRow).at(1) + "','" + divisionGameList.at(dataRow).at(2) + "',0,0,0,0,0,0)";
            rowCount++;
        }
    }

    return querys;
}
