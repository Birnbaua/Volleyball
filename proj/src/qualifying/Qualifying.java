package qualifying;

import base.Team;
import base.BaseGameHandling;
import base.Field;

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
}
