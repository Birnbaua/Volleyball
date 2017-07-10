/*
 * Created by SharpDevelop.
 * User: cfr
 * Date: 15.05.2017
 * Time: 10:44
 */
using System;
using System.Collections.Generic;
using System.Data;

namespace volleyball
{
	public class BaseGameHandling
	{
		#region members
		Database db;
		public List<String> grPrefix, fieldNames;
		public int satz, min, pause, fieldCount, teamsCount, gamesCount;
		#endregion
		
		public BaseGameHandling(Database db, List<String> grPrefix)
		{
			this.db = db;
			this.grPrefix = grPrefix;
		}
		
		public virtual void writeListToDatabase(List<String> querys)
		{
			if(querys.Count > 0)
			{
				foreach(String query in querys)
		    		db.write(query);
			}
			else
			{
				Logging.write("WARNING: no entry in list, cancel database write action");
			}
		}
		
		public virtual List<List<String>> readListFromDatabase(String query)
		{
			return db.read(query);
		}
				
		public virtual void setParameters(int satz, int min, int pause, int fieldCount, int teamsCount, int gamesCount, 
		                                  List<String> fieldNames)
		{
		    this.satz = satz;
		    this.min = min;
		    this.pause = pause;
		    this.fieldCount = fieldCount;
		    this.fieldNames = fieldNames;
		    this.teamsCount = teamsCount;
		    this.gamesCount = gamesCount;
		}
		
		public virtual void clearAllData(List<String> tables)
		{		
			foreach(String table in tables)
		    	db.write("DELETE FROM " + table);
		}
		
		public virtual void calculateResult(String round, String resultTableName)
		{
		    Logging.write("calculating " + round + " results");
		    
		    List<List<String>> vrGameResults = db.read("SELECT spiel, ms_a, ms_b, satz1a, satz1b, satz2a, satz2b, satz3a, satz3b FROM " + round + " WHERE ms_a != '---' ORDER BY id ASC");
		    List<TeamResult> teamResults = CalculateResults.addResultsVrZw(CalculateResults.calculateResults(vrGameResults));
		
		    foreach(TeamResult tR in teamResults)
		    {
		        String division = "";
		        for(int i = 0; i < grPrefix.Count; i++)
		        {
		        	String prefix = grPrefix[i];
		
		            if(db.read("SELECT * FROM " + resultTableName + prefix + " WHERE ms = '" + tR.TeamName + "'").Count > 0)
		                division = prefix;
		        }
		        
		        db.write("UPDATE " + resultTableName + division + " SET punkte=" + tR.Sets + ", satz=" + tR.Points + " WHERE ms = '" + tR.TeamName + "'");
		    }
		}
		
		public virtual void recalculateTimeSchedule(DataTable dt)
		{
		    /*DateTime zeit = qtv->currentIndex().data().toTime();
		    int addzeit = ((satz * min) + pause) * 60;
		    int runde = model->data(model->index(qtv->currentIndex().row(), 1)).toInt();
		
		    for(int i = qtv->currentIndex().row(); i <= model->rowCount(); i++)
		    {
		        if(runde != model->data(model->index(i, 1)).toInt())
		        {
		            zeit = zeit.AddSeconds(addzeit);
		            runde++;
		        }
		        model->setData(model->index(i, 3), zeit.ToString("hh:mm"));
		    }
		    */
		}

		public virtual List<String> insertFieldNr(String round)
		{
			List<String> querys = new List<String>();
		
		    for (int i = 1, field = 1; i <= gamesCount; i++)
		    {
		        for(int x = 1, fieldHelp = field; x <= fieldCount; x++, fieldHelp++, i++)
		        {
		            querys.Add("UPDATE " + round + " SET feldnummer = " + fieldHelp + " WHERE id = " + i);
		            if(fieldHelp >= fieldCount)
		                fieldHelp = 0;
		        }
		
		        i--;
		
		        if(field < fieldCount)
		            field++;
		        else
		            field = 1;
		    }
		
		    return querys;
		}

		public virtual List<String> insertFieldNames(String round)
		{
			List<String> querys = new List<String>();
		
		    for(int i = 1; i <= fieldNames.Count; i++)
		    	querys.Add("UPDATE " + round + " SET feldname = '" + fieldNames[i - 1] + "' WHERE feldnummer = " + i);
		
		    return querys;
		}

		
		public virtual List<String> generateResultTables(String round, List<List<String>> divisionsList)
		{
			List<String> querys = new List<String>();
		
		    for(int i = 0, prefix = 0; i < divisionsList.Count; i++, prefix++)
		    {
		    	List<String> division = divisionsList[i];
		    	String group = grPrefix[prefix];
		
		        for(int x = 0; x < division.Count; x++)
		        {
		        	String team = division[x];
		        	querys.Add("INSERT INTO " + round + group + " VALUES(" + x + ",'" + team + "',0,0,0,0)");
		        }
		    }
		
		    return querys;
		}

		public virtual List<String> checkEqualDivisionResults(String round, String resultTableName)
		{
			List<String> result = new List<String>();
		
			for(int i = 0; i < grPrefix.Count; i++)
		    {
				String prefix = grPrefix[i];
		
		        List<List<String>> getTeams = db.read("select distinct ms1.ms from " + resultTableName
		                                                  + prefix + " ms1, (select ms, satz, punkte, intern from " + resultTableName
		                                                  + prefix + ") ms2 where ms1.satz = ms2.satz and  ms1.punkte = ms2.punkte and ms1.intern = ms2.intern and ms1.ms != ms2.ms");
		
		        if(getTeams.Count == 2)
		        {
		        	List<String> team1 = getTeams[0];
		        	List<String> team2 = getTeams[1];
		        	
		            String gamenr = db.read("SELECT spiel from " + round + " where ms_a = '" 
		        	                         + team1[0] + "' and ms_b = '" + team2[0] + "' or ms_a = '"
		        	                         + team2[0] + "' and ms_b = '" + team1[0] + "'")[0][0];
		
		            result.Add("0");
		            result.Add(gamenr);
		            result.Add(team1[0]);
		            result.Add(team2[0]);
		            
		            return result;
		        }
		        
		        if(getTeams.Count > 2)
		        {
		        	List<String> teams = new List<String>();
		
		        	teams.Add("1");
		
		            foreach(List<String> team in getTeams)
		            	teams.Add(team[0]);
		
		            return teams;
		        }
		    }

    		return result;
		}

		public virtual String getPrefix(int index)
		{
			return grPrefix[index];
		}

		public virtual int getPrefixCount()
		{
		    return grPrefix.Count;
		}
	}
}
