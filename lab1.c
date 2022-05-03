/* Lucas Voron
 * COEN 11
 * Lab 5
 * Tuesday 9:15am
 */

#include <stdio.h>

int main(void);
int division(int, int);

int counter = 0;
int result;

int main(void)
{
	srand((int)time(NULL));

	int i;

	for(i=0; i<10; i++)
	{
		int divisor = rand() % 12+1;
		int quotient = rand() % 13;

		result = division(divisor, quotient);
		if(result==1)
		{
			printf("Correct!\n");
		}
		else
		{
			printf("Incorrect :( here is the right answer: %d\n", quotient);
		}
	}
	printf("You got %d0 percent correct.\n", counter);
}

int division(int divisor, int quotient)
{
	int x;

	printf("%d / %d = ?\n", divisor*quotient, divisor);
	scanf(" %d", &x);

	if(x==quotient)
	{
		counter++;
		return 1;
	}
	else
	{
		return 0;
	}
}
