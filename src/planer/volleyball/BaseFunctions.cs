/*
 * Created by SharpDevelop.
 * User: cfr
 * Date: 26.06.2017
 * Time: 11:45
 */
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Data.SQLite;
using System.IO;
using System.Net;

namespace volleyball
{
	public class BaseFunctions
	{
		#region members
		Database db;
		List<String> fieldNames;
		int teamsCount, divisionCount;
		QualifyingGames qf;
		InterimGames im;
		PreClassementGames pcg;
		ClassementGames clg;
		#endregion
	
		public BaseFunctions(Database db)
		{
			this.db = db;		
			
			qf = new QualifyingGames(db, MainForm.grPrefix);
			im = new InterimGames(db, MainForm.grPrefix);
			pcg = new PreClassementGames(db, MainForm.grPrefix);
			clg = new ClassementGames(db, MainForm.grPrefix);
		}
		
		public static int parseToInt(String parse)
		{
			return Int32.Parse(parse);
		}
		
		public void ftpUpload()
		{
			Logging.write("INFO: copy database file for upload");
			
			try
			{
				File.Copy(ConfigurationManager.AppSettings["Database"], ConfigurationManager.AppSettings["FTPDatabase"]);
				
				using (WebClient client = new WebClient())
				{
					Logging.write("INFO: start ftp upload");
					
				    client.Credentials = new NetworkCredential(ConfigurationManager.AppSettings["FTPUser"], ConfigurationManager.AppSettings["FTPPw"]);
				    
				    client.UploadFile(ConfigurationManager.AppSettings["FTPUrl"], "STOR", ConfigurationManager.AppSettings["FTPDatabase"]);
				}
			}
			catch(IOException ex)
			{
				Logging.write("ERROR: " + ex);
			}
		}
		
		public void writeConfig(int anzfelder, bool kreuzspiele, bool vorplatzspiele, String startturnier, int pausevrzw, 
		                        int pausezwkr, int pausekrpl, int satzvr, int minsatzvr, int pauseminvr, int satzzw, 
		                        int minsatzzw, int pauseminzw, int satzkr, int minsatzkr, int pauseminkr, int satzpl, 
		                        int minsatzpl, int zeitfinale, int pauseplehrung)
		{
			app.Default.AnzFelder = anzfelder;
			app.Default.Kreuzspiele = kreuzspiele;
			app.Default.Vorplatzspiele = vorplatzspiele;
			app.Default.Startturnier = startturnier;
			app.Default.Pausevrzw = pausevrzw;
			app.Default.Pausezwkr = pausezwkr;
			app.Default.Pausekrpl = pausekrpl;
			app.Default.Satzvr = satzvr;
			app.Default.Minsatzvr = minsatzvr;
			app.Default.Pauseminvr = pauseminvr;
			app.Default.Satzzw = satzzw;
			app.Default.Minsatzzw = minsatzzw;
			app.Default.Pauseminzw = pauseminzw;
			app.Default.Satzkr = satzkr;
			app.Default.Minsatzkr = minsatzkr;
			app.Default.Pauseminkr = pauseminkr;
			app.Default.Satzpl = satzpl;
			app.Default.Minsatzpl = minsatzpl;
			app.Default.Zeitfinale = zeitfinale;
			app.Default.Pauseplehrung = pauseplehrung;
			app.Default.Save();
		}
		
		public void saveTeamChanges(DataTable dt, String query)
		{
			foreach(DataRow dr in dt.Rows)
			{
				SQLiteCommand cmd = db.createCommand(query);
				cmd.Parameters.AddWithValue("@ID", Int32.Parse(dr[0].ToString()));
				cmd.Parameters.AddWithValue("@A", dr[1].ToString());
				cmd.Parameters.AddWithValue("@B", dr[2].ToString());
				cmd.Parameters.AddWithValue("@C", dr[3].ToString());
				cmd.Parameters.AddWithValue("@D", dr[4].ToString());
				cmd.Parameters.AddWithValue("@E", dr[5].ToString());
				cmd.Parameters.AddWithValue("@F", dr[6].ToString());
				cmd.Parameters.AddWithValue("@G", dr[7].ToString());
				cmd.Parameters.AddWithValue("@H", dr[8].ToString());
				cmd.Parameters.AddWithValue("@I", dr[9].ToString());
				cmd.Parameters.AddWithValue("@J", dr[10].ToString());
				cmd.Parameters.AddWithValue("@K", dr[11].ToString());
				cmd.Parameters.AddWithValue("@L", dr[12].ToString());
				
				cmd.ExecuteNonQuery();
			}
		}
		
		public void saveGameplanChanges(DataTable dt, String query)
		{
			foreach(DataRow dr in dt.Rows)
			{
				SQLiteCommand cmd = db.createCommand(query);
				cmd.Parameters.AddWithValue("@ID", Int32.Parse(dr[0].ToString()));
				cmd.Parameters.AddWithValue("@RUNDE", dr[1].ToString());
				cmd.Parameters.AddWithValue("@SPIEL", dr[2].ToString());
				cmd.Parameters.AddWithValue("@ZEIT", dr[3].ToString());
				cmd.Parameters.AddWithValue("@FELDNUMMER", dr[4].ToString());
				cmd.Parameters.AddWithValue("@FELDNAME", dr[5].ToString());
				cmd.Parameters.AddWithValue("@MSA", dr[6].ToString());
				cmd.Parameters.AddWithValue("@MSB", dr[7].ToString());
				cmd.Parameters.AddWithValue("@SR", dr[8].ToString());
				cmd.Parameters.AddWithValue("@SATZ1A", dr[9].ToString());
				cmd.Parameters.AddWithValue("@SATZ1B", dr[10].ToString());
				cmd.Parameters.AddWithValue("@SATZ2A", dr[11].ToString());
				cmd.Parameters.AddWithValue("@SATZ2B", dr[12].ToString());
				cmd.Parameters.AddWithValue("@SATZ3A", dr[13].ToString());
				cmd.Parameters.AddWithValue("@SATZ3B", dr[14].ToString());
				
				cmd.ExecuteNonQuery();
			}
		}
		
		public void resetConfig()
		{
			writeConfig(4, true, false, "10:00", 0, 0, 0, 1, 10, 0, 1, 10, 0, 1, 10, 0, 1, 10, 15, 30);
		}
		
		public List<String> getFieldNames()
		{
			List<List<String>> fieldNameList = db.read(ConfigurationManager.AppSettings["SelectFields"]);
		    List<String> nameList = new List<String>();
		
		    foreach(List<String> fieldName in fieldNameList)
		    	nameList.Add(fieldName[0]);
		
		    return nameList;
		}
		
		public int getTeamsCount()
		{
		    List<List<String>> table = db.read(ConfigurationManager.AppSettings["CountTeams"]);
		    int count = parseToInt(table[0][0]);
		
		    Logging.write("GENERAL: teams count => " + count);
		    return count;
		}
		
		public int getDivisionsCount()
		{
			List<List<String>> table = db.read(ConfigurationManager.AppSettings["CountDivisions"]);
		    int count = parseToInt(table[0][0]);
		
		    Logging.write("GENERAL: division count => " + count);
		    return count;
		}
		
		public void setFieldsTableRows(decimal spinBoxCount)
		{
			int count = Int32.Parse(db.read(ConfigurationManager.AppSettings["CountFields"])[0][0]);
			
		    if(count < spinBoxCount)
		    {
		    	for (int i = count + 1; i <= spinBoxCount; i++)
		    	{
		    		SQLiteCommand cmd = db.createCommand(ConfigurationManager.AppSettings["InsertField"]);
					cmd.Parameters.AddWithValue("@ID", Int32.Parse(i.ToString()));
					cmd.ExecuteNonQuery();
		    	}
		    }
		    else if(count > spinBoxCount)
		    {
		    	db.write(ConfigurationManager.AppSettings["DeleteField"] + spinBoxCount);
		    }
		}
		
		public void resetTeams()
		{
			db.write(ConfigurationManager.AppSettings["DeleteTeams"]);
		
		    foreach(String row in MainForm.insertRows)
		    	db.write(row);
		}
		
		public bool checkDoubleTeamNames(DataTable dt)
		{
		    int count = 0;
		    bool twoteams = false;
		    String team = "";
		
		    for(int row = 0, col = 1; col < dt.Columns.Count;)
		    {
		    	team = dt.Rows[row][col].ToString();
		        for(int i = 0; i < dt.Rows.Count; i++)
		        {
		            for(int j = 1; j < dt.Columns.Count; j++)
		            {
		                if(team == dt.Rows[i][j].ToString() && team != "" )
		                	count++;
		                
		                if(count > 1)
		                {
		                    twoteams = true;
		                    break;
		                }
		            }
		        }
		        
		        count = 0;
		        row++;
		        
		        if(row == dt.Rows.Count)
		        {
		            col++;
		            row = 0;
		        }
		    }
		
		    return twoteams;
		}
				
		public void setParametersQualifyingGames()
		{
		    fieldNames = getFieldNames();
		    teamsCount = getTeamsCount();
		    divisionCount = getDivisionsCount();
		    qf.setParameters(app.Default.Startturnier,app.Default.Satzvr, app.Default.Minsatzvr, app.Default.Pauseminvr, 
		                     app.Default.AnzFelder, teamsCount, fieldNames);
		}
		
		public void generateQualifyingGames()
		{
		    qf.generateGames();
		}
	
		public void clearQualifyingGames()
		{
		    qf.clearAllData(MainForm.qfTablesToClear);
		}
		
		public void calculateQualifyingGames()
		{
		    qf.calculateResult("vorrunde_spielplan", "vorrunde_erg_gr");
		}
		
		public void recalculateQualifyingGamesTimeSchedule(DataTable dt)
		{
		    //qf.recalculateTimeSchedule(qtv, tm);
		}
		
		public int getQualifyingGamesCount()
		{
		    return db.read("SELECT * FROM vorrunde_spielplan").Count;
		}
		
		public List<String> checkEqualDivisionResults()
		{
		    return qf.checkEqualDivisionResults("vorrunde_spielplan", "vorrunde_erg_gr");
		}
		
		public String getQualifyingGamesMaxTime()
		{
			return db.read(ConfigurationManager.AppSettings["QualifyingMaxTime"])[0][0];
		}
		
		public void setParametersInterimGames()
		{
			List<String> parameter = db.read(ConfigurationManager.AppSettings["InterimLastRoundData"])[0];
			im.setParameters(parameter[2], app.Default.Pausevrzw, app.Default.Satzzw, app.Default.Minsatzzw, app.Default.Pauseminzw,
		                      app.Default.AnzFelder, teamsCount, divisionCount, fieldNames,
		                      parseToInt(parameter[0]), parseToInt(parameter[1]), app.Default.Vorplatzspiele);
		}
		
		public bool generateInterimGames()
		{
		    return im.generateGames();
		}
		
		public void clearInterimGames()
		{
		    im.clearAllData(MainForm.itTablesToClear);
		}
		
		public void calculateInterimGames()
		{
		    im.calculateResult("zwischenrunde_spielplan", "zwischenrunde_erg_gr");
		}
		
		public void recalculateInterimGamesTimeSchedule(DataTable dt)
		{
		    //im->recalculateTimeSchedule(qtv, tm);
		}
		
		public int getInterimGamesCount()
		{
		    return db.read(ConfigurationManager.AppSettings["InterimGamesCount"]).Count;
		}
		
		public String getInterimGamesMaxTime()
		{
			return db.read(ConfigurationManager.AppSettings["InterimGameMaxTime"])[0][0];
		}
		
		public void setParametersPreClassement()
		{
			List<String> parameter = db.read(ConfigurationManager.AppSettings["PreClassementLastRoundData"])[0];
			pcg.setParameters(parameter[2], ((app.Default.Satzzw * app.Default.Minsatzzw) + app.Default.Pauseminzw),
			                  app.Default.Pausezwkr, app.Default.Satzkr, app.Default.Minsatzkr, app.Default.Pauseminkr, app.Default.AnzFelder, teamsCount,
			                  divisionCount, fieldNames, parseToInt(parameter[0]), parseToInt(parameter[1]), app.Default.Vorplatzspiele);
		}
		
		public void generatePreClassement()
		{
		    pcg.generatePreClassement();
		}
		
		public void clearPreClassement()
		{
		    pcg.clearAllData(MainForm.pcTablesToClear);
		}
		
		public void recalculatePreClassementTimeSchedule(DataTable dt)
		{
		    //cg->recalculateTimeSchedule(qtv, tm);
		}
		
		public int getPreClassementCount()
		{
		    return db.read(ConfigurationManager.AppSettings["PreClassementCount"]).Count;
		}
		
		public String getPreClassementMaxTime()
		{
			return db.read(ConfigurationManager.AppSettings["PreClassementMaxTime"])[0][0];
		}
		
		public void setParametersClassementGames()
		{
			List<String> parameter = db.read(ConfigurationManager.AppSettings["ClassementLastRoundData"])[0];
			clg.setParameters(parameter[2], ((app.Default.Satzkr * app.Default.Minsatzkr) + app.Default.Pauseminkr),
			                  app.Default.Pausekrpl, app.Default.Satzpl, app.Default.Minsatzpl, app.Default.AnzFelder, teamsCount, 
			                  divisionCount, fieldNames, parseToInt(parameter[0]), parseToInt(parameter[1]), app.Default.Vorplatzspiele);
		}
		
		public void generateClassementGames()
		{
		    clg.generateClassementGames();
		}
		
		public void clearClassementGames()
		{
		    clg.clearAllData(MainForm.clTablesToClear);
		}
		
		public void recalculateClassementGamesTimeSchedule(DataTable dt)
		{
		    //clg->recalculateTimeSchedule(qtv, tm);
		}
		
		public int getClassementGamesCount()
		{
		    return db.read(ConfigurationManager.AppSettings["ClassementGamesCount"]).Count;
		}
		
		public void getFinalClassement()
		{
		    clg.finalTournamentResults();
		}
		
		public String getClassementGamesMaxTime()
		{
			return db.read(ConfigurationManager.AppSettings["ClassementMaxTime"])[0][0];
		}
	}
}
