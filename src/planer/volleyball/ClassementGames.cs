/*
 * Created by SharpDevelop.
 * User: cfr
 * Date: 29.06.2017
 * Time: 11:32
 */
using System;
using System.Collections.Generic;

namespace volleyball
{
	public class ClassementGames : BaseGameHandling
	{
		#region
		DateTime startRound;
		bool vorplatzspiele;
	    int prefixCount, divisionCount, lastRoundNr, lastGameNr;
	    List<int> classements;
	    List<List<String>> krGameResults, plGameResults;
		#endregion
		
		public ClassementGames(Database db, List<String> grPrefix) : base(db, grPrefix)
		{
			krGameResults = new List<List<String>>();
			plGameResults = new List<List<String>>();
			classements = new List<int>();
		}
		
		public void setParameters(String startRound, int lastgameTime, int pauseKrPl, int countSatz, 
		                          int minSatz, int fieldCount, int teamsCount, int divisionCount, 
		                          List<String> fieldNames, int lastRoundNr, int lastGameNr, bool vorplatzspiele)
		{
		    Logging.write("PLATZSPIELE: set platzspiele params");
		    this.startRound = DateTime.Parse(startRound);
		    this.vorplatzspiele = vorplatzspiele;
		    this.divisionCount = divisionCount;
		    this.fieldNames = fieldNames;
		    this.lastGameNr = lastGameNr;
		    this.lastRoundNr = lastRoundNr;
		    this.startRound = DateTime.Parse(startRound);
		    		
		    this.startRound = this.startRound.AddSeconds(pauseKrPl * 60);
		    
		    setParameters(satz, min, pause, fieldCount, teamsCount, gamesCount, fieldNames);
		
		    if(!vorplatzspiele)
		    {
		    	classements.Clear();
		        switch(teamsCount)
		        {
		            case 20:
		        	case 25: classements = new List<int>() { 9, 10, 19, 20,
		        											 7, 8, 17, 18,
		        											 5, 6, 15, 16,
		        											 3, 4, 13, 14, 23, 24,
		        											 11, 12, 21, 22,
		        											 1, 2 };
		                break;
		
		            case 28: classements = new List<int>() { 9, 10, 19, 20,
		                									 7, 8, 17, 18, 27, 28,
		                									 5, 6, 15, 16, 25, 26,
		                									 3, 4, 13, 14, 23, 24,
		                									 11, 12, 21, 22,
		                									 1, 2 };
		                break;
		
		            case 30:
		            case 35: classements = new List<int>() { 9, 10, 19, 20, 29, 30,
		                									 7, 8, 17, 18, 27, 28,
		                									 5, 6, 15, 16, 25, 26,
		                									 3, 4, 13, 14, 23, 24,
		                									 11, 12, 21, 22,
		                									 1, 2 };
		                break;
		
		            case 40:
		            case 45: classements = new List<int>() { 9, 10, 19, 20, 29, 30, 39, 40,
		                									 7, 8, 17, 18, 27, 28, 37, 38,
		                									 5, 6, 15, 16, 25, 26, 35, 36,
		                									 3, 4, 13, 14, 23, 24, 33, 34,
		                									 11, 12, 21, 22, 31, 32,
		                									 1, 2 };
		                break;
		
		            case 50: classements = new List<int>() { 9, 10, 19, 20, 29, 30, 39, 40, 49, 50,
		                									 7, 8, 17, 18, 27, 28, 37, 38, 47, 48,
		                									 5, 6, 15, 16, 25, 26, 35, 36, 45, 46,
		                									 3, 4, 13, 14, 23, 24, 33, 34, 43, 44,
		                									 11, 12, 21, 22, 31, 32, 41, 42,
		                									 1, 2 };
		                break;
		
		            case 55: classements = new List<int>() { 9, 10, 19, 20, 29, 30, 39, 40, 49, 50,
		                									 7, 8, 17, 18, 27, 28, 37, 38, 47, 48,
		                									 5, 6, 15, 16, 25, 26, 35, 36, 45, 46,
		                									 3, 4, 13, 14, 23, 24, 33, 34, 43, 44,
		                									 11, 12, 21, 22, 31, 32, 41, 42,
		                									 1, 2 };
		                break;
		
		            case 60: classements = new List<int>() { 9, 10, 19, 20, 29, 30, 39, 40, 49, 50,
		                									 7, 8, 17, 18, 27, 28, 37, 38, 47, 48,
		                									 5, 6, 15, 16, 25, 26, 35, 36, 45, 46,
		                									 3, 4, 13, 14, 23, 24, 33, 34, 43, 44,
		                									 11, 12, 21, 22, 31, 32, 41, 42,
		                									 1, 2 };
		                break;
		        }
		    }
		}
		
		public void generateClassementGames()
		{
		    List<String> querys = new List<String>();
		
		    krGameResults.Clear();
		    prefixCount = getPrefixCount();
		
		    List<List<String>> krGames = readListFromDatabase("SELECT spiel, ms_a, ms_b, satz1a, satz1b, satz2a, satz2b, satz3a, satz3b FROM kreuzspiele_Spielplan ORDER BY id ASC");
		
		    foreach(List<String> krGame in krGames)
		    	krGameResults.Add(CalculateResults.getResultsKrPl(krGame));
		
		    querys.AddRange(generateGamePlan(startRound));
		
		    querys.AddRange(insertFieldNames("platzspiele_spielplan"));
		
		    writeListToDatabase(querys);
		}
		
		public void finalTournamentResults()
		{
		    List<String> querys = new List<String>();
		
		    if(krGameResults.Count == 0)
		    {
		        List<List<String>> krGames = readListFromDatabase("SELECT spiel, ms_a, ms_b, satz1a, satz1b, satz2a, satz2b, satz3a, satz3b FROM kreuzspiele_Spielplan ORDER BY id ASC");
		
		        foreach(List<String> krGame in krGames)
		        	krGameResults.Add(CalculateResults.getResultsKrPl(krGame));
		    }
		
		    plGameResults.Clear();
		
		    List<List<String>> plGames = readListFromDatabase("SELECT spiel, ms_a, ms_b, satz1a, satz1b, satz2a, satz2b, satz3a, satz3b FROM platzspiele_Spielplan ORDER BY id ASC");
		
		    foreach(List<String> plGame in plGames)
		    	plGameResults.Add(CalculateResults.getResultsKrPl(plGame));
		
		    querys.Add("DELETE FROM platzierungen");
		
		    querys.AddRange(createClassement());
		
		    writeListToDatabase(querys);
		}
		
		List<String> createClassement()
		{
		    List<String> querys = new List<String>();
		    List<List<String>> bottomRankings = new List<List<String>>();
		    int rowid = 0, id = 0;
		
		    // rest of classement, teams which played vorrunde and zwischenrunde
		    if(!vorplatzspiele)
		    {
		        for(int i = 0, x = 0; i < plGameResults.Count; i++)
		        {
		        	List<String> plGame = plGameResults[i];
		        	id++; x++;
		        	querys.Add("INSERT INTO platzierungen VALUES(" + (id) + "," + classements[x] + ",'" + plGame[1] + "')");
		        	id++; x++;
		        	querys.Add("INSERT INTO platzierungen VALUES(" + (id) + "," + classements[x] + ",'" + plGame[2] + "')");
		        }
		
		        switch(teamsCount)
		        {
		            case 25:
		                bottomRankings = readListFromDatabase("SELECT ms FROM zwischenrunde_gre_view");
		                id++; rowid = id + 1;
		                querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + rowid + ",'" + bottomRankings[0][0] + "')");
		                id++; rowid = id + 1;
		                querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + rowid + ",'" + bottomRankings[1][0] + "')");
		                id++; rowid = id + 1;
		                querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + rowid + ",'" + bottomRankings[2][0] + "')");
		                id++; rowid = id + 1;
		                querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + rowid + ",'" + bottomRankings[3][0] + "')");
		                id++; rowid = id + 1;
		                querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + rowid + ",'" + bottomRankings[4][0] + "')");
		                break;
		
		            case 35:
		                bottomRankings = readListFromDatabase("SELECT ms FROM zwischenrunde_grg_view");
		                id++; rowid = id + 1;
		                querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + rowid + ",'" + bottomRankings[0][0] + "')");
		                id++; rowid = id + 1;
		                querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + rowid + ",'" + bottomRankings[1][0] + "')");
		                id++; rowid = id + 1;
		                querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + rowid + ",'" + bottomRankings[2][0] + "')");
		                id++; rowid = id + 1;
		                querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + rowid + ",'" + bottomRankings[3][0] + "')");
		                id++; rowid = id + 1;
		                querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + rowid + ",'" + bottomRankings[4][0] + "')");
		                break;
		
		            case 45:
		                bottomRankings = readListFromDatabase("SELECT ms FROM zwischenrunde_gri_view");
		                id++; rowid = id + 1;
		                querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + rowid + ",'" + bottomRankings[0][0] + "')");
		                id++; rowid = id + 1;
		                querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + rowid + ",'" + bottomRankings[1][0] + "')");
		                id++; rowid = id + 1;
		                querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + rowid + ",'" + bottomRankings[2][0] + "')");
		                id++; rowid = id + 1;
		                querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + rowid + ",'" + bottomRankings[3][0] + "')");
		                id++; rowid = id + 1;
		                querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + rowid + ",'" + bottomRankings[4][0] + "')");
		                break;
		
		            case 55:
		                bottomRankings = readListFromDatabase("SELECT ms FROM zwischenrunde_grk_view");
		                id++; rowid = id + 1;
		                querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + rowid + ",'" + bottomRankings[0][0] + "')");
		                id++; rowid = id + 1;
		                querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + rowid + ",'" + bottomRankings[1][0] + "')");
		                id++; rowid = id + 1;
		                querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + rowid + ",'" + bottomRankings[2][0] + "')");
		                id++; rowid = id + 1;
		                querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + rowid + ",'" + bottomRankings[3][0] + "')");
		                id++; rowid = id + 1;
		                querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + rowid + ",'" + bottomRankings[4][0] + "')");
		                break;
		        }
		    }
		    else
		    {
		        int classement = teamsCount;
		
		        switch(teamsCount)
		        {
		            case 55:
		                // create the classements for the worst teams
		                bottomRankings = readListFromDatabase("SELECT ms FROM zwischenrunde_grk_view");
		                for(int i = 4; i >= 0; i--)
		                {
		                	querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + classement + ",'" + bottomRankings[i][0] + "')");
		                    id++; classement--;
		                }
		
		                // create the classements for teams that played cross game
		                for(int i = 0; i < 5; i++, id++, classement--)
		                {
		                   // generate looser query
		                   querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + classement + ",'" + krGameResults[i][2] + "')");
		
		                    id++; classement--;
		
		                    // generate winner query
		                    querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + classement + ",'" + krGameResults[i][1] + "')");
		                }
		
		                // create the next classements for teams that played classement game
		                for(int i = 0, x = classement; x > 0; i++, id++, x--)
		                {
		                	List<String> plGame = plGameResults[i];
		                    
		                    // generate looser query
		                    querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + x + ",'" + plGame[2] + "')");
		
		                    id++; x--;
		
		                    // generate winner query
		                    querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + x + ",'" + plGame[1] + "')");
		                }
		                
		                break;
		
		            case 60:
		                for(int i = 0, x = classement; x > 0; i++, id++, x--)
		                {
		                    // generate looser query
		                    querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + x + ",'" + plGameResults[i][2] + "')");
		
		                    id++; x--;
		
		                    // generate winner query
		                    querys.Add("INSERT INTO platzierungen VALUES(" + id + "," + x + ",'" + plGameResults[i][1] + "')");
		                }
		                break;
		        }
		    }
		
		    return querys;
		}
		
		List<String> generateGamePlan(DateTime startRound)
		{
		    int addzeit = ((satz * min) + pause) * 60;
		    List<String> querys = new List<String>();
		
		    // get list current ranking results
		    List<List<String>> resultDivisionsZw = new List<List<String>>();
		
		    // help lists
		    List<String> divisionA, divisionB, divisionC, divisionD, divisionE, divisionF, 
		    			 divisionG, divisionH, divisionI, divisionJ, divisionK, divisionL;
		
		    // read divisional rank results and add to list
		    for(int i = 0; i < prefixCount; i++)
		    {
		    	List<String> resultEdit = new List<String>();
		        List<List<String>> divisionResult = readListFromDatabase("select ms, punkte, satz from zwischenrunde_erg_gr" + getPrefix(i) + " order by punkte desc, satz desc");
		
		        foreach(List<String> team in divisionResult)
		        	resultEdit.Add(team[0]);
		
		        resultDivisionsZw.Add(resultEdit);
		    }
		
		    if(resultDivisionsZw.Count > 0 && resultDivisionsZw[0].Count > 0)
		    	divisionA = resultDivisionsZw[0];
		    else
		    	divisionA = new List<String>();
		
		    if(resultDivisionsZw.Count > 1 && resultDivisionsZw[1].Count > 0)
		    	divisionB = resultDivisionsZw[1];
		    else
		    	divisionB = new List<String>();
		
		    if(resultDivisionsZw.Count > 2 && resultDivisionsZw[2].Count > 0)
		    	divisionC = resultDivisionsZw[2];
		    else
		    	divisionC = new List<String>();
		
		    if(resultDivisionsZw.Count > 3 && resultDivisionsZw[3].Count > 0)
		    	divisionD = resultDivisionsZw[3];
		    else
		    	divisionD = new List<String>();
		
		    if(resultDivisionsZw.Count > 4 && resultDivisionsZw[4].Count > 0)
		    	divisionE = resultDivisionsZw[4];
		    else
		    	divisionE = new List<String>();
		
		    if(resultDivisionsZw.Count > 5 && resultDivisionsZw[5].Count > 0)
		    	divisionF = resultDivisionsZw[5];
		    else
		    	divisionF = new List<String>();
		
		    if(resultDivisionsZw.Count > 6 && resultDivisionsZw[6].Count > 0)
		    	divisionG = resultDivisionsZw[6];
		    else
		    	divisionG = new List<String>();
		
		    if(resultDivisionsZw.Count > 7 && resultDivisionsZw[7].Count > 0)
		    	divisionH = resultDivisionsZw[7];
		    else
		    	divisionH = new List<String>();
		
		    if(resultDivisionsZw.Count > 8 && resultDivisionsZw[8].Count > 0)
		    	divisionI = resultDivisionsZw[8];
		    else
		    	divisionI = new List<String>();
		
		    if(resultDivisionsZw.Count > 9 && resultDivisionsZw[9].Count > 0)
		    	divisionJ = resultDivisionsZw[9];
		    else
		    	divisionJ = new List<String>();
		
		    if(resultDivisionsZw.Count > 10 && resultDivisionsZw[10].Count > 0)
		    	divisionK = resultDivisionsZw[10];
		    else
		    	divisionK = new List<String>();
		
		    if(resultDivisionsZw.Count > 11 && resultDivisionsZw[11].Count > 0)
		    	divisionL = resultDivisionsZw[11];
		    else
		    	divisionL = new List<String>();
		
		    lastRoundNr++;
		
		    if(!vorplatzspiele)
		    {
		        switch(teamsCount)
		        {
		            case 20:
		            case 25:
		                // spiel um platz 9
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(1," + lastRoundNr + "," + lastGameNr +  ",'" + startRound.ToString("hh:mm") + "',1,'','" + divisionA[4] + "','" + divisionB[4] + "','" + divisionA[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 7
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(2," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + krGameResults[1][2] + "','" + krGameResults[5][2] + "','" + divisionB[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 19
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(3," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + divisionC[4] + "','" + divisionD[4] + "','" + divisionC[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 17
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(4," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + krGameResults[3][2] + "','" + krGameResults[7][2] + "','" + divisionD[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 5
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(5," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + krGameResults[1][1] + "','" + krGameResults[5][1] + "','" + divisionA[4] + "',0,0,0,0,0,0)");
		
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++;
		                // spiel um platz 3
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(6," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + krGameResults[0][2] + "','" + krGameResults[4][2] + "','" + divisionB[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 15
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(7," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + krGameResults[3][1] + "','" + krGameResults[7][1] + "','" + divisionC[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 13
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(8," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + krGameResults[2][2] + "','" + krGameResults[6][2] + "','" + divisionD[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 11
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(9," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + krGameResults[2][1] + "','" + krGameResults[6][1] + "','" + divisionC[3] + "',0,0,0,0,0,0)");
		
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++;
		                // spiel um platz 1
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(10," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + krGameResults[0][1] + "','" + krGameResults[4][1] + "','" + divisionA[3] + "',0,0,0,0,0,0)");
		                break;
		
		            case 28:
		                // spiel um platz 7
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(1," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + krGameResults[1][2] + "','" + krGameResults[7][2] + "','" + divisionB[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 19
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(2," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + divisionC[4] + "','" + divisionD[4] + "','" + divisionC[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 17
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(3," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',6,'','" + krGameResults[3][2] + "','" + krGameResults[9][2] + "','" + divisionD[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 27
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(4," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + divisionE[4] + "','" + divisionF[4] + "','" + divisionE[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 25
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(5," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + krGameResults[5][2] + "','" + krGameResults[11][2] + "','" + divisionF[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 5
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(6," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + krGameResults[1][1] + "','" + krGameResults[7][2] + "','" + krGameResults[1][2] + "',0,0,0,0,0,0)");
		                // spiel um platz 3
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(7," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',6,'','" + krGameResults[0][2] + "','" + krGameResults[6][2] + "','" + krGameResults[7][2] + "',0,0,0,0,0,0)");
		
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++;
		                // spiel um platz 15
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(8," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + krGameResults[3][1] + "','" + krGameResults[9][1] + "','" + divisionC[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 13
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(9," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + krGameResults[2][2] + "','" + krGameResults[8][2] + "','" + divisionD[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 23
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(10," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + krGameResults[5][1] + "','" + krGameResults[11][1] + "','" + divisionE[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 9
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(11," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + krGameResults[4][2] + "','" + krGameResults[10][2] + "','" + divisionF[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 21
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(12," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + krGameResults[4][1] + "','" + krGameResults[10][1] + "','" + divisionE[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 11
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(13," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + krGameResults[2][1] + "','" + krGameResults[8][1] + "','" + divisionC[4] + "',0,0,0,0,0,0)");
		
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++;
		                // spiel um platz 1
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(14," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + krGameResults[0][1] + "','" + krGameResults[6][1] + "','" + divisionA[3] + "',0,0,0,0,0,0)");
		                break;
		
		            case 30:
		            case 35:
		                // spiel um platz 9
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(1," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + divisionA[4] + "','" + divisionB[4] + "','" + divisionA[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 19
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(2," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + divisionC[4] + "','" + divisionD[4] + "','" + divisionC[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 29
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(3," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + divisionE[4] + "','" + divisionF[4] + "','" + divisionE[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 7
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(4," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + krGameResults[1][2] + "','" + krGameResults[7][2] + "','" + divisionB[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 17
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(5," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + krGameResults[3][2] + "','" + krGameResults[9][2] + "','" + divisionD[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 27
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(6," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',6,'','" + krGameResults[5][2] + "','" + krGameResults[11][2] + "','" + divisionF[1] + "',0,0,0,0,0,0)");
		
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++;
		                // spiel um platz 5
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(7," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + krGameResults[1][1] + "','" + krGameResults[7][1] + "','" + divisionA[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 15
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(9," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + krGameResults[3][1] + "','" + krGameResults[9][1] + "','" + divisionC[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 25
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(11," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + krGameResults[5][1] + "','" + krGameResults[11][1] + "','" + divisionE[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 3
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(8," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + krGameResults[0][2] + "','" + krGameResults[6][2] + "','" + divisionB[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 13
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(10," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + krGameResults[2][2] + "','" + krGameResults[8][2] + "','" + divisionD[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 23
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(12," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',6,'','" + krGameResults[4][2] + "','" + krGameResults[10][2] + "','" + divisionF[4] + "',0,0,0,0,0,0)");
		
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++;
		                // spiel um platz 21
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(13," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + krGameResults[2][1] + "','" + krGameResults[8][1] + "','" + divisionA[3] + "',0,0,0,0,0,0)");
		                // spiel um platz 11
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(14," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + krGameResults[4][1] + "','" + krGameResults[10][1] + "','" + divisionB[3] + "',0,0,0,0,0,0)");
		
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++;
		                // spiel um platz 1
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(15," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + krGameResults[0][1] + "','" + krGameResults[6][1] + "','" + divisionA[3] + "',0,0,0,0,0,0)");
		                break;
		
		            case 40:
		            case 45:
		                // spiel um platz 9
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(1," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + divisionA[4] + "','" + divisionB[4] + "','" + divisionA[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 19
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(2," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + divisionC[4] + "','" + divisionD[4] + "','" + divisionC[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 29
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(3," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + divisionE[4] + "','" + divisionF[4] + "','" + divisionE[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 39
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(4," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + divisionG[4] + "','" + divisionH[4] + "','" + divisionG[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 7
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(5," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + krGameResults[1][2] + "','" + krGameResults[9][2] + "','" + divisionB[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 17
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(6," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',6,'','" + krGameResults[3][2] + "','" + krGameResults[11][2] + "','" + divisionD[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 27
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(7," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',7,'','" + krGameResults[5][2] + "','" + krGameResults[13][2] + "','" + divisionF[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 37
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(8," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',8,'','" + krGameResults[7][2] + "','" + krGameResults[15][2] + "','" + divisionH[1] + "',0,0,0,0,0,0)");
		
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++;
		                // spiel um platz 5
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(9," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + krGameResults[1][1] + "','" + krGameResults[9][1] + "','" + divisionA[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 15
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(10," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + krGameResults[3][1] + "','" + krGameResults[11][1] + "','" + divisionC[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 25
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(11," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + krGameResults[5][1] + "','" + krGameResults[13][1] + "','" + divisionE[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 35
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(12," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + krGameResults[7][1] + "','" + krGameResults[15][1] + "','" + divisionG[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 3
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(13," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + krGameResults[0][2] + "','" + krGameResults[8][2] + "','" + divisionB[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 13
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(14," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',6,'','" + krGameResults[2][2] + "','" + krGameResults[10][2] + "','" + divisionD[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 23
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(15," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',7,'','" + krGameResults[4][2] + "','" + krGameResults[12][2] + "','" + divisionF[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 33
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(16," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',8,'','" + krGameResults[6][2] + "','" + krGameResults[14][2] + "','" + divisionH[4] + "',0,0,0,0,0,0)");
		
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++;
		                // spiel um platz 11
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(17," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + krGameResults[2][1] + "','" + krGameResults[10][1] + "','" + divisionA[3] + "',0,0,0,0,0,0)");
		                // spiel um platz 21
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(18," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + krGameResults[4][1] + "','" + krGameResults[12][1] + "','" + divisionB[3] + "',0,0,0,0,0,0)");
		                // spiel um platz 31
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(19," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + krGameResults[6][1] + "','" + krGameResults[14][1] + "','" + divisionC[3] + "',0,0,0,0,0,0)");
		
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++;
		                // spiel um platz 1
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(20," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + krGameResults[0][1] + "','" + krGameResults[8][1] + "','',0,0,0,0,0,0)");
		                break;
		
		            case 50:
		                // spiel um platz 9
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(1," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + divisionA[4] + "','" + divisionB[4] + "','" + divisionA[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 19
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(2," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + divisionC[4] + "','" + divisionD[4] + "','" + divisionC[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 29
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(3," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + divisionE[4] + "','" + divisionF[4] + "','" + divisionE[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 39
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(4," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + divisionG[4] + "','" + divisionH[4] + "','" + divisionG[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 49
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(5," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + divisionG[4] + "','" + divisionH[4] + "','" + divisionG[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 7
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(6," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',6,'','" + krGameResults[1][2] + "','" + krGameResults[9][2] + "','" + divisionB[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 17
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(7," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',7,'','" + krGameResults[3][2] + "','" + krGameResults[11][2] + "','" + divisionD[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 27
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(8," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',8,'','" + krGameResults[5][2] + "','" + krGameResults[13][2] + "','" + divisionF[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 37
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(9," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',9,'','" + krGameResults[7][2] + "','" + krGameResults[15][2] + "','" + divisionH[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 47
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(10," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',10,'','" + krGameResults[9][2] + "','" + krGameResults[15][2] + "','" + divisionH[1] + "',0,0,0,0,0,0)");
		
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++;
		                // spiel um platz 5
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(11," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + krGameResults[1][1] + "','" + krGameResults[9][1] + "','" + divisionA[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 15
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(12," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + krGameResults[3][1] + "','" + krGameResults[11][1] + "','" + divisionC[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 25
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(13," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + krGameResults[5][1] + "','" + krGameResults[13][1] + "','" + divisionE[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 35
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(14," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + krGameResults[7][1] + "','" + krGameResults[15][1] + "','" + divisionG[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 45
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(15," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + krGameResults[7][1] + "','" + krGameResults[15][1] + "','" + divisionG[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 3
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(16," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',6,'','" + krGameResults[0][2] + "','" + krGameResults[8][2] + "','" + divisionB[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 13
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(17," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',7,'','" + krGameResults[2][2] + "','" + krGameResults[10][2] + "','" + divisionD[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 23
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(18," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',8,'','" + krGameResults[4][2] + "','" + krGameResults[12][2] + "','" + divisionF[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 33
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(19," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',9,'','" + krGameResults[6][2] + "','" + krGameResults[14][2] + "','" + divisionH[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 43
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(20," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',10,'','" + krGameResults[6][2] + "','" + krGameResults[14][2] + "','" + divisionH[4] + "',0,0,0,0,0,0)");
		
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++;
		                // spiel um platz 11
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(21," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + krGameResults[2][1] + "','" + krGameResults[10][1] + "','" + divisionA[3] + "',0,0,0,0,0,0)");
		                // spiel um platz 21
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(22," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + krGameResults[4][1] + "','" + krGameResults[12][1] + "','" + divisionB[3] + "',0,0,0,0,0,0)");
		                // spiel um platz 31
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(23," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + krGameResults[6][1] + "','" + krGameResults[14][1] + "','" + divisionC[3] + "',0,0,0,0,0,0)");
		                // spiel um platz 41
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(24," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + krGameResults[6][1] + "','" + krGameResults[14][1] + "','" + divisionC[3] + "',0,0,0,0,0,0)");
		
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++;
		                // spiel um platz 1
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(20," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + krGameResults[0][1] + "','" + krGameResults[8][1] + "','',0,0,0,0,0,0)");
		                break;
		
		            case 55:
		                // spiel um platz 9
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(1," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + divisionA[4] + "','" + divisionB[4] + "','" + divisionA[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 19
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(2," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + divisionC[4] + "','" + divisionD[4] + "','" + divisionC[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 29
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(3," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + divisionE[4] + "','" + divisionF[4] + "','" + divisionE[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 39
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(4," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + divisionG[4] + "','" + divisionH[4] + "','" + divisionG[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 49
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(4," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + divisionG[4] + "','" + divisionH[4] + "','" + divisionG[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 7
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(5," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + krGameResults[1][2] + "','" + krGameResults[9][2] + "','" + divisionB[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 17
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(6," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',6,'','" + krGameResults[3][2] + "','" + krGameResults[11][2] + "','" + divisionD[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 27
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(7," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',7,'','" + krGameResults[5][2] + "','" + krGameResults[13][2] + "','" + divisionF[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 37
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(8," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',8,'','" + krGameResults[7][2] + "','" + krGameResults[15][2] + "','" + divisionH[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 47
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(8," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',8,'','" + krGameResults[7][2] + "','" + krGameResults[15][2] + "','" + divisionH[1] + "',0,0,0,0,0,0)");
		
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++;
		                // spiel um platz 5
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(9," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + krGameResults[1][1] + "','" + krGameResults[9][1] + "','" + divisionA[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 15
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(10," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + krGameResults[3][1] + "','" + krGameResults[11][1] + "','" + divisionC[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 25
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(11," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + krGameResults[5][1] + "','" + krGameResults[13][1] + "','" + divisionE[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 35
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(12," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + krGameResults[7][1] + "','" + krGameResults[15][1] + "','" + divisionG[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 45
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(12," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + krGameResults[7][1] + "','" + krGameResults[15][1] + "','" + divisionG[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 3
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(13," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + krGameResults[0][2] + "','" + krGameResults[8][2] + "','" + divisionB[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 13
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(14," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',6,'','" + krGameResults[2][2] + "','" + krGameResults[10][2] + "','" + divisionD[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 23
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(15," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',7,'','" + krGameResults[4][2] + "','" + krGameResults[12][2] + "','" + divisionF[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 33
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(16," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',8,'','" + krGameResults[6][2] + "','" + krGameResults[14][2] + "','" + divisionH[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 43
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(16," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',8,'','" + krGameResults[6][2] + "','" + krGameResults[14][2] + "','" + divisionH[4] + "',0,0,0,0,0,0)");
		
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++;
		                // spiel um platz 11
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(17," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + krGameResults[2][1] + "','" + krGameResults[10][1] + "','" + divisionA[3] + "',0,0,0,0,0,0)");
		                // spiel um platz 21
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(18," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + krGameResults[4][1] + "','" + krGameResults[12][1] + "','" + divisionB[3] + "',0,0,0,0,0,0)");
		                // spiel um platz 31
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(19," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + krGameResults[6][1] + "','" + krGameResults[14][1] + "','" + divisionC[3] + "',0,0,0,0,0,0)");
		                // spiel um platz 41
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(20," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + krGameResults[6][1] + "','" + krGameResults[14][1] + "','" + divisionC[3] + "',0,0,0,0,0,0)");
		
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++;
		                // spiel um platz 1
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(20," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + krGameResults[0][1] + "','" + krGameResults[8][1] + "','',0,0,0,0,0,0)");
		                break;
		
		            case 60:
		                // spiel um platz 9
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(1," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + divisionA[4] + "','" + divisionB[4] + "','" + divisionA[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 19
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(2," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + divisionC[4] + "','" + divisionD[4] + "','" + divisionC[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 29
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(3," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + divisionE[4] + "','" + divisionF[4] + "','" + divisionE[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 39
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(4," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + divisionG[4] + "','" + divisionH[4] + "','" + divisionG[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 49
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(4," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + divisionG[4] + "','" + divisionH[4] + "','" + divisionG[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 7
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(5," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + krGameResults[1][2] + "','" + krGameResults[9][2] + "','" + divisionB[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 17
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(6," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',6,'','" + krGameResults[3][2] + "','" + krGameResults[11][2] + "','" + divisionD[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 27
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(7," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',7,'','" + krGameResults[5][2] + "','" + krGameResults[13][2] + "','" + divisionF[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 37
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(8," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',8,'','" + krGameResults[7][2] + "','" + krGameResults[15][2] + "','" + divisionH[1] + "',0,0,0,0,0,0)");
		                // spiel um platz 47
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(8," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',8,'','" + krGameResults[7][2] + "','" + krGameResults[15][2] + "','" + divisionH[1] + "',0,0,0,0,0,0)");
		
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++;
		                // spiel um platz 5
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(9," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + krGameResults[1][1] + "','" + krGameResults[9][1] + "','" + divisionA[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 15
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(10," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + krGameResults[3][1] + "','" + krGameResults[11][1] + "','" + divisionC[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 25
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(11," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + krGameResults[5][1] + "','" + krGameResults[13][1] + "','" + divisionE[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 35
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(12," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + krGameResults[7][1] + "','" + krGameResults[15][1] + "','" + divisionG[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 45
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(12," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + krGameResults[7][1] + "','" + krGameResults[15][1] + "','" + divisionG[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 3
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(13," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',5,'','" + krGameResults[0][2] + "','" + krGameResults[8][2] + "','" + divisionB[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 13
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(14," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',6,'','" + krGameResults[2][2] + "','" + krGameResults[10][2] + "','" + divisionD[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 23
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(15," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',7,'','" + krGameResults[4][2] + "','" + krGameResults[12][2] + "','" + divisionF[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 33
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(16," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',8,'','" + krGameResults[6][2] + "','" + krGameResults[14][2] + "','" + divisionH[4] + "',0,0,0,0,0,0)");
		                // spiel um platz 43
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(16," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',8,'','" + krGameResults[6][2] + "','" + krGameResults[14][2] + "','" + divisionH[4] + "',0,0,0,0,0,0)");
		
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++;
		                // spiel um platz 11
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(17," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + krGameResults[2][1] + "','" + krGameResults[10][1] + "','" + divisionI[3] + "',0,0,0,0,0,0)");
		                // spiel um platz 21
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(18," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',2,'','" + krGameResults[4][1] + "','" + krGameResults[12][1] + "','" + divisionJ[3] + "',0,0,0,0,0,0)");
		                // spiel um platz 31
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(19," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',3,'','" + krGameResults[6][1] + "','" + krGameResults[14][1] + "','" + divisionK[3] + "',0,0,0,0,0,0)");
		                // spiel um platz 41
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(20," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',4,'','" + krGameResults[6][1] + "','" + krGameResults[14][1] + "','" + divisionL[3] + "',0,0,0,0,0,0)");
		
		                startRound = startRound.AddSeconds(addzeit);
		                lastRoundNr++;
		                // spiel um platz 1
		                lastGameNr++;
		                querys.Add("INSERT INTO platzspiele_spielplan VALUES(20," + lastRoundNr + "," + lastGameNr + ",'" + startRound.ToString("hh:mm") + "',1,'','" + krGameResults[0][1] + "','" + krGameResults[8][1] + "','',0,0,0,0,0,0)");
		                break;
		        }
		    }
		    else
		    {
		    	List<String> referees = new List<String>();
		        List<List<String>> krGameResultsCopy = krGameResults;
		        int resultDivisionsZwCountKorrigiert = resultDivisionsZw.Count;
		
		        // if 55 teams, remove the first 5 kr game results, because this teams do not play any classement games
		        if(teamsCount == 55)
		        {
		            for(int t = 0; t < 5; t++)
		            	krGameResultsCopy.RemoveAt(0);
		
		            resultDivisionsZwCountKorrigiert--;
		        }
		
		        // get as many referees as needed for first round
		        for(int z = 0; referees.Count < fieldCount; z++)
		        {
		        	for(int k = 0; k < resultDivisionsZw[z].Count && referees.Count < fieldCount; k++)
		        		referees.Add(resultDivisionsZw[z][k]);
		        }
		
		        // generate games
		        for(int i = 0, x = resultDivisionsZwCountKorrigiert - 1, 
		            y = ((resultDivisionsZw[x].Count + resultDivisionsZw[x - 1].Count) / 2) - 1,
		            startingReferee = 0, id = 1, fCount = 1; (i + 5) < krGameResultsCopy.Count; id++, lastGameNr++, startingReferee++)
		        {
		            String referee1 = "", referee2 = "";
		
		            // get the referee for the looser game
		            if(startingReferee < fieldCount)
		            {
		            	referee1 = referees[startingReferee];
		                startingReferee++;
		            }
		
		            // check if there is a next referee for the winner game
		            if(startingReferee < fieldCount)
		            	referee2 = referees[startingReferee];
		
		            // get winner and looser for the next related games
		            String winner1 = krGameResultsCopy[i][1];
		            String looser1 = krGameResultsCopy[i][2];
		
		            String winner2 = krGameResultsCopy[i + 5][1];
		            String looser2 = krGameResultsCopy[i + 5][2];
		
		            // create looser query
		            querys.Add("INSERT INTO platzspiele_spielplan VALUES(" + id + "," + lastRoundNr + "," + lastGameNr + ",'"
		                      + startRound.ToString("hh:mm") + "'," + fCount + ",'','"
		                      + looser1 + "','" + looser2 + "','" + referee1 + "',0,0,0,0,0,0)");
		
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
		
		            id++; lastGameNr++;
		
		            // create winner query
		            querys.Add("INSERT INTO platzspiele_spielplan VALUES(" + id + "," + lastRoundNr + "," + lastGameNr + ",'"
		                      + startRound.ToString("hh:mm") + "'," + fCount + ",'','"
		                      + winner1 + "','" + winner2 + "','" + referee2 + "',0,0,0,0,0,0)");
		
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
		
		            if(i < y)
		            {
		                i++;
		            }
		            else
		            {
		                x = x - 2;
		                int toAdd = resultDivisionsZw[x].Count + resultDivisionsZw[x - 1].Count;
		                y = y + toAdd;
		                i = i + (toAdd / 2);
		                i++;
		            }
		        }
		    }
		
		    return querys;
		}
	}
}
