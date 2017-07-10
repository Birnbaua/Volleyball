/*
 * Created by SharpDevelop.
 * User: cfr
 * Date: 15.05.2017
 * Time: 10:43
 */
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Data.SQLite;
using System.Text;
using System.Windows.Forms;
using System.IO;

namespace volleyball
{
	public partial class MainForm : Form
	{
		#region members
		Database db;
		DataTable dtTeams, dtFields, dtQualifying, dtInterim, dtPreClassement, dtClassement;
		SQLiteDataAdapter daTeams, daFields, daQualifying, daInterim, daPreClassement, daClassement;
		BaseFunctions baseFunctions;
		public static List<String> grPrefix, headerPrefix, headerGameplan, insertRows, qfTablesToClear, 
								   itTablesToClear, pcTablesToClear, clTablesToClear, headerResult;
		About about;
		String versioninfo;
		DivisonResults divisionresults;
		#endregion
						
		public MainForm()
		{
			InitializeComponent();

			init();
			
			if(db.open())
			{
				baseFunctions = new BaseFunctions(db);
				
				initGUIModules();
				
				initTeams();
				
				initFields();
				
				initQualifying(app.Default.Satzvr);	
				
				initInterim(app.Default.Satzzw);
				
				initPreClassement(app.Default.Satzkr);
				
				initClassement(app.Default.Satzpl);
			}
			else
			{
				MessageBox.Show("Can not open database!", "Error");
				Environment.Exit(-1);
			}
		}
		
		void init()
		{
			Logging.fileName = ConfigurationManager.AppSettings["Logging"];
			
			db = new Database(ConfigurationManager.AppSettings["Database"]);
			
			headerPrefix = new List<String>() { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L" };
			
			grPrefix = new List<String>() { "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l" };
			
			insertRows = new List<String>() { "INSERT INTO mannschaften (id,a,b,c,d,e,f,g,h,i,j) VALUES(0,'','','','','','','','','','')",
										      "INSERT INTO mannschaften (id,a,b,c,d,e,f,g,h,i,j) VALUES(1,'','','','','','','','','','')",
		                                      "INSERT INTO mannschaften (id,a,b,c,d,e,f,g,h,i,j) VALUES(2,'','','','','','','','','','')",
		                                      "INSERT INTO mannschaften (id,a,b,c,d,e,f,g,h,i,j) VALUES(3,'','','','','','','','','','')",
		                                      "INSERT INTO mannschaften (id,a,b,c,d,e,f,g,h,i,j) VALUES(4,'','','','','','','','','','')" };
			
			qfTablesToClear = new List<String>() { "vorrunde_spielplan", "vorrunde_erg_gr" };
			
			itTablesToClear = new List<String>() { "zwischenrunde_spielplan", "zwischenrunde_erg_gr" };
			
			pcTablesToClear = new List<String>() { "kreuzspiele_spielplan" };
			
			clTablesToClear = new List<String>() { "platzspiele_spielplan", "platzierungen" };
			
			headerGameplan = new List<String>() { "Id", "Runde", "Spiel", "Zeit", "Feldnr", "Feldname", "Mannschaft A",
												  "Mannschaft B", "Schiedsgericht", "Satz 1 A", "Satz 1 B",
												  "Satz 2 A", "Satz 2 B", "Satz 3 A", "Satz 3 B" };
		
			headerResult = new List<String>() { "Mannschaft" << "Punkte" << "Spielpunkte" << "Intern" << "Extern" };
			
			using (var streamReader = new StreamReader(new FileStream(ConfigurationManager.AppSettings["Version"], FileMode.Open, FileAccess.Read), Encoding.UTF8))
				versioninfo = streamReader.ReadToEnd();
		}
		
		void initGUIModules()
		{
			this.Text = ConfigurationManager.AppSettings["Title"] + ConfigurationManager.AppSettings["Versionnr"];
			
			about = new About(this.Text + " " + ConfigurationManager.AppSettings["About"], versioninfo);
			
			divisionresults = new DivisonResults(db, grPrefix);
			
			numericUpDownFieldCount.Value = app.Default.AnzFelder;
		}
		
		void messageboxInfo(String msg)
		{
			MessageBox.Show(msg, "Info", MessageBoxButtons.OK, MessageBoxIcon.Asterisk);
		}
		
		void messageboxWarning(String msg)
		{
			MessageBox.Show(msg, "Warnung", MessageBoxButtons.OK, MessageBoxIcon.Warning);
		}
		
		void messageboxError(String msg)
		{
			MessageBox.Show(msg, "Fehler", MessageBoxButtons.OK, MessageBoxIcon.Error);
		}
		
		bool userButtonCheck(String msg)
		{
			DialogResult result = MessageBox.Show(msg, "Warnung", MessageBoxButtons.OKCancel, MessageBoxIcon.Question);
			
			if(result == DialogResult.OK)
				return true;
			
			return false;
		}
		
		void hideColumns(DataGridView dgv, int colsoHide, bool isGameplan)
		{
			if(!isGameplan)
			{
				if(colsoHide > -1)
					dgv.Columns[colsoHide].Visible = false;
			}
			else
			{
				switch(colsoHide)
			    {
			        case 1: dgv.Columns[11].Visible = false;
			                dgv.Columns[12].Visible = false;
			                dgv.Columns[13].Visible = false;
			                dgv.Columns[14].Visible = false;
			                break;
			                
			        case 2: dgv.Columns[11].Visible = true;
			                dgv.Columns[12].Visible = true;
			                dgv.Columns[13].Visible = false;
			                dgv.Columns[14].Visible = false;
			                break;
			                
			        case 3: dgv.Columns[11].Visible = true;
			                dgv.Columns[12].Visible = true;
			                dgv.Columns[13].Visible = true;
			                dgv.Columns[14].Visible = true;
			                break;
			    }
			}
		}
		
		void initTeams()
		{
			Logging.write("INFO: init datatable teams");
			
			if(daTeams != null)
				daTeams.Dispose();
			
			daTeams = new SQLiteDataAdapter(ConfigurationManager.AppSettings["SelectTeams"], db.DBCONNECTION);
			
			if(dtTeams != null)
				dtTeams.Dispose();
			
			dtTeams = new DataTable();
			
			daTeams.Fill(dtTeams);
			
			dataGridViewTeams.DataSource = dtTeams.DefaultView;
			
			hideColumns(dataGridViewTeams, 0, false);
			
			for(int i = 0; i < headerPrefix.Count; i++)
				dataGridViewTeams.Columns[i + 1].HeaderText = "Gruppe " + headerPrefix[i];
		}
		
		void ButtonTeamsSaveClick(object sender, EventArgs e)
		{
			dataGridViewTeams.EndEdit();
			
			try
			{
				if(!baseFunctions.checkDoubleTeamNames(dtTeams))
				{
					Logging.write("INFO: no double team names");
					
					if(userButtonCheck("Bitte bestätigen um die Mannschaften zu speichern!"))
					{
						Logging.write("INFO: saving teams");
						
						baseFunctions.saveTeamChanges(dtTeams, ConfigurationManager.AppSettings["UpdateTeams"]);
						
						messageboxInfo("Mannschaften wurden gespeichert");
					}
				}
				else
				{
					Logging.write("ERROR: double team names, saving canceled");
	    		
	    			messageboxError("Doppelte Mannschaftsnamen vorhanden, speichern abgebrochen!");		
				}
			}
			catch(Exception ex)
			{
				Logging.write("ERROR: " + ex);
				
		        messageboxError("Teams speichern fehlgeschlagen!");
			}
		}	
		
		void ButtonClearTeamsClick(object sender, EventArgs e)
		{
			if(userButtonCheck("Bitte bestätigen um die Mannschaften zu löschen!"))
		    {
		        Logging.write("INFO: deleting teams");
		        
		        baseFunctions.resetTeams();
		        
		        initTeams();
		        
		        messageboxInfo("Mannschaften wurden zurückgesetzt");	        
		    }
			else
			{
				Logging.write("INFO: deleting teams aborted");
				
				messageboxInfo("Mannschaften speichern abgebrochen!");
			}
		}
		
		void initFields()
		{
			Logging.write("INFO: init datatable fields");
			
			if(daFields != null)
				daFields.Dispose();
			
			daFields = new SQLiteDataAdapter(ConfigurationManager.AppSettings["SelectFields"], db.DBCONNECTION);
			
			if(dtFields != null)
				dtFields.Dispose();
			
			dtFields = new DataTable();
			
			daFields.Fill(dtFields);
			
			dataGridViewFields.DataSource = dtFields.DefaultView;
				
			dataGridViewFields.Columns[0].HeaderText = "Feldnr.";
			dataGridViewFields.Columns[1].HeaderText = "Feldname";
		}
		
		void NumericUpDownFieldCountValueChanged(object sender, EventArgs e)
		{
			decimal value = ((NumericUpDown)sender).Value;
			
			Logging.write("INFO: field count changed to " + value);
    
			baseFunctions.setFieldsTableRows(value);
    
			initFields();
		}
		
		void initQualifying(int hideCol)
		{
			Logging.write("INFO: init datatable qualifying");
			
			if(daQualifying != null)
				daQualifying.Dispose();
			
			daQualifying = new SQLiteDataAdapter(ConfigurationManager.AppSettings["SelectQualifying"], db.DBCONNECTION);
			
			if(dtQualifying != null)
				dtQualifying.Dispose();
			
			dtQualifying = new DataTable();
			
			daQualifying.Fill(dtQualifying);
			
			dataGridViewQualifying.DataSource = dtQualifying.DefaultView;
			
			hideColumns(dataGridViewQualifying, hideCol, true);
			hideColumns(dataGridViewQualifying, 0, false);
			
			for(int i = 0; i < headerGameplan.Count; i++)
				dataGridViewQualifying.Columns[i].HeaderText = headerGameplan[i];
		}
		
		void ButtonQfGenerateClick(object sender, EventArgs e)
		{
			

		    if(dtQualifying.Rows.Count > 0)
		    {
		    	messageboxWarning("Runde wurde bereits generiert!\nGenerieren abgebrochen!");
		    	return;
		    }
		    
		    Logging.write("INFO: generate qualifying games");
		    
		    baseFunctions.setParametersQualifyingGames();
			    
			baseFunctions.generateQualifyingGames();
			
			initQualifying(app.Default.Satzvr);
			    
			messageboxInfo("Vorrunde wurde generiert");
			    
			ButtonQfSaveClick(null, null);
		}
		
		void ButtonQfSaveClick(object sender, EventArgs e)
		{
			Logging.write("INFO: saving qualifying round");

			try
			{
				dataGridViewQualifying.EndEdit();
									
				baseFunctions.saveGameplanChanges(dtQualifying, ConfigurationManager.AppSettings["UpdateQualifying"]);
				
				messageboxInfo("Vorrunde wurde gespeichert");
		        
		        baseFunctions.calculateQualifyingGames();
		        
		        baseFunctions.ftpUpload();
			}
			catch(Exception ex)
		    {
				Logging.write("ERROR: " + ex);
		        messageboxError("Vorrunde speichern fehlgeschlagen!");
		    }
		}
		
		void ButtonQfDeleteClick(object sender, EventArgs e)
		{
			if(userButtonCheck("Bitte bestätigen um Vorrunde zurückzusetzen!"))
		    {
		        Logging.write("INFO: deleting qualifyings");
		        
		        baseFunctions.clearQualifyingGames();
		        
		        ButtonQfSaveClick(null, null);
		        
		        initQualifying(app.Default.Satzvr);
		        
		        messageboxInfo("Vorrundespielplan und Ergebnisse wurden gelöscht");
		        
		        return;
		    }
		
		    Logging.write("INFO: reset qualifying aborted");
		    
		    messageboxInfo("Zurücksetzen von Vorrundespielplan und Ergebnissen abgebrochen!");
		}
		
		void ButtonQfPrintClick(object sender, EventArgs e)
		{
	
		}
		
		void ButtonQfResultsClick(object sender, EventArgs e)
		{
			divisionresults.Show();
		}
		
		void ButtonQfOverallResultsClick(object sender, EventArgs e)
		{
	
		}
		
		void initInterim(int hideCol)
		{
			Logging.write("INFO: init datatable interim");
			
			if(daInterim != null)
				daInterim.Dispose();
			
			daInterim = new SQLiteDataAdapter(ConfigurationManager.AppSettings["SelectInterim"], db.DBCONNECTION);
			
			if(dtInterim != null)
				dtInterim.Dispose();
			
			dtInterim = new DataTable();
			
			daInterim.Fill(dtInterim);
			
			dataGridViewInterim.DataSource = dtInterim.DefaultView;
			
			hideColumns(dataGridViewInterim, hideCol, true);
			hideColumns(dataGridViewInterim, 0, false);
						
			for(int i = 0; i < headerGameplan.Count; i++)
				dataGridViewInterim.Columns[i].HeaderText = headerGameplan[i];
		}
		
		void ButtonInGenerateClick(object sender, EventArgs e)
		{
			if(dtInterim.Rows.Count > 0)
		    {
		        messageboxWarning("Runde wurde bereits generiert!\nGenerieren abgebrochen!");
		        return;
		    }
			
			Logging.write("INFO: generate interim round");
		
		    List<String> equalDivisionResults = baseFunctions.checkEqualDivisionResults();
		
		    if(equalDivisionResults.Count > 0)
		    {
		    	if(equalDivisionResults[0] == "0")
		        {
		            equalDivisionResults.RemoveAt(0);
		            
		            Logging.write("WARNING: equal qualifying division results");
		            
		            messageboxWarning("Achtung! Vorrunde, Gleichstände zwischen den Mannschaften "
		                              + equalDivisionResults[1] + " und " + equalDivisionResults[2] 
		                              + " entdeckt!\nDirektes Duell bei Spielnr. " 
		                              +  equalDivisionResults[0]
		                              + "\nZwischenrunde generieren wird abgebrochen!");
		            return;
		        }
		    	
		    	if(equalDivisionResults[0] == "1")
		        {
		            equalDivisionResults.RemoveAt(0);
		            
		            Logging.write("WARNING: equal qualifying division results");
		
		            String msgtext = "Achtung! Vorrunde, Gleichstände zwischen mehrere Mannschaften entdeckt!\n";
		            msgtext += "Folgende Mannschaften sind betroffen:";
		
		            foreach(String equaldivisionteam in equalDivisionResults)
		                msgtext += "\n" + equaldivisionteam;
		
		            msgtext += "\nZwischenrunde generieren wird abgebrochen!";
		            
		            messageboxWarning(msgtext);
		            
		            return;
		        }
		    }
		
		    Logging.write("INFO: generate interim games");
		    
		    baseFunctions.setParametersInterimGames();
		    
		    if(!baseFunctions.generateInterimGames())
		    {
		        Logging.write("WARNING: equal qualifying over all divisions results");
		        
		        messageboxWarning("Achtung! Vorrunde, Gruppengleichstände zwischen Mannschaften entdeckt!"
		                          + "\nBitte Punktestände überprüfen, Zwischenrunde generieren wird abgebrochen!");
		        return;
		    }
		
		    initInterim(app.Default.Satzzw);
		    
		    messageboxInfo("Zwischenrunde wurde generiert");
		    
		    ButtonInSaveClick(null, null);
		}
		
		void ButtonInSaveClick(object sender, EventArgs e)
		{
			Logging.write("INFO: saving interim round");

			try
			{
				dataGridViewInterim.EndEdit();
									
				baseFunctions.saveGameplanChanges(dtInterim, ConfigurationManager.AppSettings["UpdateInterim"]);
				
				messageboxInfo("Zwischenrunde wurde gespeichert");
		        
		        baseFunctions.calculateInterimGames();
		        
		        baseFunctions.ftpUpload();
			}
			catch(Exception ex)
		    {
				Logging.write("ERROR: " + ex);
		        messageboxError("Zwischenrunde speichern fehlgeschlagen!");
		    }
		}
		
		void ButtonInDeleteClick(object sender, EventArgs e)
		{
			Logging.write("INFO: delete interim round");
			
			if(userButtonCheck("Bitte bestätigen um Zwischenrunde zurückzusetzen!"))
		    {
		        Logging.write("INFO: deleting interim");
		        
		        baseFunctions.clearInterimGames();
		        
		        ButtonInSaveClick(null, null);
		        
		        initInterim(app.Default.Satzzw);
		        
		        messageboxInfo("Zwischenrundenspielplan und Ergebnisse wurden gelöscht");
		        
		        return;
		    }
		
		    Logging.write("INFO: reset interim aborted");
		    
		    messageboxInfo("Zurücksetzen von Zwischenrundespielplan und Ergebnissen abgebrochen!");
		}
		
		void ButtonInPrintClick(object sender, EventArgs e)
		{
	
		}
		
		void ButtonInResultsClick(object sender, EventArgs e)
		{
	
		}
		
		void initPreClassement(int hideCol)
		{
			Logging.write("INFO: init datatable preclassement");
			
			if(daPreClassement != null)
				daPreClassement.Dispose();
			
			daPreClassement = new SQLiteDataAdapter(ConfigurationManager.AppSettings["SelectPreClassement"], db.DBCONNECTION);
			
			if(dtPreClassement != null)
				dtPreClassement.Dispose();
			
			dtPreClassement = new DataTable();
			
			daPreClassement.Fill(dtPreClassement);
			
			dataGridViewPreClassement.DataSource = dtPreClassement.DefaultView;
			
			hideColumns(dataGridViewPreClassement, hideCol, true);
			hideColumns(dataGridViewPreClassement, 0, false);
						
			for(int i = 0; i < headerGameplan.Count; i++)
				dataGridViewPreClassement.Columns[i].HeaderText = headerGameplan[i];
		}
		
		void ButtonPreClGenerateClick(object sender, EventArgs e)
		{
			if(dtPreClassement.Rows.Count > 0)
		    {
		        messageboxWarning("Runde wurde bereits generiert!\nGenerieren abgebrochen!");
		        return;
		    }
		
			Logging.write("INFO: generate preclassement round");
			
		    List<String> equalDivisionResults = baseFunctions.checkEqualDivisionResults();

		    if(equalDivisionResults.Count > 0)
		    {
		    	if(equalDivisionResults[0] == "0")
		        {
		            equalDivisionResults.RemoveAt(0);
		            
		            Logging.write("WARNING: equal interim division results");
		            
		            messageboxWarning("Achtung! Zwischenrunde, Gleichstände zwischen den Mannschaften "
		                              + equalDivisionResults[1] + " und " + equalDivisionResults[2]
		                              + " entdeckt!\nDirektes Duell bei Spielnr. " 
		                              +  equalDivisionResults[0] + "\nKreuzspiele generieren wird abgebrochen!");
		            
		            return;
		        }
		    	
		    	if(equalDivisionResults[0] == "1")
		        {
		            equalDivisionResults.RemoveAt(0);
		            
		            Logging.write("WARNING: equal interim division results");
		
		            String msgtext = "Achtung! Zwischenrunde, Gleichstände zwischen mehrere Mannschaften entdeckt!\n";
		            msgtext += "Folgende Mannschaften sind betroffen:";
		
		            foreach(String equaldivisionteam in equalDivisionResults)
		                msgtext += "\n" + equaldivisionteam;
		
		            msgtext += "\nKreuzspiele generieren wird abgebrochen!";
		            
		            messageboxWarning(msgtext);
		            
		            return;
		        }
		    	
		        return;
		    }
		
		    Logging.write("INFO: generate preclassement");
		    
		    baseFunctions.setParametersPreClassement();
		    
		    baseFunctions.generatePreClassement();
		    
		    initPreClassement(app.Default.Satzkr);
		    
		    messageboxInfo("Kreuzspiele wurden generiert");
		    
		    ButtonPreClSaveClick(null, null);
		}
		
		void ButtonPreClSaveClick(object sender, EventArgs e)
		{
			Logging.write("INFO: saving preclassement round");

			try
			{
				dataGridViewPreClassement.EndEdit();
									
				baseFunctions.saveGameplanChanges(dtPreClassement, ConfigurationManager.AppSettings["UpdatePreClassement"]);
				
				messageboxInfo("Kreuzspiele wurde gespeichert");
		        		        
		        baseFunctions.ftpUpload();
			}
			catch(Exception ex)
		    {
				Logging.write("ERROR: " + ex);
		        messageboxError("Kreuzspiele speichern fehlgeschlagen!");
		    }
		}
		
		void ButtonPreClDeleteClick(object sender, EventArgs e)
		{
			Logging.write("INFO: delete preclassement round");
			
			if(userButtonCheck("Bitte bestätigen um Kreuzspiele zurückzusetzen!"))
		    {
		        Logging.write("INFO: deleting preclassement");
		        
		        baseFunctions.clearPreClassement();
		        
		        ButtonInSaveClick(null, null);
		        
		        initInterim(app.Default.Satzkr);
		        
		        messageboxInfo("Kreuzspielespielplan und Ergebnisse wurden gelöscht");
		        
		        return;
		    }
		
		    Logging.write("INFO: reset preclassement aborted");
		    
		    messageboxInfo("Zurücksetzen von Kreuzspielespielplan abgebrochen!");
		}
		
		void ButtonPreClPrintClick(object sender, EventArgs e)
		{
	
		}
		
		void initClassement(int hideCol)
		{
			Logging.write("INFO: init datatable classement");
			
			if(daClassement != null)
				daClassement.Dispose();
			
			daClassement = new SQLiteDataAdapter(ConfigurationManager.AppSettings["SelectClassement"], db.DBCONNECTION);
			
			if(dtClassement != null)
				dtClassement.Dispose();
			
			dtClassement = new DataTable();
			
			daClassement.Fill(dtClassement);
			
			dataGridViewClassement.DataSource = dtClassement.DefaultView;
			
			hideColumns(dataGridViewClassement, hideCol, true);
			hideColumns(dataGridViewClassement, 0, false);
						
			for(int i = 0; i < headerGameplan.Count; i++)
				dataGridViewClassement.Columns[i].HeaderText = headerGameplan[i];
		}
		
		void ButtonClGenerateClick(object sender, EventArgs e)
		{
			if(dtClassement.Rows.Count > 0)
		    {
		        messageboxWarning("Runde wurde bereits generiert!\nGenerieren abgebrochen!");
		        return;
		    }
		    
		 	Logging.write("INFO: generate preclassement");
		    
		    baseFunctions.setParametersClassementGames();
		    
		    baseFunctions.generateClassementGames();
		    
		    initClassement(app.Default.Satzpl);
		    
		    messageboxInfo("Platzspiele wurden generiert");
		    
		    ButtonClSaveClick(null, null);
		}
		
		void ButtonClSaveClick(object sender, EventArgs e)
		{
	
		}
		
		void ButtonClDeleteClick(object sender, EventArgs e)
		{
	
		}
		
		void ButtonClPrintClick(object sender, EventArgs e)
		{
	
		}
		
		void ButtonClResultClick(object sender, EventArgs e)
		{
	
		}
		
		void ExitToolStripMenuItemClick(object sender, EventArgs e)
		{
			Environment.Exit(0);
		}
		
		void DokumentationToolStripMenuItemClick(object sender, EventArgs e)
		{
			
		}
		
		void AboutToolStripMenuItemClick(object sender, EventArgs e)
		{
			about.ShowDialog();
		}
	}
}
