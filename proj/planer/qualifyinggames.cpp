#include "qualifyinggames.h"

QualifyingGames::QualifyingGames(Database *db, QStringList *grPrefix)
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

QualifyingGames::~QualifyingGames()
{
}

void QualifyingGames::setParameters(QString startTurnier, int countSatz, int minSatz, int minPause, int fieldCount, int teamsCount, QStringList *fieldNames)
{
    emit logMessages("VORRUNDE:: set vr params");
    this->startTurnier = startTurnier;
    this->satz = countSatz;
    this->min = minSatz;
    this->pause = minPause;
    this->fieldCount = fieldCount;
    this->teamsCount = teamsCount;
    this->fieldNames = fieldNames;

    setTimeParameters(satz, min, pause);
}

void QualifyingGames::generateGames()
{
    QList<QStringList> divisionsList;
    QList<QList<QStringList> > divisionsGameList;
    QStringList execQuerys;

    prefixCount = getPrefixCount();
    gamesCount = 0;

    // preparte lists for all divisions
    for(int i = 0; i < prefixCount; i++)
    {
        QStringList division;
        QString group = getPrefix(i);
        QList<QStringList> list = dbRead("SELECT " + group + " FROM mannschaften WHERE " + group + " != ''");

        // for each division one stringlist
        for(int j = 0; j < list.size(); j++)
        {
            division << list.at(j).at(0);
        }

        // collect all divisions
        divisionsList << division;
    }

    // generate games for each division
    foreach(QStringList divisionList, divisionsList)
        divisionsGameList.append(generateDivisionGames(&divisionList));

    // count games in divisions
    foreach(QList<QStringList> divisionGameList, divisionsGameList)
        gamesCount += divisionGameList.count();

    // generate game plan over all divisonal games
    execQuerys << generateGamePlan(&divisionsGameList, gamesCount, QTime::fromString(startTurnier), satz, min, pause);

    // insert field numbers into gameplan
    execQuerys << insertFieldNr("vorrunde_spielplan", gamesCount, fieldCount);

    // insert field names
    execQuerys << insertFieldNames("vorrunde_spielplan", fieldNames);

    // generate vorrunde divisions result tables
    execQuerys << generateResultTables("vorrunde_erg_gr", &divisionsList);

    // execute all statements to database
    dbWrite(&execQuerys);
}

// generate divisional game plan, use game sequence defined in constructor
QList<QStringList> QualifyingGames::generateDivisionGames(QStringList *divisionList)
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
                    result.append(QStringList() << divisionList->at(game.at(0)) << divisionList->at(game.at(1)) << divisionList->at(game.at(2)));
                else
                    result.append(QStringList() << "---" << "---" << "---");
            }
            first = false;
        }
        else
        {
            foreach(QList<int> game, fourMsDivision)
            {
                if(game.at(0) != 999)
                    result.append(QStringList() << divisionList->at(game.at(0)) << divisionList->at(game.at(1)) << divisionList->at(game.at(2)));
                else
                    result.append(QStringList() << "---" << "---" << "---");
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
QStringList QualifyingGames::generateGamePlan(QList<QList<QStringList> > *divisionsGameList, int gamesCount, QTime tournamentStart, int satz, int min, int pause)
{
    QStringList querys;
    int addzeit = ((satz * min) + pause) * 60;

    for(int divisionCount = 0, rowCount = 1, dataRow = 0, roundCount = 1; rowCount <= gamesCount; divisionCount++)
    {
        if(divisionCount >= divisionsGameList->count())
        {
            divisionCount = 0;
            dataRow++;
            roundCount++;
            tournamentStart = tournamentStart.addSecs(addzeit);
        }

        if(dataRow < divisionsGameList->at(divisionCount).count())
        {
            QList<QStringList> divisionGameList = divisionsGameList->at(divisionCount);
            querys << "INSERT INTO vorrunde_spielplan VALUES(" + string(rowCount) + "," + string(roundCount) + "," + string(rowCount) + ",'" + tournamentStart.toString("hh:mm") + "',0,'','" + divisionGameList.at(dataRow).at(0) + "','" + divisionGameList.at(dataRow).at(1) + "','" + divisionGameList.at(dataRow).at(2) + "',0,0,0,0,0,0)";
            rowCount++;
        }
    }

    return querys;
}
