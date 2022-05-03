/* Lucas Voron
 * COEN 11
 * Lab 9
 * Tuesday 2:15pm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

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

void insert(char *, int);
int delete();
void list();
int search_size();
void clean();
void read_all(char *);
void save_all(char *);
void back_lists(void);
void back_names(void);
void backward_list(NODE *);
void backward_name(char *);
void delete_list(NODE *);
void *auto_save(void *);
void read_auto_saved(char *);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutext_unlock(pthread_mutex_t *mutex);
pthread_mutex_t mutex;


int main(int argc, char *argv[])
{
	
	if(argc==1)
	{
		printf("The file is not named.\n");
		return 1;
	}

	read_all(argv[1]);

	pthread_mutex_init (&mutex, NULL);
	pthread_t Th;
	pthread_create(&Th, NULL, auto_save, (void*)argv[2]);

	int x;
	int input;

	NODE *p;
	char name[20];

	printf("Schedule A Surf Lesson!\n\n");
	printf("(1) Schedule Appointment\n");
	printf("(2) Remove Appointment\n");
	printf("(3) List Schedule\n");
	printf("(4) Search by Group Size\n");
	printf("(5) Waitlist Re-ordered Backward\n");
	printf("(6) Waitlist Names Backward\n");
	printf("(7) Binary File\n");
	printf("(0) Exit\n\n");

	while(1)
	{
		scanf("%d", &input);

		switch(input)
		{
			case 0:
				pthread_cancel(Th);
				save_all(argv[1]);
				clean();
			 	return 1;
			case 1:
				printf("Please enter your name.\n");
				scanf("%s", name);
				
				if(check_duplicate(name)==1)
				{
					printf("This name is already on the waitlist.\n");
					break;
				}

				printf("Please enter the size of your group.\n");
				scanf(" %d", &x);

				insert(name, x);

				printf("A waitlist spot for %s has been booked.\n", name);
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
			case 5:
				back_lists();
				break;
			case 6:
				back_names();
				break;
			case 7:
				read_auto_saved(argv[2]);
				break;
			default:
				printf("That command is not valid.\n");
				printf("1, 2, 3, 4, 5, or 6 are the only valid commands\n\n");
				break;
		}
	}
	return 0;
}

//waitlist[i].name
//entry*next

void insert(char *name, int x)
{
	NODE *p;

	if ((p = (NODE *) malloc (sizeof (NODE))) == (NODE *)NULL)
	{
		printf ("Malloc error.\n");
		exit (1);
	}

	pthread_mutex_lock(&mutex);

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

	pthread_mutex_unlock(&mutex);
	return;
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
			pthread_mutex_lock(&mutex);
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
			pthread_mutex_unlock(&mutex);
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

void clean()
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
//calls save_all function?

void read_all(char *file_name)
{
	FILE *fp;
	char name[20];
	int x;

	if((fp = fopen(file_name, "r"))==NULL)
	{
		printf("Cannot open file lab7data.txt\n");
		return;
	}
	
	fseek( fp, 55, SEEK_SET);

	while(fscanf(fp, "%s     %d", name, &x)==2)
	{
		insert(name, x);
	}
	fclose(fp);
	return;
}
//calls insert function

void save_all(char *file_name)
{
	FILE *fp;
	NODE *p;

	int i;
	fp = fopen(file_name, "w");
	
	if(fp==NULL)
		return;

	fprintf(fp, "Name     Group Size\n ---------------------------------\n");

	for(i=0; i<4; i++)
	{
		p=waitlist[i].head;
		while(p != NULL)
		{
			fprintf(fp, "%s     %d\n", p->names, p->size);
			p = p->next;
		}
	}
	fclose(fp);
	return;
}

void back_lists(void)
{
	int i;
	int j;
	NODE *p;
	int empty = 0;

	for(j=0; j<4; j++)
	{
		if(waitlist[j].head == NULL)
			empty++;
	}

	if(empty == 4)
	{
		printf("There are no appointments on the waitlist.\n");
			return;
	}

	for(i=0; i<4; i++)
	{
		p = waitlist[i].head;
		printf("List %d:\n", i+1);
		backward_list(p);
	}

	return;
}

void backward_list(NODE *p)
{
	if(p == NULL)
		return;

	backward_list(p->next);

	printf("%s, %d\n", p->names, p->size);
		return;
}

void back_names(void)
{
	int i;
	int j;
	NODE *p;

	int empty = 0;

	for(j=0; j<4; j++)
	{
		if(waitlist[j].head == NULL)
			empty++;
	}

	if(empty == 4)
	{
		printf("There are no appointments on the waitlist.\n");
			return;
	}

	for(i=0; i<4; i++)
	{
		p = waitlist[i].head;
		printf("List %d:\n", i+1);
		while(p!=NULL)
		{
			backward_name(p->names);
			printf("\n");
			p = p->next;
		}
	}
	
	return;
}

void backward_name(char *p)
{
	if(*p == '\0')
		return;
	backward_name(p+1);
	printf("%c", *p);
		return;
}

void *auto_save(void *file_name)
{
	//char *file_name = (char*) arg;
	FILE *fp;
	NODE *p;
	
	int i;

	while(1)
	{
		sleep(15);
		printf("Auto-save\n");
		pthread_mutex_lock(&mutex);
		{
			fp = fopen(file_name, "wb");
			for(i=0; i<4; i++)
			{
				p = waitlist[i].head;
				while(p != (NODE *)NULL)
				{
					fwrite(p, sizeof(NODE), 1, fp); //loop traverse list writing to file
					p = p->next;
				}
			}
			fclose(fp);
		}
		pthread_mutex_unlock(&mutex);
	}
}

void read_auto_saved(char *file_name)
{
	FILE *fp;
	NODE p;
	int i;

	pthread_mutex_lock(&mutex);
	fp = fopen(file_name, "rb");
	while(fread(&p, sizeof(NODE), 1, fp)==1)
	{
		printf("%s, %d\n", p.names, p.size);
	}
	fclose(fp);
	pthread_mutex_unlock(&mutex);
	return;
}
