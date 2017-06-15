#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

#define N 8

void input_queen(int arr[N][N])
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			arr[i][j] = '-';
	int i, j;
	printf("row = ");
	scanf_s("%d", &i);
	printf("column = ");
	scanf_s("%d", &j);
	if (i < 1 || i > 8 || j < 1 || j > 8)
	{
		printf("\n____ERROR____\n");
		exit(1);
	}
	else
		arr[i - 1][j - 1] = 'Q';
}

void output_array(int arr[N][N])
{
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			printf("%c ", arr[i][j]);
		}
		printf("\n");
	}
}

void set_marks(int arr[N][N])
{
	int col, row, trigger = false;
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (arr[i][j] == 'Q')
			{
				row = i; 
				col = j;
				trigger = true;
				break;
			}
		}
		if (trigger)
			break;
	}
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if ((i == row || j == col || (abs(i - row) == abs(j - col))) && arr[i][j] != 'Q')
				arr[i][j] = '+';
		}
	}
}

void main()
{
	int arr[N][N];

	input_queen(arr);

	set_marks(arr);

	output_array(arr);
}
