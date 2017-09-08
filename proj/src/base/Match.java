package base;

import java.sql.Timestamp;

public class Match 
{
	private Integer round;
	private Integer match;
	private Timestamp time;
	private Team team1;
	private Team team2;
	private Team referee;
	private int points1;
	private int points2;
	private Field field;
	
	public Match(Integer match, Integer round, Timestamp time, Team a, Team b, Team ref, Field f)
	{
		this.match = match;
		this.round = round;
		this.time = time;
		this.team1 = a;
		this.team2 = b;
		this.referee = ref;
		this.field = f;	
	}
	
	public Match(Integer match, Integer round, Timestamp time, Team a, Team b, Team ref)
	{
		this(match, round, time, a, b, ref, null);
	}
	
	public void setMatchNumber(int match) 
	{
		this.match = match;
	}
	
	public int getMatchNumber() 
	{
		return this.match;
	}

	public void setRoundNumber(int round) 
	{
		this.round = round;
	}
	
	public int getRoundNumber() 
	{
		return this.round;
	}
	
	public void setTime(Timestamp time)
	{
		this.time = time;
	}
	
	public Timestamp getTime()
	{
		return this.time;
	}
	
	public Team getTeam1()
	{
		return team1;
	}
	
	public void setTeam1(Team team1) 
	{
		this.team1 = team1;
	}
	
	public Team getTeam2()
	{
		return this.team2;
	}
	
	public void setTeam2(Team team2) 
	{
		this.team2 = team2;
	}
	
	public Team getReferee()
	{
		return referee;
	}
	
	public void setReferee(Team referee) 
	{
		this.referee = referee;
	}
	
	public Field getField()
	{
		return field;
	}
	
	public void setField(Field field)
	{
		this.field = field;
	}
	
	public int getPoints1() 
	{
		return points1;
	}
	
	public void setPoints1(int points1)
	{
		this.points1 = points1;
	}
	
	public int getPoints2()
	{
		return points2;
	}
	
	public void setPoints2(int points2)
	{
		this.points2 = points2;
	}
}
