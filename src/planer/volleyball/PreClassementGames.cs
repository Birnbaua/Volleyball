/*
 * Created by SharpDevelop.
 * User: cfr
 * Date: 30.06.2017
 * Time: 09:53
 */
using System;
using System.Collections.Generic;

namespace volleyball
{
	public class PreClassementGames : BaseGameHandling
	{
		#region
		DateTime startRound;
		bool vorplatzspiele;
	    int prefixCount, divisionCount, lastRoundNr, lastGameNr;
		#endregion
		
		public PreClassementGames(Database db, List<String> grPrefix) : base(db, grPrefix)
		{
		}
		
		public void setParameters(String startRound, int lastgameTime, int pauseZwKr, int countSatz, int minSatz, int minPause,
                               int fieldCount, int teamsCount, int divisionCount, List<String> fieldNames, 
                               int lastRoundNr, int lastGameNr, bool vorplatzspiele)
		{
		    Logging.write("KREUZSPIELE: set platzspiele params");
		    this.startRound = DateTime.Parse(startRound);
		    this.vorplatzspiele = vorplatzspiele;
		    this.divisionCount = divisionCount;
		    this.fieldNames = fieldNames;
		    this.lastGameNr = lastGameNr;
		    this.lastRoundNr = lastRoundNr;
		    this.startRound = DateTime.Parse(startRound);
		    		
		    this.startRound = this.startRound.AddSeconds(pauseZwKr * 60);
		    
		    setParameters(satz, min, pause, fieldCount, teamsCount, gamesCount, fieldNames);
		}
		
		public void generatePreClassement()
		{
			List<String> querys = new List<String>();
		
		    prefixCount = getPrefixCount();
		    gamesCount = 0;
		
		    querys.AddRange(generateGamePlan(startRound));
		
		    if(vorplatzspiele)
		    	querys.AddRange(insertFieldNames("kreuzspiele_spielplan"));
		
		    writeListToDatabase(querys);
		}
		
		List<String> getDivisionTeamNames(List<List<String>> list)
		{
			List<String> nameList = new List<String>();
		
		    for(int i = 0; i < list.Count; i++)
		    	nameList.Add(list[i][0]);
		
		    return nameList;
		}
		
		List<String> generateGamePlan(DateTime startRound)
		{
		    int addzeit = ((satz * min) + pause) * 60;
		    List<String> querys = new List<String>();
		
		    // get list current ranking results
		    List<List<List<String>> > resultDivisionsZw = new List<List<List<String>>>();
		    List<List<String>> finalDivisions = new List<List<String>>();
		    
		    // help lists
		    List<String> divisionA, divisionB, divisionC, divisionD, divisionE, divisionF, 
		    			 divisionG, divisionH, divisionI, divisionJ, divisionK, divisionL;
		
		    // read divisional rank results and add to list
		    for(int i = 0; i < prefixCount; i++)
		        resultDivisionsZw.Add(readListFromDatabase("select ms, punkte, satz from zwischenrunde_erg_gr" + getPrefix(i) + " order by punkte desc, satz desc"));
		
		    divisionA = getDivisionTeamNames(resultDivisionsZw[0]);
		    divisionB = getDivisionTeamNames(resultDivisionsZw[1]);
		    divisionC = getDivisionTeamNames(resultDivisionsZw[2]);
		    divisionD = getDivisionTeamNames(resultDivisionsZw[3]);
		    divisionE = getDivisionTeamNames(resultDivisionsZw[4]);
		    divisionF = getDivisionTeamNames(resultDivisionsZw[5]);
		    divisionG = getDivisionTeamNames(resultDivisionsZw[6]);
		    divisionH = getDivisionTeamNames(resultDivisionsZw[7]);
		    divisionI = getDivisionTeamNames(resultDivisionsZw[8]);
		    divisionJ = getDivisionTeamNames(resultDivisionsZw[9]);
		    divisionK = getDivisionTeamNames(resultDivisionsZw[10]);
		    divisionL = getDivisionTeamNames(resultDivisionsZw[11]);
		
		    lastRoundNr++;
		
		    if(!vorplatzspiele)
		    {
		        switch(teamsCount)
		        {
		            case 20:
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(1," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + divisionA[0] + "','" + divisionB[1] + "','" + divisionA[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(2," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + divisionA[2] + "','" + divisionB[3] + "','" + divisionA[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(3," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + divisionC[0] + "','" + divisionD[1] + "','" + divisionC[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(4," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + divisionC[2] + "','" + divisionD[3] + "','" + divisionC[3] + "',0,0,0,0,0,0)");
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++; lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(5," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + divisionA[1] + "','" + divisionB[0] + "','" + divisionB[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(6," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + divisionA[3] + "','" + divisionB[2] + "','" + divisionB[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(7," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + divisionC[1] + "','" + divisionD[0] + "','" + divisionD[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(8," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + divisionC[3] + "','" + divisionD[2] + "','" + divisionD[3] + "',0,0,0,0,0,0)");
		                break;
		
		            case 25:
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(1," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + divisionA[0] + "','" + divisionB[1] + "','" + divisionA[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(2," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + divisionA[2] + "','" + divisionB[3] + "','" + divisionA[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(3," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + divisionC[0] + "','" + divisionD[1] + "','" + divisionC[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(4," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + divisionC[2] + "','" + divisionD[3] + "','" + divisionC[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(5," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + divisionA[1] + "','" + divisionB[0] + "','" + divisionB[1] + "',0,0,0,0,0,0)");
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++; lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(6," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + divisionA[3] + "','" + divisionB[2] + "','" + divisionB[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(7," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + divisionC[1] + "','" + divisionD[0] + "','" + divisionD[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(8," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + divisionC[3] + "','" + divisionD[2] + "','" + divisionD[3] + "',0,0,0,0,0,0)");
		                break;
		
		            case 28:
		            case 30:
		            case 35:
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(1," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + divisionA[0] + "','" + divisionB[1] + "','" + divisionA[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(2," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + divisionA[2] + "','" + divisionB[3] + "','" + divisionA[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(3," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + divisionC[0] + "','" + divisionD[1] + "','" + divisionC[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(4," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + divisionC[2] + "','" + divisionD[3] + "','" + divisionC[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(5," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + divisionE[0] + "','" + divisionF[1] + "','" + divisionE[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(6," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',6,'','" + divisionE[2] + "','" + divisionF[3] + "','" + divisionE[3] + "',0,0,0,0,0,0)");
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++; lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(7," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',6,'','" + divisionA[1] + "','" + divisionB[0] + "','" + divisionB[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(8," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + divisionA[3] + "','" + divisionB[2] + "','" + divisionB[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(9," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + divisionC[1] + "','" + divisionD[0] + "','" + divisionD[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(10," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + divisionC[3] + "','" + divisionD[2] + "','" + divisionD[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(11," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + divisionE[1] + "','" + divisionF[0] + "','" + divisionF[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(12," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + divisionE[3] + "','" + divisionF[2] + "','" + divisionF[3] + "',0,0,0,0,0,0)");
		                break;
		
		            case 40:
		            case 45:
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(1," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + divisionA[0] + "','" + divisionB[1] + "','" + divisionA[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(2," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + divisionA[2] + "','" + divisionB[3] + "','" + divisionA[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(3," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + divisionC[0] + "','" + divisionD[1] + "','" + divisionC[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(4," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + divisionC[2] + "','" + divisionD[3] + "','" + divisionC[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(5," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + divisionE[0] + "','" + divisionF[1] + "','" + divisionE[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(6," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',6,'','" + divisionE[2] + "','" + divisionF[3] + "','" + divisionE[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(7," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',7,'','" + divisionG[0] + "','" + divisionH[1] + "','" + divisionG[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(8," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',8,'','" + divisionG[2] + "','" + divisionH[3] + "','" + divisionG[3] + "',0,0,0,0,0,0)");
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++; lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(9," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',8,'','" + divisionA[1] + "','" + divisionB[0] + "','" + divisionB[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(10," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',7,'','" + divisionA[3] + "','" + divisionB[2] + "','" + divisionB[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(11," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',6,'','" + divisionC[1] + "','" + divisionD[0] + "','" + divisionD[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(12," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + divisionC[3] + "','" + divisionD[2] + "','" + divisionD[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(13," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + divisionE[1] + "','" + divisionF[0] + "','" + divisionF[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(14," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + divisionE[3] + "','" + divisionF[2] + "','" + divisionF[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(15," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + divisionG[1] + "','" + divisionH[0] + "','" + divisionH[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(16," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + divisionG[3] + "','" + divisionH[2] + "','" + divisionH[3] + "',0,0,0,0,0,0)");
		                break;
		
		            case 50:
		            case 55:
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(1," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + divisionA[0] + "','" + divisionB[1] + "','" + divisionA[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(2," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + divisionA[2] + "','" + divisionB[3] + "','" + divisionA[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(3," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + divisionC[0] + "','" + divisionD[1] + "','" + divisionC[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(4," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + divisionC[2] + "','" + divisionD[3] + "','" + divisionC[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(5," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + divisionE[0] + "','" + divisionF[1] + "','" + divisionE[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(6," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',6,'','" + divisionE[2] + "','" + divisionF[3] + "','" + divisionE[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(7," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',7,'','" + divisionG[0] + "','" + divisionH[1] + "','" + divisionG[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(8," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',8,'','" + divisionG[2] + "','" + divisionH[3] + "','" + divisionG[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(9," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',9,'','" + divisionI[0] + "','" + divisionJ[1] + "','" + divisionI[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(10," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',10,'','" + divisionI[2] + "','" + divisionJ[3] + "','" + divisionI[3] + "',0,0,0,0,0,0)");
		
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++; lastGameNr++;
		
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(11," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',10,'','" + divisionA[1] + "','" + divisionB[0] + "','" + divisionB[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(12," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',9,'','" + divisionA[3] + "','" + divisionB[2] + "','" + divisionB[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(13," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',8,'','" + divisionC[1] + "','" + divisionD[0] + "','" + divisionD[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(14," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',7,'','" + divisionC[3] + "','" + divisionD[2] + "','" + divisionD[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(15," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',6,'','" + divisionE[1] + "','" + divisionF[0] + "','" + divisionF[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(16," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + divisionE[3] + "','" + divisionF[2] + "','" + divisionF[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(17," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + divisionG[1] + "','" + divisionH[0] + "','" + divisionH[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(18," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + divisionG[3] + "','" + divisionH[2] + "','" + divisionH[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(19," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + divisionI[1] + "','" + divisionJ[0] + "','" + divisionI[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(20," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + divisionI[3] + "','" + divisionJ[2] + "','" + divisionI[3] + "',0,0,0,0,0,0)");
		                break;
		
		            case 60:
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(1," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + divisionA[0] + "','" + divisionB[1] + "','" + divisionA[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(2," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + divisionA[2] + "','" + divisionB[3] + "','" + divisionA[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(3," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + divisionC[0] + "','" + divisionD[1] + "','" + divisionC[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(4," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + divisionC[2] + "','" + divisionD[3] + "','" + divisionC[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(5," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + divisionE[0] + "','" + divisionF[1] + "','" + divisionE[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(6," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',6,'','" + divisionE[2] + "','" + divisionF[3] + "','" + divisionE[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(7," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',7,'','" + divisionG[0] + "','" + divisionH[1] + "','" + divisionG[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(8," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',8,'','" + divisionG[2] + "','" + divisionH[3] + "','" + divisionG[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(9," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',9,'','" + divisionI[0] + "','" + divisionJ[1] + "','" + divisionI[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(10," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',10,'','" + divisionI[2] + "','" + divisionJ[3] + "','" + divisionI[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(11," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',11,'','" + divisionK[2] + "','" + divisionL[3] + "','" + divisionK[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(12," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',12,'','" + divisionK[2] + "','" + divisionL[3] + "','" + divisionK[3] + "',0,0,0,0,0,0)");
		
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++; lastGameNr++;
		
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(13," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',12,'','" + divisionA[1] + "','" + divisionB[0] + "','" + divisionB[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(14," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',11,'','" + divisionA[3] + "','" + divisionB[2] + "','" + divisionB[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(15," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',10,'','" + divisionC[1] + "','" + divisionD[0] + "','" + divisionD[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(16," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',9,'','" + divisionC[3] + "','" + divisionD[2] + "','" + divisionD[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(17," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',8,'','" + divisionE[1] + "','" + divisionF[0] + "','" + divisionF[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(18," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',7,'','" + divisionE[3] + "','" + divisionF[2] + "','" + divisionF[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(19," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',6,'','" + divisionG[1] + "','" + divisionH[0] + "','" + divisionH[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(20," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + divisionG[3] + "','" + divisionH[2] + "','" + divisionH[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(21," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + divisionI[1] + "','" + divisionJ[0] + "','" + divisionJ[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(22," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + divisionI[3] + "','" + divisionJ[2] + "','" + divisionJ[3] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(23," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + divisionK[1] + "','" + divisionL[0] + "','" + divisionL[1] + "',0,0,0,0,0,0)");
		                lastGameNr++;
		                querys.Add("INSERT INTO kreuzspiele_spielplan VALUES(24," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + divisionK[3] + "','" + divisionL[2] + "','" + divisionL[3] + "',0,0,0,0,0,0)");
		                break;
		        }
		    }
		    else
		    {
		        if(divisionA.Count > 0)
		        	finalDivisions.Add(divisionA);
		
		        if(divisionB.Count > 0)
		            finalDivisions.Add(divisionB);
		
		        if(divisionC.Count > 0)
		            finalDivisions.Add(divisionC);
		
		        if(divisionD.Count > 0)
		            finalDivisions.Add(divisionD);
		
		        if(divisionE.Count > 0)
		            finalDivisions.Add(divisionE);
		
		        if(divisionF.Count > 0)
		            finalDivisions.Add(divisionF);
		
		        if(divisionG.Count > 0)
		            finalDivisions.Add(divisionG);
		
		        if(divisionH.Count > 0)
		            finalDivisions.Add(divisionH);
		
		        if(divisionI.Count > 0)
		            finalDivisions.Add(divisionI);
		
		        if(divisionJ.Count > 0)
		            finalDivisions.Add(divisionJ);
		
		        if(divisionK.Count > 0)
		            finalDivisions.Add(divisionK);
		
		        if(divisionL.Count > 0)
		            finalDivisions.Add(divisionL);
		
		        List<List<List<String>>> gameList = new List<List<List<String>>>();
		        List<String> refereeList = new List<String>();
		        lastGameNr++;
		
		        // create game list
		        for(int i = 0; i < divisionCount;)
		        {
		            if(i + 1 < finalDivisions.Count)
		            {
		            	int rest = (finalDivisions[i].Count + finalDivisions[i + 1].Count) % 2;
		                int count = (finalDivisions[i].Count + finalDivisions[i + 1].Count - rest) / 2;
		                List<List<String>> games = new List<List<String>>();
		
		                for(int x = 0; x < count; x++)
		                {
		                	games.Add(new List<String>() { finalDivisions[i][x], finalDivisions[i + 1][x] });
		                    gamesCount++;
		                }
		
		                gameList.Add(games);
		                i = i + 2;
		            }
		            else
		            {
		                break;
		            }
		        }
		
		        for(int i = 0; i < gameList.Count && i < fieldCount; i++)
		        {
		        	List<List<String>> refList = gameList[i];
		            for(int j = 0; j < refList.Count; j++)
		            {
		            	refereeList.Add(refList[j][0]);
		            	refereeList.Add(refList[j][1]);
		            }
		        }
		
		        // generate round starting with last group and last game (worst two teams)
		        for(int count = 0, fCount = 1, y = (gameList.Count - 1), startingReferee = 0,
		            rowCount = 1, dataRow = gameList[(gameList.Count - 1)].Count - 1;
		            count < gamesCount; rowCount++, lastGameNr++, count++, startingReferee++)
		        {
		            String referee = "";
		            if(startingReferee < fieldCount)
		            	referee = refereeList[startingReferee];
		
		            querys.Add("INSERT INTO kreuzspiele_spielplan VALUES("
		                      + rowCount + "," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "', " + fCount + ",'','"
		                      + gameList[y][dataRow][0] + "','"
		                      + gameList[y][dataRow][1] + "','"
		                      + referee + "',"
		                      + "0,0,0,0,0,0)");
		
		            if(fCount >= fieldCount)
		            {
		                fCount = 1;
		                lastRoundNr++;
		                startRound = startRound.AddSeconds(addzeit);
		            }
		            else
		            {
		                fCount++;
		            }
		
		            if(dataRow < 1)
		            {
		            	dataRow = gameList[y].Count - 1;
		                y--;
		            }
		            else
		            {
		                dataRow--;
		            }
		        }
		    }
		
		    return querys;
		}
	}
}
