#include <stdio.h>
#include <math.h>

int main()
{
	int answer, input_number;

	printf("N = ");
	scanf_s("%d", &input_number);

	answer = sqrt(input_number);

	printf("k = %d", answer);
	return 0;
}
