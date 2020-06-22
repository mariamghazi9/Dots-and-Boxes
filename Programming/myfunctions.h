
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
int numberOfGames=0;
int startTime,t1;
int minutes;
int seconds;
int pcLOAD=0;
//winner information
typedef struct
{
    int score;
    char name [100];
} winner;

winner topten[100];
//function returns 1 if there are still moves left and 0 otherwise
int endGame(int array[][50],int n)
{
    int x=0;
    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if(array[i][j]==' ')
                x=1;


        }
    }
    if(x==1)
        return 1;
    else

        return 0;



}
//copy name and score of the winner from the struct to the struct of type winner
winner construct(char *name,int score)
{
    winner p;
    strcpy(p.name,name);
    p.score=score;
    return p;
}
//reads the string until the space(name) then reads the score
winner decodeline(char *line)
{
    char *name=strtok(line," ");
    int score= atoi(strtok(NULL,"\n"));
    return construct(name,score);

}
void loadRanks()
{
    FILE *fn;
    char buff[200];
    char c;
    int j;



    fn=fopen("ranks.txt","r");
    if(!fn)
        printf("cannot open file");

    for(c=getc(fn); c!=EOF; c=getc(fn))
    {//new line indicates a new winner
        if (c=='\n')
            numberOfGames++;
    }
    //returns cursor to beginning of the file
    fseek(fn,0L,SEEK_SET);
    for(j=0; j<numberOfGames; j++)
    {
        if(!fgets(buff,sizeof(buff),fn))
            break;
        topten[j]=decodeline(buff);
    }
    fclose(fn);

}
typedef struct player
{
    char name[100];
    int score;
    int playerColour;
    int numberOfmoves;
} player;

player pc;

player playerOne;
player playerTwo;

winner temp;


//compare scores of 2 players
int compare(int score1,int score2)
{

    if(score1>score2)
    {
        fflush(stdin);


        return 0;
    }
    else if(score1==score2)
    {
        printf("Draw!\n");
        exit(0);
    }

    else
    {
        fflush(stdin);




        return 1;
    }

}

//save number of games in file
void saveNumber(int k)
{
    FILE *sum;
    sum=fopen("sum.txt","w");
    fprintf(sum,"%d",k);
    fclose(sum);
}
//load number of games from file
void loadNumber(int *k)
{
    FILE *sum;
    sum=fopen("sum.txt","r");
    fscanf(sum,"%d",k);
    fclose(sum);
}

//copy the winner from the file to an array of structs
void Ranks()
{
    loadNumber(&numberOfGames);
    FILE *ranks=fopen("ranks.txt","a+");
    fflush(stdin);
    numberOfGames++;
    if(compare(playerOne.score,playerTwo.score))
    {
        printf("Congratulations player two!\n");
        printf("Enter your name:");
        gets(playerTwo.name);
        memcpy(topten[numberOfGames-1].name,playerTwo.name,100);
        topten[numberOfGames-1].score=playerTwo.score;
    }
    else
    {
        printf("Congratulations player one!\n");
        printf("Enter your name:");
        gets(playerOne.name);
        memcpy(topten[numberOfGames-1].name,playerOne.name,100);
        topten[numberOfGames-1].score=playerOne.score;

    }
//numberOfGames++;
    saveNumber(numberOfGames);
    fclose(ranks);
}



//save current game
void save( int array[][50],int color[][50],int n, player playerOne, player playerTwo, int turn, int fileNum,int pcLOAD)
{

    FILE *ft;
    if(fileNum == 1)  //open file based on selected file to overwrite
    {
        ft=fopen("Save1.txt","w");
    }
    else if(fileNum == 2)
    {
        ft=fopen("Save2.txt","w");
    }
    else
    {
        ft=fopen("Save3.txt","w");
    }
    fprintf(ft,"%d ",pcLOAD);
    fprintf(ft,"%d ", turn);
    fprintf(ft,"%d ",playerOne.score);
    fprintf(ft,"%d ",playerTwo.score);
    fprintf(ft,"%d ",playerOne.playerColour);
    fprintf(ft,"%d ",playerTwo.playerColour);
    fprintf(ft,"%d ",playerOne.numberOfmoves);
    fprintf(ft,"%d ",playerTwo.numberOfmoves);
    fprintf(ft,"%d ",n); //saves size

    for(int i=0; i<n; i++) //2 nested for loops to save array
    {
        for(int j=0; j<n; j++)
        {
            fprintf(ft,"%d ",array[i][j]);

        }
    }
    for(int i=0; i<n; i++) //2 nested for loops to save colored array
    {
        for(int j=0; j<n; j++)
        {
            fprintf(ft,"%d ",color[i][j]);

        }
    }
    fclose(ft);
}

//load saved game
void load(int array[][50],int color[][50],int* pn, player* playerOne, player* playerTwo, int* turn, int fileNum,int *pcLOAD)
{

    FILE *ft;
    if(fileNum == 1)
    {
        ft=fopen("Save1.txt","r");
    }
    else if(fileNum == 2)
    {
        ft=fopen("Save2.txt","r");
    }
    else
    {
        ft=fopen("Save3.txt","r");
    }
    fscanf(ft,"%d ",pcLOAD);
    fscanf(ft,"%d", turn);
    fscanf(ft,"%d ",&((*playerOne).score));
    fscanf(ft,"%d ",&((*playerTwo).score));
    fscanf(ft,"%d ",&((*playerOne).playerColour));
    fscanf(ft,"%d ",&((*playerTwo).playerColour));
    fscanf(ft,"%d ",&((*playerOne).numberOfmoves));
    fscanf(ft,"%d ",&((*playerTwo).numberOfmoves));
    fscanf(ft,"%d",pn);
    int n = *pn;
    for(int i=0; i<n; i++) //loading saved array
    {
        for(int j=0; j<n; j++)
        {
            fscanf(ft,"%d",&array[i][j]);
        }
    }
     for(int i=0; i<n; i++) //load current colors
    {
        for(int j=0; j<n; j++)
        {
            fscanf(ft,"%d",&color[i][j]);
        }
    }
    fclose(ft);

}



//functions to print colored lines
void red()
{
    printf("\033[1;31m");
}

void yellow()
{
    printf("\033[1;33m");
}

void reset()
{
    printf("\033[0m");
}
//to undo a previous step in the game
void undo(int array[][50],int size,int row,int column)
{
    array[row][column]=' ';
}
//redo a step in the game
void redo(int array[][50],int size,int row,int column)
{
    if(row%2==0 && column%2==1)
        array[row][column]=196;
    else if(row%2==1 && column%2==0)
        array[row][column]='|';
}





//function that assigns dots and spaces to the grid
void assigngrid(int array[][50],int color[][50],int n)
{

    for(int i=0; i<n; i++)
    {
        for(int j=0; j<n; j++)
        {
            if((j%2)==0 && (i%2==0))
            {
                color[i][j]=248;
                array[i][j]=248;
            }
            else
            {
                color[i][j]=' ';
                array[i][j]=' ';
            }

        }

    }
}
//draw a line in a particular valid position
int assignLine(int array[][50],int color[][50],int size,int row,int column,int turn)
{
    //draw a horizontal line
    if(((row%2==0)&& (column%2==1)&& array[row][column]==' '))
        array[row][column]=196;
    //draw a vertical line
    else if (((row%2==1)&& (column%2==0)&& array[row][column]==' '))
        array[row][column]='|';
//updates the number of moves
    if(turn==0)
    {
        color[row][column]=0;
        playerOne.numberOfmoves++;
    }
    else
    {
        color[row][column]=1;
        playerTwo.numberOfmoves++;
    }
    return 0;


}
//prints the grid
void printArray(int array[][50],int color[][50],int n)
{
    //print index of columns
    for(int i=0; i<n; i++)
        printf("%6d",i);

    printf("\n\n\n");

    for(int i=0; i<n; i++)
    {
        printf("%2d",i);
        for(int j=0; j<n; j++)
        {
            if(color[i][j]==0)
            {
                red();
                printf("%6c",array[i][j]);
                reset();
            }
            else if(color[i][j]==1)
            {
                yellow();
                printf("%6c",array[i][j]);
                reset();
            }
            else
                printf("%6c",array[i][j]);
        }
        printf("\n\n");
    }


}
//function to check if a box is complete and updates the player's score
int checkBox (int array[][50],int color[][50],int n,int turn)
{
    int score=0;

    for (int i=1; i<n; i+=2)
    {
        for(int j=1; j<n; j+=2)
        {
            if(array[i][j-1]!=' ' && array[i-1][j]!=' ' && array[i][j+1]!=' ' && array[i+1][j]!=' ' &&array[i][j]==' ' )
            {
                score++;
                if(turn==0)
                {
                    array[i][j]='A';
                    color[i][j]=0;
                }
                else
                {
                    array[i][j]='B';
                    color[i][j]=1;
                }
            }
            // if the player undo his last move of completing a box. this function updates his score and the box becomes empty
            else if((array[i][j-1]==' ' || array[i-1][j]==' ' || array[i][j+1]==' ' || array[i+1][j]==' ' )&&array[i][j]!=' ' )
            {
                score--;
                array[i][j]=' ';
            }
        }
    }
    //if no box complete shift the turn
    if(score==0)
    {
        if(turn==0)
        {
            turn=1;
            return turn;
        }
        else
        {
            turn=0;
            return turn;
        }
    }

    else //if(score!=0)
    {
        if(turn==0)
        {
            playerOne.score+=score;

            return turn;
        }
        else
        {

            playerTwo.score+=score;
            pc.score+=score;
            return turn;
        }
    }
}



//checks the validity of the inputs
int checkScan(int max,int* choice, int arr[][50],int color[][50], int size, int zeroIncluded, int turn)
{
    int x;
    char garbage[1000];
    while(1)
    {
        scanf("%d",&x);
        if(x>=0 && x<=max && zeroIncluded)
        {
            *choice=x;
            return 0;
        }
        else if(x>0 && x<=max)
        {
            *choice=x;
            return 0;
        }
        else if(x == 91)//saving in first file
        {
            save(arr,color,size, playerOne, playerTwo, turn, 1,pcLOAD);
        }
        else if(x == 92)//saving in second file
        {
            save(arr,color,size, playerOne, playerTwo, turn, 2,pcLOAD);
        }
        else if(x == 93)//saving in third file
        {
            save(arr,color,size, playerOne, playerTwo, turn, 3,pcLOAD);
        }

        else
        {
            fgets(garbage,100,stdin);
            printf("Invalid\n");
            continue;
        }

    }
}
//swaps 2 structs
void swapstruct(winner topten[],int a,int b)
{
    temp=topten[a];
    topten[a]=topten[b];
    topten[b]=temp;
}


void sortstruct(winner topten[])
{
    for(int i=0; i<numberOfGames; i++)
    {
        for(int j=0; j<numberOfGames-1; j++)
            if(topten[j].score<topten[j+1].score)
                swapstruct(topten,j,j+1);

    }
}

void printTop(winner topten[])
{
    FILE *ranks=fopen("ranks.txt","w");
    for(int i=0; i<numberOfGames; i++)
    {
        fprintf(ranks,"%s %d\n",topten[i].name,topten[i].score);

    }
    fclose(ranks);

}

void pcMoves(int *row,int *column,int array[][50],int color[][50],int n,int turn)
{
    int x=1;
    int flag=0;
    while(turn==1)
    {

        if(x%2==1)
        {
            for (int i=1; i<n; i+=2)
            {
                for(int j=1; j<n; j+=2)
                {
                    if( array[i][j-1]!=' ' && array[i-1][j]!=' ' && array[i][j+1]!=' ' &&array[i][j]==' '  )
                    {
                        array[i+1][j]=196;
                        color[i+1][j]=1;
                        flag=1;
                        break;
                    }
                    else if(array[i-1][j]!=' ' && array[i][j+1]!=' ' && array[i+1][j]!=' ' &&array[i][j]==' ')
                    {
                        array[i][j-1]='|';
                        color[i][j-1]=1;
                        flag=1;
                        break;
                    }
                    else if(array[i][j-1]!=' '  && array[i][j+1]!=' ' && array[i+1][j]!=' ' &&array[i][j]==' ')
                    {
                        array[i-1][j]=196;
                        color[i-1][j]=1;
                        flag=1;
                        break;
                    }
                    else if(array[i][j-1]!=' ' && array[i-1][j]!=' '  && array[i+1][j]!=' ' &&array[i][j]==' ')
                    {
                        array[i][j+1]='|';
                        color[i][j+1]=1;
                        flag=1;
                        break;
                    }
                }
                x++;
                break;
            }
            if(flag==1)
                break;
        }
        else
        {
            x++;
            srand(time(0));
            *row=rand()%n;
            *column=rand()%n;
            if(((*row%2==0)&& (*column%2==1)&& array[*row][*column]==' '))
            {
                array[*row][*column]=196;
                color[*row][*column]=1;
                break;
            }

            else if (((*row%2==1)&& (*column%2==0)&& array[*row][*column]==' '))
            {
                array[*row][*column]='|';
                color[*row][*column]=1;
                break;
            }
        }
    }

}
