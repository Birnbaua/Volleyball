/*
 * Created by SharpDevelop.
 * User: cfr
 * Date: 15.05.2017
 * Time: 11:37
 */
using System;
using System.IO;

namespace volleyball
{
	public static class Logging
	{
		public static String fileName;
		
		public static void write(String msg)
		{
			using (StreamWriter writer = new StreamWriter(fileName, true))
	        {
				writer.WriteLine(DateTime.Now.ToString("yyyy.MM.dd HH:mm:ss") + " => " + msg);
	        }
		}
	}
}
