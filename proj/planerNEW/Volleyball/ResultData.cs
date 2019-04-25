using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Volleyball
{
    class ResultData
    {
        #region members
        int rank;
        String team;
        int pointsSets;
        int pointsMatches;
        int internalRank;
        int externalRank;
        #endregion

        public ResultData()
        {
            Rank = 0;
            Team = "";
            PointsSets = 0;
            PointsMatches = 0;
            InternalRank = 0;
            ExternalRank = 0;
        }

        public ResultData(String team)
        {
            Rank = 0;
            Team = team;
            PointsSets = 0;
            PointsMatches = 0;
            InternalRank = 0;
            ExternalRank = 0;
        }

        public int Rank { get => rank; set => rank = value; }
        public string Team { get => team; set => team = value; }
        public int PointsSets { get => pointsSets; set => pointsSets = value; }
        public int PointsMatches { get => pointsMatches; set => pointsMatches = value; }
        public int InternalRank { get => internalRank; set => internalRank = value; }
        public int ExternalRank { get => externalRank; set => externalRank = value; }

        public void fillRowWithCSVString(String data)
        {
            String[] dataArray = data.Split(';');

            Rank = Convert.ToInt32(dataArray[0]);
            Team = dataArray[1];
            PointsSets = Convert.ToInt32(dataArray[2]);
            PointsMatches = Convert.ToInt32(dataArray[3]);
            InternalRank = Convert.ToInt32(dataArray[4]);
            ExternalRank = Convert.ToInt32(dataArray[5]);
        }

        public String getRowdataAsCSVString()
        {
            String csvstring = Rank.ToString() + ";";
            csvstring += Team + ";";
            csvstring += PointsSets.ToString() + ";";
            csvstring += PointsMatches.ToString() + ";";
            csvstring += InternalRank + ";";
            csvstring += ExternalRank;

            return csvstring;
        }
    }
}
