using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Volleyball
{
    class ClassementData
    {
        #region members
        int rank;
        String team;
        #endregion

        public ClassementData()
        {
            Rank = 0;
            Team = "";
        }

        public ClassementData(String team)
        {
            Rank = 0;
            Team = team;
        }

        public int Rank { get => rank; set => rank = value; }
        public string Team { get => team; set => team = value; }
        
        public void fillRowWithCSVString(String data)
        {
            String[] dataArray = data.Split(';');

            Rank = Convert.ToInt32(dataArray[0]);
            Team = dataArray[1];
        }

        public String getRowdataAsCSVString()
        {
            String csvstring = Rank.ToString() + ";";
            csvstring += Team + ";";
        
            return csvstring;
        }
    }
}
