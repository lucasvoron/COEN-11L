/* Lucas Voron
 * COEN 11
 * Lab 4
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
	int max_age;
	char names[LENGTH];
	union extra_info
	{
		int youngest;
		float group_avg;
		char phone[20];
	} extra;
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
	union extra_info extra;

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

		printf("Please enter the age of the oldest person in the group.\n");
		scanf(" %d", &waitlist[counter].max_age);

		if(waitlist[counter].max_age<18)
		{
			printf("Please provide the phone number of a parent/guardian\n");
			scanf(" %s", waitlist[counter].extra.phone);
		}
		if(waitlist[counter].max_age>65)
		{
			printf("Please provide the age of the youngest person in the group.\n");
			scanf(" %d", &waitlist[counter].extra.youngest);
		}
		if(waitlist[counter].max_age>=18 && waitlist[counter].max_age<=65)
		{
			printf("Please provide the average age of the group.\n");
			scanf(" %f", &waitlist[counter].extra.group_avg);
		}

		strcpy(waitlist[counter].names, name);
		waitlist[counter].size = x;
		printf("A spot for %s, has been made for a group of %d\n", waitlist[counter].names, x);
		counter++;
	}

}

void delete()
{
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
					waitlist[j] = waitlist[j+1];
					j++;
				}
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
	union extra_info extra;

	if(counter==0)
	{
		printf("There is no one on the waitlist.\n");
	}
	else
	{
		printf("Name | Group Size | Max Age | Extra Info\n");
		i=0;

		while(i<counter)
		{
			printf("%s        %d        %d", waitlist[i].names, waitlist[i].size, waitlist[i].max_age);
			if(waitlist[i].max_age<18)
			{
				printf("        %s\n", waitlist[i].extra.phone);
			}
			if(waitlist[i].max_age>65)
			{
				printf("        %d\n", waitlist[i].extra.youngest);
			}
			if(waitlist[i].max_age>18 && waitlist[i].max_age<65)
			{
				printf("        %f\n", waitlist[i].extra.group_avg);
			}
			i++;
		}
	}
}

void search_size()
{
	int x;
	int i=0;
	int flag=0;
	union extra_info extra;

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
				printf("%s        %d        %d", waitlist[i].names, waitlist[i].size, waitlist[i].max_age);
				if(waitlist[i].max_age<18)
				{
					printf("        %s\n", waitlist[i].extra.phone);
				}
				if(waitlist[i].max_age>65)
				{
					printf("        %d\n", waitlist[i].extra.youngest);
				}
				if(waitlist[i].max_age>18 && waitlist[i].max_age<65)
				{
					printf("        %f\n", waitlist[i].extra.group_avg);
				}
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
