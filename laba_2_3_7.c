#include "stdio.h"
#include "stdlib.h"
#define true 1
#define false 0

#define N 8

void input_queen(int arr[N][N])
{
	for (int i = 0; i < N; i++)
		for (int j = 0; j < N; j++)
			arr[i][j] = 219;
	int i, j;
	printf("column = ");
	scanf_s("%d", &i);
	printf("row = ");
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
			printf("%c\t", arr[i][j]);
		}
		printf("\n");
	}
}

void set_marks(int arr[N][N])
{
	int col, row;
	for (int i = 0; i < N; i++)
	{
		int trigger = false;
		for (int j = 0; j < N; j++)
		{
			if (arr[i][j] == 'Q')
			{
				row = i + 1; 
				col = j + 1;
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
			if (((i + 1) == row || (j + 1) == col || (i + j + 2) == (row + col) || (abs(i + 1 - row) == abs(j + 1 - col))) && arr[i][j] != 'Q')
				arr[i][j] = 253;
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
