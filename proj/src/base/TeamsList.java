package base;

import java.util.ArrayList;
import java.util.List;

public class TeamsList
{
	private List<Team> list = new ArrayList<Team>();

	public int size()
	{
		return list.size();
	}
	
	public void add(Team t)
	{
		list.add(t);
	}
	
	public Team get(String name)
	{
		for(int i = 0; i < list.size(); i++)
		{
			Team t = list.get(i);
			
			if(t.getName() == name)
				return t;
		}
		
		return null;
	}
	
	public Team get(int index)
	{
		return list.get(index);
	}
}