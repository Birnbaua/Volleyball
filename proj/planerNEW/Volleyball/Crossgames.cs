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
        List<List<ResultData>> divisionsInterimList;
        #endregion

        public CrossGames(Logging log) : base(log)
        {
            this.log = log;
        }

        public void setParameters(List<List<ResultData>> divisionsInterimList, DateTime startRound,
            int pauseBetweenInterimCrossgames, int setCounter, int minutesSet, int minutesPause,
            int fieldCount, int teamsCount, List<String> fieldNames, int lastRoundNr, int lastGameNr, bool useSecondGamePlaning)
        {
            this.divisionsInterimList = divisionsInterimList;
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

            startRound = startRound.AddSeconds(pauseBetweenInterimCrossgames * 60);
        }

        public void generateGames()
        {
            // generate game plan over all divisonal games
            generateGamePlan();

            if (matchData.Count > 0)
            {
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
            int addzeit = ((setCounter * minutesSet) + minutesPause) * 60;

            // help lists
            List<ResultData> divisionA = divisionsInterimList[0];
            List<ResultData> divisionB = divisionsInterimList[1];
            List<ResultData> divisionC = divisionsInterimList[2];
            List<ResultData> divisionD = divisionsInterimList[3];
            List<ResultData> divisionE = divisionsInterimList[4];
            List<ResultData> divisionF = divisionsInterimList[5];
            List<ResultData> divisionG = divisionsInterimList[6];
            List<ResultData> divisionH = divisionsInterimList[7];
            List<ResultData> divisionI = divisionsInterimList[8];
            List<ResultData> divisionJ = divisionsInterimList[9];
            List<ResultData> divisionK = divisionsInterimList[10];
            List<ResultData> divisionL = divisionsInterimList[11];

            if (!useSecondGamePlaning)
            {
                if (teamsCount == 20)
                {
                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr, Time = startRound, FieldNumber = 1,
                        TeamA   = divisionA[0].Team,
                        TeamB   = divisionB[1].Team,
                        Referee = divisionA[1].Team
                    });
                    
                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 2,
                        TeamA   = divisionA[2].Team,
                        TeamB   = divisionB[3].Team,
                        Referee = divisionA[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 3,
                        TeamA   = divisionC[0].Team,
                        TeamB   = divisionD[1].Team,
                        Referee = divisionC[1].Team
                    });
                
                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 4,
                        TeamA   = divisionC[2].Team,
                        TeamB   = divisionD[3].Team,
                        Referee = divisionC[3].Team
                    });
                    
                    startRound = startRound.AddSeconds(addzeit);
                    lastRoundNr++; 

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 1,
                        TeamA   = divisionA[1].Team,
                        TeamB   = divisionB[0].Team,
                        Referee = divisionB[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 2,
                        TeamA   = divisionA[3].Team,
                        TeamB   = divisionB[2].Team,
                        Referee = divisionB[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 3,
                        TeamA   = divisionC[1].Team,
                        TeamB   = divisionD[0].Team,
                        Referee = divisionD[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 4,
                        TeamA   = divisionC[3].Team,
                        TeamB   = divisionD[2].Team,
                        Referee = divisionD[3].Team
                    });
                }
                else if (teamsCount == 25)
                {
                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr, Time = startRound, FieldNumber = 1,
                        TeamA   = divisionA[0].Team,
                        TeamB   = divisionB[1].Team,
                        Referee = divisionA[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 2,
                        TeamA   = divisionA[2].Team,
                        TeamB   = divisionB[3].Team,
                        Referee = divisionA[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 3,
                        TeamA   = divisionC[0].Team,
                        TeamB   = divisionD[1].Team,
                        Referee = divisionC[1].Team
                    });
                    
                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 4,
                        TeamA   = divisionC[2].Team,
                        TeamB   = divisionD[3].Team,
                        Referee = divisionC[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 5,
                        TeamA   = divisionA[1].Team,
                        TeamB   = divisionB[0].Team,
                        Referee = divisionB[1].Team
                    });

                    startRound = startRound.AddSeconds(addzeit);
                    lastRoundNr++;

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 1,
                        TeamA   = divisionA[3].Team,
                        TeamB   = divisionB[2].Team,
                        Referee = divisionB[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 2,
                        TeamA   = divisionC[1].Team,
                        TeamB   = divisionD[0].Team,
                        Referee = divisionD[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 3,
                        TeamA   = divisionC[3].Team,
                        TeamB   = divisionD[2].Team,
                        Referee = divisionD[3].Team
                    });
                }
                else if (teamsCount == 28 || teamsCount == 30 || teamsCount == 35)
                {
                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr, Time = startRound, FieldNumber = 1,
                        TeamA   = divisionA[0].Team,
                        TeamB   = divisionB[1].Team,
                        Referee = divisionA[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 2,
                        TeamA   = divisionA[2].Team,
                        TeamB   = divisionB[3].Team,
                        Referee = divisionA[3].Team
                    });
                    
                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 3,
                        TeamA   = divisionC[0].Team,
                        TeamB   = divisionD[1].Team,
                        Referee = divisionC[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 4,
                        TeamA   = divisionC[2].Team,
                        TeamB   = divisionD[3].Team,
                        Referee = divisionC[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 5,
                        TeamA   = divisionE[0].Team,
                        TeamB   = divisionF[1].Team,
                        Referee = divisionE[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 6,
                        TeamA   = divisionE[2].Team,
                        TeamB   = divisionF[3].Team,
                        Referee = divisionE[3].Team
                    });

                    startRound = startRound.AddSeconds(addzeit);
                    lastRoundNr++;

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 6,
                        TeamA   = divisionA[1].Team,
                        TeamB   = divisionB[0].Team,
                        Referee = divisionB[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 5,
                        TeamA   = divisionA[3].Team,
                        TeamB   = divisionB[2].Team,
                        Referee = divisionB[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 4,
                        TeamA   = divisionC[1].Team,
                        TeamB   = divisionD[0].Team,
                        Referee = divisionD[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 3,
                        TeamA   = divisionC[3].Team,
                        TeamB   = divisionD[2].Team,
                        Referee = divisionD[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 2,
                        TeamA   = divisionE[1].Team,
                        TeamB   = divisionF[0].Team,
                        Referee = divisionF[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 1,
                        TeamA   = divisionE[3].Team,
                        TeamB   = divisionF[2].Team,
                        Referee = divisionF[3].Team
                    });
                }
                else if (teamsCount == 40 || teamsCount == 45)
                {
                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr, Time = startRound, FieldNumber = 1,
                        TeamA   = divisionA[0].Team,
                        TeamB   = divisionB[1].Team,
                        Referee = divisionA[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 2,
                        TeamA   = divisionA[2].Team,
                        TeamB   = divisionB[3].Team,
                        Referee = divisionA[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 3,
                        TeamA   = divisionC[0].Team,
                        TeamB   = divisionD[1].Team,
                        Referee = divisionC[1].Team
                    });
                    
                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 4,
                        TeamA   = divisionC[2].Team,
                        TeamB   = divisionD[3].Team,
                        Referee = divisionC[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 5,
                        TeamA   = divisionE[0].Team,
                        TeamB   = divisionF[1].Team,
                        Referee = divisionE[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 6,
                        TeamA   = divisionE[2].Team,
                        TeamB   = divisionF[3].Team,
                        Referee = divisionE[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 7,
                        TeamA   = divisionG[0].Team,
                        TeamB   = divisionH[1].Team,
                        Referee = divisionG[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 8,
                        TeamA   = divisionG[2].Team,
                        TeamB   = divisionH[3].Team,
                        Referee = divisionG[3].Team
                    });

                    startRound = startRound.AddSeconds(addzeit);
                    lastRoundNr++;

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 8,
                        TeamA   = divisionA[1].Team,
                        TeamB   = divisionB[0].Team,
                        Referee = divisionB[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 7,
                        TeamA   = divisionA[3].Team,
                        TeamB   = divisionB[2].Team,
                        Referee = divisionB[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 6,
                        TeamA   = divisionC[1].Team,
                        TeamB   = divisionD[0].Team,
                        Referee = divisionD[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 5,
                        TeamA   = divisionC[3].Team,
                        TeamB   = divisionD[2].Team,
                        Referee = divisionD[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 4,
                        TeamA   = divisionE[1].Team,
                        TeamB   = divisionF[0].Team,
                        Referee = divisionF[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 3,
                        TeamA   = divisionE[3].Team,
                        TeamB   = divisionF[2].Team,
                        Referee = divisionF[3].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 2,
                        TeamA   = divisionG[1].Team,
                        TeamB   = divisionH[0].Team,
                        Referee = divisionH[1].Team
                    });

                    matchData.Add(new MatchData() { Round = lastRoundNr, Game = lastGameNr++, Time = startRound, FieldNumber = 1,
                        TeamA   = divisionG[3].Team,
                        TeamB   = divisionH[2].Team,
                        Referee = divisionH[3].Team
                    });
                }
                else if (teamsCount == 50 || teamsCount == 55)
                {
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(1," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA.at(0) + "','" + divisionB.at(1) + "','" + divisionA.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(2," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionA.at(2) + "','" + divisionB.at(3) + "','" + divisionA.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(3," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionC.at(0) + "','" + divisionD.at(1) + "','" + divisionC.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(4," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionC.at(2) + "','" + divisionD.at(3) + "','" + divisionC.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(5," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionE.at(0) + "','" + divisionF.at(1) + "','" + divisionE.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(6," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + divisionE.at(2) + "','" + divisionF.at(3) + "','" + divisionE.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(7," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + divisionG.at(0) + "','" + divisionH.at(1) + "','" + divisionG.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + divisionG.at(2) + "','" + divisionH.at(3) + "','" + divisionG.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(9," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',9,'','" + divisionI.at(0) + "','" + divisionJ.at(1) + "','" + divisionI.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(10," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',10,'','" + divisionI.at(2) + "','" + divisionJ.at(3) + "','" + divisionI.at(3) + "',0,0,0,0,0,0)";

                    startRound = startRound.addSecs(addzeit);
                    lastRoundNr++; lastGameNr++;

                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(11," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',10,'','" + divisionA.at(1) + "','" + divisionB.at(0) + "','" + divisionB.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',9,'','" + divisionA.at(3) + "','" + divisionB.at(2) + "','" + divisionB.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(13," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + divisionC.at(1) + "','" + divisionD.at(0) + "','" + divisionD.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(14," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + divisionC.at(3) + "','" + divisionD.at(2) + "','" + divisionD.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(15," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + divisionE.at(1) + "','" + divisionF.at(0) + "','" + divisionF.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(16," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionE.at(3) + "','" + divisionF.at(2) + "','" + divisionF.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(17," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionG.at(1) + "','" + divisionH.at(0) + "','" + divisionH.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(18," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionG.at(3) + "','" + divisionH.at(2) + "','" + divisionH.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(19," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionI.at(1) + "','" + divisionJ.at(0) + "','" + divisionI.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(20," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionI.at(3) + "','" + divisionJ.at(2) + "','" + divisionI.at(3) + "',0,0,0,0,0,0)";
                }
                else if (teamsCount == 60)
                {
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(1," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionA.at(0) + "','" + divisionB.at(1) + "','" + divisionA.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(2," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionA.at(2) + "','" + divisionB.at(3) + "','" + divisionA.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(3," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionC.at(0) + "','" + divisionD.at(1) + "','" + divisionC.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(4," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionC.at(2) + "','" + divisionD.at(3) + "','" + divisionC.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(5," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionE.at(0) + "','" + divisionF.at(1) + "','" + divisionE.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(6," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + divisionE.at(2) + "','" + divisionF.at(3) + "','" + divisionE.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(7," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + divisionG.at(0) + "','" + divisionH.at(1) + "','" + divisionG.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(8," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + divisionG.at(2) + "','" + divisionH.at(3) + "','" + divisionG.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(9," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',9,'','" + divisionI.at(0) + "','" + divisionJ.at(1) + "','" + divisionI.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(10," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',10,'','" + divisionI.at(2) + "','" + divisionJ.at(3) + "','" + divisionI.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(11," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',11,'','" + divisionK.at(2) + "','" + divisionL.at(3) + "','" + divisionK.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(12," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',12,'','" + divisionK.at(2) + "','" + divisionL.at(3) + "','" + divisionK.at(3) + "',0,0,0,0,0,0)";

                    startRound = startRound.addSecs(addzeit);
                    lastRoundNr++; lastGameNr++;

                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(13," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',12,'','" + divisionA.at(1) + "','" + divisionB.at(0) + "','" + divisionB.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(14," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',11,'','" + divisionA.at(3) + "','" + divisionB.at(2) + "','" + divisionB.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(15," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',10,'','" + divisionC.at(1) + "','" + divisionD.at(0) + "','" + divisionD.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(16," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',9,'','" + divisionC.at(3) + "','" + divisionD.at(2) + "','" + divisionD.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(17," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',8,'','" + divisionE.at(1) + "','" + divisionF.at(0) + "','" + divisionF.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(18," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',7,'','" + divisionE.at(3) + "','" + divisionF.at(2) + "','" + divisionF.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(19," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',6,'','" + divisionG.at(1) + "','" + divisionH.at(0) + "','" + divisionH.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(20," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',5,'','" + divisionG.at(3) + "','" + divisionH.at(2) + "','" + divisionH.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(21," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',4,'','" + divisionI.at(1) + "','" + divisionJ.at(0) + "','" + divisionJ.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(22," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',3,'','" + divisionI.at(3) + "','" + divisionJ.at(2) + "','" + divisionJ.at(3) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(23," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',2,'','" + divisionK.at(1) + "','" + divisionL.at(0) + "','" + divisionL.at(1) + "',0,0,0,0,0,0)";
                    lastGameNr++;
                    querys << "INSERT INTO kreuzspiele_spielplan VALUES(24," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "',1,'','" + divisionK.at(3) + "','" + divisionL.at(2) + "','" + divisionL.at(3) + "',0,0,0,0,0,0)";
                }
            }
            else
            {
                if (divisionA.count() > 0)
                    finalDivisions.append(&divisionA);

                if (divisionB.count() > 0)
                    finalDivisions.append(&divisionB);

                if (divisionC.count() > 0)
                    finalDivisions.append(&divisionC);

                if (divisionD.count() > 0)
                    finalDivisions.append(&divisionD);

                if (divisionE.count() > 0)
                    finalDivisions.append(&divisionE);

                if (divisionF.count() > 0)
                    finalDivisions.append(&divisionF);

                if (divisionG.count() > 0)
                    finalDivisions.append(&divisionG);

                if (divisionH.count() > 0)
                    finalDivisions.append(&divisionH);

                if (divisionI.count() > 0)
                    finalDivisions.append(&divisionI);

                if (divisionJ.count() > 0)
                    finalDivisions.append(&divisionJ);

                if (divisionK.count() > 0)
                    finalDivisions.append(&divisionK);

                if (divisionL.count() > 0)
                    finalDivisions.append(&divisionL);

                QList<QList<QStringList>> gameList;
                QStringList refereeList;
                lastGameNr++;

                // create game list
                for (int i = 0; i < divisionCount;)
                {
                    if (i + 1 < finalDivisions.count())
                    {
                        int rest = (finalDivisions.at(i)->count() + finalDivisions.at(i + 1)->count()) % 2;
                        int count = (finalDivisions.at(i)->count() + finalDivisions.at(i + 1)->count() - rest) / 2;
                        QList<QStringList> games;

                        for (int x = 0; x < count; x++)
                        {
                            games.append(QStringList() << finalDivisions.at(i)->at(x) << finalDivisions.at(i + 1)->at(x));
                            gamesCount++;
                        }

                        gameList.append(games);
                        i = i + 2;
                    }
                    else
                    {
                        break;
                    }
                }

                for (int i = 0; i < gameList.count() && i < fieldCount; i++)
                {
                    QList<QStringList> refList = gameList.at(i);
                    for (int j = 0; j < refList.count(); j++)
                    {
                        refereeList.append(refList.at(j).at(0));
                        refereeList.append(refList.at(j).at(1));
                    }
                }

                // generate round starting with last group and last game (worst two teams)
                for (int count = 0, fCount = 1, y = (gameList.count() - 1), startingReferee = 0,
                    rowCount = 1, dataRow = gameList.at((gameList.count() - 1)).count() - 1;
                    count < gamesCount; rowCount++, lastGameNr++, count++, startingReferee++)
                {
                    QString referee = "";
                    if (startingReferee < fieldCount)
                        referee = refereeList.at(startingReferee);

                    querys << "INSERT INTO kreuzspiele_spielplan VALUES("
                              + string(rowCount) + "," + string(lastRoundNr) + "," + string(lastGameNr) + ",'" + startRound.toString("hh:mm") + "', " + string(fCount) + ",'','"
                              + gameList.at(y).at(dataRow).at(0) + "','"
                              + gameList.at(y).at(dataRow).at(1) + "','"
                              + referee + "',"
                              + "0,0,0,0,0,0)";

                    if (fCount >= fieldCount)
                    {
                        fCount = 1;
                        lastRoundNr++;
                        startRound = startRound.addSecs(addzeit);
                    }
                    else
                    {
                        fCount++;
                    }

                    if (dataRow < 1)
                    {
                        dataRow = gameList.at(y).count() - 1;
                        y--;
                    }
                    else
                    {
                        dataRow--;
                    }
                }
            }
        }
    }
}
