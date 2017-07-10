/*
 * Created by SharpDevelop.
 * User: cfr
 * Date: 26.06.2017
 * Time: 15:46
 */
using System;
using System.Collections.Generic;

namespace volleyball
{
	public class InterimGames : BaseGameHandling
	{
		#region members
		DateTime startRound;
		bool first, vorplatzspiele;
	    int prefixCount, divisionCount, lastRoundNr, lastGameNr;
	    List<List<int>> firstFourMsDivision, fourMsDivision, fiveMsDivision;
		#endregion
		
		public InterimGames(Database db, List<String> grPrefix) : base(db, grPrefix)
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
		
		public void setParameters(String startRound, int pauseVrZw, int satz, int min, int pause,
                                 int fieldCount, int teamsCount, int divisionCount, List<String> fieldNames, int lastRoundNr, int lastGameNr,
                                 bool vorplatzspiele)
		{
		    Logging.write("ZWISCHENRUNDE: set zwischenrunde params");
		    
		    this.startRound = DateTime.Parse(startRound);
		    this.vorplatzspiele = vorplatzspiele;
		    this.divisionCount = divisionCount;
		    this.fieldNames = fieldNames;
		    this.lastGameNr = lastGameNr;
		    this.lastRoundNr = lastRoundNr;
		    this.startRound = DateTime.Parse(startRound);
		    		
		    this.startRound = this.startRound.AddSeconds(pauseVrZw * 60);
		    
		    setParameters(satz, min, pause, fieldCount, teamsCount, gamesCount, fieldNames);
		}
		
		public bool generateGames()
		{
			List<List<String>> divisionsList = new List<List<String>>();
			List<List<List<String>>> divisionsGameList = new List<List<List<String>>>();
			List<String> querys = new List<String>();
		
		    prefixCount = getPrefixCount();
		    gamesCount = 0;
		
		    divisionsList = generateNewDivisions();
		
		    if(divisionsList.Count == 0)
		        return false;
		
		    // generate games for each division
		    foreach(List<String> divisionList in divisionsList)
		        divisionsGameList.Add(generateDivisionGames(divisionList));
		
		    // count games in divisions
		    foreach(List<List<String>> divisionGameList in divisionsGameList)
		        gamesCount += divisionGameList.Count;
		
		    // generate game plan over all divisonal games
		    querys.AddRange(generateGamePlan(divisionsGameList));
		
		    // insert field numbers
		    querys.AddRange(insertFieldNr("zwischenrunde_spielplan"));
		
		    // insert field names
		    querys.AddRange(insertFieldNames("zwischenrunde_spielplan"));
		
		    // generate vorrunde divisions result tables
		    querys.AddRange(generateResultTables("zwischenrunde_erg_gr", divisionsList));
		
		    // execute all statements to database
		    writeListToDatabase(querys);
		
		    return true;
		}
		
		List<List<String>> sortList(List<List<String>> listSort)
		{
		    for(int x = listSort.Count - 1; x > 0; x--)
		    {
		        for (int y = 0; y < x; y++)
		        {
		        	if(BaseFunctions.parseToInt(listSort[y][1]) < BaseFunctions.parseToInt(listSort[y + 1][1]))
		            {
		        		List<String> saveList = listSort[y];
		        		listSort[y] = listSort[y + 1];
		                listSort[y + 1] = saveList;
		            }
		
		        	if(BaseFunctions.parseToInt(listSort[y][1]) == BaseFunctions.parseToInt(listSort[y + 1][1])
		        	   && BaseFunctions.parseToInt(listSort[y][2]) < BaseFunctions.parseToInt(listSort[y + 1][2]))
		            {
		                List<String> saveList = listSort[y];
		        		listSort[y] = listSort[y + 1];
		                listSort[y + 1] = saveList;
		            }
		        	else if(BaseFunctions.parseToInt(listSort[y][1]) == BaseFunctions.parseToInt(listSort[y + 1][1])
		        	        && BaseFunctions.parseToInt(listSort[y][2]) == BaseFunctions.parseToInt(listSort[y + 1][2])
		        	        && BaseFunctions.parseToInt(listSort[y][4]) > BaseFunctions.parseToInt(listSort[y + 1][4]))
		            {
		                List<String> saveList = listSort[y];
		        		listSort[y] = listSort[y + 1];
		                listSort[y + 1] = saveList;
		            }
		        }
		    }
		    
		    return listSort;
		}
		
		bool checkListDoubleResults(List<List<String>> list)
		{
			for(int i = 0; i < list.Count; i++)
		    {
				List<String> team1 = list[i];
		        for(int x = 0; x < list.Count; x++)
		        {
		        	List<String> team2 = list[x];
		        	if(team1[0] != team2[0])
		            {
		        		if(team1[1] == team2[1] && team1[2] == team2[2] && team1[4] == team2[4])
		                    return true;
		            }
		        }
		    }
			
		    return false;
		}
		
		List<List<String>> getDivisionsClassement(List<List<List<String>>> divisionsClassements, int rank)
		{
			List<List<String>> result = new List<List<String>>();
		
		    if(rank == 0)
		        return new List<List<String>>();
		
		    for(int i = 0; i < divisionsClassements.Count; i++)
		    	result.Add(divisionsClassements[i][rank - 1]);
		
		    return result;
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
		    int addzeit = ((base.satz * base.min) + base.pause) * 60;
		
		    for(int divisionCount = 0, rowCount = 1, dataRow = 0, roundCount = 1; rowCount <= gamesCount; divisionCount++)
		    {
		    	if(divisionCount >= divisionsGameList.Count)
		        {
		            divisionCount = 0;
		            dataRow++;
		            roundCount++;
		            startRound = startRound.AddSeconds(addzeit);
		        }
		
		    	if(dataRow < divisionsGameList[divisionCount].Count)
		        {
		        	List<List<String>> divisionGameList = divisionsGameList[divisionCount];
		        	querys.Add("INSERT INTO zwischenrunde_spielplan VALUES(" 
		        	           + rowCount + "," + roundCount + "," + rowCount 
		        	           + ",'" + startRound.ToString("hh:mm") + "',0,'','" 
		        	           + divisionGameList[dataRow][0]
		        	           + "','" + divisionGameList[dataRow][1]
		        	           + "','" + divisionGameList[dataRow][2]
		        	           + "',0,0,0,0,0,0)");
		            rowCount++;
		        }
		    }
		
		    return querys;
		}
		
		List<String> getTeamList(List<List<String>> teamsDivisions)
		{
			List<String> result = new List<String>();
		
		    for(int i = 0; i < teamsDivisions.Count; i++)
		    	result.Add(teamsDivisions[i][0]);
		
		    return result;
		}
		
		List<List<String>> generateNewDivisions()
		{
		    // help lists
		    List<List<String>> divisionsFirst, divisionsSecond, divisionsThird, divisionsFourth, divisionsFifth;
		    List<String> divisionsFirstNames, divisionsSecondNames, divisionsThirdNames, divisionsFourthNames, divisionsFifthNames;
		
		    // get list current ranking results
		    List<List<List<String>>> resultDivisionsVr = new List<List<List<String>>>();
		
		    // new list for new divisions by rank result
		    List<List<String>> newDivisionsZw = new List<List<String>>();
		
		    // read divisional rank results and add to list
		    for(int i = 0; i < divisionCount; i++)
		        resultDivisionsVr.Add(readListFromDatabase("select ms, punkte, satz, intern, extern from vorrunde_erg_gr" + getPrefix(i) + " order by punkte desc, satz desc, intern asc"));
		
		    divisionsFirst = getDivisionsClassement(resultDivisionsVr, 1);
		    divisionsSecond = getDivisionsClassement(resultDivisionsVr, 2);
		    divisionsThird = getDivisionsClassement(resultDivisionsVr, 3);
		    divisionsFourth = getDivisionsClassement(resultDivisionsVr, 4);
		    divisionsFifth = getDivisionsClassement(resultDivisionsVr, 5);
		
		    Logging.write("INFO: teams count=" + teamsCount + ", vorplatzspiel=" + vorplatzspiele);
		
		    if(!vorplatzspiele)
		    {
		        switch(teamsCount)
		        {
		            case 20:
		                // make ranking of all divisions thrid teams
		                divisionsThird = sortList(divisionsThird);
		
		                if(checkListDoubleResults(divisionsThird))
		                	return new List<List<String>>();
		
		                divisionsFirstNames = getTeamList(divisionsFirst);
		                divisionsSecondNames = getTeamList(divisionsSecond);
		                divisionsThirdNames = getTeamList(divisionsThird);
		                divisionsFourthNames = getTeamList(divisionsFourth);
		                divisionsFifthNames = getTeamList(divisionsFifth);
		
		                // create divisions with max 5 teams from helpList(can contain teams up to 6)
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[0],
		                                   						divisionsFirstNames[1],
		                                   						divisionsSecondNames[2],
		                                   						divisionsSecondNames[3],
		                                   						divisionsThirdNames[0]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[0],
		                                   						divisionsSecondNames[1],
		                                   						divisionsFirstNames[2],
		                                   						divisionsFirstNames[3],
		                                   						divisionsThirdNames[1]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsThirdNames[2],
		                                   						divisionsFourthNames[0],
		                                   						divisionsFourthNames[1],
		                                   						divisionsFifthNames[2],
		                                   						divisionsFifthNames[3]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsThirdNames[3],
		                                   						divisionsFifthNames[0],
		                                   						divisionsFifthNames[1],
		                                   						divisionsFourthNames[2],
		                                   						divisionsFourthNames[3]});
		                break;
		
		            case 25:
		                divisionsFirstNames = getTeamList(divisionsFirst);
		                divisionsSecondNames = getTeamList(divisionsSecond);
		                divisionsThirdNames = getTeamList(divisionsThird);
		                divisionsFourthNames = getTeamList(divisionsFourth);
		                divisionsFifthNames = getTeamList(divisionsFifth);
		
		                newDivisionsZw.Add(divisionsFirstNames);
		                newDivisionsZw.Add(divisionsSecondNames);
		                newDivisionsZw.Add(divisionsThirdNames);
		                newDivisionsZw.Add(divisionsFourthNames);
		                newDivisionsZw.Add(divisionsFifthNames);
		                break;
		
		            case 28:
		                // make ranking of all divisions second teams
		                divisionsSecond = sortList(divisionsSecond);
		
		                if(checkListDoubleResults(divisionsSecond))
		                    return new List<List<String>>();
		
		                divisionsFirstNames = getTeamList(divisionsFirst);
		                divisionsSecondNames = getTeamList(divisionsSecond);
		                divisionsThirdNames = getTeamList(divisionsThird);
		                divisionsFourthNames = getTeamList(divisionsFourth);
		                divisionsFifthNames = getTeamList(divisionsFifth);
		
		                // create divisions with max 5 teams from helpList(can contain teams up to 6)
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[0],
		                                   						divisionsFirstNames[1],
		                                   						divisionsFirstNames[2],
		                                   						divisionsSecondNames[0]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[3],
		                                   						divisionsFirstNames[4],
		                                   						divisionsFirstNames[5],
		                                   						divisionsSecondNames[1]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[2],
		                                   						divisionsSecondNames[5],
		                                   						divisionsThirdNames[0],
		                                   						divisionsThirdNames[1],
		                                   						divisionsThirdNames[2]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[3],
		                                   						divisionsSecondNames[4],
		                                   						divisionsThirdNames[3],
		                                   						divisionsThirdNames[4],
		                                   						divisionsThirdNames[5]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFourthNames[0],
		                                   						divisionsFourthNames[1],
		                                   						divisionsFourthNames[2],
		                                   						divisionsFifthNames[2],
		                                   						divisionsFifthNames[3]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFourthNames[3],
		                                   						divisionsFourthNames[4],
		                                   						divisionsFourthNames[5],
		                                   						divisionsFifthNames[0],
		                                   						divisionsFifthNames[1]});
		                break;
		
		            case 30:
		                // make ranking of all divisions second teams
		                divisionsSecond = sortList(divisionsSecond);
		
		                if(checkListDoubleResults(divisionsSecond))
		                    return new List<List<String>>();
		
		                // make ranking of all divisions fourth teams
		                divisionsFourth = sortList(divisionsFourth);
		
		                if(checkListDoubleResults(divisionsFourth))
		                    return new List<List<String>>();
		
		                divisionsFirstNames = getTeamList(divisionsFirst);
		                divisionsSecondNames = getTeamList(divisionsSecond);
		                divisionsThirdNames = getTeamList(divisionsThird);
		                divisionsFourthNames = getTeamList(divisionsFourth);
		                divisionsFifthNames = getTeamList(divisionsFifth);
		
		                // create divisions with max 5 teams from helpList(can contain teams up to 6)
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[0],
		                                   						divisionsFirstNames[1],
		                                   						divisionsFirstNames[2],
		                                   						divisionsSecondNames[0],
		                                   						divisionsSecondNames[3]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[3],
		                                   						divisionsFirstNames[4],
		                                   						divisionsFirstNames[5],
		                                   						divisionsSecondNames[1],
		                                   						divisionsSecondNames[2]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[4],
		                                   						divisionsThirdNames[0],
		                                   						divisionsThirdNames[1],
		                                   						divisionsThirdNames[2],
		                                   						divisionsFourthNames[1]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[5],
		                                   						divisionsThirdNames[3],
		                                   						divisionsThirdNames[4],
		                                   						divisionsThirdNames[5],
		                                   						divisionsFourthNames[0]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFourthNames[2],
		                                   						divisionsFourthNames[5],
		                                   						divisionsFifthNames[0],
		                                   						divisionsFifthNames[1],
		                                   						divisionsFifthNames[2]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFourthNames[3],
		                                   						divisionsFourthNames[4],
		                                   						divisionsFifthNames[3],
		                                   						divisionsFifthNames[4],
		                                   						divisionsFifthNames[5]});
		                break;
		
		            case 35:
		                // make ranking of all divisions second teams
		                divisionsSecond = sortList(divisionsSecond);
		
		                if(checkListDoubleResults(divisionsFourth))
		                    return new List<List<String>>();
		
		                // make ranking of all divisions third teams
		                divisionsThird = sortList(divisionsThird);
		
		                if(checkListDoubleResults(divisionsThird))
		                    return new List<List<String>>();
		
		                // make ranking of all divisions fourth teams
		                divisionsFourth = sortList(divisionsFourth);
		
		                if(checkListDoubleResults(divisionsFourth))
		                    return new List<List<String>>();
		
		                // make ranking of all divisions fifth teams
		                divisionsFifth = sortList(divisionsFifth);
		
		                if(checkListDoubleResults(divisionsFifth))
		                    return new List<List<String>>();
		
		                // get team names from divisions
		                divisionsFirstNames = getTeamList(divisionsFirst);
		                divisionsSecondNames = getTeamList(divisionsSecond);
		                divisionsThirdNames = getTeamList(divisionsThird);
		                divisionsFourthNames = getTeamList(divisionsFourth);
		                divisionsFifthNames = getTeamList(divisionsFifth);
		
		                // create divisions with max 5 teams from helpList(can contain teams up to 6)
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[0],
		                                   						divisionsFirstNames[1],
		                                   						divisionsFirstNames[2],
		                                   						divisionsFirstNames[3],
		                                   						divisionsSecondNames[1]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[4],
		                                   						divisionsFirstNames[5],
		                                   						divisionsFirstNames[6],
		                                   						divisionsSecondNames[0],
		                                   						divisionsSecondNames[2]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[3],
							                                   	divisionsSecondNames[5],
							                                   	divisionsThirdNames[0],
							                                   	divisionsThirdNames[2],
							                                   	divisionsThirdNames[4]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[4],
		                                   						divisionsSecondNames[6],
		                                   						divisionsThirdNames[1],
		                                   						divisionsThirdNames[3],
		                                   						divisionsThirdNames[5]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsThirdNames[6],
		                                   						divisionsFourthNames[1],
		                                   						divisionsFourthNames[3],
		                                   						divisionsFourthNames[5],
		                                   						divisionsFifthNames[0]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFourthNames[0],
		                                   						divisionsFourthNames[2],
		                                   						divisionsFourthNames[4],
		                                   						divisionsFourthNames[6],
		                                   						divisionsFifthNames[1]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFifthNames[2],
		                                   						divisionsFifthNames[3],
		                                   						divisionsFifthNames[4],
		                                   						divisionsFifthNames[5],
		                                   						divisionsFifthNames[6]});
		                break;
		
		            case 40:
		                // make ranking of all divisions second teams
		                divisionsSecond = sortList(divisionsSecond);
		
		                if(checkListDoubleResults(divisionsSecond))
		                    return new List<List<String>>();
		
		                // make ranking of all divisions third teams
		                divisionsThird = sortList(divisionsThird);
		
		                if(checkListDoubleResults(divisionsThird))
		                    return new List<List<String>>();
		
		                // make ranking of all divisions fourth teams
		                divisionsFourth = sortList(divisionsFourth);
		
		                if(checkListDoubleResults(divisionsFourth))
		                    return new List<List<String>>();
		
		                // make ranking of all divisions fifth teams
		                divisionsFifth = sortList(divisionsFifth);
		
		                if(checkListDoubleResults(divisionsFifth))
		                    return new List<List<String>>();
		
		                // get team names from divisions
		                divisionsFirstNames = getTeamList(divisionsFirst);
		                divisionsSecondNames = getTeamList(divisionsSecond);
		                divisionsThirdNames = getTeamList(divisionsThird);
		                divisionsFourthNames = getTeamList(divisionsFourth);
		                divisionsFifthNames = getTeamList(divisionsFifth);
		
		                // create divisions with max 5 teams from helpList(can contain teams up to 5)
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[0],
		                                   						divisionsFirstNames[1],
		                                   						divisionsFirstNames[2],
		                                   						divisionsFirstNames[3],
		                                   						divisionsSecondNames[0]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[4],
		                                   						divisionsFirstNames[5],
		                                   						divisionsFirstNames[6],
		                                   						divisionsFirstNames[7],
		                                   						divisionsSecondNames[1]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[2],
		                                   						divisionsSecondNames[3],
		                                   						divisionsSecondNames[4],
		                                   						divisionsThirdNames[0],
		                                   						divisionsThirdNames[2]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[5],
		                                   						divisionsSecondNames[6],
		                                   						divisionsSecondNames[7],
		                                   						divisionsThirdNames[1],
		                                   						divisionsThirdNames[3]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsThirdNames[4],
		                                   						divisionsThirdNames[6],
		                                   						divisionsFourthNames[0],
		                                   						divisionsFourthNames[2],
		                                   						divisionsFourthNames[4]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsThirdNames[5],
		                                   						divisionsThirdNames[7],
		                                   						divisionsFourthNames[1],
		                                   						divisionsFourthNames[3],
		                                   						divisionsFourthNames[5]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFourthNames[6],
		                                   						divisionsFifthNames[0],
		                                   						divisionsFifthNames[2],
		                                   						divisionsFifthNames[4],
		                                   						divisionsFifthNames[6]});
		                                        
		                newDivisionsZw.Add(new List<String>() { divisionsFourthNames[7],
		                                   						divisionsFifthNames[1],
		                                   						divisionsFifthNames[3],
		                                   						divisionsFifthNames[5],
		                                   						divisionsFifthNames[7]});
		                break;
		
		            case 45:
		                // make ranking of all divisions second teams
		                divisionsSecond = sortList(divisionsSecond);
		
		                if(checkListDoubleResults(divisionsSecond))
		                    return new List<List<String>>();
		
		                // make ranking of all divisions third teams
		                divisionsThird = sortList(divisionsThird);
		
		                if(checkListDoubleResults(divisionsThird))
		                    return new List<List<String>>();
		
		                // make ranking of all divisions fourth teams
		                divisionsFourth = sortList(divisionsFourth);
		
		                if(checkListDoubleResults(divisionsFourth))
		                    return new List<List<String>>();
		
		                // make ranking of all divisions fifth teams
		                divisionsFifth = sortList(divisionsFifth);
		
		                if(checkListDoubleResults(divisionsFifth))
		                    return new List<List<String>>();
		
		                // get team names from divisions
		                divisionsFirstNames = getTeamList(divisionsFirst);
		                divisionsSecondNames = getTeamList(divisionsSecond);
		                divisionsThirdNames = getTeamList(divisionsThird);
		                divisionsFourthNames = getTeamList(divisionsFourth);
		                divisionsFifthNames = getTeamList(divisionsFifth);
		
		                // create divisions with max 5 teams from helpList(can contain teams up to 5)
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[0],
		                                   						divisionsFirstNames[1],
		                                   						divisionsFirstNames[2],
		                                   						divisionsFirstNames[3],
		                                   						divisionsFirstNames[4]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[5],
		                                   						divisionsFirstNames[6],
		                                   						divisionsFirstNames[7],
		                                   						divisionsFirstNames[8],
		                                   						divisionsSecondNames[0]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[1],
		                                   						divisionsSecondNames[2],
		                                   						divisionsSecondNames[3],
		                                   						divisionsSecondNames[4],
		                                   						divisionsThirdNames[0]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[5],
		                                   						divisionsSecondNames[6],
		                                   						divisionsSecondNames[7],
		                                   						divisionsSecondNames[8],
		                                   						divisionsThirdNames[1]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsThirdNames[2],
		                                   						divisionsThirdNames[4],
		                                   						divisionsThirdNames[6],
		                                   						divisionsThirdNames[8],
		                                   						divisionsFourthNames[0]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsThirdNames[3],
		                                   						divisionsThirdNames[5],
		                                   						divisionsThirdNames[7],
		                                   						divisionsFourthNames[1],
		                                   						divisionsFourthNames[2]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFourthNames[4],
		                                   						divisionsFourthNames[6],
		                                   						divisionsFourthNames[8],
		                                   						divisionsFifthNames[0],
		                                   						divisionsFifthNames[2]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFourthNames[3],
		                                   						divisionsFourthNames[5],
		                                   						divisionsFourthNames[7],
		                                   						divisionsFifthNames[1],
		                                   						divisionsFifthNames[3]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFifthNames[4],
		                                   						divisionsFifthNames[5],
		                                   						divisionsFifthNames[6],
		                                   						divisionsFifthNames[7],
		                                   						divisionsFifthNames[8]});
		                break;
		
		            case 50:
		                // get team names from divisions
		                divisionsFirstNames = getTeamList(divisionsFirst);
		                divisionsSecondNames = getTeamList(divisionsSecond);
		                divisionsThirdNames = getTeamList(divisionsThird);
		                divisionsFourthNames = getTeamList(divisionsFourth);
		                divisionsFifthNames = getTeamList(divisionsFifth);
		
		                // create divisions with max 5 teams from helpList(can contain teams up to 5)
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[0],
		                                   						divisionsFirstNames[1],
		                                   						divisionsFirstNames[2],
		                                   						divisionsFirstNames[3],
		                                   						divisionsFirstNames[4]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[5],
		                                   						divisionsFirstNames[6],
		                                   						divisionsFirstNames[7],
		                                   						divisionsFirstNames[8],
		                                   						divisionsFirstNames[9]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[0],
		                                   						divisionsSecondNames[1],
		                                   						divisionsSecondNames[2],
		                                   						divisionsSecondNames[3],
		                                   						divisionsSecondNames[4]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[5],
		                                   						divisionsSecondNames[6],
		                                   						divisionsSecondNames[7],
		                                   						divisionsSecondNames[8],
		                                   						divisionsSecondNames[9]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsThirdNames[0],
		                                   						divisionsThirdNames[1],
		                                   						divisionsThirdNames[2],
		                                   						divisionsThirdNames[3],
		                                   						divisionsThirdNames[4]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsThirdNames[5],
		                                   						divisionsThirdNames[6],
		                                   						divisionsThirdNames[7],
		                                   						divisionsThirdNames[8],
		                                   						divisionsThirdNames[9]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFourthNames[0],
		                                   						divisionsFourthNames[1],
		                                   						divisionsFourthNames[2],
		                                   						divisionsFourthNames[3],
		                                   						divisionsFourthNames[4]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFourthNames[5],
		                                   						divisionsFourthNames[6],
		                                   						divisionsFourthNames[7],
		                                   						divisionsFourthNames[8],
		                                   						divisionsFourthNames[9]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFifthNames[0],
		                                   						divisionsFifthNames[1],
		                                   						divisionsFifthNames[2],
		                                   						divisionsFifthNames[3],
		                                   						divisionsFifthNames[4]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFifthNames[5],
		                                   						divisionsFifthNames[6],
		                                   						divisionsFifthNames[7],
		                                   						divisionsFifthNames[8],
		                                   						divisionsFifthNames[9]});
		                break;
		
		            case 55:
		                // make ranking of all divisions second teams
		                divisionsFirst = sortList(divisionsFirst);
		
		                if(checkListDoubleResults(divisionsFirst))
		                    return new List<List<String>>();
		
		                // make ranking of all divisions second teams
		                divisionsSecond = sortList(divisionsSecond);
		
		                if(checkListDoubleResults(divisionsSecond))
		                    return new List<List<String>>();
		
		                // make ranking of all divisions third teams
		                divisionsThird = sortList(divisionsThird);
		
		                if(checkListDoubleResults(divisionsThird))
		                    return new List<List<String>>();
		
		                // make ranking of all divisions fourth teams
		                divisionsFourth = sortList(divisionsFourth);
		
		                if(checkListDoubleResults(divisionsFourth))
		                    return new List<List<String>>();
		
		                // make ranking of all divisions fifth teams
		                divisionsFifth = sortList(divisionsFifth);
		
		                if(checkListDoubleResults(divisionsFifth))
		                    return new List<List<String>>();
		
		                // get team names from divisions
		                divisionsFirstNames = getTeamList(divisionsFirst);
		                divisionsSecondNames = getTeamList(divisionsSecond);
		                divisionsThirdNames = getTeamList(divisionsThird);
		                divisionsFourthNames = getTeamList(divisionsFourth);
		                divisionsFifthNames = getTeamList(divisionsFifth);
		
		                // profi
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[0],
		                                   						divisionsFirstNames[2],
		                                   						divisionsFirstNames[4],
		                                   						divisionsFirstNames[6],
		                                   						divisionsFirstNames[8]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[1],
		                                   						divisionsFirstNames[3],
		                                   						divisionsFirstNames[5],
		                                   						divisionsFirstNames[7],
		                                   						divisionsFirstNames[9]});
		
		                // hobby a
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[10],
		                                   						divisionsSecondNames[0],
		                                   						divisionsSecondNames[2],
		                                   						divisionsSecondNames[4],
		                                   						divisionsSecondNames[6]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[1],
		                                   						divisionsSecondNames[3],
		                                   						divisionsSecondNames[5],
		                                   						divisionsSecondNames[7],
		                                   						divisionsSecondNames[8]});
		
		                // hobby b
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[9],
		                                   						divisionsThirdNames[0],
		                                   						divisionsThirdNames[2],
		                                   						divisionsThirdNames[4],
		                                   						divisionsThirdNames[6]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[10],
		                                   						divisionsThirdNames[1],
		                                   						divisionsThirdNames[3],
		                                   						divisionsThirdNames[5],
		                                   						divisionsThirdNames[7]});
		
		                // hobby c
		                newDivisionsZw.Add(new List<String>() { divisionsThirdNames[8],
		                                   						divisionsThirdNames[10],
		                                   						divisionsFourthNames[0],
		                                   						divisionsFourthNames[2],
		                                   						divisionsFourthNames[4]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsThirdNames[9],
		                                   						divisionsFourthNames[1],
		                                   						divisionsFourthNames[3],
		                                   						divisionsFourthNames[5],
		                                   						divisionsFourthNames[6]});
		
		                // hobby d
		                newDivisionsZw.Add(new List<String>() { divisionsFourthNames[8],
		                                   						divisionsFourthNames[10],
		                                   						divisionsFifthNames[0],
		                                   						divisionsFifthNames[2],
		                                   						divisionsFifthNames[4]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFourthNames[7],
		                                   						divisionsFourthNames[9],
		                                   						divisionsFifthNames[1],
		                                   						divisionsFifthNames[3],
		                                   						divisionsFifthNames[5]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFifthNames[6],
		                                   						divisionsFifthNames[7],
		                                   						divisionsFifthNames[8],
		                                   						divisionsFifthNames[9],
		                                   						divisionsFifthNames[10]});
		                break;
		
		            case 60:
		                // make ranking of all divisions second teams
		                divisionsSecond = sortList(divisionsSecond);
		
		                if(checkListDoubleResults(divisionsSecond))
		                    return new List<List<String>>();
		
		                // make ranking of all divisions third teams
		                divisionsThird = sortList(divisionsThird);
		
		                if(checkListDoubleResults(divisionsThird))
		                    return new List<List<String>>();
		
		                // make ranking of all divisions fourth teams
		                divisionsFourth = sortList(divisionsFourth);
		
		                if(checkListDoubleResults(divisionsFourth))
		                    return new List<List<String>>();
		
		                // make ranking of all divisions fifth teams
		                divisionsFifth = sortList(divisionsFifth);
		
		                if(checkListDoubleResults(divisionsFifth))
		                    return new List<List<String>>();
		
		                // get team names from divisions
		                divisionsFirstNames = getTeamList(divisionsFirst);
		                divisionsSecondNames = getTeamList(divisionsSecond);
		                divisionsThirdNames = getTeamList(divisionsThird);
		                divisionsFourthNames = getTeamList(divisionsFourth);
		                divisionsFifthNames = getTeamList(divisionsFifth);
		
		                // profi
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[0],
		                                   						divisionsFirstNames[1],
		                                   						divisionsFirstNames[2],
		                                   						divisionsFirstNames[3],
		                                   						divisionsFirstNames[4]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[5],
		                                   						divisionsFirstNames[6],
		                                   						divisionsFirstNames[7],
		                                   						divisionsFirstNames[8],
		                                   						divisionsFirstNames[9]});
		
		                // hobby a
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[10],
		                                   						divisionsSecondNames[0],
		                                   						divisionsSecondNames[1],
		                                   						divisionsSecondNames[2],
		                                   						divisionsSecondNames[3]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[11],
		                                   						divisionsSecondNames[4],
		                                   						divisionsSecondNames[5],
		                                   						divisionsSecondNames[6],
		                                   						divisionsSecondNames[7]});
		
		                // hobby b
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[8],
		                                   						divisionsSecondNames[9],
		                                   						divisionsThirdNames[0],
		                                   						divisionsThirdNames[2],
		                                   						divisionsThirdNames[4]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[10],
		                                   						divisionsSecondNames[11],
		                                   						divisionsThirdNames[1],
		                                   						divisionsThirdNames[3],
		                                   						divisionsThirdNames[5]});
		
		                // hobby c
		                newDivisionsZw.Add(new List<String>() { divisionsThirdNames[6],
		                                   						divisionsThirdNames[8],
		                                   						divisionsThirdNames[10],
		                                   						divisionsFourthNames[0],
		                                   						divisionsFourthNames[1]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsThirdNames[7],
		                                   						divisionsThirdNames[9],
		                                   						divisionsThirdNames[11],
		                                   						divisionsFourthNames[2],
		                                   						divisionsFourthNames[3]});
		
		                // hobby d
		                newDivisionsZw.Add(new List<String>() { divisionsFourthNames[4],
		                                   						divisionsFourthNames[6],
		                                   						divisionsFourthNames[8],
		                                   						divisionsFourthNames[10],
		                                   						divisionsFifthNames[0]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFourthNames[5],
		                                   						divisionsFourthNames[7],
		                                   						divisionsFourthNames[9],
		                                   						divisionsFourthNames[11],
		                                   						divisionsFifthNames[1]});
		
		                // hobby e
		                newDivisionsZw.Add(new List<String>() { divisionsFifthNames[2],
		                                   						divisionsFifthNames[4],
		                                   						divisionsFifthNames[6],
		                                   						divisionsFifthNames[8],
		                                   						divisionsFifthNames[10]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFifthNames[3],
		                                   						divisionsFifthNames[5],
		                                   						divisionsFifthNames[7],
		                                   						divisionsFifthNames[9],
		                                   						divisionsFifthNames[11]});
		
		                break;
		
		            default: Logging.write("ZWISCHENRUNDE_ERROR: team count not correct");
		            	break;
		        }
		    }
		    else
		    {
		        switch(teamsCount)
		        {
		            case 50:
		                // get team names from divisions
		                divisionsFirstNames = getTeamList(divisionsFirst);
		                divisionsSecondNames = getTeamList(divisionsSecond);
		                divisionsThirdNames = getTeamList(divisionsThird);
		                divisionsFourthNames = getTeamList(divisionsFourth);
		                divisionsFifthNames = getTeamList(divisionsFifth);
		
		                // profi
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[0],
		                                   						divisionsFirstNames[1],
		                                   						divisionsSecondNames[2],
		                                   						divisionsSecondNames[3],
		                                   						divisionsSecondNames[4]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[2],
		                                   						divisionsFirstNames[3],
		                                   						divisionsSecondNames[5],
		                                   						divisionsSecondNames[6],
		                                   						divisionsSecondNames[7]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[4],
		                                   						divisionsFirstNames[5],
		                                   						divisionsFirstNames[6],
		                                   						divisionsSecondNames[8],
		                                   						divisionsSecondNames[9]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[7],
		                                   						divisionsFirstNames[8],
		                                   						divisionsFirstNames[9],
		                                   						divisionsSecondNames[0],
		                                   						divisionsSecondNames[1]});
		
		                // hobby a
		                newDivisionsZw.Add(new List<String>() { divisionsThirdNames[0],
		                                   						divisionsThirdNames[1],
		                                   						divisionsFourthNames[2],
		                                   						divisionsFourthNames[3],
		                                   						divisionsFourthNames[4]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsThirdNames[2],
		                                   						divisionsThirdNames[3],
		                                   						divisionsFourthNames[5],
		                                   						divisionsFourthNames[6],
		                                   						divisionsFourthNames[7]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsThirdNames[4],
		                                   						divisionsThirdNames[5],
		                                   						divisionsThirdNames[6],
		                                   						divisionsFourthNames[8],
		                                   						divisionsFourthNames[9]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsThirdNames[7],
		                                   						divisionsThirdNames[8],
		                                   						divisionsThirdNames[9],
		                                   						divisionsFourthNames[0],
		                                   						divisionsFourthNames[1]});
		
		                // hobby b
		                newDivisionsZw.Add(new List<String>() { divisionsFifthNames[0],
		                                   						divisionsFifthNames[1],
		                                   						divisionsFifthNames[2],
		                                   						divisionsFifthNames[3],
		                                   						divisionsFifthNames[4]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFifthNames[5],
		                                   						divisionsFifthNames[6],
		                                   						divisionsFifthNames[7],
		                                   						divisionsFifthNames[8],
		                                   						divisionsFifthNames[9]});
		                break;
		
		            case 55:
		                // make ranking of all divisions second teams
		                divisionsSecond = sortList(divisionsSecond);
		
		                if(checkListDoubleResults(divisionsSecond))
		                    return new List<List<String>>();
		
		                // make ranking of all divisions second teams
		                divisionsFourth = sortList(divisionsFourth);
		
		                if(checkListDoubleResults(divisionsFourth))
		                    return new List<List<String>>();
		
		                // make ranking of all divisions second teams
		                divisionsFifth = sortList(divisionsFifth);
		
		                if(checkListDoubleResults(divisionsFifth))
		                    return new List<List<String>>();
		
		                // get team names from divisions
		                divisionsFirstNames = getTeamList(divisionsFirst);
		                divisionsSecondNames = getTeamList(divisionsSecond);
		                divisionsThirdNames = getTeamList(divisionsThird);
		                divisionsFourthNames = getTeamList(divisionsFourth);
		                divisionsFifthNames = getTeamList(divisionsFifth);
		
		                // profi
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[0],
		                                   						divisionsFirstNames[1],
		                                   						divisionsFirstNames[2],
		                                   						divisionsSecondNames[3],
		                                   						divisionsSecondNames[7]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[3],
		                                   						divisionsFirstNames[4],
		                                   						divisionsFirstNames[5],
		                                   						divisionsSecondNames[2],
		                                   						divisionsSecondNames[6]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[6],
		                                   						divisionsFirstNames[7],
		                                   						divisionsFirstNames[8],
		                                   						divisionsSecondNames[1],
		                                   						divisionsSecondNames[5]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[9],
		                                   						divisionsFirstNames[10],
		                                   						divisionsSecondNames[0],
		                                   						divisionsSecondNames[4],
		                                   						divisionsSecondNames[8]});
		
		                // hobby a
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[9],
		                                   						divisionsThirdNames[6],
		                                   						divisionsThirdNames[7],
		                                   						divisionsThirdNames[8],
		                                   						divisionsFourthNames[6]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[10],
		                                   						divisionsThirdNames[9],
		                                   						divisionsThirdNames[10],
		                                   						divisionsFourthNames[0],
		                                   						divisionsFourthNames[5]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsThirdNames[0],
		                                   						divisionsThirdNames[1],
		                                   						divisionsThirdNames[2],
		                                   						divisionsFourthNames[1],
		                                   						divisionsFourthNames[4]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsThirdNames[3],
		                                   						divisionsThirdNames[4],
		                                   						divisionsThirdNames[5],
		                                   						divisionsFourthNames[2],
		                                   						divisionsFourthNames[3]});
		
		                // hobby b
		                newDivisionsZw.Add(new List<String>() { divisionsFourthNames[7],
		                                   						divisionsFourthNames[10],
		                                   						divisionsFifthNames[0],
		                                   						divisionsFifthNames[3],
		                                   						divisionsFifthNames[4]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFourthNames[8],
		                                   						divisionsFourthNames[9],
		                                   						divisionsFifthNames[1],
		                                   						divisionsFifthNames[2],
		                                   						divisionsFifthNames[5]});
		
		                // hobby c
		                newDivisionsZw.Add(new List<String>() { divisionsFifthNames[6],
		                                   						divisionsFifthNames[7],
		                                   						divisionsFifthNames[8],
		                                   						divisionsFifthNames[9],
		                                   						divisionsFifthNames[10]});
		
		                break;
		
		            case 60:
		                // make ranking of all divisions second teams
		                divisionsSecond = sortList(divisionsSecond);
		
		                if(checkListDoubleResults(divisionsSecond))
		                    return new List<List<String>>();
		
		                // make ranking of all divisions second teams
		                divisionsFourth = sortList(divisionsFourth);
		
		                if(checkListDoubleResults(divisionsFourth))
		                    return new List<List<String>>();
		
		                // get team names from divisions
		                divisionsFirstNames = getTeamList(divisionsFirst);
		                divisionsSecondNames = getTeamList(divisionsSecond);
		                divisionsThirdNames = getTeamList(divisionsThird);
		                divisionsFourthNames = getTeamList(divisionsFourth);
		                divisionsFifthNames = getTeamList(divisionsFifth);
		
		                // profi
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[0],
		                                   						divisionsFirstNames[1],
		                                   						divisionsFirstNames[2],
		                                   						divisionsSecondNames[0],
		                                   						divisionsSecondNames[7]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[3],
		                                   						divisionsFirstNames[4],
		                                   						divisionsFirstNames[5],
		                                   						divisionsSecondNames[1],
		                                   						divisionsSecondNames[6]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[6],
		                                   						divisionsFirstNames[7],
		                                   						divisionsFirstNames[8],
		                                   						divisionsSecondNames[2],
		                                   						divisionsSecondNames[5]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFirstNames[9],
		                                   						divisionsFirstNames[10],
		                                   						divisionsFirstNames[11],
		                                   						divisionsSecondNames[3],
		                                   						divisionsSecondNames[4]});
		
		                // hobby a
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[8],
		                                   						divisionsThirdNames[0],
		                                   						divisionsThirdNames[1],
		                                   						divisionsThirdNames[2],
		                                   						divisionsFourthNames[3]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[9],
		                                   						divisionsThirdNames[3],
		                                   						divisionsThirdNames[4],
		                                   						divisionsThirdNames[5],
		                                   						divisionsFourthNames[2]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[10],
		                                   						divisionsThirdNames[6],
		                                   						divisionsThirdNames[7],
		                                   						divisionsThirdNames[8],
		                                   						divisionsFourthNames[1]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsSecondNames[11],
		                                   						divisionsThirdNames[9],
		                                   						divisionsThirdNames[10],
		                                   						divisionsThirdNames[11],
		                                   						divisionsFourthNames[0]});
		
		                // hobby b
		                newDivisionsZw.Add(new List<String>() { divisionsFourthNames[4],
		                                   						divisionsFourthNames[11],
		                                   						divisionsFifthNames[0],
		                                   						divisionsFifthNames[1],
		                                   						divisionsFifthNames[2]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFourthNames[5],
		                                   						divisionsFourthNames[10],
		                                   						divisionsFifthNames[3],
		                                   						divisionsFifthNames[4],
		                                   						divisionsFifthNames[5]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFourthNames[6],
		                                   						divisionsFourthNames[9],
		                                   						divisionsFifthNames[6],
		                                   						divisionsFifthNames[7],
		                                   						divisionsFifthNames[8]});
		
		                newDivisionsZw.Add(new List<String>() { divisionsFourthNames[7],
		                                   						divisionsFourthNames[8],
		                                   						divisionsFifthNames[9],
		                                   						divisionsFifthNames[10],
		                                   						divisionsFifthNames[11]});
		                break;
		
		            default: Logging.write("ZWISCHENRUNDE_ERROR: team count not correct");
		            	break;
		        }
		    }
		
		    return newDivisionsZw;
		}
	}
}
