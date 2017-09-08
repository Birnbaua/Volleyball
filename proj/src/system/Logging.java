package system;

import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Logging 
{
	private static PrintWriter file;
	private static int Loglevel = 0;
	
	public static void setFile(PrintWriter pw)
	{
		file = pw;
	}
	
	public static void setLoglevel(int level)
	{
		Loglevel = level;
	}
	
	private static String newTimestamp()
	{
		return new SimpleDateFormat("yyyy.MM.dd HH:mm:ss").format(new Date());
	}
	
	public static void write(String message)
	{
		String s = newTimestamp() + " => " + message;
		
		switch(Loglevel)
		{
			case 0:
				file.println(s);
				System.out.println(s);
				break;
			
			case 1:
				file.println(s);
				break;
			
			case 2:
				System.out.println(s);
				break;
			
			default: 
				System.out.println(s);
		}		
		
		file.flush();
	}
}
