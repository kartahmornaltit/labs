#include <stdio.h>
#include <stdlib.h>


void set_N_M(int * N, int * M)
{
	FILE *file_in;
	int simb = 0, m = 0, in_numb = 0;

	file_in = fopen("input.txt", "r");

	while ((simb = fgetc(file_in)) != EOF)
	{
		if (simb == 32) {
			in_numb = 0;
		}
		else if (simb == 10) {
			if (*N > 1) {
				if (*M != m) {
					printf("ERROR\n");
					exit(1);
				}
			}
			(*N)++;
			*M = m;
			m = 0;
			in_numb = 0;
		}
		else if (simb > 47 & simb < 58) {
			if (in_numb)
				continue;
			in_numb++;
			m++;
		}
	}

	fclose(file_in);
}

void input_data(int **arr, int N, int M)
{
	FILE *file_in;

	file_in = fopen("input.txt", "r");

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			fscanf(file_in, "%d", &arr[i][j]);

	fclose(file_in);
}

void search(int **a, int N, int M) {
	int count = 0, min, max;
	for (int i = 0; i < N; i++) 
	{
		min = a[i][0];
		for (int j = 0; j < M; j++)
			if (a[i][j] < min)
				min = a[i][j];
		for (int j = 0; j < M; j++) 
			if (a[i][j] == min) 
			{
				max = a[0][j];
				for (int k = 0; k < N; k++) 
					if (a[k][j] > max) 
						max = a[k][j];
				if (min == max) {
					printf("i = %d; j = %d\n", i + 1, j + 1);
					count++;
				}
			}
	}
	if (count == 0) 
		printf("no such elements");
	else
		printf("%d elements\n", count);
}



void main()
{
	int **arr;
	int N = 0, M = 0;

	set_N_M(&N, &M);

	arr = (int**)malloc(N * sizeof(int));

	for (int i = 0; i < N; i++)
		arr[i] = (int*)malloc(M * sizeof(int));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			arr[i][j] = 0;
		}
	}

	input_data(arr, N, M);

	search(arr, N, M);

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < M; j++)
			printf("%4.0d", arr[i][j]);
		printf("\n");
	}
}
