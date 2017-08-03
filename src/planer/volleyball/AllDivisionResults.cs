/*
 * Created by SharpDevelop.
 * User: cfr
 * Date: 20.07.2017
 * Time: 14:33
 */
using System;
using System.Windows.Forms;
using System.Configuration;
using System.Data;
using System.Data.SQLite;

namespace volleyball
{
	public partial class AllDivisionResults : Form
	{
		#region members
		SQLiteDataAdapter da;
		DataTable dt;
		Database db;
		#endregion
		
		public AllDivisionResults(Database db, String round)
		{
			InitializeComponent();
			
			this.db = db;
			
			Logging.write("INFO: init datatable " + round);
			
			String query = ConfigurationManager.AppSettings["SelectAllResults"] + round;
						
			if(da != null)
				da.Dispose();
			
			da = new SQLiteDataAdapter(query, db.DBCONNECTION);
			
			if(dt != null)
				dt.Dispose();
			
			dt = new DataTable();
			
			da.Fill(dt);
			
			dataGridView.DataSource = dt.DefaultView;		
						
			for(int x = 0; x < MainForm.headerAllResult.Count; x++)
				dataGridView.Columns[x].HeaderText = MainForm.headerAllResult[x];
		}
	}
}
