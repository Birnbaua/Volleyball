﻿using System;
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
        List<ClassementData> finalClassement;
        #endregion

        public ClassementGames(Logging log) : base(log)
        {
            this.log = log;
            finalClassement = new List<ClassementData>();
        }

        public void setParameters(List<List<ResultData>> resultInterimList, List<MatchData> resultCrossgamesList, DateTime startRound,
            int pauseBetweenCrossgamesClassement, int setCounter, int minutesSet, int minutesPause,
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

            this.startRound = this.startRound.AddSeconds(pauseBetweenCrossgamesClassement * 60);
        }

        public void generateGames()
        {
            // clear matches if already existing
            matchData.Clear();

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

            if (!useSecondGamePlaning)
            {

            }
            else
            {
                List<String> refereeList = new List<String>();
                List<MatchData> copyCrossgamesList = resultCrossgamesList;
                int resultInterimListCount = resultInterimList.Count();
                List<String> winAndlooser;

                // if 55 teams, remove the first 5 kr game results, because this teams do not play any classement games
                if (teamsCount == 45 || teamsCount == 55)
                {
                    for (int i = 0; i < 5; i++)
                        resultCrossgamesList.RemoveAt(0);

                    resultInterimListCount--;
                }

                // get as many referees as needed for first round
                for (int i = 0; refereeList.Count() < fieldCount; i++)
                {
                    for (int ii = 0; ii < resultInterimList[i].Count() && refereeList.Count() < fieldCount; ii++)
                        refereeList.Add(resultInterimList[i][ii].Team);
                }

                // generate games
                for (int i = 0, x = resultInterimListCount - 1, y = ((resultInterimList[x].Count() + resultInterimList[x - 1].Count()) / 2) - 1,
                    startingReferee = 0, fCount = 1; (i + 5) < copyCrossgamesList.Count(); startingReferee++)
                {
                    String referee1 = "", referee2 = "";
                
                    // get the referee for the looser game
                    if (startingReferee < fieldCount)
                    {
                        referee1 = refereeList[startingReferee];
                        startingReferee++;
                    }
                
                    // check if there is a next referee for the winner game
                    if (startingReferee < fieldCount)
                        referee2 = refereeList[startingReferee];

                    // get winner and looser for the next related games
                    winAndlooser = CalculateResults.getResultsForCrossgamesAndClassementgames(copyCrossgamesList[i]);
                    String winner1 = winAndlooser[1];
                    String looser1 = winAndlooser[2];

                    winAndlooser = CalculateResults.getResultsForCrossgamesAndClassementgames(copyCrossgamesList[i + 5]);
                    String winner2 = winAndlooser[1];
                    String looser2 = winAndlooser[2];

                    // create looser match
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = fCount,
                        TeamA = looser1,
                        TeamB = looser2,
                        Referee = referee1
                    });
                                    
                    if (fCount >= fieldCount)
                    {
                        fCount = 1;
                        lastRoundNr++;
                    }
                    else
                    {
                        fCount++;
                    }

                    // create winner query
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = fCount,
                        TeamA = winner1,
                        TeamB = winner2,
                        Referee = referee2
                    });
                                    
                    if (fCount >= fieldCount)
                    {
                        fCount = 1;
                        lastRoundNr++;
                    }
                    else
                    {
                        fCount++;
                    }
                
                    if (i < y)
                    {
                        i++;
                    }
                    else
                    {
                        x = x - 2;
                        int toAdd = resultInterimList[x].Count() + resultInterimList[x - 1].Count();
                        y = y + toAdd;
                        i = i + (toAdd / 2);
                        i++;
                    }
                }
            }
        }

        public void createFinalClassement()
        {
            int classement = teamsCount;

            finalClassement.Clear();

            switch (teamsCount)
            {
                case 55:
                    // create the classements for the worst teams
                    List<ResultData> bottomRankings = resultInterimList[10];

                    for (int i = 4; i >= 0; i--)
                    {
                        finalClassement.Add(new ClassementData() { Rank = classement, Team = bottomRankings[i].Team });
                        classement--;
                    }

                    // create the classements for teams that played cross game
                    for (int i = 0; i < 5; i++, classement--)
                    {
                        List<String> cgGameResult = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[i]);
                        
                        // generate looser
                        finalClassement.Add(new ClassementData() { Rank = classement, Team = cgGameResult[2] });
                        classement--;

                        // generate winner
                        finalClassement.Add(new ClassementData() { Rank = classement, Team = cgGameResult[1] });
                    }

                    // create the next classements for teams that played classement game
                    for (int i = 0, x = classement; x > 0; i++, x--)
                    {
                        List<String> clgGameResult = CalculateResults.getResultsForCrossgamesAndClassementgames(matchData[i]);
                        
                        // generate looser
                        finalClassement.Add(new ClassementData() { Rank = x, Team = clgGameResult[2] });
                        x--;

                        // generate winner query
                        finalClassement.Add(new ClassementData() { Rank = x, Team = clgGameResult[1] });
                    }
                    break;

                case 60:
                    for (int i = 0, x = classement; x > 0; i++, x--)
                    {
                        List<String> clgGameResult = CalculateResults.getResultsForCrossgamesAndClassementgames(matchData[i]);
                        
                        // generate looser
                        finalClassement.Add(new ClassementData() { Rank = x, Team = clgGameResult[2] });
                        x--;

                        // generate winner query
                        finalClassement.Add(new ClassementData() { Rank = x, Team = clgGameResult[1] });
                    }
                    break;
            }
        }
    }
}