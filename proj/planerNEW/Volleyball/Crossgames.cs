using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Volleyball
{
    class CrossGames : BaseGameHandling
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
        List<List<ResultData>> resultCrossgamesList;
        int gamesCount;
        #endregion

        public CrossGames(Logging log) : base(log)
        {
            this.log = log;
            gamesCount = 0;
        }

        public void setParameters(List<List<ResultData>> resultCrossgamesList, DateTime startRound,
            int pauseBetweenInterimCrossgames, int setCounter, int minutesSet, int minutesPause,
            int fieldCount, int teamsCount, List<String> fieldNames, int lastRoundNr, int lastGameNr, bool useSecondGamePlaning)
        {
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
            List<List<ResultData>> finalDivisions = new List<List<ResultData>>();
            int addzeit = ((setCounter * minutesSet) + minutesPause) * 60;

            // help lists
            List<ResultData> divisionA = resultCrossgamesList[0];
            List<ResultData> divisionB = resultCrossgamesList[1];
            List<ResultData> divisionC = resultCrossgamesList[2];
            List<ResultData> divisionD = resultCrossgamesList[3];
            List<ResultData> divisionE = resultCrossgamesList[4];
            List<ResultData> divisionF = resultCrossgamesList[5];
            List<ResultData> divisionG = resultCrossgamesList[6];
            List<ResultData> divisionH = resultCrossgamesList[7];
            List<ResultData> divisionI = resultCrossgamesList[8];
            List<ResultData> divisionJ = resultCrossgamesList[9];
            List<ResultData> divisionK = resultCrossgamesList[10];
            List<ResultData> divisionL = resultCrossgamesList[11];

            if (!useSecondGamePlaning)
            {
                if (teamsCount == 20)
                {
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 1,
                        TeamA   = divisionA[0].Team,
                        TeamB   = divisionB[1].Team,
                        Referee = divisionA[1].Team
                    });
                    
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 2,
                        TeamA   = divisionA[2].Team,
                        TeamB   = divisionB[3].Team,
                        Referee = divisionA[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 3,
                        TeamA   = divisionC[0].Team,
                        TeamB   = divisionD[1].Team,
                        Referee = divisionC[1].Team
                    });
                
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 4,
                        TeamA   = divisionC[2].Team,
                        TeamB   = divisionD[3].Team,
                        Referee = divisionC[3].Team
                    });
                    
                    lastRoundNr++; 

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 1,
                        TeamA   = divisionA[1].Team,
                        TeamB   = divisionB[0].Team,
                        Referee = divisionB[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 2,
                        TeamA   = divisionA[3].Team,
                        TeamB   = divisionB[2].Team,
                        Referee = divisionB[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 3,
                        TeamA   = divisionC[1].Team,
                        TeamB   = divisionD[0].Team,
                        Referee = divisionD[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 4,
                        TeamA   = divisionC[3].Team,
                        TeamB   = divisionD[2].Team,
                        Referee = divisionD[3].Team
                    });
                }
                else if (teamsCount == 25)
                {
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 1,
                        TeamA   = divisionA[0].Team,
                        TeamB   = divisionB[1].Team,
                        Referee = divisionA[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 2,
                        TeamA   = divisionA[2].Team,
                        TeamB   = divisionB[3].Team,
                        Referee = divisionA[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 3,
                        TeamA   = divisionC[0].Team,
                        TeamB   = divisionD[1].Team,
                        Referee = divisionC[1].Team
                    });
                    
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 4,
                        TeamA   = divisionC[2].Team,
                        TeamB   = divisionD[3].Team,
                        Referee = divisionC[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 5,
                        TeamA   = divisionA[1].Team,
                        TeamB   = divisionB[0].Team,
                        Referee = divisionB[1].Team
                    });
                    
                    lastRoundNr++;

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 1,
                        TeamA   = divisionA[3].Team,
                        TeamB   = divisionB[2].Team,
                        Referee = divisionB[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 2,
                        TeamA   = divisionC[1].Team,
                        TeamB   = divisionD[0].Team,
                        Referee = divisionD[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 3,
                        TeamA   = divisionC[3].Team,
                        TeamB   = divisionD[2].Team,
                        Referee = divisionD[3].Team
                    });
                }
                else if (teamsCount == 28 || teamsCount == 30 || teamsCount == 35)
                {
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 1,
                        TeamA   = divisionA[0].Team,
                        TeamB   = divisionB[1].Team,
                        Referee = divisionA[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 2,
                        TeamA   = divisionA[2].Team,
                        TeamB   = divisionB[3].Team,
                        Referee = divisionA[3].Team
                    });
                    
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 3,
                        TeamA   = divisionC[0].Team,
                        TeamB   = divisionD[1].Team,
                        Referee = divisionC[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 4,
                        TeamA   = divisionC[2].Team,
                        TeamB   = divisionD[3].Team,
                        Referee = divisionC[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 5,
                        TeamA   = divisionE[0].Team,
                        TeamB   = divisionF[1].Team,
                        Referee = divisionE[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 6,
                        TeamA   = divisionE[2].Team,
                        TeamB   = divisionF[3].Team,
                        Referee = divisionE[3].Team
                    });

                    lastRoundNr++;

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 6,
                        TeamA   = divisionA[1].Team,
                        TeamB   = divisionB[0].Team,
                        Referee = divisionB[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 5,
                        TeamA   = divisionA[3].Team,
                        TeamB   = divisionB[2].Team,
                        Referee = divisionB[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 4,
                        TeamA   = divisionC[1].Team,
                        TeamB   = divisionD[0].Team,
                        Referee = divisionD[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 3,
                        TeamA   = divisionC[3].Team,
                        TeamB   = divisionD[2].Team,
                        Referee = divisionD[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 2,
                        TeamA   = divisionE[1].Team,
                        TeamB   = divisionF[0].Team,
                        Referee = divisionF[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 1,
                        TeamA   = divisionE[3].Team,
                        TeamB   = divisionF[2].Team,
                        Referee = divisionF[3].Team
                    });
                }
                else if (teamsCount == 40 || teamsCount == 45)
                {
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 1,
                        TeamA   = divisionA[0].Team,
                        TeamB   = divisionB[1].Team,
                        Referee = divisionA[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 2,
                        TeamA   = divisionA[2].Team,
                        TeamB   = divisionB[3].Team,
                        Referee = divisionA[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 3,
                        TeamA   = divisionC[0].Team,
                        TeamB   = divisionD[1].Team,
                        Referee = divisionC[1].Team
                    });
                    
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 4,
                        TeamA   = divisionC[2].Team,
                        TeamB   = divisionD[3].Team,
                        Referee = divisionC[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 5,
                        TeamA   = divisionE[0].Team,
                        TeamB   = divisionF[1].Team,
                        Referee = divisionE[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 6,
                        TeamA   = divisionE[2].Team,
                        TeamB   = divisionF[3].Team,
                        Referee = divisionE[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 7,
                        TeamA   = divisionG[0].Team,
                        TeamB   = divisionH[1].Team,
                        Referee = divisionG[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 8,
                        TeamA   = divisionG[2].Team,
                        TeamB   = divisionH[3].Team,
                        Referee = divisionG[3].Team
                    });

                    lastRoundNr++;

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 8,
                        TeamA   = divisionA[1].Team,
                        TeamB   = divisionB[0].Team,
                        Referee = divisionB[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 7,
                        TeamA   = divisionA[3].Team,
                        TeamB   = divisionB[2].Team,
                        Referee = divisionB[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 6,
                        TeamA   = divisionC[1].Team,
                        TeamB   = divisionD[0].Team,
                        Referee = divisionD[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 5,
                        TeamA   = divisionC[3].Team,
                        TeamB   = divisionD[2].Team,
                        Referee = divisionD[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 4,
                        TeamA   = divisionE[1].Team,
                        TeamB   = divisionF[0].Team,
                        Referee = divisionF[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 3,
                        TeamA   = divisionE[3].Team,
                        TeamB   = divisionF[2].Team,
                        Referee = divisionF[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 2,
                        TeamA   = divisionG[1].Team,
                        TeamB   = divisionH[0].Team,
                        Referee = divisionH[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 1,
                        TeamA   = divisionG[3].Team,
                        TeamB   = divisionH[2].Team,
                        Referee = divisionH[3].Team
                    });
                }
                else if (teamsCount == 50 || teamsCount == 55)
                {
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 1,
                        TeamA   = divisionA[0].Team,
                        TeamB   = divisionB[1].Team,
                        Referee = divisionA[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 2,
                        TeamA   = divisionA[2].Team,
                        TeamB   = divisionB[3].Team,
                        Referee = divisionA[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 3,
                        TeamA   = divisionC[0].Team,
                        TeamB   = divisionD[1].Team,
                        Referee = divisionC[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 4,
                        TeamA   = divisionC[2].Team,
                        TeamB   = divisionD[3].Team,
                        Referee = divisionC[3].Team
                    });
                    
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 5,
                        TeamA   = divisionE[0].Team,
                        TeamB   = divisionF[1].Team,
                        Referee = divisionE[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 6,
                        TeamA   = divisionE[2].Team,
                        TeamB   = divisionF[3].Team,
                        Referee = divisionE[3].Team
                    });
                    
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 7,
                        TeamA   = divisionG[2].Team,
                        TeamB   = divisionH[3].Team,
                        Referee = divisionG[3].Team
                    });
                    
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 8,
                        TeamA   = divisionG[2].Team,
                        TeamB   = divisionH[3].Team,
                        Referee = divisionG[3].Team
                    });
                    
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 9,
                        TeamA   = divisionI[0].Team,
                        TeamB   = divisionJ[1].Team,
                        Referee = divisionI[1].Team
                    });
                    
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 10,
                        TeamA   = divisionI[2].Team,
                        TeamB   = divisionJ[3].Team,
                        Referee = divisionI[3].Team
                    });
                    
                    lastRoundNr++;

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 10,
                        TeamA   = divisionA[1].Team,
                        TeamB   = divisionB[0].Team,
                        Referee = divisionA[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 9,
                        TeamA   = divisionA[3].Team,
                        TeamB   = divisionB[2].Team,
                        Referee = divisionB[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 8,
                        TeamA   = divisionC[1].Team,
                        TeamB   = divisionD[0].Team,
                        Referee = divisionD[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 7,
                        TeamA   = divisionC[3].Team,
                        TeamB   = divisionD[2].Team,
                        Referee = divisionD[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 6,
                        TeamA   = divisionE[1].Team,
                        TeamB   = divisionF[0].Team,
                        Referee = divisionF[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 5,
                        TeamA   = divisionE[3].Team,
                        TeamB   = divisionF[2].Team,
                        Referee = divisionF[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 4,
                        TeamA   = divisionG[1].Team,
                        TeamB   = divisionH[0].Team,
                        Referee = divisionH[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 3,
                        TeamA   = divisionG[3].Team,
                        TeamB   = divisionH[2].Team,
                        Referee = divisionH[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 2,
                        TeamA   = divisionI[1].Team,
                        TeamB   = divisionJ[0].Team,
                        Referee = divisionI[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 1,
                        TeamA   = divisionI[3].Team,
                        TeamB   = divisionJ[2].Team,
                        Referee = divisionI[3].Team
                    });
                }
                else if (teamsCount == 60)
                {
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 1,
                        TeamA   = divisionA[0].Team,
                        TeamB   = divisionB[1].Team,
                        Referee = divisionA[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 2,
                        TeamA   = divisionA[2].Team,
                        TeamB   = divisionB[3].Team,
                        Referee = divisionA[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 3,
                        TeamA   = divisionC[0].Team,
                        TeamB   = divisionD[1].Team,
                        Referee = divisionC[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 4,
                        TeamA   = divisionC[2].Team,
                        TeamB   = divisionD[3].Team,
                        Referee = divisionC[3].Team
                    });
                    
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 5,
                        TeamA   = divisionE[0].Team,
                        TeamB   = divisionF[1].Team,
                        Referee = divisionE[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 6,
                        TeamA   = divisionE[2].Team,
                        TeamB   = divisionF[3].Team,
                        Referee = divisionE[3].Team
                    });
                    
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 7,
                        TeamA   = divisionG[2].Team,
                        TeamB   = divisionH[3].Team,
                        Referee = divisionG[3].Team
                    });
                    
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 8,
                        TeamA   = divisionG[2].Team,
                        TeamB   = divisionH[3].Team,
                        Referee = divisionG[3].Team
                    });
                    
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 9,
                        TeamA   = divisionI[0].Team,
                        TeamB   = divisionJ[1].Team,
                        Referee = divisionI[1].Team
                    });
                    
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 10,
                        TeamA   = divisionI[2].Team,
                        TeamB   = divisionJ[3].Team,
                        Referee = divisionI[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 11,
                        TeamA   = divisionK[0].Team,
                        TeamB   = divisionL[1].Team,
                        Referee = divisionK[1].Team
                    });
                    
                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 12,
                        TeamA   = divisionK[2].Team,
                        TeamB   = divisionL[3].Team,
                        Referee = divisionK[3].Team
                    });

                    lastRoundNr++;

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 12,
                        TeamA   = divisionA[1].Team,
                        TeamB   = divisionB[0].Team,
                        Referee = divisionA[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 11,
                        TeamA   = divisionA[3].Team,
                        TeamB   = divisionB[2].Team,
                        Referee = divisionB[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 10,
                        TeamA   = divisionC[1].Team,
                        TeamB   = divisionD[0].Team,
                        Referee = divisionD[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 9,
                        TeamA   = divisionC[3].Team,
                        TeamB   = divisionD[2].Team,
                        Referee = divisionD[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 8,
                        TeamA   = divisionE[1].Team,
                        TeamB   = divisionF[0].Team,
                        Referee = divisionF[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 7,
                        TeamA   = divisionE[3].Team,
                        TeamB   = divisionF[2].Team,
                        Referee = divisionF[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 6,
                        TeamA   = divisionG[1].Team,
                        TeamB   = divisionH[0].Team,
                        Referee = divisionH[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 5,
                        TeamA   = divisionG[3].Team,
                        TeamB   = divisionH[2].Team,
                        Referee = divisionH[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 4,
                        TeamA   = divisionI[1].Team,
                        TeamB   = divisionJ[0].Team,
                        Referee = divisionI[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 3,
                        TeamA   = divisionI[3].Team,
                        TeamB   = divisionJ[2].Team,
                        Referee = divisionI[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 2,
                        TeamA   = divisionK[1].Team,
                        TeamB   = divisionL[0].Team,
                        Referee = divisionL[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = 1,
                        TeamA   = divisionK[3].Team,
                        TeamB   = divisionL[2].Team,
                        Referee = divisionL[3].Team
                    });
                }
            }
            else
            {
                if (divisionA.Count > 0)
                    finalDivisions.Add(divisionA);

                if (divisionB.Count > 0)
                    finalDivisions.Add(divisionB);

                if (divisionC.Count > 0)
                    finalDivisions.Add(divisionC);

                if (divisionD.Count > 0)
                    finalDivisions.Add(divisionD);

                if (divisionE.Count > 0)
                    finalDivisions.Add(divisionE);

                if (divisionF.Count > 0)
                    finalDivisions.Add(divisionF);

                if (divisionG.Count > 0)
                    finalDivisions.Add(divisionG);

                if (divisionH.Count > 0)
                    finalDivisions.Add(divisionH);

                if (divisionI.Count > 0)
                    finalDivisions.Add(divisionI);

                if (divisionJ.Count > 0)
                    finalDivisions.Add(divisionJ);

                if (divisionK.Count > 0)
                    finalDivisions.Add(divisionK);

                if (divisionL.Count > 0)
                    finalDivisions.Add(divisionL);

                List<MatchData> gameList = new List<MatchData>();
                List<String> refereeList = new List<String>();

                // create game list
                for (int i = 0; i < finalDivisions.Count;)
                {
                    if (i + 1 < finalDivisions.Count)
                    {
                        int rest = (finalDivisions[i].Count + finalDivisions[i + 1].Count) % 2;
                        int count = (finalDivisions[i].Count + finalDivisions[i + 1].Count - rest) / 2;
                        
                        for (int x = 0; x < count; x++)
                        {
                            gameList.Add(new MatchData() { TeamA = finalDivisions[i][x].Team, TeamB = finalDivisions[i + 1][x].Team });
                            gamesCount++;
                        }

                        i = i + 2;
                    }
                    else
                    {
                        break;
                    }
                }

                for (int i = 0; i < gameList.Count && i < fieldCount; i++)
                {
                    MatchData refList = gameList[i];

                    refereeList.Add(refList.TeamA);
                    refereeList.Add(refList.TeamB);
                }

                // generate round starting with last group and last game (worst two teams)
                for (int count = 0, fCount = 1, y = (gameList.Count - 1), startingReferee = 0;
                    count < gamesCount; count++, startingReferee++, y--)
                {
                    String referee = "";
                    if (startingReferee < fieldCount)
                        referee = refereeList[startingReferee];

                    matchData.Add(new MatchData() { Round = lastRoundNr, FieldNumber = fCount,
                        TeamA = gameList[y].TeamA,
                        TeamB = gameList[y].TeamB,
                        Referee = referee
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
                }
            }
        }
    }
}
