#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdbool.h>

#define PORT 8080
#define BUFF_SIZE 1024


int main()
{

  int sfd,cfd;//server and client file descriptor

  struct sockaddr_in address;
  int addr_len = sizeof(address);

  char buff[BUFF_SIZE] = {0};

  //HTTP Response we send to browser
  char* http_response = 
  "HTTP/1.1 200 OK\r\n"
  "Content-Type: text/html\r\n"
  "Content-Length: 50\r\n"
  "Connection: close\r\n"
  "\r\n"
  "<html><body><h1>Hello From Backend</h1></body><html>";


  sfd = socket(AF_INET,SOCK_STREAM,0);
  if(sfd == 0)
  {
    fprintf(stderror,"Socket creation >Failed!\n");
    exit(EXIT_FAILURE);
  }

  //Server config>
  address.sin_family = AF_INET;//IPv4
  address.sin_addr.s_addr = INADDR_ANY;//listen on all interfaces
  address.sin_port = htons(PORT);//converts to NetworkByteOrder


  if(bind(sfd,(struct sockaddr*)&address,sizeof(address))<0)
  {
    fprintf(stderror,"Bind failed\n");
    close(sfd);
    exit(EXIT_FAILURE);
  }

  if(listen(sfd,5)<0)
  {
    fprintf(stderror,"Listen Failed\n");
    close(sfd);
    exit(EXIT_FAILURE);
  }


  while(true)
  {










    
  }






























}