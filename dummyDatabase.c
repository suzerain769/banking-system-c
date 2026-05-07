//pre entry file creation to run 
#include<stdio.h>
#include<conio.h>
#include<string.h>
//
struct client{
	char name[50];
	int id;
	char accountNo[15];
	char phoneNumber[15];
	char password[30];
	float balance;
	float interestRate;
	float interest;
}c[100];
float byaj(float, float);
int main()
{
	int flag1 =0;
	FILE *fptr;
	fptr = fopen("clients.txt", "wb");
	if(fptr==NULL)
	{
		printf("Error! File couldn't be opened.");
	}
	else{
		c[0].id = 1;
		strcpy(c[0].name,"Prashant Acharya");
		strcpy(c[0].accountNo, "17502805279");
		strcpy(c[0].phoneNumber, "9762252757");
		c[0].balance = 12572.79;
		c[0].interestRate = 4;
		c[0].interest = byaj(12572.79, 4);
		
		c[1].id = 2;
		strcpy(c[1].name,"Yugal Kishore Dahal");
		strcpy(c[1].accountNo, "17502805289");
		strcpy(c[1].phoneNumber, "9767174067");
		c[1].balance = 15000;
		c[1].interestRate = 4;
		c[1].interest = byaj(15000, 4);
		
		c[2].id = 3;
		strcpy(c[2].name,"Ghanshyam prasad pokhrel");
		strcpy(c[2].accountNo, "17502805299");
		strcpy(c[2].phoneNumber, "9840032911");
		c[2].balance = 13500;
		c[2].interestRate = 4;
		c[2].interest = byaj(13500, 4);
		
//		int i=0;
//		char ch;
//		printf("\n-------------Enter client details(press 'esc' when done)-------------\n");
//		while(1)
//		{
//			printf("Client %d: \n", i+1);
//			printf("Client ID: ");
//			scanf("%s", c[i].id);
//			printf("Name: ");
//			fflush(stdin);	
//			gets(c[i].name);
//			printf("Account number: ");
//			scanf("%ld", &c[i].accountNo);
//			printf("Contact number: ");
//			scanf("%ld", &c[i].phoneNumber);
//			printf("Account balance: ");
//			scanf("%f", &c[i].balance);
//			printf("Current interest rate(p.a.): ");
//			scanf("%f", &c[i].interestRate);
//			if((ch=getch()) == 27)
//			{
//				break;
//			}
//			i++;
//			flag1++;
//		}
		fwrite(c, sizeof(struct client), 3, fptr );
	//	fwrite(&c, sizeof(c),flag1, fptr);
		printf("\nClients data stored successfully!");
	}
	
	fclose(fptr);
	getch();
	return 0;
}
float byaj(float principle, float rate)
{
	float interest = (principle *rate*1)/100;
	return interest;
}
