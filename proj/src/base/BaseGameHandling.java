package base;

import java.sql.Timestamp;

public class BaseGameHandling 
{
	protected Team[] teams;
	protected Match[] matches;
	protected Field[] fields;
	protected int groups = 0;
	protected int groupLength = 0;
	protected Team[] evaluatedList;
	protected Team[] [] innerEvaluated;
	protected Team[] newTeamList;
	
	public BaseGameHandling(Team[] team, Field[] fields)
	{
		this.teams = team;
		
		if(groupLength == 0)
			this.groupLength = 5;
		
		this.newTeamList = new Team[teams.length];
		this.fields = fields;
		this.groups = team.length / this.groupLength;
		this.matches = new Match[groups * groupLength * 2];
		this.evaluatedList = new Team[teams.length];
		this.innerEvaluated = new Team[groups][groupLength];
	}
	
	protected boolean generateRound(int startField) //complete
	{ 
		if(teams != null)
		{
			for(int j = 0; j < groupLength; j++)
			{
				//first half of games
				for(int i = 0; i < groups; i++)
					matches[i + groups * j] = new Match(null, null , new Timestamp(System.currentTimeMillis()), 
														teams[i * groupLength + j],
														teams[i * groupLength + (2 + j) % groupLength],
														teams[i * groupLength + (3 + j) % groupLength]);
				
				//last half of games
				for(int i = 0; i < groups; i++)
					matches[i + groups * j + groups * groupLength] = new Match(null, null, new Timestamp(System.currentTimeMillis()),
																			   teams[i * groupLength + (2 + j * 3) % groupLength],
																			   teams[i * groupLength + (3 + j * 3) % groupLength],
																			   teams[i * groupLength + (j * 3) % groupLength]);
			}
		
			return true;
		}
	
		return false;
	}
	
	protected void generateMatchNumber(int startingNumber)
	{
		for(int i = startingNumber; i < matches.length; i++)
			matches[i].setMatchNumber(i + 1);
	}
	
	protected void generateRoundNumber(int startingNumber)
	{
		for(int i = 0, round = 1; i < matches.length; i++, round++)
		{
			if(round >= groupLength)
				round = 1;
		
			matches[i].setRoundNumber(round);
		}
	}
	
	protected void generateFields(int startField) //generate fields for games 
	{
		for(int i = 0; i < matches.length; i++)
		{
			matches[i].setField(fields[(startField + i) % groups]);
				
			if(i % groups == groups - 1) // to go one field forward each round
				startField++;
		}
	}
	
	public void evaluateRound() //sorted list of all teams
	{ 
		evaluatedList = new Sort().mergeSort(teams);
	}
	
	protected boolean allGamesPlayed() //checks if all games are finished
	{
		boolean[] isPlayed = new boolean[matches.length];
		
		for(int i = 0; i < matches.length; i++)
		{
			if(matches[i].getPoints1() !=0 || matches[i].getPoints2() != 0)
				isPlayed[i]=true;
		}
		
		int i = 0;
		boolean isAllPlayed=true;
		
		while(matches.length > i)
		{
			if(!isPlayed[i])
				isAllPlayed=false;//set to false if one match isn't finished

			i++;
		}

		return isAllPlayed;
	}
	
	protected Match searchMatch(Team a, Team b) //gives back the match of the two teams, if there isn't a match it returns null
	{ 
		//to check direct encounters between two teams
		Match buffer = null;
		
		if(isMatch(a,b))
		{
			for(int i = 0; i < matches.length; i++)
			{
				if((matches[i].getTeam1() == a && matches[i].getTeam2() == b) || (matches[i].getTeam2() == a && matches[i].getTeam1() == b))
				{
					buffer=matches[i];
					return buffer;
				}
			}
		}
		
		return buffer;
	}
	
	public boolean isMatch(Team a, Team b)//checks if there is a match of these teams
	{ 
		for(int i = 0; i < matches.length; i++)
		{
			if((matches[i].getTeam1() == a && matches[i].getTeam2() == b) || (matches[i].getTeam2() == a && matches[i].getTeam1() == b))
				return true;
		}
		
		return false;
	}
	
	public void setMatchPoints(int matchNumber, int a, int b)//matchnumber starts at 0
	{
		if(matchNumber < matches.length && matchNumber > -1)
		{
			matches[matchNumber].setPoints1(a);
			matches[matchNumber].setPoints2(b);
		}
	}
	
	public int[] getMatchPoints(int matchNumber) //matchnumber starts at 0
	{
		int[] arr = new int[2];
		
		if(matchNumber < matches.length && matchNumber> -1)
		{
			arr[0]=matches[matchNumber].getPoints1();
			arr[1]=matches[matchNumber].getPoints2();
		}
		
		return arr;
	}
	
	//returns a string of all matches
	public String toString()
	{
		String str = " Game Nr. | Round | Time | Team 1 | Team 2 | Referee | Field Nr.\n";
		str += "----------------------------------------------------------\n";
		
		for(int i = 0; i < matches.length; i++)
			str += "  " + String.valueOf(matches[i].getMatchNumber()) + " |  " + 
				   String.valueOf(matches[i].getRoundNumber()) + "  |  " +  
				   String.valueOf(matches[i].getTime()) +  "  |  " + 
				   String.valueOf(matches[i].getTeam1().getName()) +  "  |  " + 
				   String.valueOf(matches[i].getTeam2().getName()) +  "  |  " + 
			       String.valueOf(matches[i].getReferee().getName()) +  "  |  " + 
			       String.valueOf(matches[i].getField().getNumber()) + "\n";
		
		return str.toString();
	}
	
	//getter & setter
	public Team[] getNewTeamList()
	{
		return newTeamList;
	}

	public void setNewTeamList(Team[] newTeamList) 
	{
		this.newTeamList = newTeamList;
	}
	
	public void deleteRound()
	{
		this.matches = null;
	}
	
	public Team[] getTeams() 
	{
		return teams;
	}
	
	public void setTeams(Team[] teams)
	{
		this.teams = teams;
	}
	
	public Match[] getMatches() 
	{
		return matches;
	}
	
	public void setMatches(Match[] matches)
	{
		this.matches = matches;
	}

	public int getGroups()
	{
		return groups;
	}

	public void setGroups(int groups)
	{
		this.groups = groups;
	}

	public int getGroupLength()
	{
		return groupLength;
	}

	public void setGroupLength(int groupLength)
	{
		this.groupLength = groupLength;
	}

	public Field[] getFields()
	{
		return fields;
	}

	public void setFields(Field[] fields) 
	{
		this.fields = fields;
	}

	public Team[] getEvaluatedList()
	{
		return evaluatedList;
	}

	public void setEvaluatedList(Team[] evaluatedList) 
	{
		this.evaluatedList = evaluatedList;
	}

	public Team[] [] getInnerEvaluated() 
	{
		return innerEvaluated;
	}

	public void setInnerEvaluated(Team[] [] innerEvaluated)
	{
		this.innerEvaluated = innerEvaluated;
	}
}
