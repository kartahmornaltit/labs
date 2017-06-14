#include "stdio.h"
#include "stdlib.h"

#define N 100

int input_array(int *arr)
{
	int c, i = 0;
	while ((c = getchar()) != EOF)
	{
		arr[i] = c;
		i++;
	}
	return i;
}

int output_array(int *arr, int c)
{
	for (int i = 0; i < c; i++)
		putchar(arr[i]);
	return 0;
}

int cheak_bkt(int *arr, int c)
{
	int triger = 0;
	for (int i = 0; i < c; ++i)
	{
		c = arr[i];
		if (c == '(')
		{
			arr[i] = -2;
			triger++;
		}
		else if (c == ')') 
		{
			arr[i] = -2;
			triger--;
		}
		else if (triger > 0)
			arr[i] = -2;

	}
	if (!triger)
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
	int cnt_of_elem, cheak, shift = 0;

	cnt_of_elem = input_array(arr);

	cheak_bkt(arr, cnt_of_elem);

	for (int i = 0; i < cnt_of_elem; i++)
	{
		if (arr[i] == -2)
		{
			arr[i] = 0;
			shift++;
			continue;
		}
		arr[i - shift] = arr[i];
	} cnt_of_elem -= shift;

	output_array(arr, cnt_of_elem);

	exit(1);
}
