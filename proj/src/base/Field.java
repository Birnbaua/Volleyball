package base;

public class Field 
{
	private String name;
	private int number;
	
	public Field(String str, int num)
	{
		this.name=str;
		this.number=num;
	}
	
	public int getNumber()
	{
		return number;
	}
	
	public void setNumber(int number)
	{
		this.number = number;
	}
	
	public String getName()
	{
		return name;
	}
	
	public void setName(String name) 
	{
		this.name = name;
	}
}
