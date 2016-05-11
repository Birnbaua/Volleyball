#ifndef ZWISCHENRUNDE
#define ZWISCHENRUNDE

#include <QTableView>

#include "database_v1.3.h"
#include "calculate.h"

class zwischenrunde : public QObject
{
    Q_OBJECT
public:
    zwischenrunde(database *m_Db, calculate *m_Calc, QStringList grPrefix)
    {
        this->m_Db = m_Db;
        this->m_Calc = m_Calc;
        this->grPrefix = grPrefix;

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
    
    // set vorrunde params
    void setParams(QString startTurnier, int pauseVrZw, int countSatz, int minSatz, int minPause, int fieldCount, int teamsCount, QStringList fieldNames, int lastRoundNr, int lastGameNr)
    {
        emit zwischenrundeLog("ZWISCHENRUNDE:: set zwischenrunde params");
        this->startTurnier = startTurnier;
        this->satz = countSatz;
        this->min = minSatz;
        this->pause = minPause;
        this->fieldCount = fieldCount;
        this->teamsCount = teamsCount;
        this->fieldNames = fieldNames;
        this->lastGameNr = lastGameNr;
        this->lastRoundNr = lastRoundNr;

        QTime time = QTime::fromString(this->startTurnier, "hh:mm");
        time = time.addSecs(pauseVrZw * 60);
        this->startTurnier = time.toString("hh:mm");
    }
    
    // generate zwischenrunde
    bool generate()
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
            divisionsGameList.append(generateDivisionGames(divisionList));

        // count games in divisions
        foreach(QList<QStringList> divisionGameList, divisionsGameList)
            gamesCount += divisionGameList.count();

        // generate game plan over all divisonal games
        execQuerys << generateGamePlan(divisionsGameList, gamesCount, QTime::fromString(startTurnier), lastRoundNr, lastGameNr, satz, min, pause);
        
        // insert field numbers and names
        execQuerys << insertFieldNr(gamesCount, fieldCount);
        execQuerys << insertFieldNames();
        
        // generate vorrunde divisions result tables
        execQuerys << generateResultTables(divisionsList);

        // execute all statements to database
        writeChangesDatabase(execQuerys);

        return true;
    }

    // clear zwischenrunde
    void clear()
    {
        QStringList tables;
        QStringList querys;
        
        tables << "zwischenrunde_spielplan";
        
        foreach(QString prefix, grPrefix)
        {
            tables << ("zwischenrunde_erg_gr" + prefix);
        }

        foreach(QString table, tables)
            querys << "DELETE FROM " + table;

        writeChangesDatabase(querys);
    }

    // calculate result zwischenrunde
    void calculateResult()
    {
        emit zwischenrundeLog("INFO:: calculating zwischenrunde results");
        QStringList execQuerys;
        QList<QStringList> zwGameResults = m_Db->read("SELECT spiel, ms_a, ms_b, satz1a, satz1b, satz2a, satz2b, satz3a, satz3b FROM zwischenrunde_spielplan WHERE ms_a != '---' ORDER BY id ASC");
        QList<calculate::teamResult> teamResults = m_Calc->addResultsVrZw(m_Calc->calculateResults(zwGameResults));

        foreach(calculate::teamResult tR, teamResults)
        {
            QString division;
            foreach(QString prefix, grPrefix)
            {
                if(m_Db->read("SELECT * FROM zwischenrunde_erg_gr" + prefix + " WHERE ms = '" + tR.teamName + "'").count() > 0)
                    division = prefix;
            }
            execQuerys << "UPDATE zwischenrunde_erg_gr" + division + " SET punkte=" + QString::number(tR.sets) + ", satz=" + QString::number(tR.points) + " WHERE ms = '" + tR.teamName + "'";
        }

        writeChangesDatabase(execQuerys);
    }

    // recalculate time schedule
    void recalculateTimeSchedule(QTableView *qtv, QSqlTableModel *model)
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

    QStringList checkEqualDivisionResults()
    {
        foreach(QString prefix, grPrefix)
        {
            QList<QStringList> result = m_Db->read("select distinct ms1.ms from zwischenrunde_erg_gr" + prefix + " ms1, (select ms, satz, punkte, intern from zwischenrunde_erg_gr" + prefix + ") ms2 where ms1.satz = ms2.satz and  ms1.punkte = ms2.punkte and ms1.intern = ms2.intern and ms1.ms != ms2.ms");
            if(result.count() == 2)
            {
                QStringList team1 = result.at(0);
                QStringList team2 = result.at(1);
                QString gamenr = m_Db->read("SELECT spiel from zwischenrunde_spielplan where ms_a = '" + team1.at(0) + "' and ms_b = '" + team2.at(0) + "' or ms_a = '" + team2.at(0) + "' and ms_b = '" + team1.at(0)+ "'").at(0).at(0);
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
    
signals:
    // send log msg
    void zwischenrundeLog(QString);

    void doubleResultsOverDivisions();
    
private:
    // sort qlist<qstringlist>
    QList<QStringList> sortList(QList<QStringList> sortList)
    {
        for(int x = sortList.count() - 1; x > 0; x--)
        {
            for (int y = 0; y < x; y++)
            {
                if (sortList.at(y).at(1) < sortList.at(y + 1).at(1))
                {
                    QStringList saveList = sortList.at(y);
                    sortList[y] = sortList.at(y + 1);
                    sortList[y + 1] = saveList;
                }
                if (sortList[y][1].toInt() == sortList[y + 1][1].toInt() && sortList[y][2].toInt() < sortList[y + 1][2].toInt())
                {
                    QStringList saveList = sortList.at(y);
                    sortList[y] = sortList.at(y + 1);
                    sortList[y + 1] = saveList;
                }
                else if(sortList[y][1].toInt() == sortList[y + 1][1].toInt() && sortList[y][2].toInt() == sortList[y + 1][2].toInt() && sortList[y][4].toInt() > sortList[y + 1][4].toInt())
                {
                    QStringList saveList = sortList.at(y);
                    sortList[y] = sortList.at(y + 1);
                    sortList[y + 1] = saveList;
                }
            }
        }
        return sortList;
    }

    bool checkListDoubleResults(QList<QStringList> list)
    {
        foreach(QStringList team1, list)
        {
            foreach(QStringList team2, list)
            {
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
    QList<QStringList> getDivisionsClassement(QList<QList<QStringList> > divisionsClassements, int rank)
    {
        QList<QStringList> result;

        if(rank == 0)
            return QList<QStringList>();

        foreach(QList<QStringList> divisionClassement, divisionsClassements)
        {
            result.append(divisionClassement.at(rank - 1));
        }

        return result;
    }
    
    // create team list
    QStringList getTeamList(QList<QStringList> teamsDivisions)
    {
        QStringList result;

        foreach(QStringList team, teamsDivisions)
            result.append(team.at(0));

        return result;
    }

    // generate new divisions
    QList<QStringList> generateNewDivisions()
    {
        // help lists
        QList<QStringList> divisionsFirst, divisionsSecond, divisionsThird, divisionsFourth, divisionsFifth;
        QStringList divisionsFirstNames, divisionsSecondNames, divisionsThirdNames, divisionsFourthNames, divisionsFifthNames;

        // get list current ranking results
        QList<QList<QStringList> > resultDivisionsVr;
        
        // new list for new divisions by rank result
        QList<QStringList> newDivisionsZw;
        
        // read divisional rank results and add to list
        foreach(QString prefix, grPrefix)
            resultDivisionsVr.append(m_Db->read("select ms, punkte, satz, intern, extern from vorrunde_erg_gr" + prefix + " order by punkte desc, satz desc, intern asc"));

        divisionsFirst = getDivisionsClassement(resultDivisionsVr, 1);
        divisionsSecond = getDivisionsClassement(resultDivisionsVr, 2);
        divisionsThird = getDivisionsClassement(resultDivisionsVr, 3);
        divisionsFourth = getDivisionsClassement(resultDivisionsVr, 4);
        divisionsFifth = getDivisionsClassement(resultDivisionsVr, 5);

        switch(teamsCount)
        {
            case 20:
                    // make ranking of all divisions thrid teams
                    divisionsThird = sortList(divisionsThird);
                    
                    if(checkListDoubleResults(divisionsThird))
                        return QList<QStringList>();

                    divisionsFirstNames = getTeamList(divisionsFirst);
                    divisionsSecondNames = getTeamList(divisionsSecond);
                    divisionsThirdNames = getTeamList(divisionsThird);
                    divisionsFourthNames = getTeamList(divisionsFourth);
                    divisionsFifthNames = getTeamList(divisionsFifth);

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
                    divisionsFirstNames = getTeamList(divisionsFirst);
                    divisionsSecondNames = getTeamList(divisionsSecond);
                    divisionsThirdNames = getTeamList(divisionsThird);
                    divisionsFourthNames = getTeamList(divisionsFourth);
                    divisionsFifthNames = getTeamList(divisionsFifth);

                    newDivisionsZw.append(divisionsFirstNames);
                    newDivisionsZw.append(divisionsSecondNames);
                    newDivisionsZw.append(divisionsThirdNames);
                    newDivisionsZw.append(divisionsFourthNames);
                    newDivisionsZw.append(divisionsFifthNames);
                    break;
            case 28: 
                    // make ranking of all divisions second teams
                    divisionsSecond = sortList(divisionsSecond);
                    
                    if(checkListDoubleResults(divisionsSecond))
                        return QList<QStringList>();

                    divisionsFirstNames = getTeamList(divisionsFirst);
                    divisionsSecondNames = getTeamList(divisionsSecond);
                    divisionsThirdNames = getTeamList(divisionsThird);
                    divisionsFourthNames = getTeamList(divisionsFourth);
                    divisionsFifthNames = getTeamList(divisionsFifth);

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
                    divisionsSecond = sortList(divisionsSecond);
                    
                    if(checkListDoubleResults(divisionsSecond))
                        return QList<QStringList>();

                    // make ranking of all divisions fourth teams
                    divisionsFourth = sortList(divisionsFourth);
                    
                    if(checkListDoubleResults(divisionsFourth))
                        return QList<QStringList>();

                    divisionsFirstNames = getTeamList(divisionsFirst);
                    divisionsSecondNames = getTeamList(divisionsSecond);
                    divisionsThirdNames = getTeamList(divisionsThird);
                    divisionsFourthNames = getTeamList(divisionsFourth);
                    divisionsFifthNames = getTeamList(divisionsFifth);

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
                divisionsSecond = sortList(divisionsSecond);

                if(checkListDoubleResults(divisionsFourth))
                    return QList<QStringList>();

                // make ranking of all divisions third teams
                divisionsThird = sortList(divisionsThird);

                if(checkListDoubleResults(divisionsThird))
                    return QList<QStringList>();

                // make ranking of all divisions fourth teams
                divisionsFourth = sortList(divisionsFourth);

                if(checkListDoubleResults(divisionsFourth))
                    return QList<QStringList>();

                // make ranking of all divisions fifth teams
                divisionsFifth = sortList(divisionsFifth);

                if(checkListDoubleResults(divisionsFifth))
                    return QList<QStringList>();

                // get team names from divisions
                divisionsFirstNames = getTeamList(divisionsFirst);
                divisionsSecondNames = getTeamList(divisionsSecond);
                divisionsThirdNames = getTeamList(divisionsThird);
                divisionsFourthNames = getTeamList(divisionsFourth);
                divisionsFifthNames = getTeamList(divisionsFifth);

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
                divisionsSecond = sortList(divisionsSecond);

                if(checkListDoubleResults(divisionsSecond))
                    return QList<QStringList>();

                // make ranking of all divisions third teams
                divisionsThird = sortList(divisionsThird);

                if(checkListDoubleResults(divisionsThird))
                    return QList<QStringList>();

                // make ranking of all divisions fourth teams
                divisionsFourth = sortList(divisionsFourth);

                if(checkListDoubleResults(divisionsFourth))
                    return QList<QStringList>();

                // make ranking of all divisions fifth teams
                divisionsFifth = sortList(divisionsFifth);

                if(checkListDoubleResults(divisionsFifth))
                    return QList<QStringList>();

                // get team names from divisions
                divisionsFirstNames = getTeamList(divisionsFirst);
                divisionsSecondNames = getTeamList(divisionsSecond);
                divisionsThirdNames = getTeamList(divisionsThird);
                divisionsFourthNames = getTeamList(divisionsFourth);
                divisionsFifthNames = getTeamList(divisionsFifth);

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
            default: zwischenrundeLog("ZWISCHENRUNDE_ERROR:: team count not correct");
        }
        
        return newDivisionsZw;
    }
    
    // generate divisional game plan, use game sequence defined in constructor
    QList<QStringList> generateDivisionGames(QStringList divisionList)
    {
        QList<QStringList> result;

        // four teams in division
        if(divisionList.count() == 4)
        {
            if(first)
            {
                foreach(QList<int> game, firstFourMsDivision)
                {
                    if(game.at(0) != 999)
                    {
                        result.append(QStringList() << divisionList.at(game.at(0)) << divisionList.at(game.at(1)) << divisionList.at(game.at(2)));
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
                        result.append(QStringList() << divisionList.at(game.at(0)) << divisionList.at(game.at(1)) << divisionList.at(game.at(2)));
                    }
                    else
                    {
                        result.append(QStringList() << "---" << "---" << "---");
                    }
                }
                first = true;
            }
        }
        
        if(divisionList.count() == 5)
        {
            // five teams in division
            foreach(QList<int> game, fiveMsDivision)
                result.append(QStringList() << divisionList.at(game.at(0)) << divisionList.at(game.at(1)) << divisionList.at(game.at(2)));
        }

        return result;
    }

    // generate game plan over all divisions
    QStringList generateGamePlan(QList<QList<QStringList> > divisionsGameList, int gamesCount, QTime startRound, int lastRoundNr, int lastGameNr, int satz, int min, int pause)
    {
        QStringList querys;
        int addzeit = ((satz * min) + pause) * 60;
        lastRoundNr++;

        for(int divisionCount = 0, rowCount = 1, dataRow = 0, roundCount = lastRoundNr; rowCount <= gamesCount; divisionCount++)
        {
            if(divisionCount >= divisionsGameList.count())
            {
                divisionCount = 0;
                dataRow++;
                roundCount++;
                startRound = startRound.addSecs(addzeit);
            }

            if(dataRow < divisionsGameList.at(divisionCount).count())
            {
                QList<QStringList> divisionGameList = divisionsGameList.at(divisionCount);
                querys << "INSERT INTO zwischenrunde_spielplan VALUES(" + QString::number(rowCount) + "," + QString::number(roundCount) + "," + QString::number(rowCount + lastGameNr) + ",'" + startRound.toString("hh:mm") + "',0,'','" + divisionGameList.at(dataRow).at(0) + "','" + divisionGameList.at(dataRow).at(1) + "','" + divisionGameList.at(dataRow).at(2) + "',0,0,0,0,0,0)";
                rowCount++;
            }
        }

        return querys;
    }

    // insert field numbers
    QStringList insertFieldNr(int gameCount, int fieldCount)
    {
        QStringList querys;

        for(int i = 1, field = 1; i <= gameCount; i++)
        {
            for(int x = 1, fieldHelp = field; x <= fieldCount; x++, fieldHelp++, i++)
            {
                querys << "UPDATE zwischenrunde_spielplan SET feldnummer = " + QString::number(fieldHelp) + " WHERE id = " + QString::number(i);
                if(fieldHelp >= fieldCount)
                    fieldHelp = 0;
            }

            i--;

            if(field < fieldCount)
            {
                field++;
            }
            else
            {
                field = 1;
            }
        }

        return querys;
    }

    // insert field names
    QStringList insertFieldNames()
    {
        QStringList querys;
        int fieldCount = fieldNames.count();
        for(int i = 1; i <= fieldCount; i++)
            querys << "UPDATE zwischenrunde_spielplan SET feldname = '" + fieldNames.at(i-1) + "' WHERE feldnummer = " + QString::number(i);

        return querys;
    }

    // generate vorrunde divisions result table
    QStringList generateResultTables(QList<QStringList> divisionsList)
    {
        int prefix = 0;
        QStringList querys;

        foreach(QStringList division, divisionsList)
        {
            int i = 1;
            QString group = grPrefix.at(prefix);
            foreach(QString team, division)
            {
                querys << "INSERT INTO zwischenrunde_erg_gr" + group + " VALUES(" + QString::number(i) + ",'" + team + "',0,0,0,0)";
                i++;
            }
            prefix++;
        }

        return querys;
    }
    
    // write to database
    void writeChangesDatabase(QStringList querys)
    {
        foreach(QString query, querys)
            m_Db->write(query);
    }

    database *m_Db;
    calculate *m_Calc;

    QList<QList<int> > firstFourMsDivision, fourMsDivision, fiveMsDivision;
    
    QStringList grPrefix, fieldNames;
    int satz, min, pause, fieldCount, teamsCount, lastGameNr, lastRoundNr;
    QString startTurnier;
    bool first;
};
#endif // ZWISCHENRUNDE
