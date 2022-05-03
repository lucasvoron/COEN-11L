/* Lucas Voron
 * COEN 11
 * Lab 2
 * Tuesday 2:15pm
 */

#include <stdio.h>
#include <string.h>
#define SIZE 5
#define LENGTH 20

int counter = 0;
int size[SIZE];
char names[SIZE][LENGTH];

void insert(void);
void delete(void);
void list(void);

int main()
{
	int input;
	
	printf("Schedule A Surf Lesson!\n\n");
	printf("(1) Schedule Appointment\n");
	printf("(2) Remove Appointment\n");
	printf("(3) List Schedule\n");
	printf("(0) Exit\n\n");

	while(1)
	{
		scanf("%d", &input);

		switch(input)
		{
			case 0:
				return 0;
			case 1:
				insert();
				break;
			case 2:
				delete();
				break;
			case 3:
				list();
				break;
			default:
				printf("That command is not valid.\n");
				printf("1, 2, or 3 are the only valid commands\n\n");
				break;
		}
	}
	return 0;
}

void insert()
{
	int x; 
	char name[20];
	int i;
	int j;

	if(counter==5)
		printf("The waitlist is full, please come back to schedule a surf appointment later.\n");
	else
	{
		printf("Please enter your name.\n");
		scanf("%s", name);

		printf("Please enter the size of your group.\n");
		scanf(" %d", &x);

		i=0;
		while(i<=counter)
		{
			if(names[i][0]=='\0')
			{
				strcpy(names[i], name);
				size[i] = x;
				printf("A spot for %s, has been made for a group of %d\n", names[i], x);
				counter++;
				break;
			}
			i++;
		}
	}

}

void delete()
{
	char null[20] = {'\0'};
	int x;
	int i;
	int j;

	if(counter==0)
		printf("There are no spots on the waitlist to cancel.\n");
	else
	{
		printf("What is the number of people of you have space to remove off of the waitlist?\n");
		scanf("%d", &x);

		i=0;
		while(i<counter && x>0)
		{
			if(x>=size[i])
			{
				x = x-size[i];
				printf("An appointment spot has been filled by %s.\n", names[i]);
				j=i;
				while(j<counter-1)
				{
					strcpy(names[j], names[j+1]);
					size[j] = size[j+1];
					j++;
				}
				strcpy(names[counter], null);
				size[counter] = 0;
				counter--;
			}
			else
				i++;
		}
	}
}

void list()
{
	int i;

	if(counter==0)
	{
		printf("There is no one on the waitlist.\n");
	}
	else
	{
		printf("Name   Group Size\n");
		i=0;

		while(i<counter)
		{
			printf("%s   %d\n", names[i], size[i]);
			i++;
		}
	}
}

