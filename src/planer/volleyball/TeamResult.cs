/*
 * Created by SharpDevelop.
 * User: cfr
 * Date: 15.05.2017
 * Time: 12:26
 */
using System;

namespace volleyball
{
	public class TeamResult
	{
		String teamName;
		int sets;
		int points;
		
		public TeamResult(String teamName, int sets, int points)
		{
			this.teamName = teamName;
			this.sets = sets;
			this.points = points;
		}
		
		public String TeamName
		{
			get{ return teamName; }
			set{ teamName = value; }
		}
		
		public int Sets
		{
			get{ return sets; }
			set{ sets = value; }
		}
		
		public int Points
		{
			get{ return points; }
			set{ points = value; }
		}
	}
}
