/*
 * Created by SharpDevelop.
 * User: cfr
 * Date: 06.07.2017
 * Time: 14:45
  */
using System;
using System.Collections.Generic;
using System.Configuration;
using System.Data;
using System.Data.SQLite;
using System.Windows.Forms;

namespace volleyball
{
	public partial class DivisionResults : Form
	{
		#region
		SQLiteDataAdapter daA = null, daB = null, daC = null, daD = null, daE = null, daF = null, daG = null, daH = null, daI = null, daJ = null, daK = null, daL = null;
		DataTable dtA = null, dtB = null, dtC = null, dtD = null, dtE = null, dtF = null, dtG = null, dtH = null, dtI = null, dtJ = null, dtK = null, dtL = null;
		Database db;
		List<DataTable> dtList;
		List<SQLiteDataAdapter> daList;
		List<DataGridView> dgvList;
		bool valueChanged = false;
		String round = null;
		#endregion
		
		public DivisionResults(Database db)
		{
			InitializeComponent();
			
			this.db = db;
			
			dtList = new List<DataTable>();
			daList = new List<SQLiteDataAdapter>();
			dgvList = new List<DataGridView>();
			
			dtList.Add(dtA); daList.Add(daA); dgvList.Add(dataGridViewA);
			dtList.Add(dtB); daList.Add(daB); dgvList.Add(dataGridViewB);
			dtList.Add(dtC); daList.Add(daC); dgvList.Add(dataGridViewC);
			dtList.Add(dtD); daList.Add(daD); dgvList.Add(dataGridViewD);
			dtList.Add(dtE); daList.Add(daE); dgvList.Add(dataGridViewE);
			dtList.Add(dtF); daList.Add(daF); dgvList.Add(dataGridViewF);
			dtList.Add(dtG); daList.Add(daG); dgvList.Add(dataGridViewG);
			dtList.Add(dtH); daList.Add(daH); dgvList.Add(dataGridViewH);
			dtList.Add(dtI); daList.Add(daI); dgvList.Add(dataGridViewI);
			dtList.Add(dtJ); daList.Add(daJ); dgvList.Add(dataGridViewJ);
			dtList.Add(dtK); daList.Add(daK); dgvList.Add(dataGridViewK);
			dtList.Add(dtL); daList.Add(daL); dgvList.Add(dataGridViewL);
		}
		
		void saveChanges(String table, DataTable dt, String query)
		{
			foreach(DataRow dr in dt.Rows)
			{
				query = query.Replace("@RUNDE", table);
				SQLiteCommand cmd = db.createCommand(query);
				cmd.Parameters.AddWithValue("@ID", Int32.Parse(dr[0].ToString()));
				cmd.Parameters.AddWithValue("@MS", dr[1].ToString());
				cmd.Parameters.AddWithValue("@PUNKTE", dr[2].ToString());
				cmd.Parameters.AddWithValue("@SATZ", dr[3].ToString());
				cmd.Parameters.AddWithValue("@INTERN", dr[4].ToString());
				cmd.Parameters.AddWithValue("@EXTERN", dr[5].ToString());
				cmd.ExecuteNonQuery();
			}
		}
		
		public void setParameters(String round)
		{
			for(int i = 0; i < MainForm.grPrefix.Count; i++)
			{
				this.round = round;
				String newRound = this.round + MainForm.grPrefix[i];
				Logging.write("INFO: init datatable " + newRound);
			
				String query = ConfigurationManager.AppSettings["SelectResults"];
				query = query.Replace("@RUNDE", newRound);
				
				if(daList[i] != null)
					daList[i].Dispose();
				
				daList[i] = new SQLiteDataAdapter(query, db.DBCONNECTION);
				
				if(dtList[i] != null)
					dtList[i].Dispose();
				
				dtList[i] = new DataTable();
				
				daList[i].Fill(dtList[i]);
				
				dgvList[i].DataSource = dtList[i].DefaultView;
										
				dgvList[i].Columns[0].Visible = false;
				
				for(int x = 0; x < MainForm.headerResult.Count; x++)
					dgvList[i].Columns[x].HeaderText = MainForm.headerResult[x];
			}
		}
		
		void DivisionResultsResize(object sender, EventArgs e)
		{
			int panelTW = panelT.Width;
			int panelMW = panelM.Width;
			int panelBW = panelB.Width;
			int height = (Height / 3) - 25;
						
			panelT.Height = height;
			panelM.Height = height;
			panelB.Height = height;
			
			foreach(GroupBox gb in panelT.Controls)
				gb.Width = panelTW / 4;
			
			foreach(GroupBox gb in panelM.Controls)
				gb.Width = panelMW / 4;
			
			foreach(GroupBox gb in panelB.Controls)
				gb.Width = panelBW / 4;			
		}
		
		void DataGridViewCellValueChanged(object sender, DataGridViewCellEventArgs e)
		{
			valueChanged = true;
		}
		
		void DivisionResultsFormClosing(object sender, FormClosingEventArgs e)
		{
			if(valueChanged)
			{
				bool ok = MainForm.userButtonCheck("Achtung, noch ungespeicherte Daten vorhanden! Fenster wirklich schließen?!");
				
				if(!ok)
					e.Cancel = true;
			}
		}
		
		void ButtonSaveClick(object sender, EventArgs e)
		{
			foreach(DataGridView dgv in dgvList)
				dgv.EndEdit();
					
			for(int i = 0; i < MainForm.grPrefix.Count; i++)
				saveChanges(this.round + MainForm.grPrefix[i], dtList[i], ConfigurationManager.AppSettings["UpdateResults"]);
				
			MainForm.messageboxInfo("Änderungen wurden gespeichert");
			
			valueChanged = false;
		}
	}
}
