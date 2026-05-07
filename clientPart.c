//client part
#include<stdio.h>
#include<conio.h>
#include<string.h>
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
int main(){
	char name[50], phoneNo[15], password[30], rePassword[30];
	printf("\t\tWelcome to client portal!\n\n ");
	 //	int cnt=count();
 //	int choice = 2;
	int flag=0, t, i, flag2=0, attempts, menuOption;
    FILE *fptr;
	fptr = fopen("clients.txt", "rb+");
	fread(c, sizeof(struct client), 3, fptr);
	printf("\nPlease enter your name to continue!\t");
	fflush(stdin);
	gets(name);
	for(i=0; i<3; i++)
	{
		if(strcasecmp(name, c[i].name)==0)
		{
			flag = 1;
			t = i;
		}
	}
	
	if(flag == 1)
	{
		printf("Welcome %s. \nPlease enter your registered phone number continue. \n", c[t].name);
		attempts=3;
		while(attempts!=0){
		printf("\nPhone number: ");
		fflush(stdin);
		gets(phoneNo);
		if(strcmp(c[t].phoneNumber, phoneNo)==0)
		{
			attempts=0;
			if(c[t].password[0]=='\0'){
				//	flag2 = 1;
				//	printf("\ntrue\n"); error handeling
				attempts = 3;
				
				while(attempts!=0){
				printf("\nCreate your password: ");
				fflush(stdin);
				gets(password);
				printf("\nRe-enter your password to confirm: ");
				fflush(stdin);
				gets(rePassword);
				if(strcmp(password, rePassword)==0){
					printf("\nPassword set successfully. Please re-Run to login.");
					strcpy(c[t].password, password);
					fseek(fptr, t * sizeof(struct client), SEEK_SET);
    				fwrite(&c[t], sizeof(struct client), 1, fptr);
    				fflush(fptr);
					//printf("\npassword: %s\n", c[t].password); error handeling
					attempts = 0;
				    }
				else{
					printf("\n\aError! Password doesn't match.");
					attempts--;
						if (attempts !=0){
							printf("\n%d attempt left. ", attempts);
						}
						else{
							break;
				       }
				    }
			      }
				}
			else{
				attempts = 3;
				while(attempts!=0){
					printf("\nPassword: ");
					fflush(stdin);
					gets(password);
					if(strcmp(c[t].password, password)==0){
						printf("Login Successful!\n ");
						printf("Name: %s\nID: %d\nAccount number: %s\nPhone number: %s\nAccount balance: %f\nCurrent interest rate: %f", c[t].name, c[t].id, c[t].accountNo, c[t].phoneNumber, c[t].balance, c[t].interestRate);
						attempts = 0;
						printf("\n\nPress 1 to transfer money.\n");
						printf("Press any other key to exit. \n");
						scanf("%d", &menuOption);
						if(menuOption==1){
							printf("Money transfer process under construction. \nThis process should ask user to type phone number or account number. \ncheck if it matches anyone in database. \nif yes, continue money transfer. \nif no destination account doesnot exist. Contact your nearest branch. ");
							
						}
						else{
							printf("PROGRAM TERMINATED\a");
							break;
						}
					}
					else{
						printf("\n\aError! Password doesn't match.");
						attempts--;
						if (attempts !=0){
							printf("\n%d attempt left. ", attempts);
						}
						else{
							printf("\nContact nearest branch!");
						}
					}
				
				}
			
				}
		
//		printf("Name: %s\nID: %d\nAccount number: %s\nPhone number: %s\nAccount balance: %f\nCurrent interest rate: %f", c[t].name, c[t].id, c[t].accountNo, c[t].phoneNumber, c[t].balance, c[t].interestRate);

		}
		else{
			printf("\aPhone number didn't match!");
			attempts--;
				if (attempts !=0){
					printf("\n%d attempt left. ", attempts);
				}
				else{
					printf("\nContact your nearest branch!");
				}
			}
		}
		
		
	}
	else{
		printf("Client not found! Contact to your nearest branch.\n");
		}
	
	fclose(fptr);
	getch();
	return 0;
}
