#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>
#include<stdlib.h>
#define MAX_SIZE_USER_NAME 30
#define MAX_SIZE_PASSWORD  20
#define FILE_NAME  "mostafa.bin"
#define MAX_BOOK_NAME   50
#define FILE_HEADER_SIZE  sizeof(sFileHeader)


void mainmenu(); // to display the main menu
void add_books(); // to display the add books screen
void delete_books();// to display the delete function
void edit_books(); // to display the edit function
void search_books(); // to display the search function
void view_books();// too display the view books function
int wrong=1, count;//global variable for login function of int type
int i=0, valid=0;
char choice=0 ;
char answer;
int target=0,found=0;
struct books// to call in program
{
	int books_id,book_quantity; // declare the integer data type
	char b_name[20];// declare the character data type
}m;
int main() // declare main function
{
mainmenu();
return 0;
}
// mainmenu function
void mainmenu(void)
	{
		int choice;
		system("cls");
		printf("MAIN MENU");
		printf("\n1. Add Books");
		printf("\n2. Search Books by it's name");
		printf("\n3. View Books details");
		printf("\n4. Delete Books by it's id");
		printf("\n5. Close Application");
		printf("\n\nPlease Enter a choice[1-6]:");
		scanf("%i",&choice);
		switch(choice)
			{
				case 1:
				add_books();
				break;
				case 2:
			    search_books();
				break;
				case 3:
				view_books();
				break;
				case 4:
				delete_books();
				case 5:
				exit(0);
				break;
				default:
                printf("Wrong Entry!!");
                exit(0);
			}
}

// add books function
void add_books()
{
	system("cls");
	FILE *sfile;
	sfile = fopen("BookRecord.txt","a");
	printf("ENTER YOUR DETAILS BELOW:");
	printf("\nBook ID NO.:");
	fflush(stdin);
	scanf("%i",&m.books_id);
	do
	{
		printf("\nBook Name:");
		fflush(stdin);
		gets(m.b_name);
		m.b_name[0]=toupper(m.b_name[0]);
		for (i=0;i<strlen(m.b_name); ++i)
		{
            if(isalpha(m.b_name[i]))
			{
				valid = 1;
			}
			else
			{
				valid = 0;
				break;
			}
		}
		if (!valid)
		{
			printf("\nName contain invalid character. Please enter again.");
		}
	}
	while(!valid);
    printf("\nenter the book quantity :");
    fflush(stdin);
    scanf("%i",&m.book_quantity);
	fprintf(sfile,"%i %s %i\n\n",m.books_id, m.b_name ,m.book_quantity);
	fclose(sfile);
	printf("\nSUCCESFULLY RECORDED.\n");
	getch();
	printf("\n Do you want to add another book?[Y/N]:");
	scanf("%s",&answer);
	while(toupper(answer)!='Y'&& toupper(answer)!='N')
	{
		printf("Invalid!\nDo you want to add book?[Y/N]:");
		scanf("%s",&answer);
	}
	if(toupper(answer)=='Y')
	{
		add_books();
	}
	else
	{
		printf("\nPress any key to go to mainmenu.....");
		mainmenu();
	}
}
// search books function
void search_books()
{
	int found=0;
	char id[40];
	FILE *sfile;
	system("cls");
	sfile=fopen("BookRecord.txt","rb");
	printf("\n\t\t******************************************************");
	printf("\n\t\t***************** SEARCH BOOKS LIST*******************");
	printf("\n\t\t******************************************************\n\n");
	printf("\nEnter Book Name to search:");
	fflush(stdin);
	scanf("%s",id);
	id[0]=toupper(id[0]);
	printf("                                                                                     \n");
	printf(" Book ID NO. Book Name    Publication    Student Name   Student Address   Due Days");
	printf("\n=====================================================================================\n");
	while(fscanf(sfile,"%i %s %i\n\n",&m.books_id, m.b_name,&m.book_quantity)!=EOF)
	{
		if(strcmp(id,m.b_name)==0)
		{
			found=1;
			printf("%i",m.books_id);
			printf("%s",m.b_name);
			break;
		}
	}
		if(!found) printf("\n\n\tNo Record");
		fclose(sfile);
		printf("\n\n\nPress any key to go to mainmenu.....");
		getch();
		mainmenu();

}

// view books function
void view_books()
{
     int found = 0;
    int countBook = 1;
	FILE*sfile;
	system("cls");
	sfile=fopen("BookRecord.txt","r");
	if(sfile==NULL)
	{
		printf("\n\n RECORD EMPTY");
		getch();
	}
	else
	{
		printf("Book Id NO.");
		printf("\t\t\tBook Name");
		printf("\t\t\tbook quantity\n");
		found = 1;
        ++countBook;
		while(fscanf(sfile,"%i %s %i\n\n",&m.books_id,m.b_name,&m.book_quantity)!=EOF)
		{
			printf("\n%i",m.books_id);
			printf("\t\t\t\t%s",m.b_name);
			printf("\t\t\t\t%i",m.book_quantity);
			break;
		}
	}
	printf("\n\n\Press any key for main menu........");
	fclose(sfile);
	getch();
	mainmenu();
}
// delete function
// delete function
void deleteBooks()
{
    system("cls");
    int found = 0 , max = 50 ;
    int bookDelete = 0;
    m books = {0};
    char bookName[50] = {0};
    m add_books = {0};
    FILE *fp = NULL;
    FILE *tmpFp = NULL;
    int status = 0;
    fp = fopen(FILE_NAME,"rb");
    if(fp == NULL)
    {
        printf("File is not opened\n");
        exit(1);
    }
    tmpFp = fopen("tmp.bin","wb");
    if(tmpFp == NULL)
    {
        fclose(fp);
        printf("File is not opened\n");
        exit(1);
    }
    fread (&fileHeaderInfo,FILE_HEADER_SIZE, 1, fp);
    fwrite(&fileHeaderInfo,FILE_HEADER_SIZE, 1, tmpFp);
    printf("Enter Book ID NO. for delete:");
    scanf("%d",&bookDelete);
    while (fread (&addBookInfoInDataBase, sizeof(addBookInfoInDataBase), 1, fp))
    {
        if(addBookInfoInDataBase.books_id != bookDelete)
        {
            fwrite(&addBookInfoInDataBase,sizeof(addBookInfoInDataBase), 1, tmpFp);
        }
        else
        {
            found = 1;
        }
    }
    system("cls");
    (found)? printf("\nRecord deleted successfully....."):printf("\nRecord not found");
    fclose(fp);
    fclose(tmpFp);
    remove(FILE_NAME);
    rename("tmp.bin",FILE_NAME);
}
