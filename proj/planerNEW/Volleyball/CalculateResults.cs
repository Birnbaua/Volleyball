using System;
using System.Collections.Generic;

namespace Volleyball
{
    class CalculateResults
    {
        public static List<TeamResult> calculateSetResult(int teamASetpoints, int teamBSetpoints)
        {
            TeamResult teamA = new TeamResult();
            TeamResult teamB = new TeamResult();
                        
            if (teamASetpoints > teamBSetpoints) // first team wins
            {
                teamA.PointsSet = 2;
                teamA.PointsMatch = teamASetpoints - teamBSetpoints;
                teamB.PointsMatch = teamBSetpoints - teamASetpoints;
            }
            else if (teamASetpoints < teamBSetpoints) // second team wins
            {
                teamB.PointsSet = 2;
                teamB.PointsMatch = teamBSetpoints - teamASetpoints;
                teamA.PointsMatch = teamASetpoints - teamBSetpoints;
            }
            else // draw game
            {
                teamA.PointsSet = 1;
                teamB.PointsSet = 1;
            }

            return new List<TeamResult> { teamA, teamB };
        }


        public static List<TeamResult> calculateResults(List<MatchData> resultsToCalculate)
        {
            List<TeamResult> resultList = new List<TeamResult>();

            foreach(MatchData resultToCalculate in resultsToCalculate)
            {
                TeamResult teamA = new TeamResult();
                TeamResult teamB = new TeamResult();

                teamA.TeamName = resultToCalculate.TeamA;
                teamB.TeamName = resultToCalculate.TeamB;
                
                if (resultToCalculate.PointsMatch1TeamA > 0 && resultToCalculate.PointsMatch1TeamB > 0)
                {
                    List<TeamResult> teamResultsSet = calculateSetResult(resultToCalculate.PointsMatch1TeamA, resultToCalculate.PointsMatch1TeamB);
                    teamA.PointsSet += teamResultsSet[0].PointsSet;
                    teamA.PointsMatch += teamResultsSet[0].PointsMatch;
                    teamB.PointsSet += teamResultsSet[1].PointsSet;
                    teamB.PointsMatch += teamResultsSet[1].PointsMatch;
                }

                if (resultToCalculate.PointsMatch2TeamA > 0 && resultToCalculate.PointsMatch2TeamB > 0)
                {
                    List<TeamResult> teamResultsSet = calculateSetResult(resultToCalculate.PointsMatch2TeamA, resultToCalculate.PointsMatch2TeamB);
                    teamA.PointsSet += teamResultsSet[0].PointsSet;
                    teamA.PointsMatch += teamResultsSet[0].PointsMatch;
                    teamB.PointsSet += teamResultsSet[1].PointsSet;
                    teamB.PointsMatch += teamResultsSet[1].PointsMatch;
                }

                if (resultToCalculate.PointsMatch3TeamA > 0 && resultToCalculate.PointsMatch3TeamB > 0)
                {
                    List<TeamResult> teamResultsSet = calculateSetResult(resultToCalculate.PointsMatch3TeamA, resultToCalculate.PointsMatch3TeamB);
                    teamA.PointsSet += teamResultsSet[0].PointsSet;
                    teamA.PointsMatch += teamResultsSet[0].PointsMatch;
                    teamB.PointsSet += teamResultsSet[1].PointsSet;
                    teamB.PointsMatch += teamResultsSet[1].PointsMatch;
                }

                resultList.Add(teamA);
                resultList.Add(teamB);
            }

            return resultList;
        }

        public static List<TeamResult> addResultsForQualifyingAndInterimRounds(List<TeamResult> teamResults)
        {
            List<TeamResult> calcTeamResults = new List<TeamResult>();

            while (teamResults.Count > 0)
            {
                TeamResult result = new TeamResult();
                result.TeamName = teamResults[0].TeamName;

                for (int i = 0; i < teamResults.Count;)
                {
                    if (teamResults[i].TeamName == result.TeamName)
                    {
                        result.PointsSet += teamResults[i].PointsSet;
                        result.PointsMatch += teamResults[i].PointsMatch;

                        teamResults.RemoveAt(i);
                    }
                    else
                    {
                        i++;
                    }
                }

                calcTeamResults.Add(result);
            }

            return calcTeamResults;
        }

        public static List<String> getResultsForCrossgamesAndClassementgames(MatchData resultToCalculate)
        {
            TeamResult teamA = new TeamResult();
            TeamResult teamB = new TeamResult();

            String spiel = resultToCalculate.Game.ToString();

            teamA.TeamName = resultToCalculate.TeamA;
            teamB.TeamName = resultToCalculate.TeamB;

            if (resultToCalculate.PointsMatch1TeamA > 0 && resultToCalculate.PointsMatch1TeamB > 0)
            {
                List<TeamResult> teamResultsSet = calculateSetResult(resultToCalculate.PointsMatch1TeamA, resultToCalculate.PointsMatch1TeamB);
                teamA.PointsSet += teamResultsSet[0].PointsSet;
                teamA.PointsMatch += teamResultsSet[0].PointsMatch;
                teamB.PointsSet += teamResultsSet[1].PointsSet;
                teamB.PointsMatch += teamResultsSet[1].PointsMatch;
            }

            if (resultToCalculate.PointsMatch2TeamA > 0 && resultToCalculate.PointsMatch2TeamB > 0)
            {
                List<TeamResult> teamResultsSet = calculateSetResult(resultToCalculate.PointsMatch2TeamA, resultToCalculate.PointsMatch2TeamB);
                teamA.PointsSet += teamResultsSet[0].PointsSet;
                teamA.PointsMatch += teamResultsSet[0].PointsMatch;
                teamB.PointsSet += teamResultsSet[1].PointsSet;
                teamB.PointsMatch += teamResultsSet[1].PointsMatch;
            }

            if (resultToCalculate.PointsMatch3TeamA > 0 && resultToCalculate.PointsMatch3TeamB > 0)
            {
                List<TeamResult> teamResultsSet = calculateSetResult(resultToCalculate.PointsMatch3TeamA, resultToCalculate.PointsMatch3TeamB);
                teamA.PointsSet += teamResultsSet[0].PointsSet;
                teamA.PointsMatch += teamResultsSet[0].PointsMatch;
                teamB.PointsSet += teamResultsSet[1].PointsSet;
                teamB.PointsMatch += teamResultsSet[1].PointsMatch;
            }

            if (teamA.PointsSet > teamB.PointsSet)
            {
                return new List<String> { spiel, teamA.TeamName, teamB.TeamName };
            }
            else if (teamA.PointsSet < teamB.PointsSet)
            {
                return new List<String> { spiel, teamB.TeamName, teamA.TeamName };
            }
            else
            {
                if (teamA.PointsMatch > teamB.PointsMatch)
                {
                    return new List<String> { spiel, teamA.TeamName, teamB.TeamName };
                }
                else if (teamA.PointsMatch < teamB.PointsMatch)
                {
                    return new List<String> { spiel, teamB.TeamName, teamA.TeamName };
                }
                else
                {
                    return new List<String> { spiel, teamA.TeamName, teamB.TeamName };
                }
            }
        }
    }
}
