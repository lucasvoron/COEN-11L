/* Lucas Voron
 * COEN 11
 * Lab 5
 * Tuesday 2:15pm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 5
#define LENGTH 20
#define NODE struct node

struct node
{
	int size;
	char names[LENGTH];
	NODE *next;
};

NODE *head = (NODE *)NULL;
NODE *tail = (NODE *)NULL;

void insert();
int delete();
void list();
int search_size();

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
				printf("1, 2, 3, or 4 are the only valid commands\n\n");
				break;
		}
	}
	return 0;
}

//waitlist[i].name
//entry*next

void insert(char *names, int size)
{
	NODE *p;
	int x; 
	char name[20];
	int i;

	if ((p = (NODE *) malloc (sizeof (NODE))) == (NODE *)NULL)
	{
		printf ("Malloc error.\n");
		exit (1);
	}

	printf("Please enter your name.\n");
	scanf("%s", name);
	
	if(check_duplicate(name)==1)
	{
		printf("This name is already on the waitlist.\n");
		return;
	}

	printf("Please enter the size of your group.\n");
	scanf(" %d", &x);

	p=malloc(sizeof(NODE));
	strcpy(p->names, name);
	p->size = x;
	p->next = head;
	head = p;
	printf("A spot for %s, has been made for a group of %d\n", p->names, x);

}


int delete(int size)
{
	NODE *p, *q;
	p=q=head;

	int x;

	if(head==NULL)
		printf("There are no spots on the waitlist to cancel.\n");
	else
	{
		printf("What is the number of people of you have space to remove off of the waitlist?\n");
		scanf("%d", &x);
	
		while (p != (NODE *)NULL)
		{
			if(p->size <= x)
			{
				x=x-p->size;
				if(head==tail)
				{
					free(p);
					head=NULL;
					tail=NULL;
					return(1);
				}
				else if(p==head)
				{
					head=p->next;
					free(p);
					p=q=head;
				}
				else if(p==tail)
				{
					tail=q;
					q->next=NULL;
					free(p);
					return(1);
				}
				else
				{
					q->next=p->next;
					free(p);
					p=q->next;
				}
			}
			else
			{
				q = p;
				p = p->next;
			}
		}
	}
	return (1);
}


void list()
{
	NODE	*p;

	if (head == (NODE *)NULL)
	{
		printf ("the list is empty\n");
		return;
	}

	p = head;
	while (p != (NODE *)NULL)
	{
		printf ("%s, %d\n", p->names, p->size);
		p = p->next;
	}
	return;
}

int search_size()
{
	NODE	*p;
	int y;

	printf("Enter a group size.\n");
	scanf(" %d", &y);

	if(head == (NODE*)NULL)
		printf("There are no appointments to search.\n");
	else
	{
		p=head;
		while(p != (NODE*)NULL)
		{
			if(p->size <= y)
			{
				printf("%s, %d\n", p->names, p->size);
			}
			else
			{
				printf("There are no appointments smaller than the group size provided.\n");
			}
		p = p->next;
		}
	}
	return (0);
}

int check_duplicate(char *name)
{
	NODE *p;

	p = head;
	while(p != (NODE *)NULL)
	{
		if(strcmp(name, p->names)==0)
			return 1;
		p = p->next;
	}
	return 0;
}
