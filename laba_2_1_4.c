#include <stdio.h>
#define N 100
int arr[N];

int input_array()
{
	int c = 0, i = 0;
	while ((c = getchar()) != EOF)
	{
		arr[i] = c;
		i++;
	}
	return i;
}

int output_array(int c, int c1)
{
	for (int i = 0; i < c; i++)
		putchar(arr[i]);
	printf("Capital letters:%d\n", c1);
	return 0;
}

int main()
{
	int i, c, c1 = 0;
	c = input_array();

	for (i = 0; i < c; i++)
	{
		if (arr[i] >= 65 && arr[i] <= 90)
			c1++;
	}
	output_array(c, c1);
    return 0;
}