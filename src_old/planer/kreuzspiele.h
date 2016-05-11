#ifndef KREUZSPIELE
#define KREUZSPIELE

#include <QTableView>

#include "database_v1.3.h"
#include "calculate.h"

class kreuzspiele : public QObject
{
    Q_OBJECT
public:
    kreuzspiele(database *m_Db, calculate *m_Calc, QStringList grPrefix)
    {
        this->m_Db = m_Db;
        this->m_Calc = m_Calc;
        this->grPrefix = grPrefix;
    }

    // set kreuzspiele params
    void setParams(QString startTurnier, int lastgameTime, int pauseZwKr, int countSatz, int minSatz, int minPause, int fieldCount, int teamsCount, QStringList fieldNames, int lastRoundNr, int lastGameNr)
    {
        emit kreuzspieleLog("KREUZSPIELE:: set kreuszpiele params");
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
        time = time.addSecs((pauseZwKr * 60) + (lastgameTime * 60));
        this->startTurnier = time.toString("hh:mm");
    }

    // clear kreuzspiele
    void clear()
    {
        QStringList tables;
        QStringList querys;
        tables << "kreuzspiele_spielplan";

        foreach(QString table, tables)
            querys << "DELETE FROM " + table;

        writeChangesDatabase(querys);
    }
    
    // generate kreuzspiele
    void generate()
    {
        QStringList execQuerys;
        
        execQuerys << generateGamePlan(QTime::fromString(startTurnier));
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

signals:
    // send log msg
    void kreuzspieleLog(QString);
    
private:
    // get teamnames from list
    QStringList getDivisionTeamNames(QList<QStringList> list)
    {
        QStringList nameList;

        foreach(QStringList team, list)
            nameList << team.at(0);

        return nameList;
    }

    // generate game plan over all divisions
    QStringList generateGamePlan(QTime startRound)
    {
        int addzeit = ((satz * min) + pause)*60;
        QStringList querys;

        // get list current ranking results
        QList<QList<QStringList> > resultDivisionsZw;
        
        // help lists
        QStringList divisionA, divisionB, divisionC, divisionD, divisionE, divisionF, divisionG, divisionH;

        // read divisional rank results and add to list
        foreach(QString prefix, grPrefix)
            resultDivisionsZw.append(m_Db->read("select ms, punkte, satz from zwischenrunde_erg_gr" + prefix + " order by punkte desc, satz desc"));

        divisionA = getDivisionTeamNames(resultDivisionsZw.at(0));
        divisionB = getDivisionTeamNames(resultDivisionsZw.at(1));
        divisionC = getDivisionTeamNames(resultDivisionsZw.at(2));
        divisionD = getDivisionTeamNames(resultDivisionsZw.at(3));
        divisionE = getDivisionTeamNames(resultDivisionsZw.at(4));
        divisionF = getDivisionTeamNames(resultDivisionsZw.at(5));
        divisionG = getDivisionTeamNames(resultDivisionsZw.at(6));
        divisionH = getDivisionTeamNames(resultDivisionsZw.at(7));
        
        lastRoundNr++;

        switch(teamsCount)
        {
            case 20:
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(1," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA.at(0) + "','" + divisionB.at(1) + "','" + divisionA.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(2," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionA.at(2) + "','" + divisionB.at(3) + "','" + divisionA.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(3," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionC.at(0) + "','" + divisionD.at(1) + "','" + divisionC.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(4," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionC.at(2) + "','" + divisionD.at(3) + "','" + divisionC.at(3) + "',0,0,0,0,0,0)";
                    startRound = startRound.addSecs(addzeit);
                    lastRoundNr++; lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(5," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA.at(1) + "','" + divisionB.at(0) + "','" + divisionB.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(6," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionA.at(3) + "','" + divisionB.at(2) + "','" + divisionB.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(7," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionC.at(1) + "','" + divisionD.at(0) + "','" + divisionD.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(8," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionC.at(3) + "','" + divisionD.at(2) + "','" + divisionD.at(3) + "',0,0,0,0,0,0)";
                    break;

            case 25:
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(1," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA.at(0) + "','" + divisionB.at(1) + "','" + divisionA.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(2," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionA.at(2) + "','" + divisionB.at(3) + "','" + divisionA.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(3," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionC.at(0) + "','" + divisionD.at(1) + "','" + divisionC.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(4," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionC.at(2) + "','" + divisionD.at(3) + "','" + divisionC.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(5," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionA.at(1) + "','" + divisionB.at(0) + "','" + divisionB.at(1) + "',0,0,0,0,0,0)";
                    startRound = startRound.addSecs(addzeit);
                    lastRoundNr++; lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(6," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA.at(3) + "','" + divisionB.at(2) + "','" + divisionB.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(7," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionC.at(1) + "','" + divisionD.at(0) + "','" + divisionD.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(8," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionC.at(3) + "','" + divisionD.at(2) + "','" + divisionD.at(3) + "',0,0,0,0,0,0)";
                    break;

            case 28:
            case 30:
            case 35:
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(1," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA.at(0) + "','" + divisionB.at(1) + "','" + divisionA.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(2," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionA.at(2) + "','" + divisionB.at(3) + "','" + divisionA.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(3," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionC.at(0) + "','" + divisionD.at(1) + "','" + divisionC.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(4," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionC.at(2) + "','" + divisionD.at(3) + "','" + divisionC.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(5," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionE.at(0) + "','" + divisionF.at(1) + "','" + divisionE.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(6," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + divisionE.at(2) + "','" + divisionF.at(3) + "','" + divisionE.at(3) + "',0,0,0,0,0,0)";
                    startRound = startRound.addSecs(addzeit);
                    lastRoundNr++; lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(7," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + divisionA.at(1) + "','" + divisionB.at(0) + "','" + divisionB.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(8," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionA.at(3) + "','" + divisionB.at(2) + "','" + divisionB.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(9," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionC.at(1) + "','" + divisionD.at(0) + "','" + divisionD.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(10," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionC.at(3) + "','" + divisionD.at(2) + "','" + divisionD.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(11," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionE.at(1) + "','" + divisionF.at(0) + "','" + divisionF.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(12," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionE.at(3) + "','" + divisionF.at(2) + "','" + divisionF.at(3) + "',0,0,0,0,0,0)";
                    break;

            case 40:
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(1," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA.at(0) + "','" + divisionB.at(1) + "','" + divisionA.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(2," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionA.at(2) + "','" + divisionB.at(3) + "','" + divisionA.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(3," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionC.at(0) + "','" + divisionD.at(1) + "','" + divisionC.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(4," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionC.at(2) + "','" + divisionD.at(3) + "','" + divisionC.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(5," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionE.at(0) + "','" + divisionF.at(1) + "','" + divisionE.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(6," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + divisionE.at(2) + "','" + divisionF.at(3) + "','" + divisionE.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(7," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + divisionG.at(0) + "','" + divisionH.at(1) + "','" + divisionG.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(8," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + divisionG.at(2) + "','" + divisionH.at(3) + "','" + divisionG.at(3) + "',0,0,0,0,0,0)";
                    startRound = startRound.addSecs(addzeit);
                    lastRoundNr++; lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(9," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + divisionA.at(1) + "','" + divisionB.at(0) + "','" + divisionB.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(10," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + divisionA.at(3) + "','" + divisionB.at(2) + "','" + divisionB.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(11," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + divisionC.at(1) + "','" + divisionD.at(0) + "','" + divisionD.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(12," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionC.at(3) + "','" + divisionD.at(2) + "','" + divisionD.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(13," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionE.at(1) + "','" + divisionF.at(0) + "','" + divisionF.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(14," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionE.at(3) + "','" + divisionF.at(2) + "','" + divisionF.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(15," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionG.at(1) + "','" + divisionH.at(0) + "','" + divisionH.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(16," + intToStr(lastRoundNr) + "," + intToStr(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionG.at(3) + "','" + divisionH.at(2) + "','" + divisionH.at(3) + "',0,0,0,0,0,0)";
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
            querys << "UPDATE kreuzspiele_spielplan SET feldname = '" + fieldNames.at(i-1) + "' WHERE feldnummer = " + QString::number(i);

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
#endif // KREUZSPIELE
