#include "interimgames.h"

InterimGames::InterimGames(Database *db, QStringList *grPrefix)
{
    this->db = db;
    this->grPrefix = grPrefix;

    first = true;

    tablesToClear << "zwischenrunde_spielplan";

    for(int i = 0; i < grPrefix->size(); i++)
        tablesToClear << ("zwischenrunde_erg_gr" + grPrefix->at(i));

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
void InterimGames::setParameters(QString startRound, int pauseVrZw, int countSatz, int minSatz, int minPause, int fieldCount, int teamsCount, QStringList *fieldNames, int lastRoundNr, int lastGameNr)
{
    emit logMessages("ZWISCHENRUNDE:: set zwischenrunde params");
    this->startRound = startRound;
    this->satz = countSatz;
    this->min = minSatz;
    this->pause = minPause;
    this->fieldCount = fieldCount;
    this->teamsCount = teamsCount;
    this->fieldNames = fieldNames;
    this->lastGameNr = lastGameNr;
    this->lastRoundNr = lastRoundNr;

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
    int gamesCount = 0;

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

    // insert field numbers and names
    execQuerys << insertFieldNr(gamesCount, fieldCount);
    execQuerys << insertFieldNames();

    // generate vorrunde divisions result tables
    execQuerys << generateResultTables(&divisionsList);

    // execute all statements to database
    writeToDb(&execQuerys);

    return true;
}

// clear zwischenrunde
void InterimGames::clearAllData()
{
    QStringList querys;

    foreach(QString table, tablesToClear)
        querys << "DELETE FROM " + table;

    writeToDb(&querys);
}

// calculate result zwischenrunde
void InterimGames::calculateResult()
{
    emit logMessages("INFO:: calculating zwischenrunde results");
    QStringList execQuerys;
    QList<QStringList> zwGameResults = db->read("SELECT spiel, ms_a, ms_b, satz1a, satz1b, satz2a, satz2b, satz3a, satz3b FROM zwischenrunde_spielplan WHERE ms_a != '---' ORDER BY id ASC");
    QList<CalculateResults::teamResult> teamResults = CalculateResults::addResultsVrZw(CalculateResults::calculateResults(&zwGameResults));

    foreach(CalculateResults::teamResult tR, teamResults)
    {
        QString division;
        for(int i = 0; i < grPrefix->size(); i++)
        {
            if(db->read("SELECT * FROM zwischenrunde_erg_gr" + grPrefix->at(i) + " WHERE ms = '" + tR.teamName + "'").count() > 0)
                division = grPrefix->at(i);
        }
        execQuerys << "UPDATE zwischenrunde_erg_gr" + division + " SET punkte=" + QString::number(tR.sets) + ", satz=" + QString::number(tR.points) + " WHERE ms = '" + tR.teamName + "'";
    }

    writeToDb(&execQuerys);
}

// recalculate time schedule
void InterimGames::recalculateTimeSchedule(QTableView *qtv, QSqlTableModel *model)
{
    QTime zeit = qtv->currentIndex().data().toTime();
    int addzeit = ((satz * min) + pause)* 60;
    int runde = model->data(model->index(qtv->currentIndex().row(), 1)).toInt();

    for(int i = qtv->currentIndex().row(); i <= model->rowCount(); i++)
    {
        if(runde != model->data(model->index(i, 1)).toInt())
        {
            zeit = zeit.addSecs(addzeit);
            runde++;
        }
        model->setData(model->index(i, 3), zeit.toString("hh:mm"));
    }
}

QStringList InterimGames::checkEqualDivisionResults()
{
    for(int i = 0; i < grPrefix->size(); i++)
    {
        QList<QStringList> result = db->read("select distinct ms1.ms from zwischenrunde_erg_gr" + grPrefix->at(i)
                                             + " ms1, (select ms, satz, punkte, intern from zwischenrunde_erg_gr" + grPrefix->at(i)
                                             + ") ms2 where ms1.satz = ms2.satz and  ms1.punkte = ms2.punkte and ms1.intern = ms2.intern and ms1.ms != ms2.ms");
        if(result.count() == 2)
        {
            QStringList team1 = result.at(0);
            QStringList team2 = result.at(1);
            QString gamenr = db->read("SELECT spiel from zwischenrunde_spielplan where ms_a = '" + team1.at(0) + "' and ms_b = '" + team2.at(0) + "' or ms_a = '" + team2.at(0) + "' and ms_b = '" + team1.at(0)+ "'").at(0).at(0);
            return QStringList() << "0" << gamenr << team1.at(0) << team2.at(0);
        }
        else if(result.count() > 2)
        {
            QStringList teams;

            teams << "1";
            foreach(QStringList team, result)
                teams << team.at(0);

            return teams;
        }
    }
    return QStringList();
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
    for(int i = 0; i < grPrefix->size(); i++)
        resultDivisionsVr.append(db->read("select ms, punkte, satz, intern, extern from vorrunde_erg_gr" + grPrefix->at(i) + " order by punkte desc, satz desc, intern asc"));

    divisionsFirst = getDivisionsClassement(&resultDivisionsVr, 1);
    divisionsSecond = getDivisionsClassement(&resultDivisionsVr, 2);
    divisionsThird = getDivisionsClassement(&resultDivisionsVr, 3);
    divisionsFourth = getDivisionsClassement(&resultDivisionsVr, 4);
    divisionsFifth = getDivisionsClassement(&resultDivisionsVr, 5);

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
        default: logMessages("ZWISCHENRUNDE_ERROR:: team count not correct");
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

// insert field numbers
QStringList InterimGames::insertFieldNr(int gameCount, int fieldCount)
{
    QStringList querys;

    for (int i = 1, field = 1; i <= gameCount; i++)
    {
        for(int x = 1, fieldHelp = field; x <= fieldCount; x++, fieldHelp++, i++)
        {
            querys << "UPDATE zwischenrunde_spielplan SET feldnummer = " + QString::number(fieldHelp) + " WHERE id = " + QString::number(i);
            if(fieldHelp >= fieldCount)
                fieldHelp = 0;
        }

        i--;

        if(field < fieldCount)
            field++;
        else
            field = 1;
    }

    return querys;
}

// insert field names
QStringList InterimGames::insertFieldNames()
{
    QStringList querys;

    for(int i = 1; i <= fieldNames->count(); i++)
        querys << "UPDATE zwischenrunde_spielplan SET feldname = '" + fieldNames->at(i-1) + "' WHERE feldnummer = " + QString::number(i);

    return querys;
}

// generate qualifying divisions result table
QStringList InterimGames::generateResultTables(QList<QStringList> *divisionsList)
{
    QStringList querys;

    for(int i = 0, prefix = 0; i < divisionsList->size(); i++, prefix++)
    {
        QStringList division = divisionsList->at(i);
        QString group = grPrefix->at(prefix);

        for(int x = 0; x < division.size(); x++)
        {
            QString team = division.at(x);
            querys << "INSERT INTO zwischenrunde_erg_gr" + group + " VALUES(" + QString::number(x) + ",'" + team + "',0,0,0,0)";
        }
    }

    return querys;
}

void InterimGames::writeToDb(QStringList *querys)
{
    for(int i = 0; i < querys->size(); i++)
        db->write(querys->at(i));
}
