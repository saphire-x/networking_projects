#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include<pthread.h>


char board[9]={'1','2','3','4','5','6','7','8','9'};

void printBoard()
{
    printf("\n");
    printf("%c | %c | %c\n",board[0],board[1],board[2]);
    printf("--+---+--\n");
    printf("%c | %c | %c\n",board[3],board[4],board[5]);
    printf("--+---+--\n");
    printf("%c | %c | %c\n",board[6],board[7],board[8]);
    printf("\n");
}

int isWin(char p)
{
    int w[8][3]={
        {0,1,2},
        {3,4,5},
        {6,7,8},
        {0,3,6},
        {1,4,7},
        {2,5,8},
        {0,4,8},
        {2,4,6}
    };

    for(int i=0;i<8;i++)
    {
        if(board[w[i][0]]==p &&
           board[w[i][1]]==p &&
           board[w[i][2]]==p)
            return 1;
    }

    return 0;
}


int main()
{
    printBoard();
}

int main2()
{
    int sfd = socket(AF_INET,SOCK_STREAM,0);

    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_port = htons(8080);
    server.sin_addr.s_addr = INADDR_ANY;

    bind(sfd,(struct sockaddr*)&server,sizeof(server));

    listen(sfd,1);

    printf("Waiting for client...\n");

    int cfd = accept(sfd,NULL,NULL);

    printf("Client connected\n");

    while(1)
    {
        int move;

        printBoard();

        printf("Your move (X): ");
        scanf("%d",&move);

        move--;

        if(board[move]=='X' || board[move]=='O')
            continue;

        board[move]='X';

        send(cfd,&move,sizeof(move),0);

        if(isWin('X'))
        {
            printBoard();
            printf("You win\n");
            break;
        }

        recv(cfd,&move,sizeof(move),0);

        board[move]='O';

        if(isWin('O'))
        {
            printBoard();
            printf("Client wins\n");
            break;
        }
    }

    close(cfd);
    close(sfd);

    return 0;
}