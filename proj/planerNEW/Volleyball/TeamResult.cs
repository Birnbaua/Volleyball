using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Volleyball
{
    class TeamResult
    {
        #region members
        String teamName;
        int pointsMatch;
        int pointsSet;
        #endregion

        public string TeamName
        {
            get => teamName;
            set => teamName = value;
        }

        public int PointsMatch
        {
            get => pointsMatch;
            set => pointsMatch = value;
        }

        public int PointsSet
        {
            get => pointsSet;
            set => pointsSet = value;
        }
        
        public TeamResult()
        {
            TeamName = "";
            PointsMatch = 0;
            PointsSet = 0;
        }
    }
}
