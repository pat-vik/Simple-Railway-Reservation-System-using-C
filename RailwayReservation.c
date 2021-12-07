#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

typedef struct passenger
{
    char name[30];
    int seats;
    char date[15];
    int train_num;
}pass_details;

void trains();
int login(char *un);
void signup();
int menu(int *choice);
void reserve();
float charge(int train_num,int seats);
void ticket(char *name,int seats,int train_num,char *date,float charges);
void specifictrain(int train_num);
void view(char *un);
void loginpage(char *un);

int main()
{
    printf("\n    ****************************************************\n");
    printf("\n\t\t        WELCOME");
    printf("\n\n\t\t\t   TO");
    printf("\n\n\t\tRAILWAY RESERVATION SYSTEM!");
    printf("\n\n   ****************************************************");
    printf("\n\n\tPress any key to continue...");
    getch();
    char un[30];

    loginpage(un);

    int choice;
    int *p=choice;
    choice=menu(p);
    while(choice)
    {
        switch(choice)
        {
            case 1: reserve(un);
                        system("cls");
                        break;
            case 2:
                        trains();
                        printf("\n\nPress any key to go to the Main Menu...");
                        getch();
                        system("cls");
                        break;
            case 3: view(un);
                        printf("\tPress any key to go to the Main Menu...");
                        getch();
                        system("cls");
                        break;
            case 4: loginpage(un);
                        break;
            default: printf("\n\tINVALID OPTION!");
                        printf("\n\tPress any key to re-enter your option...");
                        getch();
                        system("cls");
        }
        choice=menu(p);
    }
    return 0;
}

void trains()
{
	system("cls");
	printf("-----------------------------------------------------------------------------");
	printf("\n\nTr.No\tName\t\t\tDestinations\t\tCharges\t\tTime\n\n");
	printf("-----------------------------------------------------------------------------");
	printf("\n\n1001\tAgra Express\t\tAgra To New Delhi\tRs.5000\t\t9am");
	printf("\n\n1002\tAgra Express\t\tNew Delhi To Agra\tRs.5000\t\t12pm");
	printf("\n\n1003\tDeccan Express\t\tMumbai To Pune\t\tRs.4500\t\t8am");
	printf("\n\n1004\tDeccan Express\t\tPune To Mumbai\t\tRs.4500\t\t11am");
	printf("\n\n1005\tBrindavan Express\tBangalore To Chennai\tRs.4000\t\t7am");
	printf("\n\n1006\tBrindavan Express\tChennai To Bangalore\tRs.4000\t\t9.30am");
    printf("\n\n1007\tGoa Express\t\tGoa To Mumbai\t\tRs.3500\t\t1pm");
    printf("\n\n1008\tGoa Express\t\tMumbai To Goa\t\tRs.3500\t\t4pm");
    printf("\n\n1009\tGujarat Express\t\tAhmedabad To Bangalore\tRs.6000\t\t3.35pm");
    printf("\n\n1010\tGujarat Express\t\tBangalore To Ahmedabad\tRs.6000\t\t4.15pm");
}

int menu(int *choice)
{
    printf("\n\t\t=================================\n");
	printf("   \t\t    RAILWAY RESERVATION SYSTEM");
	printf("\n\t\t=================================");
	printf("\n\n\t\t1) Book A Ticket");
	printf("\n\n\t\t------------------------");
	printf("\n\n\t\t2) View All Available Trains");
	printf("\n\n\t\t------------------------");
	printf("\n\n\t\t3) View your Bookings");
	printf("\n\n\t\t------------------------");
	printf("\n\n\t\t4) Log-Out");
	printf("\n\n\t\t------------------------");
    printf("\n\n\tEnter any option:");
    scanf("%d",&choice);
    return choice;
}

int login(char *un)
{   system("cls");
    char u[30];
    char pass[30],p[30];
    printf("\n\tENTER USERNAME:");
    scanf("%s",un);
    printf("\n\tENTER PASSWORD:");
    scanf("%s",pass);
    FILE *f;
    f=fopen("login.txt","r");
    int pr=1;
    while(fscanf(f,"%s\t%s",u,p)!=EOF)
    {
        if(strcmp(u,un)==0 && strcmp(p,pass)==0)
        {
            pr=0;
            printf("\n\tYOU HAVE LOGGED IN SUCCESSFULLY!");
            getch();
            system("cls");
            return 0;
        }
    }

    if(pr)
    {
        printf("\n\tINVALID USERNAME AND PASSWORD!");
        printf("\n\n\tIf you are a new user then sign-up!");
        printf("\n\n\tPress enter to return to login page...");
        getch();
        system("cls");
        return 1;
    }
    fclose(f);
}

void signup()
    {   system("cls");
        char un[30],pass[30];
        printf("\n\tCREATE NEW USERNAME AND PASSWORD:");
        printf("\n\n\tEnter username:");
        scanf("%s",un);
        printf("\n\n\tEnter password:");
        scanf("%s",pass);
        FILE *f;
        f=fopen("login.txt","a");
        fprintf(f,"\n%s\t%s",un,pass);
        fclose(f);
        printf("\n\tYOU HAVE SIGNED-UP SUCCESSFULLY!");
        printf("\n\n\tPress Enter to return to Login Page....");
        getch();
        system("cls");
}

void reserve(char *un)
{
    system("cls");
    pass_details p;
    char confirm[5];
    float charges;
    FILE *f;
    char filename[100];
    sprintf(filename,"%s.txt",un);
    f=fopen(filename,"a");
    printf("\n\t************ RESERVATION ************");
    printf("\n\n\tENTER YOUR NAME:");
    scanf("%s",p.name);
    printf("\n\tENTER THE NUMBER OF SEATS:");
    scanf("%d",&p.seats);
    printf("\n\tENTER DATE (dd/mm/yy):");
    scanf("%s",p.date);
    printf("\n\n\t>>PRESS ENTER TO VIEW AVAILABLE TRAINS<<");
    int s=1;
    while(s)
    {
        getch();
        system("cls");
        trains();
        printf("\n\n\t>>>ENTER TRAIN NUMBER:");
        scanf("%d",&p.train_num);
        if(p.train_num>=1001 && p.train_num<=1010)
        {
            charges=charge(p.train_num,p.seats);
            ticket(p.name,p.seats,p.train_num,p.date,charges);
            s=0;
        }
        else
        {
            printf("\nInvalid train Number! Enter again--> ");
        }
    }
    int b=1;
    while(b)
    {
        printf("\n\n\tConfirm Ticket (yes/no):>");
        scanf("%s",confirm);
        if(strcmp(confirm,"yes")==0)
        {
            fprintf(f,"\n%s\t%d\t%d\t%s\t%f",p.name,p.seats,p.train_num,p.date,charges);
            b=0;
            printf("\n\t==================");
            printf("\n \tReservation Done\n");
            printf("\t==================");
            printf("\n\tPress any key to go back to Main menu...");
        }
        else
        {
            if(strcmp(confirm,"no")==0)
            {
                b=0;
                printf("\nReservation Not Done!\nPress any key to go back to  Main menu!");
            }
            else
            {
			printf("\nInvalid choice entered! Enter again-----> ");
            }
        }
    }
	fclose(f);
	getch();
}


float charge(int train_num,int seats)
{
		if (train_num==1001)
	{
		return(5000.0*seats);
	}
	if (train_num==1002)
	{
		return(5000.0*seats);
	}
	if (train_num==1003)
	{
		return(4500.0*seats);
	}
	if (train_num==1004)
	{
		return(4500.0*seats);
	}
	if (train_num==1005)
	{
		return(4000.0*seats);
	}
	if (train_num==1006)
	{
		return(4000.0*seats);
	}
	if (train_num==1007)
	{
		return(3500.0*seats);
	}
	if (train_num==1008)
	{
		return(3500.0*seats);
	}
	if (train_num==1009)
	{
		return(6000.0*seats);
	}
	if (train_num==1010)
	{
		return(6000.0*seats);
	}
}

void ticket(char *name,int seats,int train_num,char *date,float charges)
{
	system("cls");
	printf("\t-------------------\n");
	printf("\t\tTICKET\n");
	printf("\t-------------------\n\n");
	printf("\tName:\t\t\t%s",name);
	printf("\n\tNumber Of Seats:\t%d",seats);
	printf("\n\tTrain Number:\t\t%d",train_num);
    printf("\n\tDate of Journey:\t%s",date);
	specifictrain(train_num);
	printf("\n\tCharges:\t\t%.2f",charges);
}

void specifictrain(int train_num)
{

	if (train_num==1001)
	{
		printf("\n\tTrain:\t\t\tAgra Express");
		printf("\n\tDestination:\t\tAgra To New Delhi");
		printf("\n\tDeparture:\t\t9am ");
	}
	if (train_num==1002)
	{
		printf("\n\tTrain:\t\t\tAgra Express");
		printf("\n\tDestination:\t\tNew Delhi To Agra");
		printf("\n\tDeparture:\t\t12pm");
	}
	if (train_num==1003)
	{
		printf("\n\tTrain:\t\t\tDeccan Express");
		printf("\n\tDestination:\t\tMumbai To Pune");
		printf("\n\tDeparture:\t\t8am");
	}
	if (train_num==1004)
	{
		printf("\n\tTrain:\t\t\tDeccan Express");
		printf("\n\tDestination:\t\tPune To Mumbai");
		printf("\n\tDeparture:\t\t11am ");
	}
	if (train_num==1005)
	{
		printf("\n\tTrain:\t\t\tBrindavan Express");
		printf("\n\tDestination:\t\tBangalore To Chennai");
		printf("\n\tDeparture:\t\t7am");
	}
	if (train_num==1006)
	{
		printf("\n\tTrain:\t\t\tBrindavan Express");
		printf("\n\tDestination:\t\tChennai To Bangalore");
		printf("\n\tDeparture:\t\t9.30am ");
	}
	if (train_num==1007)
	{
		printf("\n\tTrain:\t\t\tGoa Express");
		printf("\n\tDestination:\t\tGoa To Mumbai");
		printf("\n\tDeparture:\t\t1pm ");
	}
	if (train_num==1008)
	{
		printf("\n\tTrain:\t\t\tGoa Express");
		printf("\n\tDestination:\t\tMumbai To Goa");
		printf("\n\tDeparture:\t\t4pm ");
	}
	if (train_num==1009)
	{
		printf("\n\tTrain:\t\t\tGujarat Express");
		printf("\n\tDestination:\t\tAhmedabad To Bangalore");
		printf("\n\tDeparture:\t\t3.35pm ");
	}
	if (train_num==1010)
	{
		printf("\n\tTrain:\t\t\tGujarat Express");
		printf("\n\tDestination:\t\t Bangalore To Ahmedabad");
		printf("\n\tDeparture:\t\t1.15pm ");
	}
}

void view(char *un)
{   system("cls");
    float charge;
    pass_details pd;
    int i=1;
    FILE *f;
    char filename[100];
    sprintf(filename,"%s.txt",un);
    f=fopen(filename,"r+");
    printf("\n\t************ RESERVED TICKETS ************\n");
    while(fscanf(f,"\n%s\t%d\t%d\t%s\t%f",pd.name,&pd.seats,&pd.train_num,pd.date,&charge)!=EOF)
    {
        printf("\n<%d>\tName:\t\t\t%s",i,pd.name);
        printf("\n\tNumber Of Seats:\t%d",pd.seats);
        printf("\n\tTrain Number:\t\t%d",pd.train_num);
        printf("\n\tDate of Journey:\t%s",pd.date);
        specifictrain(pd.train_num);
        printf("\n\tCharges:\t\t%.2f\n\n",charge);
        i++;
    }
    fclose(f);
}

void loginpage(char *un)
{   system("cls");
    int a=1;
    while(a)
    {
        int c;
        printf("\t************************");
        printf("\n\t\tLOGIN PAGE");
        printf("\n\t************************");
        printf("\n\n\t1. Login");
        printf("\n\n\t2. Sign Up");
        printf("\n\n\t3. Exit");
        printf("\n\n\tEnter any option:");
        scanf("%d",&c);
        switch(c)
        {
            case 1:a=login(un);
                    break;
            case 2:signup();
                    break;
            case 3:exit(0);
                    break;
            default:printf("\n\tInvalid option!");
                    printf("\n\n\tPress any key to re-enter your option....");
                    getch();
                    system("cls");
        }
    }
}
