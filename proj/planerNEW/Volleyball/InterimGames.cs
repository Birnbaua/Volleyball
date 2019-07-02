using System;
using System.Collections.Generic;

namespace Volleyball
{
    class InterimGames : BaseGameHandling
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
        List<List<ResultData>> divisionsQualifyingList;
        List<List<String>> divisionsList;
        List<int[]> gamePlan;
        #endregion

        public InterimGames(Logging log) : base(log)
        {
            this.log = log;
        }

        public void setParameters(List<List<ResultData>> divisionsQualifyingList, List<int[]> gamePlan, DateTime startRound, 
            int pauseBetweenQualifyingInterim, int setCounter, int minutesSet, int minutesPause,
            int fieldCount, int teamsCount, List<String> fieldNames, int lastRoundNr, int lastGameNr, bool useSecondGamePlaning)
        {
            this.divisionsQualifyingList = divisionsQualifyingList;
            this.startRound = startRound;
            this.setCounter = setCounter;
            this.minutesSet = minutesSet;
            this.minutesPause = minutesPause;
            this.fieldCount = fieldCount;
            this.teamsCount = teamsCount;
            this.fieldNames = fieldNames;
            this.lastGameNr = lastGameNr;
            this.lastRoundNr = lastRoundNr;
            this.gamePlan = gamePlan;
            this.useSecondGamePlaning = useSecondGamePlaning;

            setTimeParameters(setCounter, minutesSet, minutesPause);

            this.startRound = this.startRound.AddSeconds(pauseBetweenQualifyingInterim * 60);
        }

        public void generateGames()
        {
            // clear matches if already existing
            matchData.Clear();

            divisionsList = generateNewDivisions();

            // generate game plan over all divisonal games
            if (divisionsList.Count > 0 && generateGamePlan())
            {
                insertGameNumber(lastGameNr);

                insertRoundNumber(lastRoundNr, fieldCount);

                insertGameTime(startRound);

                insertFieldnumbersAndFieldnames(fieldCount, fieldNames);

                fillResultLists(divisionsList);
            }
            else
            {
                log.write("could not generate interim games!");
            }
        }

        bool generateGamePlan()
        {
            if (teamsCount % 5 == 0)
            {
                int gamesCount = 0;
                List<List<MatchData>> matchDataHelperList = new List<List<MatchData>>();

                foreach (List<String> divisionList in divisionsList)
                {
                    List<MatchData> matchDataList = new List<MatchData>();

                    foreach (int[] game in gamePlan)
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

        List<ResultData> giveMeSort(List<ResultData> divisionTeams)
        {
            for (int i = divisionTeams.Count - 1; i > 0; i--)
            {
                for (int ii = 0; ii < i; ii++)
                {
                    if (divisionTeams[ii].PointsSets < divisionTeams[ii + 1].PointsSets)
                    {
                        ResultData team = divisionTeams[ii];

                        divisionTeams[ii] = divisionTeams[ii + 1];
                        divisionTeams[ii + 1] = team;
                    }
                    else if (divisionTeams[ii].PointsSets == divisionTeams[ii + 1].PointsSets
                        && divisionTeams[ii].PointsMatches < divisionTeams[ii + 1].PointsMatches)
                    {
                        ResultData team = divisionTeams[ii];

                        divisionTeams[ii] = divisionTeams[ii + 1];
                        divisionTeams[ii + 1] = team;
                    }
                    else if (divisionTeams[ii].PointsSets == divisionTeams[ii + 1].PointsSets
                        && divisionTeams[ii].PointsMatches == divisionTeams[ii + 1].PointsMatches
                        && divisionTeams[ii].ExternalRank > divisionTeams[ii + 1].ExternalRank)
                    {
                        ResultData team = divisionTeams[ii];

                        divisionTeams[ii] = divisionTeams[ii + 1];
                        divisionTeams[ii + 1] = team;
                    }
                }
            }

            return divisionTeams;
        }

        List<String> giveMeTeamnames(List<ResultData> divisionTeams)
        {
            List<String> teamList = new List<String>();

            for (int i = 0; i < divisionTeams.Count; i++)
                teamList.Add(divisionTeams[i].Team);

            return teamList;
        }

        // generate new divisions
        List<List<String>> generateNewDivisions()
        {
            List<List<String>> newDivisionList = new List<List<String>>();
            
            // help lists
            List<List<ResultData>> divisionRanksFirstToFifth = new List<List<ResultData>>();
            
            for (int i = 0; i < 5; i++)
            {
                List<ResultData> nextRank = new List<ResultData>();

                foreach (List<ResultData> rdList in divisionsQualifyingList)
                {
                    if(rdList.Count > i)
                        nextRank.Add(rdList[i]);
                }

                divisionRanksFirstToFifth.Add(nextRank);
            }
            
            log.write("teams count for new interim divisions = " + divisionsQualifyingList.Count + ", useSecondGamePlaning = " + useSecondGamePlaning);

            // there is a second set of game plans for 50 or more teams, can be choosen in gui => game configuration
            if (!useSecondGamePlaning)
            {
                if (teamsCount == 20)
                {
                    // make ranking of all divisions thrid teams
                    divisionRanksFirstToFifth[2] = giveMeSort(divisionRanksFirstToFifth[2]);

                    // group A
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][0].Team,
                            divisionRanksFirstToFifth[0][1].Team,
                            divisionRanksFirstToFifth[1][2].Team,
                            divisionRanksFirstToFifth[1][3].Team,
                            divisionRanksFirstToFifth[2][0].Team
                        });

                    // group B
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][2].Team,
                            divisionRanksFirstToFifth[0][3].Team,
                            divisionRanksFirstToFifth[1][0].Team,
                            divisionRanksFirstToFifth[1][1].Team,
                            divisionRanksFirstToFifth[2][1].Team
                        });

                    // group C
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[2][2].Team,
                            divisionRanksFirstToFifth[3][0].Team,
                            divisionRanksFirstToFifth[3][1].Team,
                            divisionRanksFirstToFifth[4][2].Team,
                            divisionRanksFirstToFifth[4][3].Team
                        });

                    // group D
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[2][3].Team,
                            divisionRanksFirstToFifth[3][2].Team,
                            divisionRanksFirstToFifth[3][3].Team,
                            divisionRanksFirstToFifth[4][0].Team,
                            divisionRanksFirstToFifth[4][1].Team
                        });
                }
                else if (teamsCount == 25)
                {
                    // group A
                    newDivisionList.Add(giveMeTeamnames(divisionRanksFirstToFifth[0]));

                    // group B
                    newDivisionList.Add(giveMeTeamnames(divisionRanksFirstToFifth[1]));

                    // group C
                    newDivisionList.Add(giveMeTeamnames(divisionRanksFirstToFifth[2]));

                    // group D
                    newDivisionList.Add(giveMeTeamnames(divisionRanksFirstToFifth[3]));

                    // group E
                    newDivisionList.Add(giveMeTeamnames(divisionRanksFirstToFifth[4]));
                }
                else if (teamsCount == 28)
                {
                    // make ranking of all divisions second teams
                    divisionRanksFirstToFifth[1] = giveMeSort(divisionRanksFirstToFifth[1]);

                    // group A
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][0].Team,
                            divisionRanksFirstToFifth[0][1].Team,
                            divisionRanksFirstToFifth[0][2].Team,
                            divisionRanksFirstToFifth[1][0].Team
                        });

                    // group B
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][3].Team,
                            divisionRanksFirstToFifth[0][4].Team,
                            divisionRanksFirstToFifth[0][5].Team,
                            divisionRanksFirstToFifth[1][1].Team
                        });

                    // group C
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[1][2].Team,
                            divisionRanksFirstToFifth[1][5].Team,
                            divisionRanksFirstToFifth[2][0].Team,
                            divisionRanksFirstToFifth[2][1].Team,
                            divisionRanksFirstToFifth[2][2].Team
                        });

                    // group D
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[1][3].Team,
                            divisionRanksFirstToFifth[1][4].Team,
                            divisionRanksFirstToFifth[2][3].Team,
                            divisionRanksFirstToFifth[2][4].Team,
                            divisionRanksFirstToFifth[2][5].Team
                        });

                    // group E
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[3][0].Team,
                            divisionRanksFirstToFifth[3][1].Team,
                            divisionRanksFirstToFifth[3][2].Team,
                            divisionRanksFirstToFifth[4][2].Team,
                            divisionRanksFirstToFifth[4][3].Team
                        });

                    // group F
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[3][3].Team,
                            divisionRanksFirstToFifth[3][4].Team,
                            divisionRanksFirstToFifth[3][5].Team,
                            divisionRanksFirstToFifth[4][0].Team,
                            divisionRanksFirstToFifth[4][1].Team
                        });

                }
                else if (teamsCount == 30)
                {
                    // make ranking of all divisions second teams
                    divisionRanksFirstToFifth[1] = giveMeSort(divisionRanksFirstToFifth[1]);

                    // make ranking of all divisions fourth teams
                    divisionRanksFirstToFifth[3] = giveMeSort(divisionRanksFirstToFifth[3]);

                    // group A
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][0].Team,
                            divisionRanksFirstToFifth[0][1].Team,
                            divisionRanksFirstToFifth[0][2].Team,
                            divisionRanksFirstToFifth[1][0].Team,
                            divisionRanksFirstToFifth[1][3].Team
                        });

                    // group B
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][3].Team,
                            divisionRanksFirstToFifth[0][4].Team,
                            divisionRanksFirstToFifth[0][5].Team,
                            divisionRanksFirstToFifth[1][1].Team,
                            divisionRanksFirstToFifth[1][2].Team
                        });

                    // group C
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[1][4].Team,
                            divisionRanksFirstToFifth[2][0].Team,
                            divisionRanksFirstToFifth[2][1].Team,
                            divisionRanksFirstToFifth[2][2].Team,
                            divisionRanksFirstToFifth[3][1].Team
                        });

                    // group D
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[1][5].Team,
                            divisionRanksFirstToFifth[2][3].Team,
                            divisionRanksFirstToFifth[2][4].Team,
                            divisionRanksFirstToFifth[2][5].Team,
                            divisionRanksFirstToFifth[3][0].Team
                        });

                    // group E
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[3][2].Team,
                            divisionRanksFirstToFifth[3][5].Team,
                            divisionRanksFirstToFifth[4][0].Team,
                            divisionRanksFirstToFifth[4][1].Team,
                            divisionRanksFirstToFifth[4][2].Team
                        });

                    // group F
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[3][3].Team,
                            divisionRanksFirstToFifth[3][4].Team,
                            divisionRanksFirstToFifth[4][3].Team,
                            divisionRanksFirstToFifth[4][4].Team,
                            divisionRanksFirstToFifth[4][5].Team
                        });

                }
                else if (teamsCount == 35)
                {
                    // make ranking of all divisions second teams
                    divisionRanksFirstToFifth[1] = giveMeSort(divisionRanksFirstToFifth[1]);

                    // make ranking of all divisions third teams
                    divisionRanksFirstToFifth[2] = giveMeSort(divisionRanksFirstToFifth[2]);

                    // make ranking of all divisions fourth teams
                    divisionRanksFirstToFifth[3] = giveMeSort(divisionRanksFirstToFifth[3]);

                    // make ranking of all divisions fifth teams
                    divisionRanksFirstToFifth[4] = giveMeSort(divisionRanksFirstToFifth[4]);

                    // group A
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][0].Team,
                            divisionRanksFirstToFifth[0][1].Team,
                            divisionRanksFirstToFifth[0][2].Team,
                            divisionRanksFirstToFifth[0][3].Team,
                            divisionRanksFirstToFifth[1][1].Team
                        });

                    // group B
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][4].Team,
                            divisionRanksFirstToFifth[0][5].Team,
                            divisionRanksFirstToFifth[0][6].Team,
                            divisionRanksFirstToFifth[1][0].Team,
                            divisionRanksFirstToFifth[1][2].Team
                        });

                    // group C
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[1][3].Team,
                            divisionRanksFirstToFifth[1][5].Team,
                            divisionRanksFirstToFifth[2][0].Team,
                            divisionRanksFirstToFifth[2][2].Team,
                            divisionRanksFirstToFifth[2][4].Team
                        });

                    // group D
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[1][4].Team,
                            divisionRanksFirstToFifth[1][6].Team,
                            divisionRanksFirstToFifth[2][1].Team,
                            divisionRanksFirstToFifth[2][3].Team,
                            divisionRanksFirstToFifth[2][5].Team
                        });

                    // group E
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[2][6].Team,
                            divisionRanksFirstToFifth[3][1].Team,
                            divisionRanksFirstToFifth[3][3].Team,
                            divisionRanksFirstToFifth[3][5].Team,
                            divisionRanksFirstToFifth[4][0].Team
                        });

                    // group F
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[3][0].Team,
                            divisionRanksFirstToFifth[3][2].Team,
                            divisionRanksFirstToFifth[3][4].Team,
                            divisionRanksFirstToFifth[3][6].Team,
                            divisionRanksFirstToFifth[4][1].Team
                        });

                    // group G
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[4][2].Team,
                            divisionRanksFirstToFifth[4][3].Team,
                            divisionRanksFirstToFifth[4][4].Team,
                            divisionRanksFirstToFifth[4][5].Team,
                            divisionRanksFirstToFifth[4][6].Team
                        });
                }
                else if (teamsCount == 40)
                {
                    // make ranking of all divisions second teams
                    divisionRanksFirstToFifth[1] = giveMeSort(divisionRanksFirstToFifth[1]);

                    // make ranking of all divisions third teams
                    divisionRanksFirstToFifth[2] = giveMeSort(divisionRanksFirstToFifth[2]);

                    // make ranking of all divisions fourth teams
                    divisionRanksFirstToFifth[3] = giveMeSort(divisionRanksFirstToFifth[3]);

                    // make ranking of all divisions fifth teams
                    divisionRanksFirstToFifth[4] = giveMeSort(divisionRanksFirstToFifth[4]);

                    // group A
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][0].Team,
                            divisionRanksFirstToFifth[0][1].Team,
                            divisionRanksFirstToFifth[0][2].Team,
                            divisionRanksFirstToFifth[0][3].Team,
                            divisionRanksFirstToFifth[1][0].Team
                        });

                    // group B
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][4].Team,
                            divisionRanksFirstToFifth[0][5].Team,
                            divisionRanksFirstToFifth[0][6].Team,
                            divisionRanksFirstToFifth[0][7].Team,
                            divisionRanksFirstToFifth[1][1].Team
                        });

                    // group C
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[1][2].Team,
                            divisionRanksFirstToFifth[1][3].Team,
                            divisionRanksFirstToFifth[1][4].Team,
                            divisionRanksFirstToFifth[2][0].Team,
                            divisionRanksFirstToFifth[2][2].Team
                        });

                    // group D
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[1][5].Team,
                            divisionRanksFirstToFifth[1][6].Team,
                            divisionRanksFirstToFifth[1][7].Team,
                            divisionRanksFirstToFifth[2][1].Team,
                            divisionRanksFirstToFifth[2][3].Team
                        });

                    // group E
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[2][4].Team,
                            divisionRanksFirstToFifth[2][6].Team,
                            divisionRanksFirstToFifth[3][0].Team,
                            divisionRanksFirstToFifth[3][2].Team,
                            divisionRanksFirstToFifth[3][4].Team
                        });

                    // group F
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[2][5].Team,
                            divisionRanksFirstToFifth[2][7].Team,
                            divisionRanksFirstToFifth[3][1].Team,
                            divisionRanksFirstToFifth[3][3].Team,
                            divisionRanksFirstToFifth[3][5].Team
                        });

                    // group G
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[3][6].Team,
                            divisionRanksFirstToFifth[4][0].Team,
                            divisionRanksFirstToFifth[4][2].Team,
                            divisionRanksFirstToFifth[4][4].Team,
                            divisionRanksFirstToFifth[4][6].Team
                        });

                    // group H
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[3][7].Team,
                            divisionRanksFirstToFifth[4][1].Team,
                            divisionRanksFirstToFifth[4][3].Team,
                            divisionRanksFirstToFifth[4][5].Team,
                            divisionRanksFirstToFifth[4][7].Team
                        });
                }
                else if (teamsCount == 45)
                {
                    // make ranking of all divisions second teams
                    divisionRanksFirstToFifth[1] = giveMeSort(divisionRanksFirstToFifth[1]);

                    // make ranking of all divisions third teams
                    divisionRanksFirstToFifth[2] = giveMeSort(divisionRanksFirstToFifth[2]);

                    // make ranking of all divisions fourth teams
                    divisionRanksFirstToFifth[3] = giveMeSort(divisionRanksFirstToFifth[3]);

                    // make ranking of all divisions fifth teams
                    divisionRanksFirstToFifth[4] = giveMeSort(divisionRanksFirstToFifth[4]);

                    // group A
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][0].Team,
                            divisionRanksFirstToFifth[0][1].Team,
                            divisionRanksFirstToFifth[0][2].Team,
                            divisionRanksFirstToFifth[0][3].Team,
                            divisionRanksFirstToFifth[0][4].Team
                        });

                    // group B
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][5].Team,
                            divisionRanksFirstToFifth[0][6].Team,
                            divisionRanksFirstToFifth[0][7].Team,
                            divisionRanksFirstToFifth[0][8].Team,
                            divisionRanksFirstToFifth[1][0].Team
                        });

                    // group C
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[1][1].Team,
                            divisionRanksFirstToFifth[1][2].Team,
                            divisionRanksFirstToFifth[1][3].Team,
                            divisionRanksFirstToFifth[1][4].Team,
                            divisionRanksFirstToFifth[2][0].Team
                        });

                    // group D
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[1][5].Team,
                            divisionRanksFirstToFifth[1][6].Team,
                            divisionRanksFirstToFifth[1][7].Team,
                            divisionRanksFirstToFifth[1][8].Team,
                            divisionRanksFirstToFifth[2][1].Team
                        });

                    // group E
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[2][2].Team,
                            divisionRanksFirstToFifth[2][4].Team,
                            divisionRanksFirstToFifth[2][6].Team,
                            divisionRanksFirstToFifth[2][8].Team,
                            divisionRanksFirstToFifth[3][0].Team
                        });

                    // group F
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[2][3].Team,
                            divisionRanksFirstToFifth[2][5].Team,
                            divisionRanksFirstToFifth[2][7].Team,
                            divisionRanksFirstToFifth[3][1].Team,
                            divisionRanksFirstToFifth[3][2].Team
                        });

                    // group G
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[3][4].Team,
                            divisionRanksFirstToFifth[3][6].Team,
                            divisionRanksFirstToFifth[3][8].Team,
                            divisionRanksFirstToFifth[4][0].Team,
                            divisionRanksFirstToFifth[4][2].Team
                        });

                    // group H
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[3][3].Team,
                            divisionRanksFirstToFifth[3][5].Team,
                            divisionRanksFirstToFifth[3][7].Team,
                            divisionRanksFirstToFifth[4][1].Team,
                            divisionRanksFirstToFifth[4][3].Team
                        });

                    // group J
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[4][4].Team,
                            divisionRanksFirstToFifth[4][5].Team,
                            divisionRanksFirstToFifth[4][6].Team,
                            divisionRanksFirstToFifth[4][7].Team,
                            divisionRanksFirstToFifth[4][8].Team
                        });
                }
                else if (teamsCount == 50)
                {
                    // group A
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][0].Team,
                            divisionRanksFirstToFifth[0][1].Team,
                            divisionRanksFirstToFifth[0][2].Team,
                            divisionRanksFirstToFifth[0][3].Team,
                            divisionRanksFirstToFifth[0][4].Team
                        });

                    // group B
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][5].Team,
                            divisionRanksFirstToFifth[0][6].Team,
                            divisionRanksFirstToFifth[0][7].Team,
                            divisionRanksFirstToFifth[0][8].Team,
                            divisionRanksFirstToFifth[0][9].Team
                        });

                    // group C
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[1][0].Team,
                            divisionRanksFirstToFifth[1][1].Team,
                            divisionRanksFirstToFifth[1][2].Team,
                            divisionRanksFirstToFifth[1][3].Team,
                            divisionRanksFirstToFifth[1][4].Team
                        });

                    // group D
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[1][5].Team,
                            divisionRanksFirstToFifth[1][6].Team,
                            divisionRanksFirstToFifth[1][7].Team,
                            divisionRanksFirstToFifth[1][8].Team,
                            divisionRanksFirstToFifth[1][9].Team
                        });

                    // group E
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[2][0].Team,
                            divisionRanksFirstToFifth[2][1].Team,
                            divisionRanksFirstToFifth[2][2].Team,
                            divisionRanksFirstToFifth[2][3].Team,
                            divisionRanksFirstToFifth[2][4].Team
                        });

                    // group F
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[2][5].Team,
                            divisionRanksFirstToFifth[2][6].Team,
                            divisionRanksFirstToFifth[2][7].Team,
                            divisionRanksFirstToFifth[2][8].Team,
                            divisionRanksFirstToFifth[2][9].Team
                        });

                    // group G
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[3][0].Team,
                            divisionRanksFirstToFifth[3][1].Team,
                            divisionRanksFirstToFifth[3][2].Team,
                            divisionRanksFirstToFifth[3][3].Team,
                            divisionRanksFirstToFifth[3][4].Team
                        });

                    // group H
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[3][5].Team,
                            divisionRanksFirstToFifth[3][6].Team,
                            divisionRanksFirstToFifth[3][7].Team,
                            divisionRanksFirstToFifth[3][8].Team,
                            divisionRanksFirstToFifth[3][9].Team
                        });

                    // group I
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[4][0].Team,
                            divisionRanksFirstToFifth[4][1].Team,
                            divisionRanksFirstToFifth[4][2].Team,
                            divisionRanksFirstToFifth[4][3].Team,
                            divisionRanksFirstToFifth[4][4].Team
                        });

                    // group J
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[4][5].Team,
                            divisionRanksFirstToFifth[4][6].Team,
                            divisionRanksFirstToFifth[4][7].Team,
                            divisionRanksFirstToFifth[4][8].Team,
                            divisionRanksFirstToFifth[4][9].Team
                        });
                }
            }
            else
            {
                if(teamsCount == 50)
                {
                    # region profi
                    // group A
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][0].Team,
                            divisionRanksFirstToFifth[0][1].Team,
                            divisionRanksFirstToFifth[1][2].Team,
                            divisionRanksFirstToFifth[1][3].Team,
                            divisionRanksFirstToFifth[1][4].Team
                        });

                    // group B
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][2].Team,
                            divisionRanksFirstToFifth[0][3].Team,
                            divisionRanksFirstToFifth[1][5].Team,
                            divisionRanksFirstToFifth[1][6].Team,
                            divisionRanksFirstToFifth[1][7].Team
                        });

                    // group C
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][4].Team,
                            divisionRanksFirstToFifth[0][5].Team,
                            divisionRanksFirstToFifth[0][6].Team,
                            divisionRanksFirstToFifth[1][8].Team,
                            divisionRanksFirstToFifth[1][9].Team
                        });

                    // group D
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][7].Team,
                            divisionRanksFirstToFifth[0][8].Team,
                            divisionRanksFirstToFifth[0][9].Team,
                            divisionRanksFirstToFifth[1][0].Team,
                            divisionRanksFirstToFifth[1][1].Team
                        });
                    #endregion

                    #region hobby a
                    // group A
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[2][0].Team,
                            divisionRanksFirstToFifth[2][1].Team,
                            divisionRanksFirstToFifth[3][2].Team,
                            divisionRanksFirstToFifth[3][3].Team,
                            divisionRanksFirstToFifth[3][4].Team
                        });

                    // group B
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[2][2].Team,
                            divisionRanksFirstToFifth[2][3].Team,
                            divisionRanksFirstToFifth[3][5].Team,
                            divisionRanksFirstToFifth[3][6].Team,
                            divisionRanksFirstToFifth[3][7].Team
                        });

                    // group C
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[2][4].Team,
                            divisionRanksFirstToFifth[2][5].Team,
                            divisionRanksFirstToFifth[2][6].Team,
                            divisionRanksFirstToFifth[3][8].Team,
                            divisionRanksFirstToFifth[3][9].Team
                        });

                    // group D
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[2][7].Team,
                            divisionRanksFirstToFifth[2][8].Team,
                            divisionRanksFirstToFifth[2][9].Team,
                            divisionRanksFirstToFifth[3][0].Team,
                            divisionRanksFirstToFifth[3][1].Team
                        });
                    #endregion

                    #region hobby b
                    // group A
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[4][0].Team,
                            divisionRanksFirstToFifth[4][1].Team,
                            divisionRanksFirstToFifth[4][2].Team,
                            divisionRanksFirstToFifth[4][3].Team,
                            divisionRanksFirstToFifth[4][4].Team
                        });

                    // group B
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[4][5].Team,
                            divisionRanksFirstToFifth[4][6].Team,
                            divisionRanksFirstToFifth[4][7].Team,
                            divisionRanksFirstToFifth[4][8].Team,
                            divisionRanksFirstToFifth[4][9].Team
                        });
                    #endregion
                }
                else if(teamsCount == 55)
                {
                    // make ranking of all divisions second teams
                    divisionRanksFirstToFifth[1] = giveMeSort(divisionRanksFirstToFifth[1]);

                    // make ranking of all divisions fourth teams
                    divisionRanksFirstToFifth[3] = giveMeSort(divisionRanksFirstToFifth[3]);

                    // make ranking of all divisions fifth teams
                    divisionRanksFirstToFifth[4] = giveMeSort(divisionRanksFirstToFifth[4]);

                    # region profi
                    // group A
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][0].Team,
                            divisionRanksFirstToFifth[0][1].Team,
                            divisionRanksFirstToFifth[0][2].Team,
                            divisionRanksFirstToFifth[1][3].Team,
                            divisionRanksFirstToFifth[1][7].Team
                        });

                    // group B
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][3].Team,
                            divisionRanksFirstToFifth[0][4].Team,
                            divisionRanksFirstToFifth[0][5].Team,
                            divisionRanksFirstToFifth[1][2].Team,
                            divisionRanksFirstToFifth[1][6].Team
                        });

                    // group C
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][6].Team,
                            divisionRanksFirstToFifth[0][7].Team,
                            divisionRanksFirstToFifth[0][8].Team,
                            divisionRanksFirstToFifth[1][1].Team,
                            divisionRanksFirstToFifth[1][5].Team
                        });

                    // group D
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][9].Team,
                            divisionRanksFirstToFifth[0][10].Team,
                            divisionRanksFirstToFifth[1][0].Team,
                            divisionRanksFirstToFifth[1][4].Team,
                            divisionRanksFirstToFifth[1][8].Team
                        });
                    #endregion

                    #region hobby a
                    // group A
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[1][9].Team,
                            divisionRanksFirstToFifth[2][6].Team,
                            divisionRanksFirstToFifth[2][7].Team,
                            divisionRanksFirstToFifth[2][8].Team,
                            divisionRanksFirstToFifth[3][6].Team
                        });

                    // group B
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[1][10].Team,
                            divisionRanksFirstToFifth[2][9].Team,
                            divisionRanksFirstToFifth[2][10].Team,
                            divisionRanksFirstToFifth[3][0].Team,
                            divisionRanksFirstToFifth[3][5].Team
                        });

                    // group C
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[2][0].Team,
                            divisionRanksFirstToFifth[2][1].Team,
                            divisionRanksFirstToFifth[2][2].Team,
                            divisionRanksFirstToFifth[3][1].Team,
                            divisionRanksFirstToFifth[3][4].Team
                        });

                    // group D
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[2][3].Team,
                            divisionRanksFirstToFifth[2][4].Team,
                            divisionRanksFirstToFifth[2][5].Team,
                            divisionRanksFirstToFifth[3][2].Team,
                            divisionRanksFirstToFifth[3][3].Team
                        });
                    #endregion

                    #region hobby b
                    // group A
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[3][7].Team,
                            divisionRanksFirstToFifth[3][10].Team,
                            divisionRanksFirstToFifth[4][0].Team,
                            divisionRanksFirstToFifth[4][3].Team,
                            divisionRanksFirstToFifth[4][4].Team
                        });

                    // group B
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[3][8].Team,
                            divisionRanksFirstToFifth[3][9].Team,
                            divisionRanksFirstToFifth[4][1].Team,
                            divisionRanksFirstToFifth[4][2].Team,
                            divisionRanksFirstToFifth[4][5].Team
                        });

                    // group C
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[4][6].Team,
                            divisionRanksFirstToFifth[4][7].Team,
                            divisionRanksFirstToFifth[4][8].Team,
                            divisionRanksFirstToFifth[4][9].Team,
                            divisionRanksFirstToFifth[4][10].Team
                        });
                    #endregion
                }
                else if (teamsCount == 60)
                {
                    // make ranking of all divisions second teams
                    divisionRanksFirstToFifth[1] = giveMeSort(divisionRanksFirstToFifth[1]);

                    // make ranking of all divisions fourth teams
                    divisionRanksFirstToFifth[3] = giveMeSort(divisionRanksFirstToFifth[3]);

                    # region profi
                    // group A
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][0].Team,
                            divisionRanksFirstToFifth[0][1].Team,
                            divisionRanksFirstToFifth[0][2].Team,
                            divisionRanksFirstToFifth[1][0].Team,
                            divisionRanksFirstToFifth[1][7].Team
                        });

                    // group B
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][3].Team,
                            divisionRanksFirstToFifth[0][4].Team,
                            divisionRanksFirstToFifth[0][5].Team,
                            divisionRanksFirstToFifth[1][1].Team,
                            divisionRanksFirstToFifth[1][6].Team
                        });

                    // group C
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][6].Team,
                            divisionRanksFirstToFifth[0][7].Team,
                            divisionRanksFirstToFifth[0][8].Team,
                            divisionRanksFirstToFifth[1][2].Team,
                            divisionRanksFirstToFifth[1][5].Team
                        });

                    // group D
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[0][9].Team,
                            divisionRanksFirstToFifth[0][10].Team,
                            divisionRanksFirstToFifth[0][11].Team,
                            divisionRanksFirstToFifth[1][3].Team,
                            divisionRanksFirstToFifth[1][4].Team
                        });
                    #endregion

                    # region hobby a
                    // group A
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[1][8].Team,
                            divisionRanksFirstToFifth[2][0].Team,
                            divisionRanksFirstToFifth[2][1].Team,
                            divisionRanksFirstToFifth[2][2].Team,
                            divisionRanksFirstToFifth[3][3].Team
                        });

                    // group B
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[1][9].Team,
                            divisionRanksFirstToFifth[2][3].Team,
                            divisionRanksFirstToFifth[2][4].Team,
                            divisionRanksFirstToFifth[2][5].Team,
                            divisionRanksFirstToFifth[3][2].Team
                        });

                    // group C
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[1][10].Team,
                            divisionRanksFirstToFifth[2][6].Team,
                            divisionRanksFirstToFifth[2][7].Team,
                            divisionRanksFirstToFifth[2][8].Team,
                            divisionRanksFirstToFifth[3][1].Team
                        });

                    // group D
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[1][11].Team,
                            divisionRanksFirstToFifth[2][9].Team,
                            divisionRanksFirstToFifth[2][10].Team,
                            divisionRanksFirstToFifth[2][11].Team,
                            divisionRanksFirstToFifth[3][0].Team
                        });
                    #endregion

                    #region hobby b
                    // group A
                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[3][4].Team,
                            divisionRanksFirstToFifth[3][11].Team,
                            divisionRanksFirstToFifth[4][0].Team,
                            divisionRanksFirstToFifth[4][1].Team,
                            divisionRanksFirstToFifth[4][2].Team
                        });

                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[3][5].Team,
                            divisionRanksFirstToFifth[3][10].Team,
                            divisionRanksFirstToFifth[4][3].Team,
                            divisionRanksFirstToFifth[4][4].Team,
                            divisionRanksFirstToFifth[4][5].Team
                        });

                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[3][6].Team,
                            divisionRanksFirstToFifth[3][9].Team,
                            divisionRanksFirstToFifth[4][6].Team,
                            divisionRanksFirstToFifth[4][7].Team,
                            divisionRanksFirstToFifth[4][8].Team
                        });

                    newDivisionList.Add(new List<string>() {
                            divisionRanksFirstToFifth[3][7].Team,
                            divisionRanksFirstToFifth[3][8].Team,
                            divisionRanksFirstToFifth[4][9].Team,
                            divisionRanksFirstToFifth[4][10].Team,
                            divisionRanksFirstToFifth[4][11].Team
                        });
                    #endregion
                }
            }

            return newDivisionList;
        }
    }
}
