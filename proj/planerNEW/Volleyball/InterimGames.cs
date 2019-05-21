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
        List<List<string>> divisionsList;
        List<int[]> gamePlan;
        #endregion

        public InterimGames(Logging log) : base(log)
        {
            this.log = log;
        }

        public void setParameters(List<List<ResultData>> divisionsQualifyingList, List< int[] > gamePlan, DateTime startRound, 
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
            this.useSecondGamePlaning = useSecondGamePlaning;

            setTimeParameters(setCounter, minutesSet, minutesPause);

            startRound = startRound.AddSeconds(pauseBetweenQualifyingInterim * 60);
        }

        public void generateGames()
        {
            // generate game plan over all divisonal games
            if (generateGamePlan())
            {
                insertGameNumber();

                insertRoundNumber(teamsCount, fieldCount);

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
            for(int i = 0; i < divisionTeams.Count; i++)
            {
                if(divisionTeams[i].PointsSets < divisionTeams[i + 1].PointsSets)
                {
                    ResultData team = divisionTeams[i];

                    divisionTeams[i] = divisionTeams[i + 1];
                    divisionTeams[i + 1] = team;
                }
                else if(divisionTeams[i].PointsSets == divisionTeams[i + 1].PointsSets
                    && divisionTeams[i].PointsMatches < divisionTeams[i + 1].PointsMatches)
                {
                    ResultData team = divisionTeams[i];

                    divisionTeams[i] = divisionTeams[i + 1];
                    divisionTeams[i + 1] = team;
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

            if (useSecondGamePlaning)
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
                    List<String> newTeamList = new List<String>();

                    for (int i = 0; i < divisionRanksFirstToFifth.Count; i++)
                    {
                        for (int ii = 0; ii < divisionRanksFirstToFifth[i].Count; i++)
                        {
                            if (newTeamList.Count % 5 == 0)
                            {
                                newDivisionList.Add(newTeamList);

                                newTeamList.Clear();
                            }

                            newTeamList.Add(divisionRanksFirstToFifth[i][ii].Team);
                        }

                        newDivisionList.Add(newTeamList);
                    }
                }
                else if (teamsCount == 55)
                {
                    // make ranking of all divisions second teams
                    sortList(&divisionsFirst);

                    if (checkListDoubleResults(&divisionsFirst))
                        return QList<QStringList>();

                    // make ranking of all divisions second teams
                    sortList(&divisionsSecond);

                    if (checkListDoubleResults(&divisionsSecond))
                        return QList<QStringList>();

                    // make ranking of all divisions third teams
                    sortList(&divisionsThird);

                    if (checkListDoubleResults(&divisionsThird))
                        return QList<QStringList>();

                    // make ranking of all divisions fourth teams
                    sortList(&divisionsFourth);

                    if (checkListDoubleResults(&divisionsFourth))
                        return QList<QStringList>();

                    // make ranking of all divisions fifth teams
                    sortList(&divisionsFifth);

                    if (checkListDoubleResults(&divisionsFifth))
                        return QList<QStringList>();

                    // get team names from divisions
                    divisionsFirstNames = getTeamList(&divisionsFirst);
                    divisionsSecondNames = getTeamList(&divisionsSecond);
                    divisionsThirdNames = getTeamList(&divisionsThird);
                    divisionsFourthNames = getTeamList(&divisionsFourth);
                    divisionsFifthNames = getTeamList(&divisionsFifth);

                    // profi
                    newDivisionsZw.append(QStringList()
                                            << divisionsFirstNames.at(0)
                                            << divisionsFirstNames.at(2)
                                            << divisionsFirstNames.at(4)
                                            << divisionsFirstNames.at(6)
                                            << divisionsFirstNames.at(8));

                    newDivisionsZw.append(QStringList()
                                            << divisionsFirstNames.at(1)
                                            << divisionsFirstNames.at(3)
                                            << divisionsFirstNames.at(5)
                                            << divisionsFirstNames.at(7)
                                            << divisionsFirstNames.at(9));

                    // hobby a
                    newDivisionsZw.append(QStringList()
                                            << divisionsFirstNames.at(10)
                                            << divisionsSecondNames.at(0)
                                            << divisionsSecondNames.at(2)
                                            << divisionsSecondNames.at(4)
                                            << divisionsSecondNames.at(6));

                    newDivisionsZw.append(QStringList()
                                            << divisionsSecondNames.at(1)
                                            << divisionsSecondNames.at(3)
                                            << divisionsSecondNames.at(5)
                                            << divisionsSecondNames.at(7)
                                            << divisionsSecondNames.at(8));

                    // hobby b
                    newDivisionsZw.append(QStringList()
                                            << divisionsSecondNames.at(9)
                                            << divisionsThirdNames.at(0)
                                            << divisionsThirdNames.at(2)
                                            << divisionsThirdNames.at(4)
                                            << divisionsThirdNames.at(6));

                    newDivisionsZw.append(QStringList()
                                            << divisionsSecondNames.at(10)
                                            << divisionsThirdNames.at(1)
                                            << divisionsThirdNames.at(3)
                                            << divisionsThirdNames.at(5)
                                            << divisionsThirdNames.at(7));

                    // hobby c
                    newDivisionsZw.append(QStringList()
                                            << divisionsThirdNames.at(8)
                                            << divisionsThirdNames.at(10)
                                            << divisionsFourthNames.at(0)
                                            << divisionsFourthNames.at(2)
                                            << divisionsFourthNames.at(4));

                    newDivisionsZw.append(QStringList()
                                            << divisionsThirdNames.at(9)
                                            << divisionsFourthNames.at(1)
                                            << divisionsFourthNames.at(3)
                                            << divisionsFourthNames.at(5)
                                            << divisionsFourthNames.at(6));

                    // hobby d
                    newDivisionsZw.append(QStringList()
                                            << divisionsFourthNames.at(8)
                                            << divisionsFourthNames.at(10)
                                            << divisionsFifthNames.at(0)
                                            << divisionsFifthNames.at(2)
                                            << divisionsFifthNames.at(4));

                    newDivisionsZw.append(QStringList()
                                            << divisionsFourthNames.at(7)
                                            << divisionsFourthNames.at(9)
                                            << divisionsFifthNames.at(1)
                                            << divisionsFifthNames.at(3)
                                            << divisionsFifthNames.at(5));

                    newDivisionsZw.append(QStringList()
                                            << divisionsFifthNames.at(6)
                                            << divisionsFifthNames.at(7)
                                            << divisionsFifthNames.at(8)
                                            << divisionsFifthNames.at(9)
                                            << divisionsFifthNames.at(10));
                }

                    case 60:
                        // make ranking of all divisions second teams
                        sortList(&divisionsSecond);

                        if (checkListDoubleResults(&divisionsSecond))
                            return QList<QStringList>();

                        // make ranking of all divisions third teams
                        sortList(&divisionsThird);

                        if (checkListDoubleResults(&divisionsThird))
                            return QList<QStringList>();

                        // make ranking of all divisions fourth teams
                        sortList(&divisionsFourth);

                        if (checkListDoubleResults(&divisionsFourth))
                            return QList<QStringList>();

                        // make ranking of all divisions fifth teams
                        sortList(&divisionsFifth);

                        if (checkListDoubleResults(&divisionsFifth))
                            return QList<QStringList>();

                        // get team names from divisions
                        divisionsFirstNames = getTeamList(&divisionsFirst);
                        divisionsSecondNames = getTeamList(&divisionsSecond);
                        divisionsThirdNames = getTeamList(&divisionsThird);
                        divisionsFourthNames = getTeamList(&divisionsFourth);
                        divisionsFifthNames = getTeamList(&divisionsFifth);

                        // profi
                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(0)
                                                << divisionsFirstNames.at(1)
                                                << divisionsFirstNames.at(2)
                                                << divisionsFirstNames.at(3)
                                                << divisionsFirstNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(5)
                                                << divisionsFirstNames.at(6)
                                                << divisionsFirstNames.at(7)
                                                << divisionsFirstNames.at(8)
                                                << divisionsFirstNames.at(9));

                        // hobby a
                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(10)
                                                << divisionsSecondNames.at(0)
                                                << divisionsSecondNames.at(1)
                                                << divisionsSecondNames.at(2)
                                                << divisionsSecondNames.at(3));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(11)
                                                << divisionsSecondNames.at(4)
                                                << divisionsSecondNames.at(5)
                                                << divisionsSecondNames.at(6)
                                                << divisionsSecondNames.at(7));

                        // hobby b
                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(8)
                                                << divisionsSecondNames.at(9)
                                                << divisionsThirdNames.at(0)
                                                << divisionsThirdNames.at(2)
                                                << divisionsThirdNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(10)
                                                << divisionsSecondNames.at(11)
                                                << divisionsThirdNames.at(1)
                                                << divisionsThirdNames.at(3)
                                                << divisionsThirdNames.at(5));

                        // hobby c
                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(6)
                                                << divisionsThirdNames.at(8)
                                                << divisionsThirdNames.at(10)
                                                << divisionsFourthNames.at(0)
                                                << divisionsFourthNames.at(1));

                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(7)
                                                << divisionsThirdNames.at(9)
                                                << divisionsThirdNames.at(11)
                                                << divisionsFourthNames.at(2)
                                                << divisionsFourthNames.at(3));

                        // hobby d
                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(4)
                                                << divisionsFourthNames.at(6)
                                                << divisionsFourthNames.at(8)
                                                << divisionsFourthNames.at(10)
                                                << divisionsFifthNames.at(0));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(5)
                                                << divisionsFourthNames.at(7)
                                                << divisionsFourthNames.at(9)
                                                << divisionsFourthNames.at(11)
                                                << divisionsFifthNames.at(1));

                        // hobby e
                        newDivisionsZw.append(QStringList()
                                                << divisionsFifthNames.at(2)
                                                << divisionsFifthNames.at(4)
                                                << divisionsFifthNames.at(6)
                                                << divisionsFifthNames.at(8)
                                                << divisionsFifthNames.at(10));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFifthNames.at(3)
                                                << divisionsFifthNames.at(5)
                                                << divisionsFifthNames.at(7)
                                                << divisionsFifthNames.at(9)
                                                << divisionsFifthNames.at(11));

                        break;

                    default:
                        log.write("interim team count not correct");
                        break;
                }
            }
            else
            {
                switch (teamsCount)
                {
                    case 50:
                        // get team names from divisions
                        divisionsFirstNames = getTeamList(&divisionsFirst);
                        divisionsSecondNames = getTeamList(&divisionsSecond);
                        divisionsThirdNames = getTeamList(&divisionsThird);
                        divisionsFourthNames = getTeamList(&divisionsFourth);
                        divisionsFifthNames = getTeamList(&divisionsFifth);

                        // profi
                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(0)
                                                << divisionsFirstNames.at(1)
                                                << divisionsSecondNames.at(2)
                                                << divisionsSecondNames.at(3)
                                                << divisionsSecondNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(2)
                                                << divisionsFirstNames.at(3)
                                                << divisionsSecondNames.at(5)
                                                << divisionsSecondNames.at(6)
                                                << divisionsSecondNames.at(7));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(4)
                                                << divisionsFirstNames.at(5)
                                                << divisionsFirstNames.at(6)
                                                << divisionsSecondNames.at(8)
                                                << divisionsSecondNames.at(9));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(7)
                                                << divisionsFirstNames.at(8)
                                                << divisionsFirstNames.at(9)
                                                << divisionsSecondNames.at(0)
                                                << divisionsSecondNames.at(1));

                        // hobby a
                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(0)
                                                << divisionsThirdNames.at(1)
                                                << divisionsFourthNames.at(2)
                                                << divisionsFourthNames.at(3)
                                                << divisionsFourthNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(2)
                                                << divisionsThirdNames.at(3)
                                                << divisionsFourthNames.at(5)
                                                << divisionsFourthNames.at(6)
                                                << divisionsFourthNames.at(7));

                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(4)
                                                << divisionsThirdNames.at(5)
                                                << divisionsThirdNames.at(6)
                                                << divisionsFourthNames.at(8)
                                                << divisionsFourthNames.at(9));

                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(7)
                                                << divisionsThirdNames.at(8)
                                                << divisionsThirdNames.at(9)
                                                << divisionsFourthNames.at(0)
                                                << divisionsFourthNames.at(1));

                        // hobby b
                        newDivisionsZw.append(QStringList()
                                                << divisionsFifthNames.at(0)
                                                << divisionsFifthNames.at(1)
                                                << divisionsFifthNames.at(2)
                                                << divisionsFifthNames.at(3)
                                                << divisionsFifthNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFifthNames.at(5)
                                                << divisionsFifthNames.at(6)
                                                << divisionsFifthNames.at(7)
                                                << divisionsFifthNames.at(8)
                                                << divisionsFifthNames.at(9));
                        break;

                    case 55:
                        // make ranking of all divisions second teams
                        sortList(&divisionsSecond);

                        if (checkListDoubleResults(&divisionsSecond))
                            return QList<QStringList>();

                        // make ranking of all divisions second teams
                        sortList(&divisionsFourth);

                        if (checkListDoubleResults(&divisionsFourth))
                            return QList<QStringList>();

                        // make ranking of all divisions second teams
                        sortList(&divisionsFifth);

                        if (checkListDoubleResults(&divisionsFifth))
                            return QList<QStringList>();

                        // get team names from divisions
                        divisionsFirstNames = getTeamList(&divisionsFirst);
                        divisionsSecondNames = getTeamList(&divisionsSecond);
                        divisionsThirdNames = getTeamList(&divisionsThird);
                        divisionsFourthNames = getTeamList(&divisionsFourth);
                        divisionsFifthNames = getTeamList(&divisionsFifth);

                        // profi
                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(0)
                                                << divisionsFirstNames.at(1)
                                                << divisionsFirstNames.at(2)
                                                << divisionsSecondNames.at(3)
                                                << divisionsSecondNames.at(7));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(3)
                                                << divisionsFirstNames.at(4)
                                                << divisionsFirstNames.at(5)
                                                << divisionsSecondNames.at(2)
                                                << divisionsSecondNames.at(6));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(6)
                                                << divisionsFirstNames.at(7)
                                                << divisionsFirstNames.at(8)
                                                << divisionsSecondNames.at(1)
                                                << divisionsSecondNames.at(5));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(9)
                                                << divisionsFirstNames.at(10)
                                                << divisionsSecondNames.at(0)
                                                << divisionsSecondNames.at(4)
                                                << divisionsSecondNames.at(8));

                        // hobby a
                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(9)
                                                << divisionsThirdNames.at(6)
                                                << divisionsThirdNames.at(7)
                                                << divisionsThirdNames.at(8)
                                                << divisionsFourthNames.at(6));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(10)
                                                << divisionsThirdNames.at(9)
                                                << divisionsThirdNames.at(10)
                                                << divisionsFourthNames.at(0)
                                                << divisionsFourthNames.at(5));

                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(0)
                                                << divisionsThirdNames.at(1)
                                                << divisionsThirdNames.at(2)
                                                << divisionsFourthNames.at(1)
                                                << divisionsFourthNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsThirdNames.at(3)
                                                << divisionsThirdNames.at(4)
                                                << divisionsThirdNames.at(5)
                                                << divisionsFourthNames.at(2)
                                                << divisionsFourthNames.at(3));

                        // hobby b
                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(7)
                                                << divisionsFourthNames.at(10)
                                                << divisionsFifthNames.at(0)
                                                << divisionsFifthNames.at(3)
                                                << divisionsFifthNames.at(4));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(8)
                                                << divisionsFourthNames.at(9)
                                                << divisionsFifthNames.at(1)
                                                << divisionsFifthNames.at(2)
                                                << divisionsFifthNames.at(5));

                        // hobby c
                        newDivisionsZw.append(QStringList()
                                                << divisionsFifthNames.at(6)
                                                << divisionsFifthNames.at(7)
                                                << divisionsFifthNames.at(8)
                                                << divisionsFifthNames.at(9)
                                                << divisionsFifthNames.at(10));

                        break;

                    case 60:
                        // make ranking of all divisions second teams
                        sortList(&divisionsSecond);

                        if (checkListDoubleResults(&divisionsSecond))
                            return QList<QStringList>();

                        // make ranking of all divisions second teams
                        sortList(&divisionsFourth);

                        if (checkListDoubleResults(&divisionsFourth))
                            return QList<QStringList>();

                        // get team names from divisions
                        divisionsFirstNames = getTeamList(&divisionsFirst);
                        divisionsSecondNames = getTeamList(&divisionsSecond);
                        divisionsThirdNames = getTeamList(&divisionsThird);
                        divisionsFourthNames = getTeamList(&divisionsFourth);
                        divisionsFifthNames = getTeamList(&divisionsFifth);

                        // profi
                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(0)
                                                << divisionsFirstNames.at(1)
                                                << divisionsFirstNames.at(2)
                                                << divisionsSecondNames.at(0)
                                                << divisionsSecondNames.at(7));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(3)
                                                << divisionsFirstNames.at(4)
                                                << divisionsFirstNames.at(5)
                                                << divisionsSecondNames.at(1)
                                                << divisionsSecondNames.at(6));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(6)
                                                << divisionsFirstNames.at(7)
                                                << divisionsFirstNames.at(8)
                                                << divisionsSecondNames.at(2)
                                                << divisionsSecondNames.at(5));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFirstNames.at(9)
                                                << divisionsFirstNames.at(10)
                                                << divisionsFirstNames.at(11)
                                                << divisionsSecondNames.at(3)
                                                << divisionsSecondNames.at(4));

                        // hobby a
                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(8)
                                                << divisionsThirdNames.at(0)
                                                << divisionsThirdNames.at(1)
                                                << divisionsThirdNames.at(2)
                                                << divisionsFourthNames.at(3));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(9)
                                                << divisionsThirdNames.at(3)
                                                << divisionsThirdNames.at(4)
                                                << divisionsThirdNames.at(5)
                                                << divisionsFourthNames.at(2));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(10)
                                                << divisionsThirdNames.at(6)
                                                << divisionsThirdNames.at(7)
                                                << divisionsThirdNames.at(8)
                                                << divisionsFourthNames.at(1));

                        newDivisionsZw.append(QStringList()
                                                << divisionsSecondNames.at(11)
                                                << divisionsThirdNames.at(9)
                                                << divisionsThirdNames.at(10)
                                                << divisionsThirdNames.at(11)
                                                << divisionsFourthNames.at(0));

                        // hobby b
                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(4)
                                                << divisionsFourthNames.at(11)
                                                << divisionsFifthNames.at(0)
                                                << divisionsFifthNames.at(1)
                                                << divisionsFifthNames.at(2));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(5)
                                                << divisionsFourthNames.at(10)
                                                << divisionsFifthNames.at(3)
                                                << divisionsFifthNames.at(4)
                                                << divisionsFifthNames.at(5));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(6)
                                                << divisionsFourthNames.at(9)
                                                << divisionsFifthNames.at(6)
                                                << divisionsFifthNames.at(7)
                                                << divisionsFifthNames.at(8));

                        newDivisionsZw.append(QStringList()
                                                << divisionsFourthNames.at(7)
                                                << divisionsFourthNames.at(8)
                                                << divisionsFifthNames.at(9)
                                                << divisionsFifthNames.at(10)
                                                << divisionsFifthNames.at(11));
                        break;

                    default: logMessages("ZWISCHENRUNDE_ERROR:: team count not correct");
                }
            }

            return newDivisionList;
        }
    }
}
