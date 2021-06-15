/*  ***************************************************project USER GUIDE  **************************************************************************** */
                  
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>


typedef struct Data{
	char user_name[20],pwd[20];
}Data;

Data d;//our user data

int isFileExists();

void Read_password();

void display_reminders();

void Write_Transactions(char mon[4]);

void Read_Transactions();

void Read_Reminders(char mon[3]);

void set_Reminder(char mon[3]);

void credit_debit_month(int n);

void writepwd();

void searchpwd();

void choices();

void view();

void writework();

int write_Check_Password(int n);

void signin();

void signup();

int check_date(int m,int y);

void deleteline(char mon[3]);

int main(){
	system("COLOR 31");
	int user;
	printf("\n\n******************************************************************************\n");
	printf("\t\t\t     WELCOME TO USER GUIDE\n");
	printf("*******************************************************************************\n");
	printf("******************************************************************************\n");
	printf("\t\t\t\tENTER:\n\t\t\t1.If you are a guest\n\t\t\t2.To create an account.\n\t\t\t3.To Login.\n");
	printf("*******************************************************************************\n                           ");
	scanf("%d",&user);
	switch(user){
		case 1: printf("\nGive the username of the person to view his text:");
			scanf("%s",d.user_name);
			view();
			break;
		case 2: signup();
			break;
		case 3: signin();
			break; 
		default:printf("\nSorry! We don't have any service of that kind.\n");
	}
	return 0;
}

//CHECKING FOR ITS USER NAME AS FILE IF ITS EXISTING RETURN 1\

int isFileExists(){
	FILE *fp;

//READING IS NULL WHEN THE FILE HAS NO CONTENTS I.E; NOT CREATED FP IS NULL;

	if((fp=fopen(d.user_name,"r"))==NULL)
		return 0;

//ELSE NEED TO CLOSE THE EXISTING FILE AND RETURN TRUE 

	fclose(fp);
	return 1;
}

//TO STORE USER'S MONTHLY TRANSACTIONS

void Write_Transactions(char mon[4]){
	FILE *fp;
	char c,file[100];
//MAKING THE FILE NAME AS USERNAME MON
	strcpy(file,d.user_name);
	strcat(file,mon);
	fp=fopen(file,"a");
	printf("\n Give data in the form of your PURPOSE : AMOUNT  only.\n   And press CTRL^Z to stop giving data\n");
	while((c=getchar())!=EOF){
		putc(c,fp);
	}
	system("cls");
	fclose(fp);
}

//TO STORE PASSWORDS OF THE USER

void writepwd(){
	FILE *fp;
	int i;
	char c,file[100];
//MAKING THE FILE NAME AS USERNAMEPWD.CSV
	strcpy(file,d.user_name);
	strcat(file,"pwd.csv");
	system("cls");
	printf("For security reasons you need to verify yourself again.\n");
	Read_password();
	if(write_Check_Password(0)){
		fp=fopen(file,"a");
		printf("\n Give data in the form of website : password only.\n Press CTRKL^Z to stop giving your data\n");
		while((c=getchar())!=EOF){
			if(c==':') putc(',',fp);
			else putc(c,fp);
		}
		fclose(fp);
		printf("\nThank you for storing your passwords.\n");
	}
//IF WRONG PASSWORDS ENTERED
	else printf("\nWrong password.");
}

//SEARCHING FOR A PASSWORD TO WEBSITE ASKED BY THE USER IN THE FILE HE STORED IT
void searchpwd(){	
	FILE *fp;
	int i,cnt=0;
	char check[500],c,key[100],file[100];
	strcpy(file,d.user_name);
	strcat(file,"pwd.csv");
	printf("For security reasons you need to verify yourself again.\n");
	Read_password();
//IF FILE IS SET BUT NOT GIVEN DATA TO IT
	if(write_Check_Password(0)){
		if((fp=fopen(file,"r"))==NULL){
			printf("\nFirst give some data to the file to search\n");
			return;
		}
		printf("\n Give name of the web to search for its password:");
		scanf("%s",key);
		while((c=getc(fp))!=EOF){
			if(c==',' && (strcmp(check,key))==0){
				printf("\n%s:",key);
				cnt=1;
				while((c=getc(fp))!='\n')
					putchar(c);
				break;
			}
			else strncat(check,&c,1);
			if(c=='\n') strcpy(check,"");
		}
//IF USER ASKS FOR SOMETHING HE NOT STORED
		if(cnt==0) printf("\n Can't find relevent web in your file.\n");
		fclose(fp);
	}
	else printf("\nWrong password.");
}

int check_date(int m,int y){
if(m >=1 && m<=12 && y>0) return 1;
else return 0;
}





//CHOICES TO THE USER 
void choices(){
	int choice,mon,y;
	char year[4];
	display_reminders();
	char m[3],date[4];
	do{
		
		printf("\n ENTER \n 1.To write to your file.\n 2.To store passwords.\n 3.To search for a password.\n 4.To store your transactions.\n 5.To get your transactions\n 6.To read remainder.\n 7.To set your remainders. \n 8.to delete any remainder. \n 9.To quit.\n");
		scanf("%d",&choice);
		switch(choice){
			case 1: //TO WRITE IN THE FILE
				writework();
				//SHOWING HIM HIS FILE CONTENTS
				printf("Your file contains");
				view();
				break;
			case 2: writepwd();
				break;
			case 3: searchpwd();
				break;
			case 4:	printf("Enter mon-year in the form ofmm/yy to store your expenditure in that month:");
				scanf("%d/%d",&mon,&y);
				if(check_date(mon,y)){
					sprintf(date,"%02d-%02d",mon,y);
					Write_Transactions(date);
				}
				else printf("\nGiven month or year not found in calender.");
				break;
			case 5: Read_Transactions();
				break;
			case 6: printf("\n Give the  month of your events you want to view in the form of \"xx\" \n");
				scanf("%s",m);
				Read_Reminders(m);
				break;
			case 7: printf("\n Give the  month of your event in the form of \"xx\" \n");
				scanf("%s",m);
				set_Reminder(m);
				break;
			
			case 8:printf("\n Give the  month of your events you want to delete in the form of \"xx\" \n");
				scanf("%s",m);
				deleteline(m);
				break;
			case 9: printf("\n Exiting....\n");
				break;
			default:printf("\nChoose correctly");
		}
	}while(choice!=9);
}


//IF FILE EXISTS READING FROM IT TO PRINT

void view(){
	system("cls");
//AGAIN CHECKING FOR FILE EXISTS BECAUSE GUEST HAS NO LOGIN AND CANNOT CHECK FOR THE FILE GIVEN BY HIM IN LOGIN
	system("COLOR F0");
	if(!isFileExists()){
		printf("\nOpps! Person with user name \"%s\" is not found in our data .Try again.\n",d.user_name);
		return;
	}
	FILE *fp;
	int cnt=0;
	fp=fopen(d.user_name,"r");
	char c,p[100];
//READING PASSWORD BECAUSE WE CAN'T PRINT IT FROM THE FILE

	fscanf(fp,"%s",p);

//TO READ THE '\N' FROM THE FILE TO READ THE CONTENTS FROM IT

	fgetc(fp);
	while((c=getc(fp))!=EOF){
		cnt=1;
		printf("%c",c);
	}
	fclose(fp);
//IF THE USER HAS CREATED AN ACCOUNT THEN HIS PASSWORD WILL BE IN THE FILE BUT IF WE DIDN'T YET CHOOSE WRITE SOMETHING THEN THIS IS PRINTED
	if(cnt==0)  printf("\nWaiting for %s to give the data.\n",d.user_name);
	//system("cls");
}


//TO WRITE IN FILE
void writework(){
	FILE *fp;
	fp=fopen(d.user_name,"a");
	char c;
	printf("\n Start writing the file. Once you finish give CTRL^Z.\n");
	while((c=getchar())!=EOF){
		fputc(c,fp);
	}
	fclose(fp);
	system("cls");
}

//WRITING PASSWORD TO FILE AND CHECKING IF THE PASSWORD IS CORRECT OR NOT
int write_Check_Password(int n){
//WRITING TO FILE
	if(n==1){
		FILE *fp;
		fp=fopen(d.user_name,"w");
		fprintf(fp,"password:%s\n",d.pwd);
		fclose(fp);
		return 1;
	}
//CHECKING IF PASSWORD IS CORRECT OR NOT
	else{
		FILE *fp;
		fp=fopen(d.user_name,"r");
		char fpwd[100];
		fscanf(fp,"password : %s",fpwd);
		fclose(fp);
		if((strcmp(d.pwd,fpwd))==0)  return 1;
		else return 0;
	}
}


	
//NEW USER LOGIN TO CREATE AN ACCOUNT
void signin(){
	int i;
	char c;
	system("cls");
	system("COLOR E5");
	printf("\nEnter your username:");
	scanf("%s",d.user_name);
	if(!isFileExists()){
		printf("\nOpps! you're a new user.Try to create an account.");
		return;
	}
	Read_password();
	int check=write_Check_Password(0);
	if(!check){
		printf("\n Try again wrong password.");
		return;
	}
	choices();
}
		
//TO CREATE A NEW ACCOUNT  
        
void signup(){
	int i;
	char c;
	system("cls");
	system("COLOR F6");
	printf("\nHeartly, Welcome new user.\n");
	printf("\nEnter username:");
	scanf("%s",d.user_name);
//UNTIL USER GIVES HIS USERNAME AS A  NON EXISTING ONE WE TAKE INPUT
	while(1){
		if(isFileExists()){
			printf("\nOpps! One of our users already has this username. \n Please give another name to your account:\n");
			scanf("%s",d.user_name);
		}
		else
			break;
	}
	Read_password();
	write_Check_Password(1);
	choices();
}
//READING PASSWORD

void Read_password(){
	int i;
	char c;
	printf("\nEnter a password:");
	for(i=0;;i++){
		c=getch();
		if(c==' ' || c=='\r'){
			d.pwd[i]='\0';
			break;
		}
		d.pwd[i]=c;
		printf("* ");
	}
}

void credit_debit_month(int n){
	FILE *fp;
	long long int amt,credit=0,debit=0;
	int i,mon,y;
	char str[1000],date[4],file[1000];
	printf("Enter mon-year in the form ofmm/yy:");
	scanf("%d/%d",&mon,&y);
//checking if correct date is entered or not
	if(check_date(mon,y)){
		sprintf(date,"%02d-%02d",mon,y);
		strcpy(file,d.user_name);
		strcat(file,date);
		fp=fopen(file,"r");
		if(fp==NULL) printf("\n Store something to print it.\n");
		while((fgets(str,1000,fp))!=NULL){
			if((strcmp(str,"\n"))==0) continue;
			for(i=1;str[i-1]!=':';i++){}
			amt=atoi(str+i);
			if(amt>0) credit+=amt;
			else debit+=amt;
		}
		if(n==1) printf("\n As per our records the total money you received in this month in %d/%d is  %ld.",mon,y,credit);
		else if(n==2) printf("\n As per our records  the total money you spent in %d/%d is  %ld.",mon,y,(debit));
		else if(n==3){
			printf("\n As per our records your savings in %d/%d is %ld.",mon,y,(credit+debit));
			if((credit+debit)>0) printf("\n Great! you have been in profit in this month.");
			else if((credit+debit)<0) printf("\n Sorry you have  spent much in this month.");
			else printf("\n Cool! your in no loss as your savings are 0");
		}
		else printf("\n We don't have service of this kind.");
		fclose(fp);
	}
	else printf("\n Given %d/%d not found in calendar.",mon,y);
}


//PRINTING OUR USER'S MONTHLY TRANSACTIONS
void Read_Transactions(){
	system("COLOR F0");	
	int n;
	printf("\n Enter \n 1. To get the money you received in the  month.\n 2. To get the total amount you used in the month. \n 3.To get your expenditures in a month.\n               ");
	scanf("%d",&n);
	credit_debit_month(n);

}
void Read_Reminders(char mon[3]){
	FILE *fp;
	char c,file[100];
	strcpy(file,d.user_name);
	strcat(file,mon);
	fp=fopen(file,"r");
	if(fp==NULL) printf("\n There is no reminder for this month.\n");
	while((c=getc(fp))!=EOF){
		if(c==',') printf(":");
		else printf("%c",c);
	}
	fclose(fp);
	printf("\nThank you.");
}
//displaying reminders based on current date at the start
void display_reminders(){
	system("COLOR C0");
	char mon[3];
	int m;
	time_t now;
	time(&now);
	struct tm *local=localtime(&now);
	m=local->tm_mon+1;
	itoa(m,mon,10);
	
	FILE *fp;
	char c,file[100];
	strcpy(file,d.user_name);
	strcat(file,mon);
	fp=fopen(file,"r");
	if(fp==NULL) 
		printf("\n There are no events in this month.\n");
	else{	
		printf("\nThese are your events in this month\n"); 
		while((c=getc(fp))!=EOF){
			if(c==',') printf(":");
			else printf("%c",c);
		}
	}
		fclose(fp);
}


void set_Reminder(char mon[3]){
	FILE *fp;
	char c,file[100];
//MAKING THE FILE NAME AS USERNAMEMON
	strcpy(file,d.user_name);
	strcat(file,mon);
	fp=fopen(file,"a");
	printf("\n Give data in the form of your date:event only.And press CTRKL^Z to stop giving data\n");
	while((c=getchar())!=EOF){
		if(c==':') putc(',',fp);
		else putc(c,fp);
	}
	system("cls");
	fclose(fp);
}
void deleteline(char mon[3]){
    FILE *fp, *fileptr2;
    char ch;
    int delete_line, temp = 1;
    char c,file[100];
    strcpy(file,d.user_name);
    strcat(file,mon);
    fp=fopen(file,"r");
    if(fp==NULL) printf("\n There is no reminder for this month.\n");
    while((c=getc(fp))!=EOF){
	    if(c==',') printf(":");
	    else printf("%c",c);
    }
//rewind
    rewind(fp);
    printf(" \n Enter line number of the remainder to be deleted:");
    scanf("%d", &delete_line);
    //open new file in write mode
    fileptr2 = fopen("replica.c", "w");
    ch = getc(fp);
    while (ch != EOF)
    {
        ch = getc(fp);
        if (ch == '\n')
            temp++;
            //except the line to be deleted
            if (temp != delete_line)
            {
                //copy all lines in file replica.c
                putc(ch, fileptr2);
            }
    }
    fclose(fp);
    fclose(fileptr2);
    remove(file);
    //rename the file replica.c to original name
    rename("replica.c", file);
    printf("\n The remainders of the month after being modified are as follows:\n");
    fp = fopen(file, "r");
    ch = getc(fp);
    while (ch != EOF)
    {
        printf("%c", ch);
        ch = getc(fp);
    }
    fclose(fp);
}
