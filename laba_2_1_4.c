#include <stdio.h>
#define N 100
int arr[N];

int input_array()
{
	int c = 0, i = 0;
	while ((c = getchar()) != '\n')
	{
		arr[i] = c;
		i++;
	}
	return i;
}

int output_array(int length, int capital_letters_count)
{
	for (int i = 0; i < length; i++)
		putchar(arr[i]);
	printf("\nCapital letters:%d\n", capital_letters_count);
	return 0;
}

int main()
{
	int length = 0, capital_letters_count = 0;
	length = input_array();

	for (int i = 0; i < length; i++)
	{
		if (arr[i] >= 65 && arr[i] <= 90)
			capital_letters_count++;
	}
	output_array(length, capital_letters_count);
    return 0;
}
