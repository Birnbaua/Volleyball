package system;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class DataHandling
{
	public static int GroupSize = 5;
	public static final String[] Prefixes = new String[] { "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L" };
	public static final String Teams = "Teams";
	public static final String QfGames = "Qf_Games";
	public static final String QfResults = "Qf_Result_";
	public static final String ItGames = "It_Games";
	public static final String ItResults = "It_Result_";
	public static final String PreClGames = "PreCl_Games";
	public static final String ClGames = "Cl_Games";
	public static final String ClResults = "Cl_Result";
			
	public static void setGroupSize(int size)
	{
		GroupSize = size;
	}
	
	public static int getGroupSize()
	{
		return GroupSize;
	}
	
	public static void writeTeams(List<String[]> teams) throws IOException
	{
		Logging.write("write teams");
		
		PrintWriter out = new PrintWriter(Teams);
		
		for(int i = 0; i < teams.size(); i++)
		{
			String row = "";
			
			for(int ii = 0; ii < teams.get(i).length; ii++)
				row += teams.get(i)[ii] + ";";
		
			row = row.substring(0, row.length() - 1); // remove last ';'
			
			Logging.write(row);
			
			out.println(row);
		}
		
		out.close();
	}
	
	public static List<String[]> readTeams() throws IOException
	{
		String line;
		List<String[]> teams = new ArrayList<String[]>();
		
		if(!new File(Teams).exists())
			return null;
		
		BufferedReader br = new BufferedReader(new FileReader(Teams));
		
		while((line = br.readLine()) != null) 
		{
			Logging.write(line);
			
			String[] row = line.split(";");
			
			teams.add(row);
		}
		
		br.close();
		
		return teams;
	}
	
	public static List<String[]> clearTeams() throws IOException
	{
		List<String[]> list = new ArrayList<String[]>(GroupSize);
						
		for(int i = 0; i < GroupSize; i++)
			list.add(new String[] { String.valueOf(i), " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " ", " " });
				
		return list;
	}
}
