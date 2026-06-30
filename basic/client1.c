#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main()
{
  int myfd = socket(AF_INET,SOCK_STREAM,0);

  struct sockaddr_in server;

  server.sin_family = AF_INET;
  server.sin_port = htons(8080);

  inet_pton(AF_INET,"127.0.0.1",&server.sin_addr);//converts ip string to binary format

  connect(myfd,(struct sockaddr*)&server,sizeof(server));

  char buffer[128];
  recv(myfd,buffer,sizeof(buffer),0);
  printf("%s\n" ,buffer);
  close(myfd);
 














}


