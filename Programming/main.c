#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "myfunctions.h"

int main()
{

    playerOne.score=0;
    playerTwo.score=0;
    int turn=0;
    int row=0,column=0;
    int size;
    int lines;
    int arr[50][50];
    int color[50][50];
    int choice;
    int flag=0;

    pc.numberOfmoves=0;
    pc.score=0;

    loadRanks();

    do
    {
        system("cls");
        printf("\033[1;32m\t\t\t\t\t         **********     \n");
            printf("\t\t\t\t\t     ***            ***\n");
            printf("\t\t\t\t\t  **                     **\n");
            printf("\t\t\t\t\t**      Dots & Boxes <3    **\n");
            printf("\t\t\t\t\t  **                     **\n");
            printf("\t\t\t\t\t     ***            ***\n");
            printf("\t\t\t\t\t         **********      \n");
            printf("\033[0m");
            printf("\033[1;34m");
            printf("\n\n");
            printf("\t\t\t\t\tWe Hope you Enjoy Our Game ^_* \n");
            printf("\n\t\t\t\t\t1-Two Players \n");
            printf("\t\t\t\t\t2-Player vs Computer \n");
            printf("\t\t\t\t\t3-Load a current game \n");
            printf("\t\t\t\t\t4-Top Ten \n");
            printf("\t\t\t\t\t5-Exit \n");
            printf("\033[0m");
        checkScan(5,&choice, arr,color, size,0,turn);
        system("cls");

        if(choice==1)
        {
            pcLOAD=0;
            printf("\033[1;34m");
            printf("\n\n\n\n");
            printf("\t\t\t\t\t1-beginner:\n\n\n \t\t\t\t\t2-expert:\n");
            printf("\033[0m");
            checkScan(2,&choice, arr,color, size,0,turn);
            system("cls");
            if(choice==1)
            {
                size=5;
                lines=12;
                flag=0;
            }
            else if(choice==2)
            {
                size=11;
                lines=60;
                flag=1;
            }
            assigngrid(arr,color,size);
            startTime=time(NULL);

        }
        else if(choice == 3)
        {
            FILE *ft=fopen("Save1.txt","r");

            pcLOAD=fscanf(ft,"%d",&pcLOAD);
            fclose(ft);
            system("cls");
            printf("Please choose games 1, 2 or 3: ");
            checkScan(3, &choice, arr,color, size, 0, turn);
            system("cls");
            load(arr,color, &size, &playerOne, &playerTwo, &turn, choice,&pcLOAD);
            pc=playerTwo;

        }


        else if(choice ==4)
        {
            int k=0;
            for(k=0; k<numberOfGames && k<10; k++)
                printf("%s %d\n",topten[k].name,topten[k].score);
            break;
        }
        else if(choice==5)
            exit(0);

        else if (choice==2)
        {
            pcLOAD=1;
            printf("\033[1;34m");
            printf("\n\n\n\n");
            printf("\t\t\t\t\t1-beginner:\n\n\n \t\t\t\t\t2-expert:\n");
            printf("\033[0m");
            checkScan(2,&choice,arr,color,size,0,turn);
            system("cls");
            if(choice==1)
            {
                size=5;
                lines=12;
                flag=0;
            }
            else if(choice==2)
            {
                size=11;
                lines=60;
                flag=1;
            }
            assigngrid(arr,color,size);
            startTime=time(NULL);

            while(endGame(arr,size))
            {
                time_t t1;
                t1=time(NULL);
                t1=t1-startTime;
                minutes=t1/60;
                seconds=(t1%60);
                printArray(arr,color,size);

                if(turn==0)
                {
                    red();
                    printf("\t\t Player one's turn\n");
                    printf("Player one's moves %d\t\t",playerOne.numberOfmoves);
                    yellow();
                    printf("Computer's moves %d\n",pc.numberOfmoves);
                    red();
                    printf("Score: %d\t\t\t",playerOne.score);
                    yellow();
                    printf("Score: %d\n",pc.score);

                    reset();
                    printf("time is %2d : %2d \n",minutes,seconds);
                    if((lines==12 && choice==1)||(lines==60&& choice==2))
                    {
                        int x=0;
                        do
                        {
                            if(x!=0)
                            {
                                printf("Invalid\n");
                                printf("enter a valid row and column\n");

                            }

                            if(flag==0)
                            {
                                checkScan(4,&row,arr,color,size,1,turn);
                                checkScan(4,&column,arr,color,size,1,turn);
                            }
                            else if(flag)
                            {
                                checkScan(10,&row,arr,color,size,1,turn);
                                checkScan(10,&column,arr,color,size,1,turn);
                            }


                            x++;
                        }
                        while(arr[row][column]!=' ' || ((row%2==1)&&(column%2==1)));
                        assignLine(arr,color,size,row,column,turn);

                    }
                    else
                    {

                        printf("1-Continue\n2-Undo\n3-Redo\nTo Save before exit enter 91\n4-Exit\n");
                        checkScan(4,&choice,arr,color,size,0,turn);
                        if(choice==1)
                        {
                            int x=0;
                            do
                            {
                                if(x!=0)
                                {
                                    printf("Invalid\n");
                                    printf("enter a valid row and column\n");

                                }
                                if(flag==0)
                                {
                                    checkScan(4,&row,arr,color,size,1,turn);
                                    checkScan(4,&column,arr,color,size,1,turn);
                                }
                                else if(flag==1)
                                {
                                    checkScan(10,&row,arr,color,size,1,turn);
                                    checkScan(10,&column,arr,color,size,1,turn);
                                }
                                x++;
                            }
                            while(arr[row][column]!=' ' || ((row%2==1)&&(column%2==1)));
                            assignLine(arr,color,size,row,column,turn);

                        }
                        else if(choice==2)
                        {
                            undo(arr,size,row,column);
                            lines+=2;
                        }
                        else if(choice==3)
                            redo(arr,size,row,column);
                        else if(choice==4)

                            exit(0);
                    }

                }
                else
                {
                    yellow();
                    printf("\t\tComputer's turn\n");
                    red();
                    printf("Player one's moves %d\t\t",playerOne.numberOfmoves);
                    yellow();
                    printf("Computer's moves %d\n",pc.numberOfmoves);
                    red();
                    printf("Score: %d\t\t\t",playerOne.score);
                    yellow();
                    printf("Score: %d\n",pc.score);
                    reset();
                    printf("time is %2d : %2d \n",minutes,seconds);

                    pcMoves(&row,&column,arr,color,size,turn);

                    pc.numberOfmoves++;
                    playerTwo.numberOfmoves++;

                }
                turn = checkBox(arr,color,size,turn);
                system("cls");


                lines--;
            }
            exit(0);
        }
        if(pcLOAD==0)
        {
            while(lines > 0)
            {
                time_t t1;
                t1=time(NULL);
                t1=t1-startTime;
                minutes=t1/60;
                seconds=(t1%60);
                printArray(arr,color,size);
                if(turn==0)
                {
                    red();
                    printf("\t\t Player one's turn\n");
                    printf("\t\tNumber of moves left: %d\n",lines);
                    printf("Player one's moves %d\t\t",playerOne.numberOfmoves);
                    yellow();
                    printf("Player two's moves %d\n",playerTwo.numberOfmoves);
                    red();
                    printf("Score: %d\t\t\t",playerOne.score);
                    yellow();
                    printf("Score: %d\n",playerTwo.score);
                    printf("time is %2d : %2d \n",minutes,seconds);

                }

                else
                {
                    yellow();
                    printf("\t\t Player two's turn\n");
                    printf("\t\tNumber of moves left: %d\n",lines);
                    red();
                    printf("Player one's moves %d\t\t",playerOne.numberOfmoves);
                    yellow();
                    printf("Player two's moves %d\n",playerTwo.numberOfmoves);
                    red();
                    printf("Score: %d\t\t\t",playerOne.score);
                    yellow();
                    printf("Score: %d\n",playerTwo.score);
                    printf("time is %2d : %2d \n",minutes,seconds);

                }
                reset();

                if((lines==12 && choice==1)||(lines==60&& choice==2))
                {
                    int x=0;
                    do
                    {
                        if(x!=0)
                        {
                            printf("Invalid\n");
                            printf("enter a valid row and column\n");

                        }

                        if(flag==0)
                        {
                            checkScan(4,&row,arr,color,size,1,turn);
                            checkScan(4,&column,arr,color,size,1,turn);
                        }
                        else if(flag)
                        {
                            checkScan(10,&row,arr,color,size,1,turn);
                            checkScan(10,&column,arr,color,size,1,turn);
                        }


                        x++;
                    }
                    while((arr[row][column]!=' ' || ((row%2==1)&&(column%2==1))) && turn==0);

                    assignLine(arr,color,size,row,column,turn);
                }
                else
                {

                    printf("1-Continue\n2-Undo\n3-Redo\nTo save before exit enter 91\n4-Exit\n");
                    checkScan(4,&choice,arr,color,size,0,turn);
                    if(choice==1)
                    {
                        int x=0;
                        do
                        {
                            if(x!=0)
                            {
                                printf("Invalid\n");
                                printf("enter a valid row and column\n");

                            }
                            if(flag==0)
                            {
                                checkScan(4,&row,arr,color,size,1,turn);
                                checkScan(4,&column,arr,color,size,1,turn);
                            }
                            else if(flag==1)
                            {
                                checkScan(10,&row,arr,color,size,1,turn);
                                checkScan(10,&column,arr,color,size,1,turn);
                            }


                            x++;
                        }
                        while(arr[row][column]!=' ' || ((row%2==1)&&(column%2==1)));
                        assignLine(arr,color,size,row,column,turn);

                    }
                    else if(choice==2)
                    {
                        undo(arr,size,row,column);
                        lines+=2;
                    }
                    else if(choice==3)
                        redo(arr,size,row,column);
                    else if(choice==4)

                        exit(0);
                }
                turn = checkBox(arr,color,size,turn);


                //printArray(arr,size);
                system("cls");


                lines--;

            }
        }



        else if(pcLOAD==1)
        {


            while(endGame(arr,size))
            {

                time_t t1;
                t1=time(NULL);
                t1=t1-startTime;
                minutes=t1/60;
                seconds=(t1%60);
                printArray(arr,color,size);

                if(turn==0)
                {
                    red();
                    printf("\t\t Player one's turn\n");
                    printf("Player one's moves %d\t\t",playerOne.numberOfmoves);
                    yellow();
                    printf("Computer's moves %d\n",pc.numberOfmoves);
                    red();
                    printf("Score: %d\t\t\t",playerOne.score);
                    yellow();
                    printf("Score: %d\n",pc.score);

                    reset();
if((lines==12 && choice==1)||(lines==60&& choice==2))
                {
                    int x=0;
                    do
                    {
                        if(x!=0)
                        {
                            printf("Invalid\n");
                            printf("enter a valid row and column\n");

                        }

                        if(flag==0)
                        {
                            checkScan(4,&row,arr,color,size,1,turn);
                            checkScan(4,&column,arr,color,size,1,turn);
                        }
                        else if(flag)
                        {
                            checkScan(10,&row,arr,color,size,1,turn);
                            checkScan(10,&column,arr,color,size,1,turn);
                        }


                        x++;
                    }
                    while(arr[row][column]!=' ' || ((row%2==1)&&(column%2==1)));

                    assignLine(arr,color,size,row,column,turn);
                }
                else
                {

                    printf("1-Continue\n2-Undo\n3-Redo\nTo save before exit enter 91\n4-Exit\n");
                    checkScan(4,&choice,arr,color,size,0,turn);
                    if(choice==1)
                    {
                        int x=0;
                        do
                        {
                            if(x!=0)
                            {
                                printf("Invalid\n");
                                printf("enter a valid row and column\n");

                            }
                            if(flag==0)
                            {
                                checkScan(4,&row,arr,color,size,1,turn);
                                checkScan(4,&column,arr,color,size,1,turn);
                            }
                            else if(flag==1)
                            {
                                checkScan(10,&row,arr,color,size,1,turn);
                                checkScan(10,&column,arr,color,size,1,turn);
                            }


                            x++;
                        }
                        while(arr[row][column]!=' ' || ((row%2==1)&&(column%2==1)));
                        assignLine(arr,color,size,row,column,turn);
                    }
                    else if(choice==2)
                    {
                        undo(arr,size,row,column);
                        lines+=2;
                    }
                    else if(choice==3)
                        redo(arr,size,row,column);
                    else if(choice==4)

                        exit(0);
                }

                }
                else
                {
                    yellow();
                    printf("\t\tComputer's turn\n");
                    red();
                    printf("Player one's moves %d\t\t",playerOne.numberOfmoves);
                    yellow();
                    printf("Computer's moves %d\n",pc.numberOfmoves);
                    red();
                    printf("Score: %d\t\t\t",playerOne.score);
                    yellow();
                    printf("Score: %d\n",pc.score);
                    reset();

                    pcMoves(&row,&column,arr,color,size,turn);
                    pc.numberOfmoves++;
                    playerTwo.numberOfmoves++;
                }
                turn = checkBox(arr,color,size,turn);
                system("cls");


                lines--;
            }
            exit(0);
        }
        if (pcLOAD==0)
        {
            loadRanks();
            Ranks();
            sortstruct(topten);
            printTop(topten);
        }
    }
    while(1);

    return 0;
}
