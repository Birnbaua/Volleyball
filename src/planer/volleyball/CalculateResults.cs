/*
 * Created by SharpDevelop.
 * User: cfr
 * Date: 15.05.2017
 * Time: 12:23
 */
using System;
using System.Collections.Generic;

namespace volleyball
{
	public static class CalculateResults
	{
		public static List<TeamResult> calculateResults(List<List<String>> toCalculate)
		{
			List<TeamResult> resultList = new List<TeamResult>();
		
		    for(int i = 0; i < toCalculate.Count; i++)
		    {
		    	List<String> rowToCalculate = toCalculate[i];
		
		    	TeamResult m1 = new TeamResult(rowToCalculate[1], 0, 0);
		        TeamResult m2 = new TeamResult(rowToCalculate[2], 0, 0);
				        		
		        // first set
		        if(Int32.Parse(rowToCalculate[3]) > 0 && Int32.Parse(rowToCalculate[4]) > 0) // 1ter satz
		        {
		            // first team wins
		            if(Int32.Parse(rowToCalculate[3]) > Int32.Parse(rowToCalculate[4]))
		            {
		                m1.Sets += 2;
		                m1.Points += Int32.Parse(rowToCalculate[3]) - Int32.Parse(rowToCalculate[4]);
		                m2.Points += Int32.Parse(rowToCalculate[4]) - Int32.Parse(rowToCalculate[3]);
		            }
		            // second team wins
		            else if(Int32.Parse(rowToCalculate[3]) < Int32.Parse(rowToCalculate[4]))
		            {
		                m2.Sets += 2;
		                m2.Points += Int32.Parse(rowToCalculate[4]) - Int32.Parse(rowToCalculate[3]);
		                m1.Points += Int32.Parse(rowToCalculate[3]) - Int32.Parse(rowToCalculate[4]);
		            }
		            // draw game
		            else
		            {
		                m1.Sets += 1;
		                m2.Sets += 1;
		            }
		
		            // second set
		            if(Int32.Parse(rowToCalculate[5]) > 0 && Int32.Parse(rowToCalculate[6]) > 0) // 2ter satz
		            {
		                // first team wins
		                if(Int32.Parse(rowToCalculate[5]) > Int32.Parse(rowToCalculate[6]))
		                {
		                    m1.Sets += 2;
		                    m1.Points += Int32.Parse(rowToCalculate[5]) - Int32.Parse(rowToCalculate[6]);
		                    m2.Points += Int32.Parse(rowToCalculate[6]) - Int32.Parse(rowToCalculate[5]);
		                }
		                // second team wins
		                else if(Int32.Parse(rowToCalculate[5]) < Int32.Parse(rowToCalculate[6]))
		                {
		                    m2.Sets += 2;
		                    m2.Points += Int32.Parse(rowToCalculate[6]) - Int32.Parse(rowToCalculate[5]);
		                    m1.Points += Int32.Parse(rowToCalculate[5]) - Int32.Parse(rowToCalculate[6]);
		                }
		                // draw game
		                else
		                {
		                    m1.Sets += 1;
		                    m2.Sets += 1;
		                }
		
		                // third set
		                if(Int32.Parse(rowToCalculate[7]) > 0 && Int32.Parse(rowToCalculate[8]) > 0) // 3ter satz
		                {
		                    // first team wins
		                    if(Int32.Parse(rowToCalculate[7]) > Int32.Parse(rowToCalculate[8]))
		                    {
		                        m1.Sets += 2;
		                        m1.Points += Int32.Parse(rowToCalculate[7]) - Int32.Parse(rowToCalculate[8]);
		                        m2.Points += Int32.Parse(rowToCalculate[8]) - Int32.Parse(rowToCalculate[7]);
		                    }
		                    // second team wins
		                    else if(Int32.Parse(rowToCalculate[7]) < Int32.Parse(rowToCalculate[8]))
		                    {
		                        m2.Sets += 2;
		                        m2.Points += Int32.Parse(rowToCalculate[8]) - Int32.Parse(rowToCalculate[7]);
		                        m1.Points += Int32.Parse(rowToCalculate[7]) - Int32.Parse(rowToCalculate[8]);
		                    }
		                    // draw game
		                    else
		                    {
		                        m1.Sets += 1;
		                        m2.Sets += 1;
		                    }
		                }
		            }
		        }
		        
		        resultList.Add(m1);
		        resultList.Add(m2);
		    }
		    
		    return resultList;
		}

		public static List<TeamResult> addResultsVrZw(List<TeamResult> teamResults)
		{
			List<TeamResult> calcTeamResults = new List<TeamResult>();
		
		    foreach(TeamResult tR in teamResults)
		    {
		        bool contains = false;
		        		        
		        foreach(TeamResult cTR in calcTeamResults)
		        {
		            if(cTR.TeamName == tR.TeamName)
		            {
		                contains = true;
		                break;
		            }
		        }
		
		        if(!contains)
		        {
		        	List<TeamResult> intermedResult = new List<TeamResult>();
		        	TeamResult result = new TeamResult(tR.TeamName, 0, 0);
		
		            foreach(TeamResult cTR in teamResults)
		            {
		                if(cTR.TeamName == tR.TeamName)
		                    intermedResult.Add(cTR);
		            }
		
		            foreach(TeamResult cTR in intermedResult)
		            {
		                result.TeamName = cTR.TeamName;
		                result.Sets += cTR.Sets;
		                result.Points += cTR.Points;
		            }
		
		            calcTeamResults.Add(result);
		        }
		    }
		
		    return calcTeamResults;
		}

		public static List<String> getResultsKrPl(List<String> rowToCalculate)
		{
		    String spiel = rowToCalculate[0];
		    TeamResult m1 = new TeamResult(rowToCalculate[1], 0, 0);
			TeamResult m2 = new TeamResult(rowToCalculate[2], 0, 0);
		    
		    // first set
		    if(Int32.Parse(rowToCalculate[3]) > 0 && Int32.Parse(rowToCalculate[4]) > 0) // 1ter satz
		    {
		        // first team wins
		        if(Int32.Parse(rowToCalculate[3]) > Int32.Parse(rowToCalculate[4]))
		        {
		            m1.Sets += 2;
		            m1.Points += Int32.Parse(rowToCalculate[3]) - Int32.Parse(rowToCalculate[4]);
		            m2.Points += Int32.Parse(rowToCalculate[4]) - Int32.Parse(rowToCalculate[3]);
		        }
		        // second team wins
		        else if(Int32.Parse(rowToCalculate[3]) < Int32.Parse(rowToCalculate[4]))
		        {
		            m2.Sets += 2;
		            m2.Points += Int32.Parse(rowToCalculate[4]) - Int32.Parse(rowToCalculate[3]);
		            m1.Points += Int32.Parse(rowToCalculate[3]) - Int32.Parse(rowToCalculate[4]);
		        }
		        // draw game
		        else
		        {
		            m1.Sets += 1;
		            m2.Sets += 1;
		        }
		
		        // second set
		        if(Int32.Parse(rowToCalculate[5]) > 0 && Int32.Parse(rowToCalculate[6]) > 0) // 2ter satz
		        {
		            // first team wins
		            if(Int32.Parse(rowToCalculate[5]) > Int32.Parse(rowToCalculate[6]))
		            {
		                m1.Sets += 2;
		                m1.Points += Int32.Parse(rowToCalculate[5]) - Int32.Parse(rowToCalculate[6]);
		                m2.Points += Int32.Parse(rowToCalculate[6]) - Int32.Parse(rowToCalculate[5]);
		            }
		            // second team wins
		            else if(Int32.Parse(rowToCalculate[5]) < Int32.Parse(rowToCalculate[6]))
		            {
		                m2.Sets += 2;
		                m2.Points += Int32.Parse(rowToCalculate[6]) - Int32.Parse(rowToCalculate[5]);
		                m1.Points += Int32.Parse(rowToCalculate[5]) - Int32.Parse(rowToCalculate[6]);
		            }
		            // draw game
		            else
		            {
		                m1.Sets += 1;
		                m2.Sets += 1;
		            }
		
		            // third set
		            if(Int32.Parse(rowToCalculate[7]) > 0 && Int32.Parse(rowToCalculate[8]) > 0) // 3ter satz
		            {
		                // first team wins
		                if(Int32.Parse(rowToCalculate[7]) > Int32.Parse(rowToCalculate[8]))
		                {
		                    m1.Sets += 2;
		                    m1.Points += Int32.Parse(rowToCalculate[7]) - Int32.Parse(rowToCalculate[8]);
		                    m2.Points += Int32.Parse(rowToCalculate[8]) - Int32.Parse(rowToCalculate[7]);
		                }
		                // second team wins
		                else if(Int32.Parse(rowToCalculate[7]) < Int32.Parse(rowToCalculate[8]))
		                {
		                    m2.Sets += 2;
		                    m2.Points += Int32.Parse(rowToCalculate[8]) - Int32.Parse(rowToCalculate[7]);
		                    m1.Points += Int32.Parse(rowToCalculate[7]) - Int32.Parse(rowToCalculate[8]);
		                }
		                // draw game
		                else
		                {
		                    m1.Sets += 1;
		                    m2.Sets += 1;
		                }
		            }
		        }
		    }
		
		    if(m1.Sets > m2.Sets)
		    	return new List<String>(){ spiel, m1.TeamName, m2.TeamName };
		    else
		    	return new List<String>(){ spiel, m2.TeamName, m1.TeamName };
		}
	}
}
