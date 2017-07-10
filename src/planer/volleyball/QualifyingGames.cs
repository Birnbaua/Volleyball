/*
 * Created by SharpDevelop.
 * User: cfr
 * Date: 26.06.2017
 * Time: 14:00
 */
using System;
using System.Collections.Generic;
using volleyball;

namespace volleyball
{
	public class QualifyingGames : BaseGameHandling
	{
		#region members
		DateTime startTurnier;
		bool first;
	    int prefixCount;
	    List<List<int>> firstFourMsDivision, fourMsDivision, fiveMsDivision;
		#endregion
		
		public QualifyingGames(Database db, List<String> grPrefix) : base(db, grPrefix)
		{
			first = true;

			firstFourMsDivision = new List<List<int>>();
			fourMsDivision = new List<List<int>>();
			fiveMsDivision = new List<List<int>>();
			
		    // game plan for 4 teams in division
		    firstFourMsDivision.Add(new List<int>() { 0, 1, 2 });
		    firstFourMsDivision.Add(new List<int>() { 2, 3, 1 });
		    firstFourMsDivision.Add(new List<int>() { 999, 999, 999 });
		    firstFourMsDivision.Add(new List<int>() { 1, 2, 3 });
		    firstFourMsDivision.Add(new List<int>() { 999, 999, 999 });
		    firstFourMsDivision.Add(new List<int>() { 0, 3, 1 });
		    firstFourMsDivision.Add(new List<int>() { 999, 999, 999 });
		    firstFourMsDivision.Add(new List<int>() { 1, 3, 0 });
		    firstFourMsDivision.Add(new List<int>() { 999, 999, 999 });
		    firstFourMsDivision.Add(new List<int>() { 0, 2, 3 });
		
		    // game plan for 4 teams in division
		    fourMsDivision.Add(new List<int>() { 0, 1, 2 });
		    fourMsDivision.Add(new List<int>() { 999, 999, 999 });
		    fourMsDivision.Add(new List<int>() { 2, 3, 1 });
		    fourMsDivision.Add(new List<int>() { 999, 999, 999 });
		    fourMsDivision.Add(new List<int>() { 1, 2, 3 });
		    fourMsDivision.Add(new List<int>() { 999, 999, 999 });
		    fourMsDivision.Add(new List<int>() { 0, 3, 1 });
		    fourMsDivision.Add(new List<int>() { 999, 999, 999 });
		    fourMsDivision.Add(new List<int>() { 1, 3, 0 });
		    fourMsDivision.Add(new List<int>() { 0, 2, 3 });
		
		    // game plan for 5 teams in division
		    fiveMsDivision.Add(new List<int>() { 0, 2, 3 });
		    fiveMsDivision.Add(new List<int>() { 1, 3, 4 });
		    fiveMsDivision.Add(new List<int>() { 2, 4, 1 });
		    fiveMsDivision.Add(new List<int>() { 0, 3, 2 });
		    fiveMsDivision.Add(new List<int>() { 1, 4, 0 });
		    fiveMsDivision.Add(new List<int>() { 2, 3, 1 });
		    fiveMsDivision.Add(new List<int>() { 0, 4, 3 });
		    fiveMsDivision.Add(new List<int>() { 1, 2, 0 });
		    fiveMsDivision.Add(new List<int>() { 3, 4, 2 });
		    fiveMsDivision.Add(new List<int>() { 0, 1, 4 });
		}
		
		public void setParameters(String startTurnier, int satz, int min, int pause, int fieldCount, 
		                          int teamsCount, List<String> fieldNames)
		{
		    Logging.write("VORRUNDE: set vr params");
		    
		    this.startTurnier = DateTime.Parse(startTurnier);
		    		
		    setParameters(satz, min, pause, fieldCount, teamsCount, gamesCount, fieldNames);
		}
		
		public void generateGames()
		{
			List<List<String>> divisionsList = new List<List<String>>();
			List<List<List<String>>> divisionsGameList = new List<List<List<String>>>();
			List<String> querys = new List<String>();
		
		    prefixCount = getPrefixCount();
		    gamesCount = 0;
		
		    // preparte lists for all divisions
		    for(int i = 0; i < prefixCount; i++)
		    {
		    	List<String> division = new List<String>();
		    	String group = getPrefix(i);
		        List<List<String>> list = readListFromDatabase("SELECT " + group + " FROM mannschaften WHERE " + group + " != ''");
		
		        // for each division one stringlist
		        for(int j = 0; j < list.Count; j++)
		        	division.Add(list[j][0]);
		
		        // collect all divisions
		        divisionsList.Add(division);
		    }
		
		    // generate games for each division
		    foreach(List<String> divisionList in divisionsList)
		        divisionsGameList.Add(generateDivisionGames(divisionList));
		
		    // count games in divisions
		    foreach(List<List<String>> divisionGameList in divisionsGameList)
		        gamesCount += divisionGameList.Count;
		
		    // generate game plan over all divisonal games
		    querys.AddRange(generateGamePlan(divisionsGameList));
		
		    // insert field numbers into gameplan
		    querys.AddRange(insertFieldNr("vorrunde_spielplan"));
		
		    // insert field names
		    querys.AddRange(insertFieldNames("vorrunde_spielplan"));
		
		    // generate vorrunde divisions result tables
		    querys.AddRange(generateResultTables("vorrunde_erg_gr", divisionsList));
		
		    // execute all statements to database
		    writeListToDatabase(querys);
		}
		
		List<List<String>> generateDivisionGames(List<String> divisionList)
		{
			List<List<String>> result = new List<List<String>>();
		
		    switch(divisionList.Count)
		    {
		    	case 4: // 4 teams in division
		    		if(first)
			        {
			            foreach(List<int> game in firstFourMsDivision)
			            {
			            	if(game[0] != 999)
			            		result.Add(new List<String>() { divisionList[game[0]], divisionList[game[1]], divisionList[game[2]] });
			                else
			                	result.Add(new List<String>() { "---", "---", "---" });
			            }
			            first = false;
			        }
			        else
			        {
			            foreach(List<int> game in fourMsDivision)
			            {
			            	if(game[0] != 999)
			                    result.Add(new List<String>() { divisionList[game[0]], divisionList[game[1]], divisionList[game[2]] });
			                else
			                    result.Add(new List<String>() { "---", "---", "---" });
			            }
			            first = true;
			        }
			        
			    	break;
			    
			    case 5: // 5 teams in division
			    	foreach(List<int> game in fiveMsDivision)
		            	result.Add(new List<String>() { divisionList[game[0]], divisionList[game[1]], divisionList[game[2]] });
			    	
			    	break;
		    }
		
		    return result;
		}
		
		List<String> generateGamePlan(List<List<List<String>>> divisionsGameList)
		{
			List<String> querys = new List<String>();
		    int addzeit = ((base.satz * min) + pause) * 60;
		
		    for(int divisionCount = 0, rowCount = 1, dataRow = 0, roundCount = 1; rowCount <= gamesCount; divisionCount++)
		    {
		    	if(divisionCount >= divisionsGameList.Count)
		        {
		            divisionCount = 0;
		            dataRow++;
		            roundCount++;
		            startTurnier = startTurnier.AddSeconds(addzeit);
		        }
		
		    	if(dataRow < divisionsGameList[divisionCount].Count)
		        {
		        	List<List<String>> divisionGameList = divisionsGameList[divisionCount];
		        	querys.Add("INSERT INTO vorrunde_spielplan VALUES(" 
		        	           + rowCount + "," + roundCount + "," + rowCount 
		        	           + ",'" + startTurnier.ToString("hh:mm") + "',0,'','" 
		        	           + divisionGameList[dataRow][0]
		        	           + "','" + divisionGameList[dataRow][1]
		        	           + "','" + divisionGameList[dataRow][2]
		        	           + "',0,0,0,0,0,0)");
		            rowCount++;
		        }
		    }
		
		    return querys;
		}
	}
}
