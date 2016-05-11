#ifndef VORRUNDE
#define VORRUNDE

#include <QTableView>

#include "database_v1.3.h"
#include "calculate.h"

class vorrunde : public QObject
{
    Q_OBJECT
public:
    vorrunde(database *m_Db, calculate *m_Calc, QStringList grPrefix)
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
    void setParams(QString startTurnier, int countSatz, int minSatz, int minPause, int fieldCount, int teamsCount, QStringList fieldNames)
    {
        emit vorrundeLog("VORRUNDE:: set vr params");
        this->startTurnier = startTurnier;
        this->satz = countSatz;
        this->min = minSatz;
        this->pause = minPause;
        this->fieldCount = fieldCount;
        this->teamsCount = teamsCount;
        this->fieldNames = fieldNames;
    }

    // generate vorrunde
    void generate()
    {
        QList<QStringList> divisionsList;
        QList<QList<QStringList> > divisionsGameList;
        QStringList execQuerys;
        int gamesCount = 0;

        // preparte lists for all divisions
        foreach(QString group, grPrefix)
        {
            QStringList division;
            QList<QStringList> list = m_Db->read("SELECT " + group + " FROM mannschaften WHERE " + group + " != ''");
            
            // for each division one stringlist
            foreach(QStringList team, list)
            {
                division << team.at(0);
            }
            
            // collect all divisions
            divisionsList << division;
        }
        
        // generate games for each division
        foreach(QStringList divisionList, divisionsList)
            divisionsGameList.append(generateDivisionGames(divisionList));

        // count games in divisions
        foreach(QList<QStringList> divisionGameList, divisionsGameList)
            gamesCount += divisionGameList.count();

        // generate game plan over all divisonal games
        execQuerys << generateGamePlan(divisionsGameList, gamesCount, QTime::fromString(startTurnier), satz, min, pause);
        
        // generate time schedule for game plan
        execQuerys << insertFieldNr(gamesCount, fieldCount);
        
        // insert field names
        execQuerys << insertFieldNames();
        
        // generate vorrunde divisions result tables
        execQuerys << generateResultTables(divisionsList);

        // execute all statements to database
        writeChangesDatabase(execQuerys);
    }

    // clear vorrunde
    void clear()
    {
        QStringList tables;
        QStringList querys;
        
        tables << "vorrunde_spielplan";
        
        foreach(QString prefix, grPrefix)
        {
            tables << ("vorrunde_erg_gr" + prefix);
        }
               
        foreach(QString table, tables)
            querys << "DELETE FROM " + table;

        writeChangesDatabase(querys);
    }

    // calculate result vorrunde
    void calculateResult()
    {
        emit vorrundeLog("INFO:: calculating vorrunde results");
        QStringList execQuerys;
        QList<QStringList> vrGameResults = m_Db->read("SELECT spiel, ms_a, ms_b, satz1a, satz1b, satz2a, satz2b, satz3a, satz3b FROM vorrunde_spielplan WHERE ms_a != '---' ORDER BY id ASC");
        QList<calculate::teamResult> teamResults = m_Calc->addResultsVrZw(m_Calc->calculateResults(vrGameResults));

        foreach(calculate::teamResult tR, teamResults)
        {
            QString division;
            foreach(QString prefix, grPrefix)
            {
                if(m_Db->read("SELECT * FROM vorrunde_erg_gr" + prefix + " WHERE ms = '" + tR.teamName + "'").count() > 0)
                    division = prefix;
            }
            execQuerys << "UPDATE vorrunde_erg_gr" + division + " SET punkte=" + QString::number(tR.sets) + ", satz=" + QString::number(tR.points) + " WHERE ms = '" + tR.teamName + "'";
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
            QList<QStringList> result = m_Db->read("select distinct ms1.ms from vorrunde_erg_gr" + prefix + " ms1, (select ms, satz, punkte, intern from vorrunde_erg_gr" + prefix + ") ms2 where ms1.satz = ms2.satz and  ms1.punkte = ms2.punkte and ms1.intern = ms2.intern and ms1.ms != ms2.ms");
            if(result.count() == 2)
            {
                QStringList team1 = result.at(0);
                QStringList team2 = result.at(1);
                QString gamenr = m_Db->read("SELECT spiel from vorrunde_spielplan where ms_a = '" + team1.at(0) + "' and ms_b = '" + team2.at(0) + "' or ms_a = '" + team2.at(0) + "' and ms_b = '" + team1.at(0)+ "'").at(0).at(0);
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
    void vorrundeLog(QString);

private:
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
    QStringList generateGamePlan(QList<QList<QStringList> > divisionsGameList, int gamesCount, QTime tournamentStart, int satz, int min, int pause)
    {
        QStringList querys;
        int addzeit = ((satz * min) + pause) * 60;

        for(int divisionCount = 0, rowCount = 1, dataRow = 0, roundCount = 1; rowCount <= gamesCount; divisionCount++)
        {
            if(divisionCount >= divisionsGameList.count())
            {
                divisionCount = 0;
                dataRow++;
                roundCount++;
                tournamentStart = tournamentStart.addSecs(addzeit);
            }

            if(dataRow < divisionsGameList.at(divisionCount).count())
            {
                QList<QStringList> divisionGameList = divisionsGameList.at(divisionCount);
                querys << "INSERT INTO vorrunde_spielplan VALUES(" + QString::number(rowCount) + "," + QString::number(roundCount) + "," + QString::number(rowCount) + ",'" + tournamentStart.toString("hh:mm") + "',0,'','" + divisionGameList.at(dataRow).at(0) + "','" + divisionGameList.at(dataRow).at(1) + "','" + divisionGameList.at(dataRow).at(2) + "',0,0,0,0,0,0)";
                rowCount++;
            }
        }

        return querys;
    }

    // insert field numbers
    QStringList insertFieldNr(int gameCount, int fieldCount)
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
            querys << "UPDATE vorrunde_spielplan SET feldname = '" + fieldNames.at(i-1) + "' WHERE feldnummer = " + QString::number(i);

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
                querys << "INSERT INTO vorrunde_erg_gr" + group + " VALUES(" + QString::number(i) + ",'" + team + "',0,0,0,0)";
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
    int satz, min, pause, fieldCount, teamsCount;
    QString startTurnier;
    bool first;
};

#endif // VORRUNDE
