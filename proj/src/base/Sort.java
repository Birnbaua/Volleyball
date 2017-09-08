package base;

public class Sort
{
	public Team[] mergeSort(Team[] arr)  //is finished, works
	{
		return mergeSortIntArray(arr);
	}
	
	private Team[] mergeSortIntArray(Team[] arr)
	{
		if(arr.length > 1)
		{
			int j = arr.length/2;
			Team[] left = new Team[j];
			int i = 0;
		
			for(; i < j; i++)
				left[i]=arr[i];

			if((arr.length) % 2 != 0)
				j++;
			
			Team[] right = new Team[j];
			
			for(int k = 0;k < j; k++)
				right[k]= arr[i+k];
			
			left = mergeSortIntArray(left);
			right = mergeSortIntArray(right);
			
			return mergeIntArray(left,right);
		}
		else
		{
			return arr;
		}
	}
	
	private Team[] mergeIntArray(Team[] left, Team[] right)
	{
		Team[] arr = new Team[left.length + right.length];
		int i = 1;
		int j = 0;
		int k = 0;
		
		while(left.length >= (j + 1) && right.length >= (k + 1))
		{
			if(left[j].getPointsFirstRound() > right[k].getPointsFirstRound()) //if left is bigger
			{
				arr[i - 1] = left[j];
				j++;
			}
			else if(left[j].getPointsFirstRound() < right[k].getPointsFirstRound()) //if right is bigger
			{
				arr[i - 1] = right[k];
				k++;
			}
			else //if they are the same
			{
				if(left[j].getGamePointsFirstRound() > right[k].getGamePointsFirstRound())//if left is bigger
				{
					arr[i - 1] = left[j];
					j++;
				}
				else //if right is bigger
				{
					arr[i - 1] = right[k];
					k++;
				}
			}
			
			i++;
		}
		
		while(j < left.length)
		{
			arr[i - 1] = left[j];
			j++;
			i++;
		}
		
		while(k < right.length)
		{
			arr[i - 1] = right[k];
			k++;
			i++;
		}
		
		return arr;
	}	
}