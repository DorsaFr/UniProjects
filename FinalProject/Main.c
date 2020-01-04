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
	int capacity [10][10];
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
};


struct Node{
	// char data[100];
	struct Sans *sans;
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
	char mounth[5];
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
		printf("\n Hi\n welcome to Dorsa cinema reservation\n please enter command number \n 1-Buy Ticket  \n 2- create Sans \n");
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
	int counter = 0;
	char buffer[1000];
	struct Sans *sans;
	struct Film *film;
	struct Date *date;

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
		}

		if (counter%5 == 0){
			printf("%s\n",Ticket);
			strcpy(film->name ,Ticket);
			sans->film=film;
			// printf("check name\n");
		}
			
		if(counter %5 == 1){
			strcpy(date->mounth,Ticket);
			// printf("check mounth\n");
		}
			
		if(counter %5 == 2)
		{
			strcpy(date->day,Ticket);
			sans->date = date;						
			// printf("check day");
		}
			
		if(counter %5 == 3)
			strcpy(sans->startingTime,Ticket);

		if(counter %5 == 4)
		strcpy(sans->finishingTime,Ticket);

		counter++;

		if (counter == 5){
			// printf("prepare linkedlist\n");
			GenerateLinkedList(sans);
			// printf("linkedlist\n");
			counter =0;
		}

		Ticket = strtok(NULL," ");
	}
	fclose(fp);
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

void GenerateLinkedList(struct Sans * sans)
{	
   	struct Node *link = (struct node*) malloc(sizeof(struct Node));
	// printf("get memory\n");

	link->sans = sans;
	link->next = head;		   
	head = link;
	// printf("Node added\n");
}

void DisplaySans()
{
	int counter =1;
	struct Node *node = head;

	// printf("Displaying \n");
	while (node != NULL)
	{
		// printf("Display Linked list\n");
		printf("%d\t",counter);
		printf("Film: %s\t",node->sans->film->name);
		printf("mounth: %s\t",node->sans->date->mounth);
		printf("Day: %s\t",node->sans->date->day);
		printf("Starting time: %s\t",node->sans->startingTime);
		printf("Finishing time: %s\n",node->sans->finishingTime);
		node = node->next;
		counter++;
	}
	
}


