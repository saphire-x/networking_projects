#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//network byte order(big endian)
int main()
{
  int sfd = socket(AF_INET,SOCK_STREAM,0);
  printf("%d\n",sfd);
  //sin = socket internet

  struct sockaddr_in server;//passed to kernel (stores info abt server)
  server.sin_family = AF_INET;//tells ipv4 address
  server.sin_port = htons(8080);//little to big endian conversion
  server.sin_addr.s_addr = INADDR_ANY;

  //bind the server (to a ip,port)
  bind(sfd,(struct sockaddr*)&server,sizeof(server));
  listen(sfd,5);//max 5 connections

  int cfd;

  cfd = accept(sfd,NULL,NULL);
  char msg_server [] = "Hi client!\n";
  send(cfd,msg_server,sizeof(msg_server),0);


  close(cfd);
  close(sfd);






}