package base;

public class Team
{
	private String name;
	private int pointsFirstRound;
	private int pointsSecondRound;
	private int gamePointsFirstRound;
	private int gamePointsSecondRound;
	
	public Team(String str)
	{
		this.name=str;
	}

	public String getName()
	{
		return name;
	}

	public void setName(String name) 
	{
		this.name = name;
	}

	public int getPointsFirstRound() 
	{
		return pointsFirstRound;
	}

	public void setPointsFirstRound(int pointsFirstRound) 
	{
		this.pointsFirstRound = pointsFirstRound;
	}
	
	public void addPointsFirstRound(int pointsFirstRound) 
	{
		this.pointsFirstRound += pointsFirstRound;
	}

	public int getPointsSecondRound()
	{
		return pointsSecondRound;
	}

	public void setPointsSecondRound(int pointsSecondRound) 
	{
		this.pointsSecondRound = pointsSecondRound;
	}
	
	public void addPointsSecondRound(int pointsSecondRound)
	{
		this.pointsSecondRound += pointsSecondRound;
	}

	public int getGamePointsFirstRound() 
	{
		return gamePointsFirstRound;
	}

	public void setGamePointsFirstRound(int gamePointsFirstRound)
	{
		this.gamePointsFirstRound = gamePointsFirstRound;
	}
	
	public void addGamePointsFirstRound(int gamePointsFirstRound)
	{
		this.gamePointsFirstRound += gamePointsFirstRound;
	}

	public int getGamePointsSecondRound() 
	{
		return gamePointsSecondRound;
	}

	public void setGamePointsSecondRound(int gamePointsSecondRound)
	{
		this.gamePointsSecondRound = gamePointsSecondRound;
	}
	
	public void addGamePointsSecondRound(int gamePointsSecondRound) 
	{
		this.gamePointsSecondRound = gamePointsSecondRound;
	}
}
