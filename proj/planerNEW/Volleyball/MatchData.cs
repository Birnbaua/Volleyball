using System;

namespace Volleyball
{
    class MatchData
    {
        #region members
        int game;
        int round;
        DateTime time;
        int fieldNumber;
        String fieldName;
        String teamA;
        String teamB;
        String referee;
        int pointsMatch1TeamA;
        int pointsMatch1TeamB;
        int pointsMatch2TeamA;
        int pointsMatch2TeamB;
        int pointsMatch3TeamA;
        int pointsMatch3TeamB;
        #endregion

        public MatchData()
        {
            Game = 0;
            Round = 0;
            Time = DateTime.Now;
            FieldNumber = 0;
            FieldName = "";
            TeamA = "";
            TeamB = "";
            Referee = "";
            PointsMatch1TeamA = 0;
            PointsMatch1TeamB = 0;
            PointsMatch2TeamA = 0;
            PointsMatch2TeamB = 0;
            PointsMatch3TeamA = 0;
            PointsMatch3TeamB = 0;
        }

        public int Game { get => game; set => game = value; }
        public int Round { get => round; set => round = value; }
        public DateTime Time { get => time; set => time = value; }
        public int FieldNumber { get => fieldNumber; set => fieldNumber = value; }
        public string FieldName { get => fieldName; set => fieldName = value; }
        public string TeamA { get => teamA; set => teamA = value; }
        public string TeamB { get => teamB; set => teamB = value; }
        public string Referee { get => referee; set => referee = value; }
        public int PointsMatch1TeamA { get => pointsMatch1TeamA; set => pointsMatch1TeamA = value; }
        public int PointsMatch1TeamB { get => pointsMatch1TeamB; set => pointsMatch1TeamB = value; }
        public int PointsMatch2TeamA { get => pointsMatch2TeamA; set => pointsMatch2TeamA = value; }
        public int PointsMatch2TeamB { get => pointsMatch2TeamB; set => pointsMatch2TeamB = value; }
        public int PointsMatch3TeamA { get => pointsMatch3TeamA; set => pointsMatch3TeamA = value; }
        public int PointsMatch3TeamB { get => pointsMatch3TeamB; set => pointsMatch3TeamB = value; }

        public void fillRowWithCSVString(String data)
        {
            String[] dataArray = data.Split(';');

            Game = Convert.ToInt32(dataArray[0]);
            Round = Convert.ToInt32(dataArray[1]);
            Time = DateTime.Parse(dataArray[2]);
            FieldNumber = Convert.ToInt32(dataArray[3]);
            FieldName = dataArray[4];
            TeamA = dataArray[5];
            TeamB = dataArray[6];
            Referee = dataArray[7];
            PointsMatch1TeamA = Convert.ToInt32(dataArray[8]);
            PointsMatch1TeamB = Convert.ToInt32(dataArray[9]);
            PointsMatch2TeamA = Convert.ToInt32(dataArray[10]);
            PointsMatch2TeamB = Convert.ToInt32(dataArray[11]);
            PointsMatch3TeamA = Convert.ToInt32(dataArray[12]);
            PointsMatch3TeamB = Convert.ToInt32(dataArray[13]);
        }

        public String getRowdataAsCSVString()
        {
            String csvstring = Game.ToString() + ";";
            csvstring += Round.ToString() + ";";
            csvstring += Time.ToString() + ";";
            csvstring += FieldNumber.ToString() + ";";
            csvstring += FieldName + ";";
            csvstring += TeamA + ";";
            csvstring += TeamB + ";";
            csvstring += Referee + ";";
            csvstring += PointsMatch1TeamA.ToString() + ";";
            csvstring += PointsMatch1TeamB.ToString() + ";";
            csvstring += PointsMatch2TeamA.ToString() + ";";
            csvstring += PointsMatch2TeamB.ToString() + ";";
            csvstring += PointsMatch3TeamA.ToString() + ";";
            csvstring += PointsMatch3TeamB.ToString();

            return csvstring;
        }
    }
}
