#include "stdio.h"
#include "stdlib.h"

#define N 100

int input_array(int arr[N])
{
	int c, i = 0;
	while ((c = getchar()) != '\n')
	{
		arr[i] = c;
		i++;
		if (i == N)
			break;
	}
	return i;
}

int output_array(int arr[N], int c)
{
	for (int i = 0; i < c; i++)
		putchar(arr[i]);
	return 0;
}

int check_bkt(int arr[N], int c)
{
	int trigger = 0;
	for (int i = 0; i < c; i++)
	{
		if (arr[i] == '(')
		{
//			arr[i] = -2;
			trigger++;
		}
		else if (arr[i] == ')') 
		{
//			arr[i] = -2;
			trigger--;
		}
		else if (trigger > 0)
			arr[i] = -2;

	}
	if (!trigger)
		return 1;
	else
	{
		printf("\n____ERROR____\n");
		exit(1);
	}
}

void main()
{
	int arr[N];
	int cnt_of_elem = 0, shift = 0;

	cnt_of_elem = input_array(arr);

	check_bkt(arr, cnt_of_elem);

	for (int i = 0; i < cnt_of_elem; i++)
	{
		if (arr[i] == -2)
		{
			shift++;
			continue;
		}
		arr[i - shift] = arr[i];
	};
	cnt_of_elem -= shift;

	output_array(arr, cnt_of_elem);

}
