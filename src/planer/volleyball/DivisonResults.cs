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
	public partial class DivisonResults : Form
	{
		#region
		SQLiteDataAdapter daA = null, daB = null, daC = null, daD = null, daE = null, daF = null, daG = null, daH = null, daI = null, daJ = null, daK = null, daL = null;
		DataTable dtA = null, dtB = null, dtC = null, dtD = null, dtE = null, dtF = null, dtG = null, dtH = null, dtI = null, dtJ = null, dtK = null, dtL = null;
		Database db;
		List<DataTable> dtList;
		List<SQLiteDataAdapter> daList;
		List<DataGridView> dgvList;
		bool valueChanged = false;
		#endregion
		
		public DivisonResults(Database db)
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
		
		void init(String round, DataGridView dgv, SQLiteDataAdapter da, DataTable dt)
		{
			Logging.write("INFO: init datatable interim");
			
			String query = ConfigurationManager.AppSettings["SelectResults"];
			query = query.Replace("@RUNDE", round);
			
			if(da != null)
				da.Dispose();
			
			da = new SQLiteDataAdapter(query, db.DBCONNECTION);
			
			if(dt != null)
				dt.Dispose();
			
			dt = new DataTable();
			
			da.Fill(dt);
			
			dgv.DataSource = dt.DefaultView;
									
			dgv.Columns[0].Visible = false;
			
			for(int i = 0; i < MainForm.headerResult.Count; i++)
				dgv.Columns[i].HeaderText = MainForm.headerResult[i];
		}
		
		public void setParameters(String round)
		{
			for(int i = 0; i < MainForm.grPrefix.Count; i++)
				init(round + "_erg_gr" + MainForm.grPrefix[i], dgvList[i], daList[i], dtList[i]);
		}
		
		void DivisonResultsResize(object sender, EventArgs e)
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
		
		void DivisonResultsFormClosing(object sender, FormClosingEventArgs e)
		{
			if(valueChanged)
			{
				bool ok = MainForm.userButtonCheck("Achtung, noch ungespeicherte Daten vorhanden! Fenster wirklich schließen?!");
				
				if(!ok)
					e.Cancel = true;
			}
		}
	}
}
