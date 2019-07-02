using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Volleyball
{
    [Serializable]
    class BaseGameHandling
    {
        #region members
        Logging log;
        int setCounter;
        int minutes;
        int pause;
        int[] rotationArray;
        public List<MatchData> matchData;
        public List<List<ResultData>> resultData;
        #endregion

        public BaseGameHandling(Logging log)
        {
            this.log = log;
            matchData = new List<MatchData>();
            resultData = new List<List<ResultData>>();
        }       

        public void setTimeParameters(int setCounter, int minutes, int pause)
        {
            this.setCounter = setCounter;
            this.minutes = minutes;
            this.pause = pause;
        }

        public void createRotationArray(int count)
        {
            rotationArray = new int[count];

            for (int i = 0; i < count; i++)
                rotationArray[i] = i + 1;
        }

        public void shiftRight(int[] list)
        {
            if (list.Length < 2)
                return;

            int oldFirst = list[0];

            for (int i = 0; i < (list.Length - 1); i++)
                list[i] = list[i + 1];

            list[list.Length - 1] = oldFirst;
        }

        // calculate results
        public void calculateResults()
        {
            List<TeamResult> teamResults = CalculateResults.addResultsForQualifyingAndInterimRounds(CalculateResults.calculateResults(matchData));

            foreach (TeamResult teamResult in teamResults)
            {
                foreach(List<ResultData> resultDataList in resultData)
                {
                    foreach(ResultData resultDataTeam in resultDataList)
                    {
                        if(resultDataTeam.Team == teamResult.TeamName)
                        {
                            resultDataTeam.PointsSets = teamResult.PointsSet;
                            resultDataTeam.PointsMatches = teamResult.PointsMatch;
                            break;
                        }
                    }
                }
            }
        }

        public void insertGameTime(DateTime startTournament)
        {
            int addtime = ((setCounter * minutes) + pause) * 60;

            for (int i = 0, lastRound = 0; i < matchData.Count; i++)
            {
                int roundValue = matchData[i].Round;

                if (lastRound < roundValue)
                {
                    lastRound = roundValue;
                    startTournament = startTournament.AddSeconds(addtime);
                }

                matchData[i].Time = startTournament;                
            }
        }

        //recalculate time schedule
        public void recalculateTimeSchedule(int changeIndex, DateTime gameTime)
        {
            int round = matchData[changeIndex].Round;
            int addTime = ((setCounter * minutes) + pause) * 60;
            
            for (int i = changeIndex; i < matchData.Count; i++)
            {
                if (round != matchData[i].Round)
                {
                    gameTime = gameTime.AddSeconds(addTime);
                    round++;
                }

                matchData[i].Time = gameTime;
            }
        }

        public void insertGameNumber(int preset)
        {
            for (int i = 0; i < matchData.Count; i++)
                matchData[i].Game = i + preset;
        }

        public void insertRoundNumber(int beginRound, int fieldCount)
        {
            for (int i = 0, ii = 1, round = beginRound; i < matchData.Count; i++)
            {
                matchData[i].Round = round;

                if (ii < fieldCount)
                {
                    ii++;
                }
                else
                {
                    ii = 1;
                    round++;
                }
            }
        }

        // insert field numbers
        public void insertFieldnumbersAndFieldnames(int fieldCount, List<String> fieldNames)
        {
            int field = 0;

            createRotationArray(fieldCount);

            foreach(MatchData md in matchData)
            {
                md.FieldNumber = rotationArray[field];
                md.FieldName = fieldNames[rotationArray[field] - 1];

                if (field < rotationArray.Length - 1)
                {
                    field++;
                }
                else
                {
                    field = 0;
                    shiftRight(rotationArray);
                }
            }
        }

        public void insertFieldnames(List<String> fieldNames)
        {
            foreach (MatchData md in matchData)
                md.FieldName = fieldNames[md.FieldNumber - 1];
        }

        // generate divisions result lists
        public void fillResultLists(List<List<String>> divisionsList)
        {
            resultData.Clear();

            foreach (List<String> divisionList in divisionsList)
            {
                List<ResultData> teamList = new List<ResultData>();
                foreach (String team in divisionList)
                    teamList.Add(new ResultData(team));

                resultData.Add(teamList);
            }
        }

        // check equal division results
        public List<String> checkEqualDivisionResults()
        {
            // help lists
            List<List<ResultData>> divisionRanksFirstToFifth = new List<List<ResultData>>();

            for (int i = 0; i < 5; i++)
            {
                List<ResultData> nextRank = new List<ResultData>();

                foreach (List<ResultData> rdList in resultData)
                {
                    if (rdList.Count > i)
                        nextRank.Add(rdList[i]);
                }

                divisionRanksFirstToFifth.Add(nextRank);
            }

            foreach (List<ResultData> rdList in divisionRanksFirstToFifth)
            {
                for (int i = 1; i < rdList.Count; i++)
                {
                    if(rdList[i - 1].PointsSets == rdList[i].PointsSets
                        && rdList[i - 1].PointsMatches == rdList[i].PointsMatches
                        && rdList[i - 1].InternalRank == rdList[i].InternalRank
                        && rdList[i - 1].ExternalRank == rdList[i].ExternalRank)
                    {
                        return new List<String>(){ rdList[i - 1].Team, rdList[i].Team };
                    }
                }
            }

            return new List<String>();
        }

        public void sortResults()
        {
            foreach(List<ResultData> rd in resultData)
            {
                if (rd != null)
                {
                    for (int i = rd.Count - 1; i > 0; i--)
                    {
                        for (int ii = 0; ii < i; ii++)
                        {
                            if (rd[ii].PointsSets < rd[ii + 1].PointsSets)
                            {
                                ResultData team = rd[ii];

                                rd[ii] = rd[ii + 1];
                                rd[ii + 1] = team;
                            }
                            else if (rd[ii].PointsSets == rd[ii + 1].PointsSets 
                                && rd[ii].PointsMatches < rd[ii + 1].PointsMatches)
                            {
                                ResultData team = rd[ii];

                                rd[ii] = rd[ii + 1];
                                rd[ii + 1] = team;
                            }
                            else if (rd[ii].PointsSets == rd[ii + 1].PointsSets 
                                && rd[ii].PointsMatches == rd[ii + 1].PointsMatches
                                && rd[ii].InternalRank > rd[ii + 1].InternalRank)
                            {
                                ResultData team = rd[ii];

                                rd[ii] = rd[ii + 1];
                                rd[ii + 1] = team;
                            }
                        }
                    }

                    for (int x = 0; x < rd.Count; x++)
                        rd[x].Rank = x + 1;
                }
            }
        }
    }
}
