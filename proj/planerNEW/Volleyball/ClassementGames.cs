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
        public List<ClassementData> finalClassement;
        List<int> classements;
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

            if(teamsCount == 30 || teamsCount == 35)
            {
                classements = new List<int>() { 9, 10, 19, 20, 29, 30,
                                            7, 8, 17, 18, 27, 28,
                                            5, 6, 15, 16, 25, 26,
                                            3, 4, 13, 14, 23, 24,
                                            11, 12, 21, 22, 1, 2 };
            }
            else if(teamsCount == 40 || teamsCount == 45)
            {
                classements = new List<int>() { 9, 10, 19, 20, 29, 30, 39, 40,
                                                7, 8, 17, 18, 27, 28, 37, 38,
                                                5, 6, 15, 16, 25, 26, 35, 36,
                                                3, 4, 13, 14, 23, 24, 33, 34,
                                                11, 12, 21, 22, 31, 32, 1, 2 };
            }
            else if (teamsCount == 50 || teamsCount == 55)
            {
                classements = new List<int>() { 9, 10, 19, 20, 29, 30, 39, 40, 49, 50,
                                                7, 8, 17, 18, 27, 28, 37, 38, 47, 48,
                                                5, 6, 15, 16, 25, 26, 35, 36, 45, 46,
                                                3, 4, 13, 14, 23, 24, 33, 34, 33, 34,
                                                11, 12, 21, 22, 31, 32, 31, 32, 1, 2 };
            }
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

                insertRoundNumber(lastRoundNr, fieldCount);

                insertGameTime(startRound);

                insertFieldnumbersAndFieldnames(fieldCount, fieldNames);
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
                if (teamsCount == 20 || teamsCount == 25)
                {
                    // spiel um platz 9
                    matchData.Add(new MatchData() {
                        TeamA = divisionA[4].Team,
                        TeamB = divisionB[4].Team,
                        Referee = divisionA[1].Team
                    });

                    // spiel um platz 7
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[1])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[5])[2],
                        Referee = divisionB[1].Team
                    });

                    // spiel um platz 19
                    matchData.Add(new MatchData() {
                        TeamA = divisionC[4].Team,
                        TeamB = divisionD[4].Team,
                        Referee = divisionC[1].Team
                    });

                    // spiel um platz 17
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[3])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[7])[2],
                        Referee = divisionD[1].Team
                    });

                    // spiel um platz 5
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[1])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[5])[1],
                        Referee = divisionA[4].Team
                    });

                    // spiel um platz 3
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[0])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[4])[2],
                        Referee = divisionB[4].Team
                    });

                    // spiel um platz 15
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[3])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[7])[1],
                        Referee = divisionC[4].Team
                    });

                    // spiel um platz 13
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[2])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[6])[2],
                        Referee = divisionD[4].Team
                    });

                    // spiel um platz 11
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[2])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[6])[1],
                        Referee = divisionC[3].Team
                    });

                    // spiel um platz 1
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[0])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[4])[1],
                        Referee = divisionA[3].Team
                    });
                }
                else if (teamsCount == 28)
                {
                    // spiel um platz 7
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[1])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[7])[2],
                        Referee = divisionB[1].Team
                    });

                    // spiel um platz 19
                    matchData.Add(new MatchData() {
                        TeamA = divisionC[4].Team,
                        TeamB = divisionD[4].Team,
                        Referee = divisionC[1].Team
                    });

                    // spiel um platz 17
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[3])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[9])[2],
                        Referee = divisionD[1].Team
                    });

                    // spiel um platz 27
                    matchData.Add(new MatchData() {
                        TeamA = divisionE[4].Team,
                        TeamB = divisionF[4].Team,
                        Referee = divisionE[1].Team
                    });

                    // spiel um platz 25
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[5])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[11])[2],
                        Referee = divisionF[1].Team
                    });

                    // spiel um platz 5
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[1])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[7])[2],
                        Referee = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[1])[2]
                    });

                    // spiel um platz 3
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[0])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[6])[2],
                        Referee = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[7])[2]
                    });

                    // spiel um platz 15
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[3])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[9])[1],
                        Referee = divisionC[4].Team
                    });

                    // spiel um platz 13
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[2])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[8])[2],
                        Referee = divisionD[4].Team
                    });

                    // spiel um platz 23
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[5])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[11])[1],
                        Referee = divisionE[4].Team
                    });

                    // spiel um platz 9
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[4])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[10])[2],
                        Referee = divisionF[4].Team
                    });

                    // spiel um platz 21
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[4])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[10])[1],
                        Referee = divisionE[4].Team
                    });

                    // spiel um platz 11
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[2])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[8])[1],
                        Referee = divisionC[4].Team
                    });

                    // spiel um platz 1
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[0])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[6])[1],
                        Referee = divisionA[4].Team
                    });
                }
                else if (teamsCount == 20 || teamsCount == 25)
                {
                    // spiel um platz 9
                    matchData.Add(new MatchData() {
                        TeamA = divisionA[4].Team,
                        TeamB = divisionB[4].Team,
                        Referee = divisionA[1].Team
                    });

                    // spiel um platz 19
                    matchData.Add(new MatchData() {
                        TeamA = divisionC[4].Team,
                        TeamB = divisionD[4].Team,
                        Referee = divisionC[1].Team
                    });

                    // spiel um platz 29
                    matchData.Add(new MatchData() {
                        TeamA = divisionE[4].Team,
                        TeamB = divisionF[4].Team,
                        Referee = divisionE[1].Team
                    });

                    // spiel um platz 7
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[1])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[7])[2],
                        Referee = divisionB[1].Team
                    });

                    // spiel um platz 17
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[3])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[9])[2],
                        Referee = divisionD[1].Team
                    });

                    // spiel um platz 27
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[5])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[11])[2],
                        Referee = divisionF[1].Team
                    });

                    // spiel um platz 5
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[1])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[7])[1],
                        Referee = divisionA[4].Team
                    });

                    // spiel um platz 15
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[3])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[9])[1],
                        Referee = divisionC[4].Team
                    });

                    // spiel um platz 25
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[5])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[11])[1],
                        Referee = divisionE[4].Team
                    });

                    // spiel um platz 3
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[0])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[6])[2],
                        Referee = divisionB[4].Team
                    });

                    // spiel um platz 13
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[2])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[8])[2],
                        Referee = divisionD[4].Team
                    });

                    // spiel um platz 23
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[4])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[10])[2],
                        Referee = divisionF[4].Team
                    });

                    // spiel um platz 21
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[2])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[8])[1],
                        Referee = divisionA[3].Team
                    });

                    // spiel um platz 11
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[4])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[10])[1],
                        Referee = divisionB[3].Team
                    });

                    // spiel um platz 1
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[0])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[6])[1],
                        Referee = divisionA[3].Team
                    });
                }
                else if (teamsCount == 40 || teamsCount == 45)
                {
                    // spiel um platz 9
                    matchData.Add(new MatchData() {
                        TeamA = divisionA[4].Team,
                        TeamB = divisionB[4].Team,
                        Referee = divisionA[1].Team
                    });

                    // spiel um platz 19
                    matchData.Add(new MatchData() {
                        TeamA = divisionC[4].Team,
                        TeamB = divisionD[4].Team,
                        Referee = divisionC[1].Team
                    });

                    // spiel um platz 29
                    matchData.Add(new MatchData() {
                        TeamA = divisionE[4].Team,
                        TeamB = divisionF[4].Team,
                        Referee = divisionE[1].Team
                    });

                    // spiel um platz 39
                    matchData.Add(new MatchData() {
                        TeamA = divisionG[4].Team,
                        TeamB = divisionH[4].Team,
                        Referee = divisionG[1].Team
                    });

                    // spiel um platz 7
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[1])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[9])[2],
                        Referee = divisionB[1].Team
                    });

                    // spiel um platz 17
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[3])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[11])[2],
                        Referee = divisionD[1].Team
                    });

                    // spiel um platz 27
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[5])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[13])[2],
                        Referee = divisionF[1].Team
                    });

                    // spiel um platz 37
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[7])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[15])[2],
                        Referee = divisionH[1].Team
                    });

                    // spiel um platz 5
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[1])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[9])[1],
                        Referee = divisionA[4].Team
                    });

                    // spiel um platz 15
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[3])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[11])[1],
                        Referee = divisionC[4].Team
                    });

                    // spiel um platz 25
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[5])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[13])[1],
                        Referee = divisionE[4].Team
                    });

                    // spiel um platz 35
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[7])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[15])[1],
                        Referee = divisionG[4].Team
                    });

                    // spiel um platz 3
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[0])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[8])[2],
                        Referee = divisionB[4].Team
                    });

                    // spiel um platz 13
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[2])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[10])[2],
                        Referee = divisionD[4].Team
                    });

                    // spiel um platz 23
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[4])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[12])[2],
                        Referee = divisionF[4].Team
                    });

                    // spiel um platz 33
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[6])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[14])[2],
                        Referee = divisionH[4].Team
                    });

                    // spiel um platz 11
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[2])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[10])[1],
                        Referee = divisionA[3].Team
                    });

                    // spiel um platz 21
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[4])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[12])[1],
                        Referee = divisionB[3].Team
                    });

                    // spiel um platz 31
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[6])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[14])[1],
                        Referee = divisionC[3].Team
                    });

                    // spiel um platz 1
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[0])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[8])[1]
                    });
                }
                else if (teamsCount == 30 || teamsCount == 35)
                {
                    // spiel um platz 9
                    matchData.Add(new MatchData() {
                        TeamA = divisionA[4].Team,
                        TeamB = divisionB[4].Team,
                        Referee = divisionA[1].Team
                    });

                    // spiel um platz 19
                    matchData.Add(new MatchData() {
                        TeamA = divisionC[4].Team,
                        TeamB = divisionD[4].Team,
                        Referee = divisionC[1].Team
                    });

                    // spiel um platz 29
                    matchData.Add(new MatchData() {
                        TeamA = divisionE[4].Team,
                        TeamB = divisionF[4].Team,
                        Referee = divisionE[1].Team
                    });

                    // spiel um platz 7
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[1])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[7])[2],
                        Referee = divisionB[1].Team
                    });

                    // spiel um platz 17
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[3])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[9])[2],
                        Referee = divisionD[1].Team
                    });

                    // spiel um platz 27
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[5])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[11])[2],
                        Referee = divisionF[1].Team
                    });

                    // spiel um platz 5
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[1])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[7])[1],
                        Referee = divisionA[4].Team
                    });

                    // spiel um platz 15
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[3])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[9])[1],
                        Referee = divisionC[4].Team
                    });

                    // spiel um platz 25
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[5])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[11])[1],
                        Referee = divisionE[4].Team
                    });

                    // spiel um platz 3
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[0])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[6])[2],
                        Referee = divisionB[4].Team
                    });

                    // spiel um platz 13
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[2])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[8])[2],
                        Referee = divisionD[4].Team
                    });

                    // spiel um platz 23
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[4])[2],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[10])[2],
                        Referee = divisionF[4].Team
                    });

                    // spiel um platz 21
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[2])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[8])[1],
                        Referee = divisionA[3].Team
                    });

                    // spiel um platz 11
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[4])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[10])[1],
                        Referee = divisionB[3].Team
                    });

                    // spiel um platz 1
                    matchData.Add(new MatchData() {
                        TeamA = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[0])[1],
                        TeamB = CalculateResults.getResultsForCrossgamesAndClassementgames(resultCrossgamesList[6])[1],
                        Referee = divisionA[3].Team
                    });
                }
                else if (teamsCount == 50)
                {
                }
                else if (teamsCount == 55)
                {
                }
            }
            else
            {
                List<String> refereeList = new List<String>();
                List<MatchData> copyCrossgamesList = resultCrossgamesList;
                int resultInterimListCount = resultInterimList.Count();
                List<String> winAndlooser;
                Console.WriteLine("Before");

                // if 55 teams, remove the first 5 kr game results, because this teams do not play any classement games
                
                if (teamsCount == 35 || teamsCount == 45 || teamsCount == 55)
                {
                    for (int i = 0; i < 5; i++)
                        resultCrossgamesList.RemoveAt(0);

                    resultInterimListCount--;
                }
                

                Console.WriteLine("After");
                Console.WriteLine(copyCrossgamesList);

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



                if(teamsCount == 45)
                {
                    matchData.Clear();
                    for (int i = 0, x = resultInterimListCount - 1, y = ((resultInterimList[x].Count() + resultInterimList[x - 1].Count()) / 2) - 1,
                    startingReferee = 0, fCount = 1; (i) < 5; startingReferee++)
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
                        matchData.Add(new MatchData()
                        {
                            Round = lastRoundNr,
                            FieldNumber = fCount,
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
                        matchData.Add(new MatchData()
                        {
                            Round = lastRoundNr,
                            FieldNumber = fCount,
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
                            //i = i + (toAdd / 2);
                            i++;
                        }
                    }
                    for (int i = 0, x = resultInterimListCount - 1, y = ((resultInterimList[x].Count() + resultInterimList[x - 1].Count()) / 2) - 1,
                    startingReferee = 0, fCount = 1; (i) < 5; startingReferee++)
                    {
                        //############################################################################################################

                        String referee1 = "", referee2 = "";

                        // get the referee for the looser game
                        if (startingReferee < fieldCount)
                        {
                            referee1 = "";
                            startingReferee++;
                        }

                        // check if there is a next referee for the winner game
                        if (startingReferee < fieldCount)
                            referee2 = "";

                        // get winner and looser for the next related games
                        winAndlooser = CalculateResults.getResultsForCrossgamesAndClassementgames(copyCrossgamesList[10+i]);
                        String winner1 = winAndlooser[1];
                        String looser1 = winAndlooser[2];

                        winAndlooser = CalculateResults.getResultsForCrossgamesAndClassementgames(copyCrossgamesList[10+i + 5]);
                        String winner2 = winAndlooser[1];
                        String looser2 = winAndlooser[2];

                        // create looser match
                        matchData.Add(new MatchData()
                        {
                            Round = lastRoundNr,
                            FieldNumber = fCount,
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
                        matchData.Add(new MatchData()
                        {
                            Round = lastRoundNr,
                            FieldNumber = fCount,
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
                            //i = i + (toAdd / 2);
                            i++;
                        }
                    }
                }
                
                if (teamsCount == 55)
                {
                    matchData.Clear();
                    for (int i = 0, x = resultInterimListCount - 1, y = ((resultInterimList[x].Count() + resultInterimList[x - 1].Count()) / 2) - 1,
                    startingReferee = 0, fCount = 1; (i) < 5; startingReferee++)
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
                        matchData.Add(new MatchData()
                        {
                            Round = lastRoundNr,
                            FieldNumber = fCount,
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
                        matchData.Add(new MatchData()
                        {
                            Round = lastRoundNr,
                            FieldNumber = fCount,
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
                            //i = i + (toAdd / 2);
                            i++;
                        }
                    }
                    for (int i = 0, x = resultInterimListCount - 1, y = ((resultInterimList[x].Count() + resultInterimList[x - 1].Count()) / 2) - 1,
                    startingReferee = 0, fCount = 1; (i) < 5; startingReferee++)
                    {
                        //############################################################################################################

                        String referee1 = "", referee2 = "";

                        // get the referee for the looser game
                        if (startingReferee < fieldCount)
                        {
                            referee1 = "";
                            startingReferee++;
                        }

                        // check if there is a next referee for the winner game
                        if (startingReferee < fieldCount)
                            referee2 = "";

                        // get winner and looser for the next related games
                        winAndlooser = CalculateResults.getResultsForCrossgamesAndClassementgames(copyCrossgamesList[10 + i]);
                        String winner1 = winAndlooser[1];
                        String looser1 = winAndlooser[2];

                        winAndlooser = CalculateResults.getResultsForCrossgamesAndClassementgames(copyCrossgamesList[10 + i + 5]);
                        String winner2 = winAndlooser[1];
                        String looser2 = winAndlooser[2];

                        // create looser match
                        matchData.Add(new MatchData()
                        {
                            Round = lastRoundNr,
                            FieldNumber = fCount,
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
                        matchData.Add(new MatchData()
                        {
                            Round = lastRoundNr,
                            FieldNumber = fCount,
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
                            //i = i + (toAdd / 2);
                            i++;
                        }
                    }
                }
            }
        }

        public void createFinalClassement()
        {
            int classement = teamsCount;
            

            finalClassement.Clear();

            for(int i = 0, x = 0; i < matchData.Count; i++)
            {
                List<string> gameData = CalculateResults.getResultsForCrossgamesAndClassementgames(matchData[i]);

                finalClassement.Add(new ClassementData()
                {
                    Rank = classements[x++],
                    Team = gameData[1]
                });

                finalClassement.Add(new ClassementData()
                {
                    Rank = classements[x++],
                    Team = gameData[2]
                });
            }

            if (teamsCount == 35)
            {
                int rank = 31;
                for(int i = 0; i < resultInterimList[(teamsCount / 5) - 1].Count; i++, rank++)
                {
                    finalClassement.Add(new ClassementData() {
                        Rank = rank,
                        Team = resultInterimList[(teamsCount / 5) - 1][i].Team
                    });
                }
            }
            if (teamsCount == 45)
            {
                finalClassement.Clear();
                for(int i = 0; i<20;i++)
                {
                    List<String> result = CalculateResults.getResultsForCrossgamesAndClassementgames(matchData[i]);
                    finalClassement.Add(new ClassementData()
                    {
                        Rank = 40 - (i*2) - 1,
                        Team = result[1]
                    });
                    finalClassement.Add(new ClassementData()
                    {
                        Rank = 40 - (i*2),
                        Team = result[2]
                    });

                }

                int rank = 41;
                for (int i = 0; i < resultInterimList[(teamsCount / 5) - 1].Count; i++, rank++)
                {
                    finalClassement.Add(new ClassementData()
                    {
                        Rank = rank,
                        Team = resultInterimList[(teamsCount / 5) - 1][i].Team
                    });
                }
                finalClassement.Sort((p,q) => p.Rank.CompareTo(q.Rank));
            }
            else if (teamsCount == 55)
            {
                finalClassement.Clear();
                classement = 55;
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
            }
            else if (teamsCount == 60)
            {
                for (int i = 0, x = classement; x > 0; i++, x--)
                {
                    List<String> clgGameResult = CalculateResults.getResultsForCrossgamesAndClassementgames(matchData[i]);
                        
                    // generate looser
                    finalClassement.Add(new ClassementData() { Rank = x, Team = clgGameResult[2] });
                    x--;

                    // generate winner query
                    finalClassement.Add(new ClassementData() { Rank = x, Team = clgGameResult[1] });
                }
            }

            finalClassement = giveMeSort(finalClassement);
        }

        List<ClassementData> giveMeSort(List<ClassementData> classement)
        {
            for (int i = classement.Count - 1; i > 0; i--)
            {
                for (int ii = 0; ii < i; ii++)
                {
                    if (classement[ii].Rank > classement[ii + 1].Rank)
                    {
                        ClassementData team = classement[ii];

                        classement[ii] = classement[ii + 1];
                        classement[ii + 1] = team;
                    }
                }
            }

            return classement;
        }
    }    
}
