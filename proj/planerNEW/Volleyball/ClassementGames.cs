using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Volleyball
{
    class ClassementGames : BaseGameHandling
    {
        #region members
        Logging log;
        DateTime startRound;
        int setCounter;
        int minutesSet;
        int minutesPause;
        int fieldCount;
        int teamsCount;
        int lastGameNr;
        int lastRoundNr;
        bool useSecondGamePlaning;
        List<String> fieldNames;
        List<List<ResultData>> resultInterimList;
        List<MatchData> resultCrossgamesList;
        int gamesCount;
        #endregion

        public ClassementGames(Logging log) : base(log)
        {
            this.log = log;
            gamesCount = 0;
        }

        public void setParameters(List<List<ResultData>> resultInterimList, List<MatchData> resultCrossgamesList, DateTime startRound,
            int pauseBetweenInterimCrossgames, int setCounter, int minutesSet, int minutesPause,
            int fieldCount, int teamsCount, List<String> fieldNames, int lastRoundNr, int lastGameNr, bool useSecondGamePlaning)
        {
            this.resultInterimList = resultInterimList;
            this.resultCrossgamesList = resultCrossgamesList;
            this.startRound = startRound;
            this.setCounter = setCounter;
            this.minutesSet = minutesSet;
            this.minutesPause = minutesPause;
            this.fieldCount = fieldCount;
            this.teamsCount = teamsCount;
            this.fieldNames = fieldNames;
            this.lastGameNr = lastGameNr;
            this.lastRoundNr = lastRoundNr;
            this.useSecondGamePlaning = useSecondGamePlaning;

            setTimeParameters(setCounter, minutesSet, minutesPause);

            this.startRound = this.startRound.AddSeconds(pauseBetweenInterimCrossgames * 60);
        }

        public void generateGames()
        {
            // clear matches if already existing
            matchData.Clear();
            gamesCount = 0;

            // generate game plan over all divisonal games
            generateGamePlan();

            if (matchData.Count > 0)
            {
                insertGameNumber(lastGameNr);

                insertGameTime(startRound);

                insertFieldnames(fieldNames);
            }
            else
            {
                log.write("could not generate crossgames games!");
                matchData.Clear();
            }
        }

        // generate game plan over all divisions
        void generateGamePlan()
        {
            int addzeit = ((setCounter * minutesSet) + minutesPause) * 60;

            // help lists
            List<ResultData> divisionA = resultInterimList[0];
            List<ResultData> divisionB = resultInterimList[1];
            List<ResultData> divisionC = resultInterimList[2];
            List<ResultData> divisionD = resultInterimList[3];
            List<ResultData> divisionE = resultInterimList[4];
            List<ResultData> divisionF = resultInterimList[5];
            List<ResultData> divisionG = resultInterimList[6];
            List<ResultData> divisionH = resultInterimList[7];
            List<ResultData> divisionI = resultInterimList[8];
            List<ResultData> divisionJ = resultInterimList[9];
            List<ResultData> divisionK = resultInterimList[10];
            List<ResultData> divisionL = resultInterimList[11];

            if(!useSecondGamePlaning)
            {

            }
            else
            {
                //QStringList referees;
                //QList<QStringList> krGameResultsCopy = krGameResults;
                //int resultDivisionsZwCountKorrigiert = resultDivisionsZw.count();
                //
                //// if 55 teams, remove the first 5 kr game results, because this teams do not play any classement games
                //if (teamsCount == 55)
                //{
                //    for (int t = 0; t < 5; t++)
                //        krGameResultsCopy.removeFirst();
                //
                //    resultDivisionsZwCountKorrigiert--;
                //}
                //
                //// get as many referees as needed for first round
                //for (int z = 0; referees.count() < fieldCount; z++)
                //{
                //    for (int k = 0; k < resultDivisionsZw.at(z).count() && referees.count() < fieldCount; k++)
                //        referees.append(resultDivisionsZw.at(z).at(k));
                //}
                //
                //// generate games
                //for (int i = 0, x = resultDivisionsZwCountKorrigiert - 1, y = ((resultDivisionsZw.at(x).count()
                //                    + resultDivisionsZw.at(x - 1).count()) / 2) - 1,
                //    startingReferee = 0, id = 1, fCount = 1; (i + 5) < krGameResultsCopy.count(); id++, lastGameNr++, startingReferee++)
                //{
                //    QString referee1 = "", referee2 = "";
                //
                //    // get the referee for the looser game
                //    if (startingReferee < fieldCount)
                //    {
                //        referee1 = referees.at(startingReferee);
                //        startingReferee++;
                //    }
                //
                //    // check if there is a next referee for the winner game
                //    if (startingReferee < fieldCount)
                //        referee2 = referees.at(startingReferee);
                //
                //    // get winner and looser for the next related games
                //    QString winner1 = krGameResultsCopy.at(i).at(1);
                //    QString looser1 = krGameResultsCopy.at(i).at(2);
                //
                //    QString winner2 = krGameResultsCopy.at(i + 5).at(1);
                //    QString looser2 = krGameResultsCopy.at(i + 5).at(2);
                //
                //    // create looser query
                //    querys << "INSERT INTO platzspiele_spielplan VALUES(" + string(id) + "," + string(lastRoundNr) + "," + string(lastGameNr) + ",'"
                //              + startRound.toString("hh:mm") + "'," + string(fCount) + ",'','"
                //              + looser1 + "','" + looser2 + "','" + referee1 + "',0,0,0,0,0,0)";
                //
                //    if (fCount >= fieldCount)
                //    {
                //        fCount = 1;
                //        lastRoundNr++;
                //        startRound = startRound.addSecs(addzeit);
                //    }
                //    else
                //    {
                //        fCount++;
                //    }
                //
                //    id++; lastGameNr++;
                //
                //    // create winner query
                //    querys << "INSERT INTO platzspiele_spielplan VALUES(" + string(id) + "," + string(lastRoundNr) + "," + string(lastGameNr) + ",'"
                //              + startRound.toString("hh:mm") + "'," + string(fCount) + ",'','"
                //              + winner1 + "','" + winner2 + "','" + referee2 + "',0,0,0,0,0,0)";
                //
                //    if (fCount >= fieldCount)
                //    {
                //        fCount = 1;
                //        lastRoundNr++;
                //        startRound = startRound.addSecs(addzeit);
                //    }
                //    else
                //    {
                //        fCount++;
                //    }
                //
                //    if (i < y)
                //    {
                //        i++;
                //    }
                //    else
                //    {
                //        x = x - 2;
                //        int toAdd = resultDivisionsZw.at(x).count() + resultDivisionsZw.at(x - 1).count();
                //        y = y + toAdd;
                //        i = i + (toAdd / 2);
                //        i++;
                //    }
                //}
            }
        }
    }
}
