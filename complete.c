#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>

#define USERNAME "admin"
#define PASSWORD "admin"
#define MAX 100

struct client {
    char name[50];
    int id;
    char accountNo[20];
    char phoneNumber[20];
    char password[30];
    float balance;
    float interestRate;
    float interest;
};

struct client c[MAX];

int totalClients = 0;

/* FUNCTION PROTOTYPES */
void loadClients();
void saveClients();
int login();
void adminMenu();
void clientMenu();
void newRegistration();
int searchClientByName(char name[]);
int searchClientByAcc(char acc[]);
void depositMoney();
void withdrawMoney();
void addInterest();
void transferMoney();
void hiddenPassword(char pass[]);

/* MAIN FUNCTION */
int main() {

    int choice;

    while(1) {

        system("cls");

        printf("\n=====================================\n");
        printf("        BANKING MANAGEMENT SYSTEM\n");
        printf("=====================================\n");

        printf("\n1. Admin");
        printf("\n2. Client");
        printf("\n3. Exit");

        printf("\n\nEnter choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice) {

            case 1:
                if(login()) {
                    adminMenu();
                }
                break;

            case 2:
                clientMenu();
                break;

            case 3:
                printf("\nProgram terminated.\n");
                exit(0);

            default:
                printf("\nInvalid choice!");
                getch();
        }
    }

    return 0;
}

/* LOAD CLIENTS */
void loadClients() {

    FILE *fp;

    totalClients = 0;

    fp = fopen("clients.txt", "rb");

    if(fp == NULL) {
        return;
    }

    while(fread(&c[totalClients], sizeof(struct client), 1, fp)) {

        totalClients++;

        if(totalClients >= MAX)
            break;
    }

    fclose(fp);
}

/* SAVE CLIENTS */
void saveClients() {

    FILE *fp;

    fp = fopen("clients.txt", "wb");

    if(fp == NULL) {
        printf("\nFile Error!");
        return;
    }

    fwrite(c, sizeof(struct client), totalClients, fp);

    fclose(fp);
}

/* ADMIN LOGIN */
int login() {

    char user[30];
    char pass[30];

    int attempts = 3;

    while(attempts != 0) {

        system("cls");

        printf("\n========== ADMIN LOGIN ==========\n");

        printf("\nUsername: ");
        fgets(user, sizeof(user), stdin);
        user[strcspn(user, "\n")] = '\0';

        printf("Password: ");
        hiddenPassword(pass);

        if(strcmp(user, USERNAME) == 0 &&
           strcmp(pass, PASSWORD) == 0) {

            printf("\n\nLogin Successful!");
            Sleep(1000);
            return 1;
        }

        attempts--;

        printf("\nInvalid credentials!");

        if(attempts != 0)
            printf("\nAttempts left: %d", attempts);

        Sleep(1500);
    }

    printf("\nAccess denied!");
    Sleep(1500);

    return 0;
}

/* HIDDEN PASSWORD */
void hiddenPassword(char pass[]) {

    int i = 0;
    char ch;

    while((ch = getch()) != 13) {

        if(ch == 8 && i > 0) {
            i--;
            printf("\b \b");
        }
        else {
            pass[i++] = ch;
            printf("*");
        }
    }

    pass[i] = '\0';
}

/* ADMIN MENU */
void adminMenu() {

    int choice;

    while(1) {

        loadClients();

        system("cls");

        printf("\n========== ADMIN MENU ==========\n");

        printf("\n1. Register Client");
        printf("\n2. Deposit");
        printf("\n3. Withdraw");
        printf("\n4. Add Interest");
        printf("\n5. View Clients");
        printf("\n6. Exit");

        printf("\n\nEnter choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice) {

            case 1:
                newRegistration();
                break;

            case 2:
                depositMoney();
                break;

            case 3:
                withdrawMoney();
                break;

            case 4:
                addInterest();
                break;

            case 5: {

                int i;

                printf("\n=========== CLIENT LIST ===========\n");

                for(i=0; i<totalClients; i++) {

                    printf("\nName: %s", c[i].name);
                    printf("\nID: %d", c[i].id);
                    printf("\nAccount No: %s", c[i].accountNo);
                    printf("\nPhone: %s", c[i].phoneNumber);
                    printf("\nBalance: %.2f", c[i].balance);
                    printf("\n---------------------------\n");
                }

                getch();
                break;
            }

            case 6:
                return;

            default:
                printf("\nInvalid choice!");
                getch();
        }
    }
}

/* NEW REGISTRATION */
void newRegistration() {

    loadClients();

    if(totalClients >= MAX) {

        printf("\nDatabase Full!");
        getch();
        return;
    }

    int i = totalClients;

    system("cls");

    printf("\n========== NEW CLIENT ==========\n");

    c[i].id = i + 1;

    sprintf(c[i].accountNo, "1000%d", c[i].id);

    printf("\nClient ID: %d", c[i].id);

    printf("\nAccount No: %s", c[i].accountNo);

    printf("\nName: ");
    fgets(c[i].name, sizeof(c[i].name), stdin);
    c[i].name[strcspn(c[i].name, "\n")] = '\0';

    printf("Phone Number: ");
    fgets(c[i].phoneNumber, sizeof(c[i].phoneNumber), stdin);
    c[i].phoneNumber[strcspn(c[i].phoneNumber, "\n")] = '\0';

    printf("Initial Balance: ");
    scanf("%f", &c[i].balance);

    printf("Interest Rate: ");
    scanf("%f", &c[i].interestRate);
    getchar();

    c[i].interest = 0;

    strcpy(c[i].password, "");

    totalClients++;

    saveClients();

    printf("\nClient Registered Successfully!");

    getch();
}

/* SEARCH BY NAME */
int searchClientByName(char name[]) {

    int i;

    for(i=0; i<totalClients; i++) {

        if(stricmp(name, c[i].name) == 0)
            return i;
    }

    return -1;
}

/* SEARCH BY ACCOUNT */
int searchClientByAcc(char acc[]) {

    int i;

    for(i=0; i<totalClients; i++) {

        if(strcmp(acc, c[i].accountNo) == 0)
            return i;
    }

    return -1;
}

/* DEPOSIT */
void depositMoney() {

    char name[50];
    int i;
    float amount;

    loadClients();

    printf("\nEnter client name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    i = searchClientByName(name);

    if(i == -1) {

        printf("\nClient not found!");
        getch();
        return;
    }

    printf("Amount: ");
    scanf("%f", &amount);

    if(amount <= 0) {

        printf("\nInvalid amount!");
        getch();
        return;
    }

    c[i].balance += amount;

    saveClients();

    printf("\nDeposit Successful!");

    getch();
}

/* WITHDRAW */
void withdrawMoney() {

    char name[50];
    int i;
    float amount;

    loadClients();

    printf("\nEnter client name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    i = searchClientByName(name);

    if(i == -1) {

        printf("\nClient not found!");
        getch();
        return;
    }

    printf("Amount: ");
    scanf("%f", &amount);

    if(amount > c[i].balance) {

        printf("\nInsufficient balance!");
        getch();
        return;
    }

    c[i].balance -= amount;

    saveClients();

    printf("\nWithdrawal Successful!");

    getch();
}

/* ADD INTEREST */
void addInterest() {

    char name[50];
    int i, months;

    loadClients();

    printf("\nEnter client name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    i = searchClientByName(name);

    if(i == -1) {

        printf("\nClient not found!");
        getch();
        return;
    }

    printf("Months: ");
    scanf("%d", &months);

    c[i].interest =
        (c[i].balance * c[i].interestRate * months) / (100 * 12);

    c[i].balance += c[i].interest;

    saveClients();

    printf("\nInterest Added!");

    getch();
}

/* CLIENT MENU */
void clientMenu() {

    loadClients();

    char name[50];
    char phone[20];
    char pass[30];

    int i;

    system("cls");

    printf("\n========== CLIENT LOGIN ==========\n");

    printf("\nEnter Name: ");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = '\0';

    i = searchClientByName(name);

    if(i == -1) {

        printf("\nClient not found!");
        getch();
        return;
    }

    printf("Phone Number: ");
    fgets(phone, sizeof(phone), stdin);
    phone[strcspn(phone, "\n")] = '\0';

    if(strcmp(phone, c[i].phoneNumber) != 0) {

        printf("\nWrong phone number!");
        getch();
        return;
    }

    if(strlen(c[i].password) == 0) {

        printf("\nCreate Password: ");
        hiddenPassword(pass);

        strcpy(c[i].password, pass);

        saveClients();

        printf("\nPassword created successfully!");
        getch();

        return;
    }

    printf("\nPassword: ");
    hiddenPassword(pass);

    if(strcmp(pass, c[i].password) != 0) {

        printf("\nWrong Password!");
        getch();
        return;
    }

    while(1) {

        int ch;

        system("cls");

        printf("\n========== CLIENT PANEL ==========\n");

        printf("\nName: %s", c[i].name);
        printf("\nBalance: %.2f", c[i].balance);

        printf("\n\n1. Transfer Money");
        printf("\n2. Exit");

        printf("\n\nChoice: ");
        scanf("%d", &ch);
        getchar();

        switch(ch) {

            case 1:
                transferMoney();
                break;

            case 2:
                return;

            default:
                printf("\nInvalid choice!");
                getch();
        }
    }
}

/* MONEY TRANSFER */
void transferMoney() {

    loadClients();

    char sender[50];
    char receiverAcc[20];

    int s, r;

    float amount;

    printf("\nSender Name: ");
    fgets(sender, sizeof(sender), stdin);
    sender[strcspn(sender, "\n")] = '\0';

    s = searchClientByName(sender);

    if(s == -1) {

        printf("\nSender not found!");
        getch();
        return;
    }

    printf("Receiver Account No: ");
    fgets(receiverAcc, sizeof(receiverAcc), stdin);
    receiverAcc[strcspn(receiverAcc, "\n")] = '\0';

    r = searchClientByAcc(receiverAcc);

    if(r == -1) {

        printf("\nReceiver not found!");
        getch();
        return;
    }

    printf("Amount: ");
    scanf("%f", &amount);

    if(amount <= 0) {

        printf("\nInvalid amount!");
        getch();
        return;
    }

    if(amount > c[s].balance) {

        printf("\nInsufficient balance!");
        getch();
        return;
    }

    c[s].balance -= amount;

    c[r].balance += amount;

    saveClients();

    printf("\nTransfer Successful!");

    getch();
}
