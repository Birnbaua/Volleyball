package interim;

import base.Team;
import base.BaseGameHandling;
import base.Field;

public class Interim extends BaseGameHandling
{
	public Interim(Team[] team, Field[] fields)
	{
		super(team, fields);
	}
	
	public boolean generateInterim(int startField) //complete
	{ 
		if(teams != null)
		{
			if(!generateRound(startField))
				return false;
			
			//generate fields for games 
			int addFirstRoundRounds = groupLength * 2;//to get the correct round number in the match class
			int addFirstRoundMatches = groupLength * groups * 2;//to get the correct match number in the match class
			
			for(int i = 0; i < matches.length; i++)
			{
				if(fields != null)
				{
					matches[i].setField(fields[(startField + i) % groups]);
					matches[i].setMatchNumber(addFirstRoundMatches + i + 1);//starts at 1
					matches[i].setRoundNumber(addFirstRoundRounds + i / groups + 1); //rounds
					
					if(i % groups == groups - 1) // to go one field forward each round
						startField++;
				}
			}
			
			return true;
		}
	
		return false;
	}
}
