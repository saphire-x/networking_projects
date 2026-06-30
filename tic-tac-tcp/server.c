#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<stdbool.h>


#define MAX_CLIENT 5
#define PORT 8080
#define SIZE 3
char board[SIZE+1][SIZE+1];





void init_board()
{
  for(int i=1;i<=SIZE;i++)
  {
    for(int j=1;j<=SIZE;j++)
    {
      board[i][j] = ' ';
    }
  }

}

void print_board()
{
  for(int i=1;i<=SIZE;i++)
  {
    for(int j=1;j<=SIZE;j++)
    {
      printf("%c",board[i][j]);
    }
    printf("\n");
  }
}


//serialize the board send to client
void display_board(int cfd)
{
    char buffer[256] = "";

    for(int i=1;i<=SIZE;i++)
    {
        for(int j=1;j<=SIZE;j++)
        {
            sprintf(buffer + strlen(buffer), " %c ", board[i][j]);

            if(j < SIZE)
                strcat(buffer, "|");
        }

        strcat(buffer, "\n");

        if(i < SIZE)
            strcat(buffer, "---+---+---\n");
    }

    send(cfd, buffer, strlen(buffer), 0);
}

void make_move()
{


}

void receive_move()
{



}

bool is_win(char player)
{

}

int main()
{
  int sfd = socket(AF_INET,SOCK_STREAM,0);
  //SIN = socket internet

  struct sockaddr_in server;//passed to kernel (stores info abt server)
  server.sin_family = AF_INET;//tells ipv4 address
  server.sin_port = htons(PORT);//little to big endian conversion
  server.sin_addr.s_addr = INADDR_ANY;

  //bind the server (to a ip,port)
  bind(sfd,(struct sockaddr*)&server,sizeof(server));
  listen(sfd,MAX_CLIENT);//max 5 connections

  int cfd;

  cfd = accept(sfd,NULL,NULL);
  char msg_server [] = "Hi client!\n";
  send(cfd,msg_server,sizeof(msg_server),0);


  close(cfd);
  close(sfd);






}