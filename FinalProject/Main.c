#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define ROWSIZE 10
#define COLSIZE 10
#define MAXCHAR 1000
 
struct Salon 
{
	char counter; 
	struct Sans *sans;
	int Place [10][10];
	int capacity;
};

struct Sans
{
	// char *date;
	char startingTime[10];
	char finishingTime[10];
	struct Date *date;
	struct Film *film; 
};

struct Film
{
	char name[75];
	char *actors; 
	char *summary;
	char *director;
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
	struct Salon *salon;
};

struct Date{
	char day[5];
	char month[5];
};

struct Node *head = NULL;

void CreateSans();
void GenerateLinkedList();
void PrintInFile();
void BuyTicket();
void SelectSans();
void DisplaySans();
void ConcatStrings(struct Ticket *ticket);

int main ()
{
	SelectSans();
	int counter = 0 ;
	while (1)
	{
		printf("\n Hi\n welcome to MAX cinema reservation\n please enter command number \n 1-Buy Ticket  \n 2- create Sans \n");
		scanf("%d",&counter);
		
		switch (counter)
		{
		case 1 :
			DisplaySans();
			break;
		case 2:
			PrintInFile();
			break;

		default:
			break;
		}
		
	}	
}

// void BuyTicket()
// {
// 	int Row = 0, Col = 0; 
// 	int Checker = 0;
// 	struct Ticket *ticket;
// 	printf ("Please enter name:\n");
// 	scanf ("%s", ticket->Name);
// 	printf ("Please enter family name:\n");
// 	scanf ("%s", ticket->Family);
// 	printf ("Please enter chair number:\n");
// 	while (Checker != 1)
// 	{
// 		scanf ("%d %d", &Row, &Col);
// 		if (ticket->chairNumber[Row][Col] != 0)
// 		{
// 			Checker = 0;
// 			printf ("This chair is reserved!");
// 		}
// 		else 
// 		{
// 			ticket->chairNumber[Row][Col] = 1;
// 			break;
// 		}
// 	}

// 	// AddTicketToFile(ticket);		
// }

void SelectSans()
{
	char Row, Col;
	char counter = 0;
	char buffer[1000];
	struct Sans *sans;
	struct Film *film;
	struct Date *date;
	struct Salon *salon;
	
	FILE *fp;
	fp = fopen("Sans.txt","r");
	fgets(buffer, 255, (FILE*)fp);
	char * Ticket = strtok(buffer," ");

	while (Ticket != NULL){

		// sizeof(struct Film) + sizeof(struct Sans) + sizeof(struct Date)
		if (counter == 0){	
			sans = (struct sans*)malloc(sizeof(struct Sans));
			film = (struct sans*)malloc(sizeof(struct Film));
			date = (struct sans*)malloc(sizeof(struct Date));
			salon = (struct salon*)malloc(sizeof(struct Salon));					
		}

		if (counter%12 == 0)
		{
			strcpy(film->ID, Ticket);						
		}
		if (counter%12 == 1)
		{
			strcpy(film->name ,Ticket);
			
			// printf("check name\n");
		}
		if (counter%12 == 2)
		{
			strcpy(film->director,Ticket);	
		}
		
		if(counter%12 == 3)
		{
			strcpy(film->actors,Ticket);
			sans->film=film;
			// printf("check mounth\n");
		}
		if(counter%12 == 4)
		{
			strcpy(sans->startingTime,Ticket);						
			// printf("check day");
		}
		
		if(counter%12 == 5)
			strcpy(sans->finishingTime,Ticket);

		if(counter %12== 6)
			strcpy(date->month,Ticket);

		if (counter%12 == 7)
		{
			strcpy(date->day,Ticket);
			sans->date=date;
			salon->sans=sans;
		}
		if (counter%12 == 8)
		{
			strcpy(salon->counter,Ticket);	
		}
		if (counter%12 == 9)
		{
			strcpy(Row ,Ticket);
			
		}
		if (counter%12 == 10)
		{
			strcpy(Col ,Ticket);
			salon->Place[Row][Col] = 1; 
		}
		if (counter%12 == 11)
		{
			strcpy(salon->capacity,Ticket);
		}
		
		counter++;

		if (counter == 12)
		{
			// printf("prepare linkedlist\n");
			GenerateLinkedList();
			counter =0;
		}
		
		Ticket = strtok(NULL," ");
	}
	
	fclose(fp);
	
}
void BuyTicket ()
{
	int counter = 0;
	FILE *fp;
	fp = fopen ("Sans.txt", "r");
	
	if (counter%14 == 1)
	{
		
	}
	
}

void ConcatStrings(struct Ticket *ticket)
{
	char result[100];
	strcat(result,ticket->Name);
	strcat (result,ticket->Family);
	// strcat (result,ticket->chairNumber);
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
// 				return(0);
// 			}
			
// 		}
	
// 	}
// }

void CreateSans()
{
	struct Sans sans;
	printf ("Please enter date(MM/DD):\n");
	scanf ("%s", sans.date);
	printf ("Please enter starting time:\n");
	scanf ("%s", sans.startingTime);
	printf ("Please enter finishing time:\n");
	scanf ("%s", sans.finishingTime);
}

// char date[], char startingTime[], char finishingTime[] 

void PrintInFile()
{
	FILE *fp;
	fp = fopen("Customer.txt","a+");
	fseek(fp,1,SEEK_SET);
	fprintf(fp,"date 12 12 12 ");
	fprintf(fp,"dateAli 12 12 12 ");
	fprintf(fp,"dateMmd 12 12 12 ");
	// fprintf(fp,date);
	// fprintf(fp,startingTime);
	// fprintf(fp,finishingTime);
	fclose(fp);
}

void GenerateLinkedList(struct Salon * salon)
{	
   	struct Node *link = (struct node*) malloc(sizeof(struct Node));
	// printf("get memory\n");

	link->salon = salon;
	link->next = head;		   
	head = link;
	// printf("Node added\n");
}

void DisplaySans()
{
	int counter = 1;
	struct Node *node = head;

	// printf("Displaying \n");
	while (node != NULL)
	{
		// printf("Display Linked list\n");
		printf("%d\t",counter);
		printf("Film: %s\t",node->salon->sans->film->name);
		printf("Starting time: %s\t",node->salon->sans->startingTime);
		printf("Finishing time: %s\n",node->salon->sans->finishingTime);
		printf("month: %s\t",node->salon->sans->date->month);
		printf("Day: %s\t",node->salon->sans->date->day);
		printf("Salon: %s\t",salon->counter);
		printf("Place: %s\t",salon->place);
		printf("Capacity: %s\t", salon->capacity);
		
		node = node->next;
		counter++;
	}
	
}
