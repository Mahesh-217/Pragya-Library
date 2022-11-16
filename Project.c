#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Creating Structure and Declaring it globally
struct LibraryDB
{
    char BkName[100];
    char AuthorName[100];
    char Genre[100];
    char ISBN[10];
};

struct User
{
    char Name[30];
    int MbNo;
};

struct LibraryDB Data[100]; //creates array of structures having the specific details
struct User DataBase[100]; 

//Functions
void userData();
void adminData();

void Read(int);
void AddBooks(int, int);
void DelBooks(int);
int min(int, int, int);
int levenshtein(char*, char*);
void EditBks(int);
void SearchBks(int);
void ViewAll(int);


//Main Function
int main()
{
    int i,bookNumber=14,BksAdd=0,BksDel=1,totalBks = bookNumber;
    system("cls");
    printf("***********************************************************\n");
    printf("\t\t \033[1;31mWelcome to Pragya Library\n");
    printf("\033[0m");
    printf("***********************************************************\n");
    printf("\033[0m");
    int firstUi;
    printf("1.User\n2.Admin\n");
    scanf("%d",&firstUi);
    switch (firstUi)
    {
    case 1:
        userData();
        break;
    
    case 2:
        adminData();
        break;
    default:
        break;
    }
    Read(bookNumber);
    printf("Enter the number of books to be added: ");
    scanf("%d",&BksAdd);
    AddBooks(BksAdd,bookNumber);
    totalBks = bookNumber + BksAdd;
    ViewAll(totalBks);
    //DelBooks(totalBks);
    totalBks = totalBks - BksDel;
    EditBks(totalBks);
    SearchBks(totalBks);
    ViewAll(totalBks);
} 

//Customer Database
void userData()
{
    FILE *fptrUser;
    int count = 1;
    fptrUser = fopen("Customer.txt","r+");
    if(fptrUser == NULL)
    {
        printf("File Not Found");
    }
    else
    {
        for (int i = 0; i < count; i++)
        {
            printf("Enter your name: ");
            fflush(stdin);
            DataBase[i].Name[0] = (char)getchar();
            fgets(DataBase[i].Name+1,40,stdin);
            fputs(DataBase[i].Name, fptrUser);
            printf("Enter your mobile number: ");
            scanf("%d",&DataBase[i].MbNo);
            putw(DataBase[i].MbNo,fptrUser);
        }
    }
    printf("Welcome to Pragya Library %s",DataBase[0].Name);
}

//Admin
void adminData()
{
    char pass[30];
    char ch;
    int pos=0;
    char string[5][30]={"amrith","saisid","karthik","mahesh","keshav"};
    char user[5][30]={"Amrith Krishnan","Sai Sidharth","Karthik Sumod","Mahesh","Keshav"};
    int flag=0;
    int index=0;

    printf("Enter your password: ");

    while(1)
    {
        ch=getch();                                 //taking characters
        if(ch==13)                                  //13 - enter key
        {
            break;
        }
        else if(ch==8)                              //8 - backspace key
        {
            if(pos>0)                               //characters need to be present
            {
                pos--;                              //reduce position
                pass[pos]= '\0';                    //make existing char null
                printf("\b \b");                    // \b - backspace character
            }
        }
        else
        {
            pass[pos]=ch;                           //put input char in array
            pos++;                                  //move to next position
            printf("*");
        }
    }
    pass[pos]='\0';                                 //terminate the character array
    printf("\n");

    for(int k=0;k<5;k++)
    {
        if(strcmp(string[k],pass)==0)
        {
            flag=1;
            index=k;
            break;
        }
    }
    if(flag==1)
    {
        printf("\n");
        switch(index)
        {
            case 0:
            {
                printf("\t\t\033[1;31mAdmin access granted to %s\n\n",user[index]);
                printf("\033[0m");
                printf("Welcome back to Pragya Library \033[1;33m %s\n",user[index]); //yellow
                printf("\033[0m");
                break;
            }
            case 1:
            {
                printf("\t\t\033[1;31mAdmin access granted to %s\n\n",user[index]);
                printf("\033[0m");
                printf("Welcome back to Pragya Library \033[1;31m %s\n",user[index]); //red
                printf("\033[0m");
                break;
            }
            case 2:
            {
                printf("\t\t\033[1;31mAdmin access granted to %s\n\n",user[index]);
                printf("\033[0m");
                printf("Welcome back to Pragya Library \033[1;32m %s\n",user[index]); //green
                printf("\033[0m");
                break;
            }
            case 3:
            {
                printf("\t\t\033[1;31mAdmin access granted to %s\n\n",user[index]);
                printf("\033[0m");
                printf("Welcome back to Pragya Library \033[1;36m %s\n",user[index]); //blue
                printf("\033[0m");
                break;
            }
            case 4:
            {
                printf("\t\t\033[1;31mAdmin access granted to %s\n\n",user[index]);
                printf("\033[0m");
                printf("Welcome back to Pragya Library \033[1;35m %s\n",user[index]); //purple
                printf("\033[0m");
                break;
            }
        }
        
    }
    else
    {
        printf("\033[1;31m Wrong password");
    }
    printf("\033[0m");
}

//Function Defining
void Read(int bookNumber)
{
    FILE *fptr;
    int i;
    fptr = fopen("Books.txt","r");
    if (fptr == NULL)
    {
        printf("File Not Found");
    }
    else
    {
        for(i=0;i<bookNumber;i++)
        {
            fgets(Data[i].BkName, 100, fptr);
            fgets(Data[i].AuthorName, 100, fptr);
            fgets(Data[i].Genre, 100, fptr);
            fgets(Data[i].ISBN, 10, fptr);
        }
        printf("\n***********************************************************\n");
        printf("\t\033[1;36mBooks have been added to Database Successfully\n");
        printf("\033[0m");
        printf("***********************************************************\n\n");
    }
}

void AddBooks(int BksAdd, int bookNumber) 
{
    FILE *fptr;
    fptr = fopen("Books.txt","a+");
    int i;
    for(i=bookNumber;i<bookNumber+BksAdd;i++)
    {
        printf("You will be entering details for Book %d\n", i+1);
        printf("Enter Book Name at %d: ",i+1);
        fflush(stdin);
        Data[i].BkName[0] = (char)getchar();
        fgets(Data[i].BkName+1, 100, stdin);
        fputs(Data[i].BkName,fptr);
        printf("Enter Author Name of %s",Data[i].BkName);
        fgets(Data[i].AuthorName, 100, stdin);
        fputs(Data[i].AuthorName,fptr);
        printf("Enter Genre of %s",Data[i].BkName);
        fgets(Data[i].Genre, 100, stdin);
        fputs(Data[i].Genre,fptr);
        printf("Enter ISBN of %s",Data[i].BkName);
        fgets(Data[i].ISBN, 10, stdin);
        fputs(Data[i].ISBN,fptr);
        printf("\n");
        printf("Details have been successfully added for %s\n",Data[i].BkName);
    }
}

void DelBooks(int totalBks)
{
    printf("You will be deleting a book\n");
    int i;
    char BkDel[100];
    for (i=0;i<totalBks;i++)
    {
        printf("%d. %s\n",i+1,Data[i].BkName);
    }
    printf("Please enter the Book name to be deleted from the above list of available books\n");
    BkDel[0] = (char)getchar();
    fgets(BkDel+1,100,stdin);
    printf("Book to be Deleted: %s\n",BkDel); //add validation using do-while
    int cmp, DelIndex;
    for (i=0;i<totalBks;i++)
    {
        cmp = strcmp(BkDel, Data[i].BkName);
        if(cmp==0)
        {
            DelIndex = i;
            int temp;
            printf("Position to be Deleted: %d\n",DelIndex);
            for (i=DelIndex;i<totalBks-1;i++)
            {
                strcpy(Data[i].BkName,Data[i+1].BkName);
                strcpy(Data[i].AuthorName,Data[i+1].AuthorName);
                strcpy(Data[i].Genre,Data[i+1].Genre);
                strcpy(Data[i].ISBN,Data[i+1].ISBN);
                temp = atoi(Data[i].ISBN);
                temp = temp - 1;
                itoa(temp, Data[i].ISBN,10); 
            }
            totalBks--;
            printf("Book has been successfully deleted.\n");
            FILE *fptr;
            fptr = fopen("Books.txt","w+");
            if (fptr == NULL)
            {
                printf("File Not Found");
            }
            else
            {
                for(i=0;i<totalBks;i++)
                {
                    fputs(Data[i].BkName, fptr);
                    fputs(Data[i].AuthorName, fptr);
                    fputs(Data[i].Genre, fptr);
                    fputs(Data[i].ISBN, fptr);
                }
                printf("Books Added to Database Successfully\n");
            }
        }
        else if(i==totalBks-1)
        {
            printf("Sorry the Book Name you entered wasn't found. Please check the name");
        }
        
    }
}

int min(int a, int b, int c)
{
    if(a <= b && a <= c)
    {
        return a;
    }
    else if(b <= a && b <= c)
    {
        return b;
    }
    else if(c <= a && c <= b)
    {
        return c;
    }
}

int levenshtein(char *s1, char *s2) {

    unsigned int x, y, s1len, s2len;
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int matrix[s2len+1][s1len+1];
    matrix[0][0] = 0;
    for (x = 1; x <= s2len; x++)
        matrix[x][0] = matrix[x-1][0] + 1;
    for (y = 1; y <= s1len; y++)
        matrix[0][y] = matrix[0][y-1] + 1;
    for (x = 1; x <= s2len; x++)
        for (y = 1; y <= s1len; y++)
            matrix[x][y] = min(matrix[x-1][y] + 1, matrix[x][y-1] + 1, matrix[x-1][y-1] + (s1[y-1] == s2[x-1] ? 0 : 1));

    return(matrix[s2len][s1len]);

}

void EditBks(int totalBks) 
{
    FILE *fptr;
    fptr = fopen("Books.txt","r+");
    int i;
    char EditBk[100];
    char choice = 'Y';
    
    printf("Enter the book name whose details need to be modified\n");
    fflush(stdin);
    EditBk[0] = (char)getchar();
    fgets(EditBk+1,100,stdin);

    int cmp, EditIndex,catagory;

    for (i=0;i<totalBks;i++)
    {
        cmp = levenshtein(EditBk, Data[i].BkName);
        if(cmp<=2)
        {
            printf("\n%d\t%s",i,Data[i].BkName);
        }
    } 

    printf("\nChoose result from above:");
    scanf("%d",EditIndex);

    while (choice == 'Y')
    {
        printf("1.Book Name: %s\n2.Author Name: %s\n3.Genre: %s\n4.ISBN: %s\n",Data[EditIndex].BkName,Data[EditIndex].AuthorName,Data[EditIndex].Genre,Data[EditIndex].ISBN);
        printf("Enter the data to be changed: ");
        scanf("%d",&catagory);
        
        switch (catagory)
        {
            
            case 1:

                printf("Previous Data: %s\n",Data[EditIndex].BkName);
                printf("Enter new value: ");
                getchar();
                fgets(Data[EditIndex].BkName, 100, stdin);
                fputs(Data[EditIndex].BkName, fptr);
                printf("Book Name has been updated successfully\n");
                break;
                
            case 2:
                 
                printf("Previous Data: %s\n",Data[EditIndex].AuthorName);
                printf("Enter new value: ");
                getchar();
                fgets(Data[EditIndex].AuthorName, 100, stdin);
                fputs(Data[EditIndex].AuthorName, fptr);
                printf("Author Name has been updated successfully.\n");
                break;

            case 3:
                    
                printf("Previous Data: %s\n",Data[EditIndex].Genre);
                printf("Enter new value: ");
                getchar();
                fgets(Data[EditIndex].Genre, 100, stdin);
                fputs(Data[EditIndex].Genre, fptr);
                printf("Genre has been updated successfully.\n");
                break;

            case 4:
                
                printf("Previous Data: %s\n",Data[EditIndex].ISBN);
                printf("Enter new value: ");
                getchar();
                fgets(Data[EditIndex].ISBN, 10, stdin);
                fputs(Data[EditIndex].ISBN, fptr);
                printf("ISBN has been successfully updated.\n");
                break;

            default:

                printf("Criteria doesn't exist. Please re-check entry.");
                break;
                
        }

        printf("Would you to update another detail for %s[Y/N]\n",Data[EditIndex].BkName);
        scanf(" %c",&choice);
        printf("\n");
        
    }
}


void SearchBks(int totalBks)
{
    printf("You will be searching for a book\n");
    int cmp, srchIndex, catagory;
    char srchBk[100], choice = 'Y';
    while (choice == 'Y')
    {
        printf("Would you like to search by - \n1.Book Name\n2.Author Name\n3.Genre\n4.ISBN\n");
        printf("Enter the catagory to be search: ");
        scanf("%d",&catagory);
        switch (catagory)
        {
        case 1:
            printf("Enter the Book Name: ");
            getchar();
            fgets(srchBk,100,stdin);
            printf("Value entered: %s",srchBk);
            for (int i = 0;i < totalBks;i++)
            {
                cmp = strcmp(srchBk, Data[i].BkName);
                if (cmp == 0)
                {
                    srchIndex = i;
                    printf("\n");
                    printf("The requested book details have been found at Index %d\n",i+1);
                    printf("Book Details is as follows\n");
                    printf("Book Name: %s\nAuthor Name: %s\nGenre: %s\nISBN: %s\n\n",Data[i].BkName,Data[i].AuthorName,Data[i].Genre,Data[i].ISBN);
                }
            }
            break;
        
        case 2:
            printf("Enter the Author Name: ");
            getchar();
            fgets(srchBk,100,stdin);
            printf("Value entered: %s",srchBk);
            for (int i = 0;i < totalBks;i++)
            {
                cmp = strcmp(srchBk, Data[i].AuthorName);
                if (cmp == 0)
                {
                    srchIndex = i;
                    printf("\n");
                    printf("The requested book details have been found at Index %d\n",i+1);
                    printf("Book Details is as follows\n");
                    printf("Book Name: %s\nAuthor Name: %s\nGenre: %s\nISBN: %s\n\n",Data[i].BkName,Data[i].AuthorName,Data[i].Genre,Data[i].ISBN);
                }
            }
            break;

        case 3:
            printf("Enter the Genre: ");
            getchar();
            fgets(srchBk,100,stdin);
            printf("Value entered: %s",srchBk);
            for (int i = 0;i < totalBks;i++)
            {
                cmp = strcmp(srchBk, Data[i].Genre);
                if (cmp == 0)
                {
                    srchIndex = i;
                    printf("\n");
                    printf("The requested book details have been found at Index %d\n",i+1);
                    printf("Book Details is as follows\n");
                    printf("Book Name: %s\nAuthor Name: %s\nGenre: %s\nISBN: %s\n\n",Data[i].BkName,Data[i].AuthorName,Data[i].Genre,Data[i].ISBN);
                }
            }
            break;

        case 4:
            printf("Enter the ISBN: ");
            getchar();
            fgets(srchBk,100,stdin);
            printf("Value entered: %s",srchBk);
            for (int i = 0;i < totalBks;i++)
            {
                cmp = strcmp(srchBk, Data[i].ISBN);
                if (cmp == 0)
                {
                    srchIndex = i;
                    printf("\n");
                    printf("Book Details is as follows\n");
                    printf("Book Name: %s\nAuthor Name: %s\nGenre: %s\nISBN: %s\n\n",Data[i].BkName,Data[i].AuthorName,Data[i].Genre,Data[i].ISBN);
                }
            }
            break;

        default:
            printf("Criteria doesn't exist. Please re-check entry.");
            break;
        }
        printf("Would you to search for another data?[Y/N]\n");
        scanf(" %c",&choice);
        printf("\n");
    }
}

void ViewAll(int totalBks)
{
    int i;
    {
        for (i=0;i<totalBks;i++)
        {
            printf("\n");
            printf("**********************************\n");
            printf("\n");
            printf("Showing Details of Book %d\n",i+1);
            printf("\n");
            printf("Book Name: %s\n",Data[i].BkName);
            printf("Author Name: %s\n",Data[i].AuthorName);
            printf("Genre: %s\n",Data[i].Genre);
            printf("ISBN: %s\n",Data[i].ISBN);
            printf("Details have been successfully printed for %s\n",Data[i].BkName);
            printf("**********************************\n");
        }
        printf("Books have been successfully printed from the database.\n");
    }   
}