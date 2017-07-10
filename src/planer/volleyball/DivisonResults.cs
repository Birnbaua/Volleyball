/*
 * Created by SharpDevelop.
 * User: cfr
 * Date: 06.07.2017
 * Time: 14:45
  */
using System;
using System.Collections.Generic;
using System.Data;
using System.Data.SQLite;
using System.Windows.Forms;

namespace volleyball
{
	public partial class DivisonResults : Form
	{
		#region
		SQLiteDataAdapter daA, daB, daC, daD, daE, daF, daG, daH, daI, daJ, daK, daL;
		DataTable dtA, dtB, dtC, dtD, dtE, dtF, dtG, dtH, dtI, dtJ, dtK, dtL;
		Database db;
		#endregion
		
		public DivisonResults(Database db)
		{
			InitializeComponent();
			
			this.db = db;

		}
		
		void init(String round, DataGridView dgv, SQLiteDataAdapter da, DataTable dt)
		{
			Logging.write("INFO: init datatable interim");
			
			if(da != null)
				da.Dispose();
			
			da = new SQLiteDataAdapter(round, db.DBCONNECTION);
			
			if(dt != null)
				dt.Dispose();
			
			dt = new DataTable();
			
			da.Fill(dt);
			
			dgv.DataSource = dt.DefaultView;
									
			for(int i = 0; i < MainForm.headerResult.Count; i++)
				dgv.Columns[i].HeaderText = MainForm.headerResult[i];
		}
		
		public void setParameters(String round)
		{
			
		}
		
		void DivisonResultsResize(object sender, EventArgs e)
		{
			int panelTW = panelT.Width;
			int panelMW = panelM.Width;
			int panelBW = panelB.Width;
			int height = Height;
						
			foreach(GroupBox gb in panelT.Controls)
				gb.Width = panelTW / 4;
			
			foreach(GroupBox gb in panelM.Controls)
				gb.Width = panelMW / 4;
			
			foreach(GroupBox gb in panelB.Controls)
				gb.Width = panelBW / 4;
			
			panelT.Height = Height / 3;
			panelM.Height = Height / 3;
			panelB.Height = Height / 3;
		}
	}
}
