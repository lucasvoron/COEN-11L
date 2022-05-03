/* Lucas Voron
 * COEN 11
 * Lab 6
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

struct list
{
	struct node *head;
	struct node *tail;
};

struct list waitlist[4] = {{NULL, NULL}, {NULL, NULL}, {NULL, NULL}, {NULL, NULL}};

void insert();
int delete();
void list();
int search_size();
void clean();

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
				clean();
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

	strcpy(p->names, name);
	p->size = x;

	if(x==1 || x==2)
	{
		if(waitlist[0].head==NULL)
		{
			p->next = NULL;
			waitlist[0].head = p;
			waitlist[0].tail = waitlist[0].head;
		}
		else
		{
			p->next = NULL;
			waitlist[0].tail->next=p;
			waitlist[0].tail=p;
		}
	}
	else if(x==3 || x==4)
	{
		if(waitlist[1].head==NULL)
		{
			p->next = NULL;
			waitlist[1].head = p;
			waitlist[1].tail = waitlist[1].head;
		}
		else
		{
			p->next = NULL;
			waitlist[1].tail->next = p;
			waitlist[1].tail = p;
		}
	}
	else if(x==5 || x==6)
	{
		if(waitlist[2].head==NULL)
		{
			p->next = NULL;
			waitlist[2].head = p;
			waitlist[2].tail = waitlist[2].head;
		}
		else
		{
			p->next = NULL;
			waitlist[2].tail->next = p;
			waitlist[2].tail = p;
		}
	}
	else
	{
		if(waitlist[3].head==NULL)
		{
			p->next = NULL;
			waitlist[3].head = p;
			waitlist[3].tail = waitlist[3].head;
		}
		else
		{
			p->next = NULL;
			waitlist[3].tail->next = p;
			waitlist[3].tail = p;
		}
	}
	printf("A spot for %s, has been made for a group of %d\n", p->names, x);

}


int delete(int size)
{
	NODE *p, *q;

	int i;
	int n;
	int counter = 0;
	int x;
	int y;

	for(n=0; n<4; n++)
	{
		if(waitlist[n].head==NULL)
			counter++;
	}
	if(counter==4)
	{
		printf("There are no spots on the waitlist to cancel.\n");
		return;
	}
	else
	{
		printf("What is the number of people of you have space to remove off of the waitlist?\n");
		scanf("%d", &x);

		if(x<=2)
			y = 1;
		else if(x<=4)
			y = 2;
		else if(x<=6)
			y = 3;
		else
			y = 4;

		for(i=0; i<y; i++)
		{
			p = q = waitlist[i].head;
	
			while (p != (NODE *)NULL)
			{
				if(p->size <= x)
				{
					x=x-p->size;
					if(waitlist[i].head==waitlist[i].tail)
					{
						free(p);
						waitlist[i].head=NULL;
						waitlist[i].tail=NULL;
						break;
					}
					else if(p==waitlist[i].head)
					{
						waitlist[i].head=p->next;
						free(p);
						p=q=waitlist[i].head;
					}
					else if(p==waitlist[i].tail)
					{
						waitlist[i].tail=q;
						q->next=NULL;
						free(p);
						break;
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
	}
	return (1);
}


void list()
{
	NODE	*p;
	int i;
	int k=0;

	for(i=0; i<4; i++)
	{
		printf("List of group sizes %d-%d:\n", k+1, k+2);

		if (waitlist[i].head == (NODE *)NULL)
		{
			printf ("empty\n");
		}

		p = waitlist[i].head;
		while (p != (NODE *)NULL)
		{
			printf ("%s, %d\n", p->names, p->size);
			p = p->next;
		}
		k=k+2;
	}
	return;
}

int search_size()
{
	NODE	*p;
	int y;
	int i;
	int n;
	int counter=0;
	int k=0;

	for(n=0; n<4; n++)
	{
		if(waitlist[n].head==NULL)
			counter++;
	}
	if(counter==4)
	{
		printf("There are no groups on the waitlist to search through.\n");
		return;
	}

	else
	{
		printf("Enter a group size.\n");
		scanf(" %d", &y);

		for(i=0; i<4; i++)
		{
			printf("List of group sizes %d-%d:\n", k+1, k+2);
			p=waitlist[i].head;
			while(p != (NODE *)NULL)
			{
				if(p->size <= y)
				{
					printf("%s, %d\n", p->names, p->size);
				}
				p = p->next;
			}
			k=k+2;
		}
	}
	return (0);
}

int check_duplicate(char *name)
{
	NODE *p;
	int i;

	for(i=0; i<4; i++)
	{
		p=waitlist[i].head;
		while(p != (NODE *)NULL)
		{
			if(strcmp(name, p->names)==0)
				return 1;
			p = p->next;
		}
	}
	return 0;
}

void clean(char*names, int size)
{
	int i;
	NODE *p;
	NODE *q;

	for(i=0; i<4; i++)
	{
		p=waitlist[i].head;
		while(p != NULL)
		{
			q=p->next;
			free(p);
			p=q;
		}
	}
}
