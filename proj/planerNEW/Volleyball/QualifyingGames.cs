using System;
using System.Collections.Generic;

namespace Volleyball
{
    class QualifyingGames : BaseGameHandling
    {
        #region members
        Logging log;
        DateTime startTournament;
        int setCounter;
        int minutesSet;
        int minutesPause;
        int fieldCount;
        int teamsCount;
        List<String> fieldNames;
        List<List<String>> divisionsList;
        List<int[]> gamePlan;
        #endregion

        public QualifyingGames(Logging log) : base(log)
        {
            this.log = log; 
        }

        public void setParameters(List<List<String>> divisionsList, List<int[]> gamePlan, DateTime startTournament, 
            int setCounter, int minutesSet, int minutesPause, int fieldCount, int teamsCount, List<String> fieldNames)
        {
            this.divisionsList = divisionsList;
            this.gamePlan = gamePlan;
            this.startTournament = startTournament;
            this.setCounter = setCounter;
            this.minutesSet = minutesSet;
            this.minutesPause = minutesPause;
            this.fieldCount = fieldCount;
            this.teamsCount = teamsCount;
            this.fieldNames = fieldNames;

            setTimeParameters(setCounter, minutesSet, minutesPause);
        }

        public void generateGames()
        {
            // clear matches if already existing
            matchData.Clear();

            // generate game plan over all divisonal games
            if (generateGamePlan())
            {                
                insertGameNumber(1);

                insertRoundNumber(1, fieldCount);

                insertGameTime(startTournament);

                insertFieldnumbersAndFieldnames(fieldCount, fieldNames);

                fillResultLists(divisionsList);
            }
            else
            {
                log.write("could not generate qualifying games, because the amount of teams is not valid => valid teams 5, 10, 15, ...");
            }
        }
                
        // generate game plan over all divisions
        bool generateGamePlan()
        {
            if (teamsCount % 5 == 0)
            {
                int gamesCount = 0;
                List<List<MatchData>> matchDataHelperList = new List<List<MatchData>>();

                foreach (List<String> divisionList in divisionsList)
                {
                    List<MatchData> matchDataList = new List<MatchData>();

                    foreach(int[] game in gamePlan)
                    {
                        MatchData newMatch = new MatchData();

                        newMatch.TeamA = divisionList[game[0]];
                        newMatch.TeamB = divisionList[game[1]];
                        newMatch.Referee = divisionList[game[2]];

                        matchDataList.Add(newMatch);
                        gamesCount++;
                    }

                    matchDataHelperList.Add(matchDataList);
                }
                                
                for (int i = 1, ii = 0; i <= gamesCount;)
                {
                    foreach (List<MatchData> mdl in matchDataHelperList)
                    {
                        matchData.Add(mdl[ii]);
                        i++;
                    }

                    if (ii >= matchDataHelperList.Count)
                        ii = 0;
                    else
                        ii++;
                }

                return true;
            }

            return false;
        }
    }
}
