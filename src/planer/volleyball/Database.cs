/*
 * Created by SharpDevelop.
 * User: cfr
 * Date: 15.05.2017
 * Time: 10:47
 */
using System;
using System.Data;
using System.Data.SQLite;
using System.Collections.Generic;

namespace volleyball
{
	public class Database
	{
		#region members
		SQLiteConnection dbConnection;
		#endregion

		
		public SQLiteConnection DBCONNECTION
		{
			get{ return dbConnection; }
		}
		
		public Database(String connectionString)
		{
			 dbConnection = new SQLiteConnection(connectionString);
		}
		
		public bool open()
		{
			dbConnection.Open();
			
			if(dbConnection != null && dbConnection.State == ConnectionState.Open)
				return true;
			
			return false;
		}
		
		public bool close()
		{
			dbConnection.Close();
			
			if(dbConnection != null && dbConnection.State == ConnectionState.Closed)
				return true;
			
			return false;
		}
		
		public bool write(String query)
		{
			try
			{
				SQLiteCommand dbCommand = new SQLiteCommand(query, dbConnection);
				dbCommand.ExecuteNonQuery();
				return true;
			}
			catch(SQLiteException e)
			{
				Logging.write(e.Message);
				return false;
			}
		}
		
		public List<List<String>> read(String query)
		{
			List<List<String>> result = new List<List<String>>();
			try
			{
				SQLiteCommand command = new SQLiteCommand(query, dbConnection);
				SQLiteDataReader reader = command.ExecuteReader();
				
				while(reader.Read())
				{
					List<String> entry = new List<String>();
					
					for(int i = 0; i < reader.FieldCount; i++)
						entry.Add(reader[i].ToString());
					
					result.Add(entry);
				}
				
				return result;
			}
			catch(SQLiteException e)
			{
				Logging.write(e.Message);
				return null;
			}
		}
		
		public SQLiteDataAdapter getDataAdapter(String query)
		{
			try
			{
				SQLiteDataAdapter da = new SQLiteDataAdapter(query, dbConnection);
				return da;
			}
			catch(SQLiteException e)
			{
				Logging.write(e.Message);
				return null;
			}
		}
		
		public SQLiteCommand createCommand(String query)
		{
			return new SQLiteCommand(query, dbConnection);
		}
	}
}
