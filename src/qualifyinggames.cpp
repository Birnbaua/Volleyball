#include "qualifyinggames.h"

QualifyingGames::QualifyingGames(Database *db, QStringList *grPrefix)
{
    this->db = db;
    this->grPrefix = grPrefix;

    first = true;

    tablesToClear << "vorrunde_spielplan";

    for(int i = 0; i < grPrefix->size(); i++)
        tablesToClear << ("vorrunde_erg_gr" + grPrefix->at(i));

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
}

void QualifyingGames::clearAllData()
{
    QStringList querys;

    foreach(QString table, tablesToClear)
        querys << "DELETE FROM " + table;

    writeToDb(&querys);
}

void QualifyingGames::generateGames()
{
    QList<QStringList> divisionsList;
    QList<QList<QStringList> > divisionsGameList;
    QStringList execQuerys;
    int gamesCount = 0;

    // preparte lists for all divisions
    for(int i = 0; i < grPrefix->size(); i++)
    {
        QStringList division;
        QString group = grPrefix->at(i);
        QList<QStringList> list = db->read("SELECT " + group + " FROM mannschaften WHERE " + group + " != ''");

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

    // generate time schedule for game plan
    execQuerys << insertFieldNr(gamesCount, fieldCount);

    // insert field names
    execQuerys << insertFieldNames();

    // generate vorrunde divisions result tables
    execQuerys << generateResultTables(&divisionsList);

    // execute all statements to database
    writeToDb(&execQuerys);
}

void QualifyingGames::calculateResult()
{
    emit logMessages("INFO:: calculating vorrunde results");
    QStringList execQuerys;
    QList<QStringList> vrGameResults = db->read("SELECT spiel, ms_a, ms_b, satz1a, satz1b, satz2a, satz2b, satz3a, satz3b FROM vorrunde_spielplan WHERE ms_a != '---' ORDER BY id ASC");
    QList<CalculateResults::teamResult> teamResults = CalculateResults::addResultsVrZw(CalculateResults::calculateResults(&vrGameResults));

    foreach(CalculateResults::teamResult tR, teamResults)
    {
        QString division;
        for(int i = 0; i < grPrefix->size();i ++)
        {
            QString prefix = grPrefix->at(i);

            if(db->read("SELECT * FROM vorrunde_erg_gr" + prefix + " WHERE ms = '" + tR.teamName + "'").count() > 0)
                division = prefix;
        }
        execQuerys << "UPDATE vorrunde_erg_gr" + division + " SET punkte=" + QString::number(tR.sets) + ", satz=" + QString::number(tR.points) + " WHERE ms = '" + tR.teamName + "'";
    }

    writeToDb(&execQuerys);
}

void QualifyingGames::recalculateTimeSchedule(QTableView *qtv, QSqlTableModel *model)
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

QStringList QualifyingGames::checkEqualDivisionResults()
{
    QStringList result;

    for(int i = 0; i < grPrefix->size(); i++)
    {
        QString prefix = grPrefix->at(i);

        QList<QStringList> getTeams = db->read("select distinct ms1.ms from vorrunde_erg_gr"
                                                   + prefix + " ms1, (select ms, satz, punkte, intern from vorrunde_erg_gr"
                                                   + prefix + ") ms2 where ms1.satz = ms2.satz and  ms1.punkte = ms2.punkte and ms1.intern = ms2.intern and ms1.ms != ms2.ms");

        if(getTeams.count() == 2)
        {
            QStringList team1 = getTeams.at(0);
            QStringList team2 = getTeams.at(1);
            QString gamenr = db->read("SELECT spiel from vorrunde_spielplan where ms_a = '"
                                         + team1.at(0) + "' and ms_b = '" + team2.at(0) + "' or ms_a = '"
                                         + team2.at(0) + "' and ms_b = '" + team1.at(0)+ "'").at(0).at(0);

            result.append("0");
            result.append(gamenr);
            result.append(team1.at(0));
            result.append(team2.at(0));
            return result;
        }
        else if(getTeams.count() > 2)
        {
            QStringList teams;

            teams << "1";

            foreach(QStringList team, getTeams)
                teams << team.at(0);

            return teams;
        }
    }

    return result;
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
            querys << "INSERT INTO vorrunde_spielplan VALUES(" + QString::number(rowCount) + "," + QString::number(roundCount) + "," + QString::number(rowCount) + ",'" + tournamentStart.toString("hh:mm") + "',0,'','" + divisionGameList.at(dataRow).at(0) + "','" + divisionGameList.at(dataRow).at(1) + "','" + divisionGameList.at(dataRow).at(2) + "',0,0,0,0,0,0)";
            rowCount++;
        }
    }

    return querys;
}

// insert field numbers
QStringList QualifyingGames::insertFieldNr(int gameCount, int fieldCount)
{
    QStringList querys;

    for (int i = 1, field = 1; i <= gameCount; i++)
    {
        for(int x = 1, fieldHelp = field; x <= fieldCount; x++, fieldHelp++, i++)
        {
            querys << "UPDATE vorrunde_spielplan SET feldnummer = " + QString::number(fieldHelp) + " WHERE id = " + QString::number(i);
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
QStringList QualifyingGames::insertFieldNames()
{
    QStringList querys;

    for(int i = 1; i <= fieldNames->count(); i++)
        querys << "UPDATE vorrunde_spielplan SET feldname = '" + fieldNames->at(i-1) + "' WHERE feldnummer = " + QString::number(i);

    return querys;
}

// generate qualifying divisions result table
QStringList QualifyingGames::generateResultTables(QList<QStringList> *divisionsList)
{
    QStringList querys;

    for(int i = 0, prefix = 0; i < divisionsList->size(); i++, prefix++)
    {
        QStringList division = divisionsList->at(i);
        QString group = grPrefix->at(prefix);

        for(int x = 0; x < division.size(); x++)
        {
            QString team = division.at(x);
            querys << "INSERT INTO vorrunde_erg_gr" + group + " VALUES(" + QString::number(x) + ",'" + team + "',0,0,0,0)";
        }
    }

    return querys;
}

void QualifyingGames::writeToDb(QStringList *querys)
{
    for(int i = 0; i < querys->size(); i++)
        db->write(querys->at(i));
}
