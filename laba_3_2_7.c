#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"


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

void output_answer(int **arr, int N, int M)
{
	FILE *file_out;

	file_out = fopen("output.txt", "w");

	for (int i = N - 1; i >= 0; i--)
	{
		for (int j = 0; j < M; j++)
			fprintf(file_out, "%d\t", arr[i][j]);
		fprintf(file_out, "\n");
	}
	fclose(file_out);
}

void swap(int **arr, int N, int M, int l, int r)
{
	for (int j = 0; j < M; j++)
	{
		int temp = arr[l][j];
		arr[l][j] = arr[r][j];
		arr[r][j] = temp;
	}
}

void qsort(int **arr, int N, int M, int b, int e)
{
	int l = b, r = e;
	int piv = arr[(l + r) / 2][0];
	while (l <= r)
	{
		while (arr[l][0] < piv)
			l++;
		while (arr[r][0] > piv)
			r--;
		if (l <= r)
			swap(arr, N, M, l++, r--);
	}
	if (b < r)
		qsort(arr, N, M, b, r);
	if (e > l)
		qsort(arr, N, M, l, e);
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

	qsort(arr, N, M, 0, N - 1);

	output_answer(arr, N, M);

	exit(1);
}
