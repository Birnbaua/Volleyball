package base;

public class Team
{
	private String name;
	private int pointsQualifying;
	private int gamePointsQualifying;
	private int pointsInterim;
	private int gamePointsInterim;
	private int pointsPreClassement;
	private int gamePointsPreClassement;
		
	public Team(String str)
	{
		this.name = str;
	}

	public String getName()
	{
		return name;
	}

	public void setName(String name) 
	{
		this.name = name;
	}

	public int getPointsQualifying() 
	{
		return pointsQualifying;
	}

	public void setPointsQualifying(int pointsQualifying) 
	{
		this.pointsQualifying = pointsQualifying;
	}
	
	public void addPointsQualifying(int pointsQualifying) 
	{
		this.pointsQualifying += pointsQualifying;
	}
	
	public int getGamePointsQualifying() 
	{
		return gamePointsQualifying;
	}
	
	public void setGamePointsQualifying(int gamePointsQualifying)
	{
		this.gamePointsQualifying = gamePointsQualifying;
	}
	
	public void addGamePointsQualifying(int gamePointsQualifying)
	{
		this.gamePointsQualifying += gamePointsQualifying;
	}

	public int getPointsInterim()
	{
		return pointsInterim;
	}

	public void setPointsInterim(int pointsInterim) 
	{
		this.pointsInterim = pointsInterim;
	}
	
	public void addPointsInterim(int pointsInterim)
	{
		this.pointsInterim += pointsInterim;
	}

	public int getGamePointsInterim() 
	{
		return gamePointsInterim;
	}

	public void setGamePointsInterim(int gamePointsInterim)
	{
		this.gamePointsInterim = gamePointsInterim;
	}
	
	public void addGamePointsInterim(int gamePointsInterim) 
	{
		this.gamePointsInterim = gamePointsInterim;
	}
	
	public int getPointsPreClassement()
	{
		return pointsPreClassement;
	}

	public void setPointsPreClassement(int pointsPreClassement) 
	{
		this.pointsPreClassement = pointsPreClassement;
	}
	
	public void addPointsPreClassement(int pointsPreClassement)
	{
		this.pointsPreClassement += pointsPreClassement;
	}

	public int getGamePointsPreClassement() 
	{
		return gamePointsPreClassement;
	}

	public void setGamePointsPreClassement(int gamePointsPreClassement)
	{
		this.gamePointsPreClassement = gamePointsPreClassement;
	}
	
	public void addGamePointsPreClassement(int gamePointsPreClassement) 
	{
		this.gamePointsPreClassement = gamePointsPreClassement;
	}
}
