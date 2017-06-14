#include <stdio.h>
#include <math.h>

int main()
{
	int c, n;

	printf("N = ");
	scanf_s("%d", &n);

	c = sqrt(n);

	printf("k = %d\n", c);
	getchar();
	return 0;
}
