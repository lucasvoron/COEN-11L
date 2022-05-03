/* Lucas Voron
 * COEN 11
 * Lab 3
 * Tuesday 2:15pm
 */

#include <stdio.h>
#include <string.h>
#define SIZE 5
#define LENGTH 20
#define WAITLIST struct waitlist

int counter = 0;

struct entry
{
	int size;
	char names[LENGTH];
};

struct entry waitlist[SIZE];

void insert();
void delete();
void list();
void search_size();

int main()
{
	int input;
	
	printf("Schedule A Surf Lesson!\n\n");
	printf("(1) Schedule Appointment\n");
	printf("(2) Remove Appointment\n");
	printf("(3) List Schedule\n");
	printf("(4) Search by Group Size\n");
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
			case 4:
				search_size();
				break;
			default:
				printf("That command is not valid.\n");
				printf("1, 2, or 3 are the only valid commands\n\n");
				break;
		}
	}
	return 0;
}

//waitlist[i].name

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

		if(check_duplicate(name)==1)
		{
			printf("This name is already on the waitlist.\n");
			return;
		}

		printf("Please enter the size of your group.\n");
		scanf(" %d", &x);

		i=0; 
		while(i<=counter)
		{
			if(waitlist[i].names[0]=='\0')
			{
				strcpy(waitlist[i].names, name);
				waitlist[i].size = x;
				printf("A spot for %s, has been made for a group of %d\n", waitlist[i].names, x);
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
			if(x>=waitlist[i].size)
			{
				x = x-waitlist[i].size;
				printf("An appointment spot has been filled by %s.\n", waitlist[i].names);
				j=i;
				while(j<counter-1)
				{
					strcpy(waitlist[j].names, waitlist[j+1].names);
					waitlist[j].size = waitlist[j+1].size;
					j++;
				}
				strcpy(waitlist[counter].names, null);
				waitlist[counter].size = 0;
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
			printf("%s   %d\n", waitlist[i].names, waitlist[i].size);
			i++;
		}
	}
}

void search_size()
{
	int x;
	int i=0;
	int flag=0;

	if(counter==0)
		printf("There is no one on the waitlist.\n");
	else
	{
		printf("Enter a group size.\n");
		scanf(" %d", &x);

		i=0;
		while(i<counter)
		{
			if(waitlist[i].size <= x)
			{
				printf("%s   %d\n", waitlist[i].names, waitlist[i].size);
				flag++;
			}
			i++;
		}
		if(flag==0)
			printf("There are no groups with a size equal to or smaller than what you enter.\n");
	}
}

int check_duplicate(char *str)
{
	int i;

	for(i=0; i<counter; i++)
	{
		if(strcmp(str, waitlist[i].names)==0)
			return 1;
	}
	return 0;
}
