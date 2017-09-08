package test;

import java.util.Random;
import base.Field;
import base.Team;
import qualifying.*;

public class VolleyBall
{
	public static void main(String[] args) 
	{
		Team[] teams = new Team[20];
	
		for(int i = 0; i < teams.length; i++)
			teams[i] = new Team(String.format("%c", 65 + i));
		
		Field[] field = new Field[teams.length / 5];
		
		for(int i = 0; i < teams.length / 5; i++)
			field[i] = new Field(String.format("Field%d", i + 1), i + 1);
		
		Qualifying test = new Qualifying(teams, field);
		
		test.generateQualifying(0, 1, 0);
		Random rnd = new Random(System.currentTimeMillis());
		
		for(int i = 0; i < teams.length * 2; i++)
			test.setMatchPoints(i, 1 + rnd.nextInt(20), 1 + rnd.nextInt(20));
		
		test.evaluateRound();
		Team[] ev = test.getEvaluatedList();
		
		System.out.println(test.innerEvaluate());
		
		for(int i = 0; i < teams.length; i++)
			System.out.printf("\n %3s | %2d | %2d", 
							  test.getInnerEvaluated()[i / test.getGroupLength()][i % test.getGroupLength()].getName(),
							  test.getInnerEvaluated()[i / test.getGroupLength()][i % test.getGroupLength()].getPointsFirstRound(),
							  test.getInnerEvaluated()[i / test.getGroupLength()][i % test.getGroupLength()].getGamePointsFirstRound());
		
		System.out.println("\n");
		System.out.println(test.toString());
	}
}
