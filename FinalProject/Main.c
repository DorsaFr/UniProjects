#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ROWSIZE 10
#define COLSIZE 10
#define MAXCHAR 1000
 
struct Salon 
{
	int counter; 
	struct Sans *sans;
	// int place[10][10];
	int capacity;
};

struct Sans
{
	char startingTime[10];
	char finishingTime[10];
	struct Date *date;
	struct Film *film; 
};

struct Film
{
	char name[75];
	char actors[200]; 
	char summary[100];
	char director[100];
	int ID;
};


struct Node{
	// char data[100];
	struct Salon *salon;
	struct Node *next;
};

struct Ticket
{
	char Name[50];
	char Family[50];
	int chairNumber[10][10];
	int filmId;
	int ticketNumber;
};

struct Date{
	char day[5];
	char month[5];
};

struct Place{
	int Row;
	int Col;
};

struct Node *head = NULL;
int filmNumber;

void GenerateLinkedList();
void BuyTicket();
void SelectSans();
void DisplaySans();
void printArray();
void quickSort(); 
int partition (); 
void swap();
void Sort();
int CheckCapacity();
void TicketReserving();
void StoreTicket();
void CreateSans();
void PrintInFile();

int main ()
{
	SelectSans();
	int counter = 0 ;
	while (1)
	{
		printf("\n Hi\n Welcome to City Cinema Reservation\n please enter command number \n 1-Buy Ticket  \n 2- Display Sans \n 3- Create sans \n 4- Exit \n");
		scanf("%d",&counter);
		
		switch (counter)
		{
		case 1 :
			BuyTicket();
			break;
		case 2:
			DisplaySans();
			break;
		case 3:	
			CreateSans ();
			break;			
		case 4:	
			exit (0);
			break;
		}
		
	}	
}

void CreateSans()
{

	char buffer[1000];
	struct Sans *sans;
	struct Film *film;
	struct Date *date;
	struct Salon *salon;
	struct Place *place;

	sans = (struct sans*)malloc(sizeof(struct Sans));
	film = (struct sans*)malloc(sizeof(struct Film));
	date = (struct sans*)malloc(sizeof(struct Date));
	salon = (struct salon*)malloc(sizeof(struct Salon));					

	printf("please enter film ID \n ");
	scanf("%d",&film->ID);
	printf("please enter film name \n ");
	scanf("%s",&film->name);
	printf("please enter film director \n ");
	scanf("%s",&film->director);
	printf("please enter film actors in this patern (actor1,actor2) \n");
	scanf("%s",&film->actors);

	printf("please enter starting time \n ");
	scanf("%c",&sans->startingTime);
	printf("please enter finishing time \n");
	scanf("%c",&sans->finishingTime);

	printf("please enter mounth \n ");
	scanf("%c",&date->month);
	printf("please enter day \n ");
	scanf("%c",&date->day);

	printf("please enter capacity \n ");
	scanf("%d",&salon->capacity);
	printf("please salon number \n ");
	scanf("%d",&salon->counter);

	sans->date = date;
	sans->film = film;
	salon->sans = sans;

	PrintInFile(salon);

}

void PrintInFile(struct Salon *salon)
{
	FILE *fp;
	fp = fopen("Sans.txt","a+");
	char contents[300];
	char temp[100];

	strcat(contents," ");
	strcat(contents,itoa(salon->sans->film->ID,temp,10));
	strcat(contents," ");
	strcat(contents,salon->sans->film->name);
	strcat(contents," ");
	strcat(contents,salon->sans->film->director);
	strcat(contents," ");
	strcat(contents,salon->sans->film->actors);
	strcat(contents," ");
	strcat(contents,salon->sans->startingTime);
	strcat(contents," ");
	strcat(contents,salon->sans->finishingTime);
	strcat(contents," ");
	strcat(contents,salon->sans->date->month);
	strcat(contents," ");
	strcat(contents,salon->sans->date->day);
	strcat(contents," ");
	strcat(contents,itoa(salon->counter,temp,10));
	strcat(contents," ");
	strcat(contents,itoa(salon->capacity,temp,10));

	fputs(contents,fp);

	fclose(fp);

	printf("successful");

}


void Sort()
{	
	
	int arr[filmNumber];
	int counter = 0;
	struct Node *node = head;
	while (node != NULL)
	{
		arr[counter] = node->salon->sans->film->ID;
		node = node->next;
		counter++;
	}

	quickSort(arr, 0, filmNumber-1); 
	printArray(arr, filmNumber); 
}

int CheckCapacity(int id,int number)
{
	struct Node *node = head;
	while (node != NULL)
	{
		if(id == node->salon->sans->film->ID)
		{
			if (node->salon->capacity - number > 0)
				return 2;
			else{
				return 4;
			}
		}

		node = node->next;
	}		
	return 3;
}

void StoreTicket(struct Ticket *ticket)
{
	char contents[1000];
	char temp[100];
	FILE *fp;

	fp = fopen("Customer.txt","a+");

	strcat(contents,ticket->Name);
	strcat(contents," ");
	strcat(contents,ticket->Family);
	strcat(contents," ");
	strcat(contents,itoa(ticket->ticketNumber,temp,10));
	strcat(contents," ");
	strcat(contents,itoa(ticket->filmId,temp,10));
	strcat(contents," ");

	printf("%s",contents);
	fputs(contents,fp);
	fclose(fp);
}

void TicketReserving(int filmId, int number)
{
	FILE *fp;
	char content[1000];
	struct Node *node = head;
	char temp[100];
	fp = fopen("Sans.txt","w");
	
	while(node != NULL)	
	{
		if (node->salon->sans->film->ID == filmId)
			node->salon->capacity = node->salon->capacity -number;

		strcat(content,itoa(node->salon->sans->film->ID,temp,10));
		strcat(content," ");
		strcat(content,node->salon->sans->film->name);
		strcat(content," ");
		strcat(content,node->salon->sans->film->director);
		strcat(content," ");
		strcat(content,node->salon->sans->film->actors);
		strcat(content," ");
		strcat(content,node->salon->sans->startingTime);
		strcat(content," ");
		strcat(content,node->salon->sans->finishingTime);
		strcat(content," ");
		strcat(content,node->salon->sans->date->month);
		strcat(content," ");
		strcat(content,node->salon->sans->date->day);
		strcat(content," ");
		strcat(content,itoa(node->salon->counter,temp,10));
		strcat(content," ");
		strcat(content,itoa(node->salon->capacity,temp,10));
		strcat(content," ");
		node = node->next;
	}
	
	fputs(content,fp);
	fclose(fp);
}

void BuyTicket()
{
	int Row = 0, Col = 0; 
	int Checker = 0;
	int cnt = 0;

	struct Ticket *ticket;
	ticket = (struct ticket*)malloc(sizeof(struct Ticket));

	printf ("Please Enter your Name:\n");
	scanf ("%s", &ticket->Name);
	printf ("Please Enter your Family Name:\n");
	scanf ("%s", &ticket->Family);
	printf ("How many ticket do you want:\n");
	scanf ("%d", &ticket->ticketNumber);
	printf("please enter film id: \n");
	scanf("%d",&ticket->filmId);

	int capacity = CheckCapacity(ticket->filmId,ticket->ticketNumber);
	if(capacity == 2)
	{
		TicketReserving(ticket->filmId,ticket->ticketNumber);
		printf("ticket is reserved");
	}
	else if(capacity == 4)
		printf("sorry salon is fulled");
	else
		printf("Film id is not corect");
				

	StoreTicket(ticket);

}

void SelectSans()
{
	int counter = 0;
	int Row;
	int Col;
	char buffer[1000];
	struct Sans *sans;
	struct Film *film;
	struct Date *date;
	struct Salon *salon;
	struct Place *place;
	
	FILE *fp;
	fp = fopen("Sans.txt","r");
	fgets(buffer, 255, (FILE*)fp);
	char *Ticket = strtok(buffer," ");

	while (Ticket != NULL){

		// sizeof(struct Film) + sizeof(struct Sans) + sizeof(struct Date)
		if (counter == 0)
		{	
			sans = (struct sans*)malloc(sizeof(struct Sans));
			film = (struct sans*)malloc(sizeof(struct Film));
			date = (struct sans*)malloc(sizeof(struct Date));
			salon = (struct salon*)malloc(sizeof(struct Salon));					
		}

		if (counter%10 == 0){
			film->ID = atoi(Ticket);						
		}
		
		if (counter%10 == 1)
			strcpy(film->name ,Ticket);
		
		if (counter%10 == 2)
			strcpy(film->director,Ticket);	
		
		if(counter%10 == 3){
			strcpy(film->actors,Ticket);
			sans->film=film;
		}
		
		if(counter%10 == 4)
		{
			strcpy(sans->startingTime,Ticket);						
		}
		
		if(counter%10 == 5)
			strcpy(sans->finishingTime,Ticket);

		if(counter %10== 6)
			strcpy(date->month,Ticket);

		if (counter%10 == 7)
		{
			strcpy(date->day,Ticket);
			sans->date=date;
			salon->sans=sans;
		}
		
		if (counter%10 == 8)
			salon->counter = atoi(Ticket);	
		
		// if (counter%12 == 9)
		// 	Row = atoi(Ticket);			
		
		// if (counter%12 == 10)
		// {
		// 	Col = atoi(Ticket);
		// 	salon->place[Row][Col] = 1;
		// }
		
		if (counter%10 == 9)
		{
			salon->capacity = atoi(Ticket);
		}
		
		counter++;

		if (counter == 10)
		{
			GenerateLinkedList(salon);
			filmNumber++;
			counter =0;
		}
		
		Ticket = strtok(NULL," ");
	}
	
	fclose(fp);
	
}

// void AddTicketToFile()
// {

// 	FILE *fp;
// 	char Result;
// 	fp = fopen ("Customer.txt", "a+");
// 	fprintf(fp,);

// }

// int ChairValidator(int chairNumber[][10],int Row, int Col)
// {
// 	for (size_t i = 0; i < 10; i++)
// 	{
// 		for (size_t j = 0; i < 10; j++)
// 		{
// 			if (chairNumber[i][j] != 0)
// 			{
// 			// Not Reserved
// 				return(0);
// 			}
			
// 		}
	
// 	}
// }

// char date[], char startingTime[], char finishingTime[] 


void GenerateLinkedList(struct Salon * salon)
{	
   	struct Node *link = (struct node*) malloc(sizeof(struct Node));

	link->salon = salon;
	link->next = head;		   
	head = link;
	
}

void DisplaySans()
{
	int counter = 1;
	struct Node *node = head;

	while (node != NULL)
	{
		printf("ID :%d\t",node->salon->sans->film->ID);
		printf("Film: %s\t",node->salon->sans->film->name);
		printf("direcor: %s\n",node->salon->sans->film->director);
		printf("actors: %s\t",node->salon->sans->film->actors);
		printf("Starting time: %s\t",node->salon->sans->startingTime);
		printf("Finishing time: %s\n",node->salon->sans->finishingTime);
		printf("month: %s\t",node->salon->sans->date->month);
		printf("Day: %s\t",node->salon->sans->date->day);
		printf("Salon: %d\n",node->salon->counter);
		// printf("Row of %s\t",node->salon->Place);
		printf("Capacity: %d\t", node->salon->capacity);
		printf("\n");
		node = node->next;
		counter++;
	}

	char question[5];
	printf("\n do you want to sort list\n");
	scanf("%s",question);

	if (strcmp(question,"yes") == 0)
		Sort();
	
}


void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
  
int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high];
    int i = (low - 1);  
  
    for (int j = low; j <= high- 1; j++) 
    { 
        if (arr[j] < pivot) 
        { 
            i++;    
            swap(&arr[i], &arr[j]); 
        } 
    } 
    swap(&arr[i + 1], &arr[high]); 
    return (i + 1); 
} 
  
void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
		
        int pi = partition(arr, low, high); 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
		
    } 
} 


void printArray(int arr[], int size) 
{ 	
    
	for (size_t i = 0; i < size; i++)
	{
		struct Node *node = head;

		while (node != NULL)
		{
			if (arr[i] == node->salon->sans->film->ID)
			{
				printf("ID :%d\t",node->salon->sans->film->ID);
				printf("Film: %s\t",node->salon->sans->film->name);
				printf("direcor: %s\n",node->salon->sans->film->director);
				printf("actors: %s\t",node->salon->sans->film->actors);
				printf("Starting time: %s\t",node->salon->sans->startingTime);
				printf("Finishing time: %s\n",node->salon->sans->finishingTime);
				printf("month: %s\t",node->salon->sans->date->month);
				printf("Day: %s\t",node->salon->sans->date->day);
				printf("Salon: %d\n",node->salon->counter);
				// printf("Row of %s\t",node->salon->Place);
				printf("Capacity: %d\t", node->salon->capacity);
				printf("\n");
			}
			node = node->next;
		}
	}	
	
} 