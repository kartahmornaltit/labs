#define _CRT_SECURE_NO_WARNINGS
#include "stdio.h"
#include "stdlib.h"

#define N 3
#define M 2

void input_data(int arr[N][M], int vec[M])
{
	FILE *file_in;

	file_in = fopen("input.txt", "r");

	for (int i = 0; i < N; i++)
		for (int j = 0; j < M; j++)
			fscanf(file_in, "%d", &arr[i][j]);
	
	for (int i = 0; i < M; i++)
		fscanf(file_in, "%d", &vec[i]);

	fclose(file_in);
}

void output_answer(int ans[N])
{
	FILE *file_out;

	file_out = fopen("output.txt", "w");

	for (int i = 0; i < N; i++)
		fprintf(file_out, "%d\n", ans[i]);

	fclose(file_out);
}

void multiply(int arr[N][M], int vec[M], int ans[N])
{
	for (int i = 0; i < N; i++)
	{
		int sum = 0;
		for (int r = 0; r < M; r++)
			sum += arr[i][r] * vec[r];
		ans[i] = sum;
	}
	
}

void main()
{
	int arr[N][M] = { { 0 } }, vec[M] = { 0 }, ans[N] = { 0 };

	input_data(arr, vec);

	multiply(arr, vec, ans);

	output_answer(ans);

	exit(1);
}
