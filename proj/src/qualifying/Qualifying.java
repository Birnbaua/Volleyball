package qualifying;

import base.Team;
import base.BaseGameHandling;
import base.Field;
import base.Match;
import base.Sort;

public class Qualifying extends BaseGameHandling
{
	public Qualifying(Team[] team, Field[] fields)
	{
		super(team, fields);
	}
	
	public boolean generateQualifying(int startingMatchNumber, int startingRoundNumber, int startField) //complete
	{ 
		if(teams != null && fields != null)
		{
			if(!generateRound(startField))
				return false;
			
			generateMatchNumber(startingMatchNumber);
			
			generateRoundNumber(startingRoundNumber);
			
			generateFields(startField);
			
			return true;
		}
		
		return false;
	}
	
	public boolean generateTeamList() //generates evaluated list for round
	{ 
		if(allGamesPlayed())//check if all games finished
		{ 
			Team[][] ranked = new Team[groupLength][groups];
			innerEvaluate();//fill member array
			
			for(int i = 0; i < groupLength; i++)
			{
				for(int j = 0; j < groups; j++)
					ranked[i][j] = innerEvaluated[j][i]; //all first, all second ... places
			}
			
			for(int i = 0; i < teams.length; i++)
				newTeamList[i] = ranked[i / groupLength][i % groups];
			
			Team[] buffer = new Team[groupLength]; //initialize new teamlist
			
			for(int i = 0; i < groups; i++)
			{
				for(int j = 0; j < groupLength; j++)
					buffer[j] = newTeamList[i * groupLength + j]; 
				
				buffer = new Sort().mergeSort(buffer);//sort the first, second... places
				
				for(int j = 0; j < groupLength; j++)
					newTeamList[i * groupLength + j] = buffer[j];
			}
			
			return true; //if generating finished return true
		}
		
		return false; //failed
	}
	
	public boolean setTeamPoints()//gives back if it could collect all points of existing matches
	{ 
		for(int i = 0; i < teams.length; i++)
		{
			teams[i].setGamePointsQualifying(0);
			teams[i].setPointsQualifying(0);
		}
		
		if(matches != null) //if matches are generated
		{
			Team ref1, ref2;
			
			for(int i = 0; i < matches.length; i++)
			{
				ref1 = matches[i].getTeam1();//Reference one and two
				ref2 = matches[i].getTeam2();
				
				if(matches[i].getPoints1() > 0 || matches[i].getPoints2() > 0)  //check if already played
				{
					if(matches[i].getPoints1() > matches[i].getPoints2())  //team1 winner
					{
						ref1.addPointsQualifying(2);
						ref2.addPointsQualifying(0);
					}
					else if(matches[i].getPoints1() < matches[i].getPoints2()) //team2 winner
					{
						ref1.addPointsQualifying(0);
						ref2.addPointsQualifying(2);
					}
					else //draw
					{
						ref1.addPointsQualifying(1);
						ref2.addPointsQualifying(1);
					}
					
					ref1.addGamePointsQualifying(matches[i].getPoints1() - matches[i].getPoints2());//adds difference
					ref2.addGamePointsQualifying(matches[i].getPoints2() - matches[i].getPoints1());
				}
			}
			
			return true;
		}
		
		return false;
	}
	
	public boolean innerEvaluate() //evaluates the groups
	{ 
		if(setTeamPoints())
		{
			for(int i = 0; i < groups; i++) //loop for every group
			{ 
				Team[] arr = new Team[groupLength];
				
				for(int j = 0;j<groupLength;j++) //gets all teams of one group
					arr[j] = teams[j + groupLength * i];
				
				innerEvaluated[i] = new Sort().mergeSort(arr);//sorts group and puts it back to the group index
				
				for(int j = 0;j<groupLength-1;j++)//checks if any teams have same Points and gamepoints
				{
					if(innerEvaluated[i][j].getPointsQualifying() == innerEvaluated[i][j + 1].getPointsQualifying()) //same Points
					{
						if(innerEvaluated[i][j].getGamePointsQualifying() == innerEvaluated[i][j + 1].getGamePointsQualifying()) //same gamepoints
						{
							//checks the direct match of the two teams, if it is no draw, inner Evaluation is valid
							Match buffer = searchMatch(innerEvaluated[i][j], innerEvaluated[i][j + 1]);
							
							if(buffer.getPoints1()==buffer.getPoints2()) //check if it is a draw
							{
								return false; //return false if it is a draw
							}
							else //corrects the order in the group if it isn't a draw
							{
								//corrects order in group looking at the direct encounter
								if(buffer.getTeam1() == innerEvaluated[i][j])// if team1 lost vs. team2 and team1 is better ranked than team2
								{ 
									if(buffer.getPoints1() < buffer.getPoints2())
									{
										Team referance = innerEvaluated[i][j];
										innerEvaluated[i][j] = innerEvaluated[i][j + 1];
										innerEvaluated[i][j + 1] = referance;
									}
								}
								else //exactly the opposite of above
								{
									if(buffer.getPoints1() > buffer.getPoints2())
									{
										Team referance = innerEvaluated[i][j];
										innerEvaluated[i][j] = innerEvaluated[i][j + 1];
										innerEvaluated[i][j+1] = referance;
									}
								}
							}
						}
					}
				}
			}
			
			return true;
		}
		
		return false; //if two teams have exactly the same points, gamepoints and played a draw
	}
}
