#ifndef PLATZSPIELE
#define PLATZSPIELE

#include <QTableView>

#include "database_v1.3.h"
#include "calculate.h"

class platzspiele : public QObject
{
    Q_OBJECT
public:
    platzspiele(database *m_Db, calculate *m_Calc, QStringList grPrefix)
    {
        this->m_Db = m_Db;
        this->m_Calc = m_Calc;
        this->grPrefix = grPrefix;
    }

    // set platzspiele params
    void setParams(QString startTurnier, int lastgameTime, int pauseKrPl, int countSatz, int minSatz, int fieldCount, int teamsCount, QStringList fieldNames, int lastRoundNr, int lastGameNr)
    {
        emit platzspieleLog("PLATZSPIELE:: set platzspiele params");
        this->startTurnier = startTurnier;
        this->satz = countSatz;
        this->min = minSatz;
        this->pause = 0;
        this->fieldCount = fieldCount;
        this->teamsCount = teamsCount;
        this->fieldNames = fieldNames;
        this->lastGameNr = lastGameNr;
        this->lastRoundNr = lastRoundNr;

        QTime time = QTime::fromString(this->startTurnier, "hh:mm");
        time = time.addSecs((pauseKrPl * 60) + (lastgameTime * 60));
        this->startTurnier = time.toString("hh:mm");
    }

    // clear platzspiele
    void clear()
    {
        QStringList tables;
        QStringList querys;
        tables << "platzspiele_spielplan" << "platzierungen";

        foreach(QString table, tables)
            querys << "DELETE FROM " + table;

        writeChangesDatabase(querys);
    }
    
    // generate platzspiele
    void generate()
    {
        QList<QStringList> krGameResults;
        QStringList execQuerys;

        QList<QStringList> krGames = m_Db->read("SELECT spiel, ms_a, ms_b, satz1a, satz1b, satz2a, satz2b, satz3a, satz3b FROM kreuzspiele_Spielplan ORDER BY id ASC");

        foreach(QStringList krGame, krGames)
            krGameResults << m_Calc->getResultsKrPl(krGame);

        execQuerys << generateGamePlan(QTime::fromString(startTurnier), krGameResults);
        execQuerys << insertFieldNames();
        
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

    // tournament results
    void finalTournamentResults()
    {
        emit platzspieleLog("INFO:: calculating kreuzspiele results");

        QList<QStringList> plGameResults;
        QStringList execQuerys;

        QList<QStringList> plGames = m_Db->read("SELECT spiel, ms_a, ms_b, satz1a, satz1b, satz2a, satz2b, satz3a, satz3b FROM platzspiele_Spielplan ORDER BY id ASC");

        foreach(QStringList plGame, plGames)
            plGameResults << m_Calc->getResultsKrPl(plGame);

        execQuerys << "DELETE FROM platzierungen";
        execQuerys << createClassement(plGameResults);

        writeChangesDatabase(execQuerys);
    }

signals:
  // send log msg
  void platzspieleLog(QString);
    
private:
    // generate game plan over all divisions
    QStringList generateGamePlan(QTime startRound, QList<QStringList> krGameResults)
    {
        int i = 0;
        int addzeit = ((satz * min) + pause) * 60;
        QStringList querys;
        
        // get list current ranking results
        QList<QStringList> resultDivisionsZw;
        
        // help lists
        QStringList divisionA, divisionB, divisionC, divisionD, divisionE, divisionF, divisionG, divisionH;
           
        // read divisional rank results and add to list
        foreach(QString prefix, grPrefix)
        {
            QStringList resultEdit;
            QList<QStringList> divisionResult = m_Db->read("select ms, punkte, satz from zwischenrunde_erg_gr" + prefix + " order by punkte desc, satz desc");

            foreach(QStringList team, divisionResult)
                resultEdit.append(team.at(0));

            resultDivisionsZw.append(resultEdit);
            i++;
        }

        divisionA = resultDivisionsZw.at(0);
        divisionB = resultDivisionsZw.at(1);
        divisionC = resultDivisionsZw.at(2);
        divisionD = resultDivisionsZw.at(3);
        divisionE = resultDivisionsZw.at(4);
        divisionF = resultDivisionsZw.at(5);
        divisionG = resultDivisionsZw.at(6);
        divisionH = resultDivisionsZw.at(7);
        
        lastRoundNr++;

        switch(teamsCount)
        {
            case 20:
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(1," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA.at(4) + "','" + divisionB.at(4) + "','" + divisionA.at(1) + "',0,0,0,0,0,0)";
                    // spiel um platz 9
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(2," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(1).at(2) + "','" + krGameResults.at(5).at(2) + "','" + divisionB.at(1) + "',0,0,0,0,0,0)";
                    // spiel um platz 7
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(3," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionC.at(4) + "','" + divisionD.at(4) + "','" + divisionC.at(1) + "',0,0,0,0,0,0)";
                    // spiel um platz 19 
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(4," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(3).at(2) + "','" + krGameResults.at(7).at(2) + "','" + divisionD.at(1) + "',0,0,0,0,0,0)";

                    startRound = startRound.addSecs(addzeit);
                    lastRoundNr++;
                    // spiel um platz 17
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(5," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(1).at(1) + "','" + krGameResults.at(5).at(2) + "','" + divisionA.at(4) + "',0,0,0,0,0,0)";
                    // spiel um platz 3
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(6," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(0).at(2) + "','" + krGameResults.at(4).at(2) + "','" + divisionB.at(4) + "',0,0,0,0,0,0)";
                    // spiel um platz 15 
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(7," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults.at(3).at(1) + "','" + krGameResults.at(7).at(1) + "','" + divisionC.at(4) + "',0,0,0,0,0,0)";
                    // spiel um platz 13 
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(8," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(2).at(2) + "','" + krGameResults.at(6).at(2) + "','" + divisionD.at(4) + "',0,0,0,0,0,0)";
                    // spiel um platz 11
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(9," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.addSecs(addzeit).toString("hh:mm") + "',2,'','" + krGameResults.at(2).at(1) + "','" + krGameResults.at(6).at(1) + "','" + divisionC.at(3) + "',0,0,0,0,0,0)";

                    startRound = startRound.addSecs(addzeit);
                    lastRoundNr++;
                    // spiel um platz 1
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(10," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(0).at(1) + "','" + krGameResults.at(4).at(1) + "','" + divisionA.at(3) + "',0,0,0,0,0,0)";
                    break;

            case 25:        
                    // spiel um platz 9
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(1," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA.at(4) + "','" + divisionB.at(4) + "','" + divisionA.at(1) + "',0,0,0,0,0,0)";
                    // spiel um platz 7
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(2," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(1).at(2) + "','" + krGameResults.at(5).at(2) + "','" + divisionB.at(1) + "',0,0,0,0,0,0)";
                    // spiel um platz 19
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(3," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionC.at(4) + "','" + divisionD.at(4) + "','" + divisionC.at(1) + "',0,0,0,0,0,0)";
                    // spiel um platz 17
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(4," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(3).at(2) + "','" + krGameResults.at(7).at(2) + "','" + divisionD.at(1) + "',0,0,0,0,0,0)";
                    // spiel um platz 5 
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(5," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults.at(1).at(1) + "','" + krGameResults.at(5).at(1) + "','" + divisionA.at(4) + "',0,0,0,0,0,0)";

                    startRound = startRound.addSecs(addzeit);
                    lastRoundNr++;
                    // spiel um platz 3
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(6," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults.at(0).at(2) + "','" + krGameResults.at(4).at(2) + "','" + divisionB.at(4) + "',0,0,0,0,0,0)";
                    // spiel um platz 15 
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(7," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(3).at(1) + "','" + krGameResults.at(7).at(1) + "','" + divisionC.at(4) + "',0,0,0,0,0,0)";
                    // spiel um platz 13
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(8," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults.at(2).at(2) + "','" + krGameResults.at(6).at(2) + "','" + divisionD.at(4) + "',0,0,0,0,0,0)";
                    // spiel um platz 11
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(9," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(2).at(1) + "','" + krGameResults.at(6).at(1) + "','" + divisionC.at(3) + "',0,0,0,0,0,0)";

                    startRound = startRound.addSecs(addzeit);
                    lastRoundNr++;
                    // spiel um platz 1
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(10," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(0).at(1) + "','" + krGameResults.at(4).at(1) + "','" + divisionA.at(3) + "',0,0,0,0,0,0)";
                    break;

            case 28:   
                    // spiel um platz 7 
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(1," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(1).at(2) + "','" + krGameResults.at(7).at(2) + "','" + divisionB.at(1) + "',0,0,0,0,0,0)";
                    // spiel um platz 19
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(2," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionC.at(4) + "','" + divisionD.at(4) + "','" + divisionC.at(1) + "',0,0,0,0,0,0)";
                    // spiel um platz 17
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(3," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults.at(3).at(2) + "','" + krGameResults.at(9).at(2) + "','" + divisionD.at(1) + "',0,0,0,0,0,0)";
                    // spiel um platz 27
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(4," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionE.at(4) + "','" + divisionF.at(4) + "','" + divisionE.at(1) + "',0,0,0,0,0,0)";
                    // spiel um platz 25
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(5," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(5).at(2) + "','" + krGameResults.at(11).at(2) + "','" + divisionF.at(1) + "',0,0,0,0,0,0)";
                    // spiel um platz 5
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(6," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults.at(1).at(1) + "','" + krGameResults.at(7).at(2) + "','" + krGameResults.at(1).at(2) + "',0,0,0,0,0,0)";
                    // spiel um platz 3 
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(7," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults.at(0).at(2) + "','" + krGameResults.at(6).at(2) + "','" + krGameResults.at(7).at(2) + "',0,0,0,0,0,0)";

                    startRound = startRound.addSecs(addzeit);
                    lastRoundNr++;
                    // spiel um platz 15
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(8," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(3).at(1) + "','" + krGameResults.at(9).at(1) + "','" + divisionC.at(4) + "',0,0,0,0,0,0)";
                    // spiel um platz 13
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(9," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(2).at(2) + "','" + krGameResults.at(8).at(2) + "','" + divisionD.at(4) + "',0,0,0,0,0,0)";
                    // spiel um platz 23 
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(10," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(5).at(1) + "','" + krGameResults.at(11).at(1) + "','" + divisionE.at(4) + "',0,0,0,0,0,0)";
                    // spiel um platz 9
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(11," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(4).at(2) + "','" + krGameResults.at(10).at(2) + "','" + divisionF.at(4) + "',0,0,0,0,0,0)";
                    // spiel um platz 21
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(12," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults.at(4).at(1) + "','" + krGameResults.at(10).at(1) + "','" + divisionE.at(4) + "',0,0,0,0,0,0)";
                    // spiel um platz 11
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(13," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(2).at(1) + "','" + krGameResults.at(8).at(1) + "','" + divisionC.at(4) + "',0,0,0,0,0,0)";

                    startRound = startRound.addSecs(addzeit);
                    lastRoundNr++;
                    // spiel um platz 1
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(14," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(0).at(1) + "','" + krGameResults.at(6).at(1) + "','" + divisionA.at(3) + "',0,0,0,0,0,0)";
                    break;

            case 30:
            case 35:
                    // spiel um platz 9
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(1," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA[4] + "','" + divisionB[4] + "','" + divisionA[1] + "',0,0,0,0,0,0)";
                    // spiel um platz 19
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(2," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionC[4] + "','" + divisionD[4] + "','" + divisionC[1] + "',0,0,0,0,0,0)";
                    // spiel um platz 29
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(3," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionE[4] + "','" + divisionF[4] + "','" + divisionE[1] + "',0,0,0,0,0,0)";
                    // spiel um platz 7
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(4," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(1).at(2) + "','" + krGameResults.at(7).at(2) + "','" + divisionB[1] + "',0,0,0,0,0,0)";
                    // spiel um platz 17
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(5," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults.at(3).at(2) + "','" + krGameResults.at(9).at(2) + "','" + divisionD[1] + "',0,0,0,0,0,0)";
                    // spiel um platz 27
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(6," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults.at(5).at(2) + "','" + krGameResults.at(11).at(2) + "','" + divisionF[1] + "',0,0,0,0,0,0)";

                    startRound = startRound.addSecs(addzeit);
                    lastRoundNr++;
                    // spiel um platz 5
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(7," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(1).at(1) + "','" + krGameResults.at(7).at(1) + "','" + divisionA[4] + "',0,0,0,0,0,0)";
                    // spiel um platz 15
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(9," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(3).at(1) + "','" + krGameResults.at(9).at(1) + "','" + divisionC[4] + "',0,0,0,0,0,0)";
                    // spiel um platz 25
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(11," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults.at(5).at(1) + "','" + krGameResults.at(11).at(1) + "','" + divisionE[4] + "',0,0,0,0,0,0)";
                    // spiel um platz 3
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(8," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(0).at(2) + "','" + krGameResults.at(6).at(2) + "','" + divisionB[4] + "',0,0,0,0,0,0)";
                    // spiel um platz 13
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(10," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults.at(2).at(2) + "','" + krGameResults.at(8).at(2) + "','" + divisionD[4] + "',0,0,0,0,0,0)";
                    // spiel um platz 23
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(12," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults.at(4).at(2) + "','" + krGameResults.at(10).at(2) + "','" + divisionF[4] + "',0,0,0,0,0,0)";

                    startRound = startRound.addSecs(addzeit);
                    lastRoundNr++;
                    // spiel um platz 21
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(13," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(2).at(1) + "','" + krGameResults.at(8).at(1) + "','" + divisionA[3] + "',0,0,0,0,0,0)";
                    // spiel um platz 11
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(14," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(4).at(1) + "','" + krGameResults.at(10).at(1) + "','" + divisionB[3] + "',0,0,0,0,0,0)";

                    startRound = startRound.addSecs(addzeit);
                    lastRoundNr++;
                    // spiel um platz 1
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(15," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(0).at(1) + "','" + krGameResults.at(6).at(1) + "','" + divisionA[3] + "',0,0,0,0,0,0)";
                    break;

            case 40:
                    // spiel um platz 9
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(1," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA[4] + "','" + divisionB[4] + "','" + divisionA[1] + "',0,0,0,0,0,0)";
                    // spiel um platz 19
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(2," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionC[4] + "','" + divisionD[4] + "','" + divisionC[1] + "',0,0,0,0,0,0)";
                    // spiel um platz 29
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(3," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionE[4] + "','" + divisionF[4] + "','" + divisionE[1] + "',0,0,0,0,0,0)";
                    // spiel um platz 39
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(4," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionG[4] + "','" + divisionH[4] + "','" + divisionG[1] + "',0,0,0,0,0,0)";
                    // spiel um platz 7
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(5," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults.at(1).at(2) + "','" + krGameResults.at(9).at(2) + "','" + divisionB[1] + "',0,0,0,0,0,0)";
                    // spiel um platz 17
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(6," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults.at(3).at(2) + "','" + krGameResults.at(11).at(2) + "','" + divisionD[1] + "',0,0,0,0,0,0)";
                    // spiel um platz 27
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(7," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + krGameResults.at(5).at(2) + "','" + krGameResults.at(13).at(2) + "','" + divisionF[1] + "',0,0,0,0,0,0)";
                    // spiel um platz 37
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(8," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults.at(7).at(2) + "','" + krGameResults.at(15).at(2) + "','" + divisionH[1] + "',0,0,0,0,0,0)";

                    startRound = startRound.addSecs(addzeit);
                    lastRoundNr++;
                    // spiel um platz 5
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(9," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(1).at(1) + "','" + krGameResults.at(9).at(1) + "','" + divisionA[4] + "',0,0,0,0,0,0)";
                    // spiel um platz 15
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(10," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(3).at(1) + "','" + krGameResults.at(11).at(1) + "','" + divisionC[4] + "',0,0,0,0,0,0)";
                    // spiel um platz 25
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(11," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults.at(5).at(1) + "','" + krGameResults.at(13).at(1) + "','" + divisionE[4] + "',0,0,0,0,0,0)";
                    // spiel um platz 35
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(12," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + krGameResults.at(7).at(1) + "','" + krGameResults.at(15).at(1) + "','" + divisionG[4] + "',0,0,0,0,0,0)";
                    // spiel um platz 3
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(13," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + krGameResults.at(0).at(2) + "','" + krGameResults.at(8).at(2) + "','" + divisionB[4] + "',0,0,0,0,0,0)";
                    // spiel um platz 13
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(14," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + krGameResults.at(2).at(2) + "','" + krGameResults.at(10).at(2) + "','" + divisionD[4] + "',0,0,0,0,0,0)";
                    // spiel um platz 23
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(15," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + krGameResults.at(4).at(2) + "','" + krGameResults.at(12).at(2) + "','" + divisionF[4] + "',0,0,0,0,0,0)";
                    // spiel um platz 33
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(16," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + krGameResults.at(6).at(2) + "','" + krGameResults.at(14).at(2) + "','" + divisionH[4] + "',0,0,0,0,0,0)";

                    startRound = startRound.addSecs(addzeit);
                    lastRoundNr++;
                    // spiel um platz 11
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(17," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(2).at(1) + "','" + krGameResults.at(10).at(1) + "','" + divisionA[3] + "',0,0,0,0,0,0)";
                    // spiel um platz 21
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(18," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + krGameResults.at(4).at(1) + "','" + krGameResults.at(12).at(1) + "','" + divisionB[3] + "',0,0,0,0,0,0)";
                    // spiel um platz 31
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(19," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + krGameResults.at(6).at(1) + "','" + krGameResults.at(14).at(1) + "','" + divisionC[3] + "',0,0,0,0,0,0)";

                    startRound = startRound.addSecs(addzeit);
                    lastRoundNr++;
                    // spiel um platz 1
                    lastGameNr++;
                    querys << "INSERT INTO platzspiele_spielplan VALUES(20," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + krGameResults.at(0).at(1) + "','" + krGameResults.at(8).at(1) + "','',0,0,0,0,0,0)";

                    break;
        }
        return querys;
    }
    
    // insert field names
    QStringList insertFieldNames()
    {
        QStringList querys;
        int fieldCount = fieldNames.count();
        for(int i = 1; i <= fieldCount; i++)
            querys << "UPDATE platzspiele_spielplan SET feldname = '" + fieldNames.at(i-1) + "' WHERE feldnummer = " + QString::number(i);

        return querys;
    }
    
    // create classement
    QStringList createClassement(QList<QStringList> plGameResults)
    {
        QStringList querys;
        QList<int> classement;
        QList<QStringList> bottomRankings;
        int i = 0, id = 0;

        switch(teamsCount)
        {
            case 20: classement << 9 << 10 << 19 << 20
                                << 7 << 8 << 17 << 18
                                << 5 << 6 << 15 << 16
                                << 3 << 4 << 13 << 14
                                << 11 << 12
                                << 1 << 2;
                    break;

            case 25: classement << 9 << 10 << 19 << 20
                                << 7 << 8 << 17 << 18
                                << 5 << 6 << 15 << 16
                                << 3 << 4 << 13 << 14 << 23 << 24
                                << 11 << 12 << 21 << 22
                                << 1 << 2;
                    break;

            case 28: classement << 9 << 10 << 19 << 20
                                << 7 << 8 << 17 << 18 << 27 << 28
                                << 5 << 6 << 15 << 16 << 25 << 26
                                << 3 << 4 << 13 << 14 << 23 << 24
                                << 11 << 12 << 21 << 22
                                << 1 << 2;
                    break;

            case 30: classement << 9 << 10 << 19 << 20 << 29 << 30
                                << 7 << 8 << 17 << 18 << 27 << 28
                                << 5 << 6 << 15 << 16 << 25 << 26
                                << 3 << 4 << 13 << 14 << 23 << 24
                                << 11 << 12 << 21 << 22
                                << 1 << 2;
                    break;

            case 35: classement << 9 << 10 << 19 << 20 << 29 << 30
                                << 7 << 8 << 17 << 18 << 27 << 28
                                << 5 << 6 << 15 << 16 << 25 << 26
                                << 3 << 4 << 13 << 14 << 23 << 24
                                << 11 << 12 << 21 << 22
                                << 1 << 2;
                    break;

            case 40: classement << 9 << 10 << 19 << 20 << 29 << 30 << 39 << 40
                                << 7 << 8 << 17 << 18 << 27 << 28 << 37 << 38
                                << 5 << 6 << 15 << 16 << 25 << 26 << 35 << 36
                                << 3 << 4 << 13 << 14 << 23 << 24 << 33 << 34
                                << 11 << 12 << 21 << 22 << 31 << 32
                                << 1 << 2;
                    break;
        }

        foreach(QStringList plGame, plGameResults)
        {
            querys << "INSERT INTO platzierungen VALUES(" + intToStr(id++) + "," + intToStr(classement.at(i++)) + ",'" + plGame.at(1) + "')";
            querys << "INSERT INTO platzierungen VALUES(" + intToStr(id++) + "," + intToStr(classement.at(i++)) + ",'" + plGame.at(2) + "')";
        }

        // rest of classement, teams which played vorrunde and zwischenrunde
        i++;
        switch(teamsCount)
        {
            case 25:
                bottomRankings = m_Db->read("SELECT ms FROM zwischenrunde_gre_view");
                querys << "INSERT INTO platzierungen VALUES(" + intToStr(id++) + "," + intToStr(i++) + ",'" + bottomRankings.at(0).at(0) + "')";
                querys << "INSERT INTO platzierungen VALUES(" + intToStr(id++) + "," + intToStr(i++) + ",'" + bottomRankings.at(1).at(0) + "')";
                querys << "INSERT INTO platzierungen VALUES(" + intToStr(id++) + "," + intToStr(i++) + ",'" + bottomRankings.at(2).at(0) + "')";
                querys << "INSERT INTO platzierungen VALUES(" + intToStr(id++) + "," + intToStr(i++) + ",'" + bottomRankings.at(3).at(0) + "')";
                querys << "INSERT INTO platzierungen VALUES(" + intToStr(id++) + "," + intToStr(i++) + ",'" + bottomRankings.at(4).at(0) + "')";
                break;

            case 35:
                bottomRankings = m_Db->read("SELECT ms FROM zwischenrunde_grg_view");
                querys << "INSERT INTO platzierungen VALUES(" + intToStr(id++) + "," + intToStr(i++) + ",'" + bottomRankings.at(0).at(0) + "')";
                querys << "INSERT INTO platzierungen VALUES(" + intToStr(id++) + "," + intToStr(i++) + ",'" + bottomRankings.at(1).at(0) + "')";
                querys << "INSERT INTO platzierungen VALUES(" + intToStr(id++) + "," + intToStr(i++) + ",'" + bottomRankings.at(2).at(0) + "')";
                querys << "INSERT INTO platzierungen VALUES(" + intToStr(id++) + "," + intToStr(i++) + ",'" + bottomRankings.at(3).at(0) + "')";
                querys << "INSERT INTO platzierungen VALUES(" + intToStr(id++) + "," + intToStr(i++) + ",'" + bottomRankings.at(4).at(0) + "')";
                break;
        }

        return querys;
    }

    // write to database
    void writeChangesDatabase(QStringList querys)
    {
        foreach(QString query, querys)
            m_Db->write(query);
    }

    // cast int to string
    QString intToStr(int nbr)
    {
        return QString::number(nbr);
    }

    database *m_Db;
    calculate *m_Calc;
    
    QStringList grPrefix, fieldNames;
    int satz, min, pause, fieldCount, teamsCount, lastGameNr, lastRoundNr;
    QString startTurnier;
};
#endif // PLATZSPIELE
