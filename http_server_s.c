#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<stdbool.h>
#include<pthread.h>


#define PORT 8080
#define BUFF_SIZE 1024

#define SOCK_ADDR (struct sockaddr*)&address
#define BAD_EXIT exit(EXIT_FAILURE)

//HTTP Response we send to browser
char* http_response = 
"HTTP/1.1 200 OK\r\n"
"Content-Type: text/html\r\n"
"Content-Length: 50\r\n"
"Connection: close\r\n"
"\r\n"
"<html><body><h1>Hello From Backend</h1></body><html>";


int main()
{

  int sfd,cfd;//server and client file descriptor

  struct sockaddr_in address;
  int addr_len = sizeof(address);

  char buff[BUFF_SIZE] = {0};



  sfd = socket(AF_INET,SOCK_STREAM,0);
  if(sfd == 0)
  {
    fprintf(stderr,"Socket creation >Failed!\n");
    BAD_EXIT;
  }

  //Server config>
  address.sin_family = AF_INET;//IPv4
  address.sin_addr.s_addr = INADDR_ANY;//listen on all interfaces
  address.sin_port = htons(PORT);//converts to NetworkByteOrder


  if(bind(sfd,SOCK_ADDR,sizeof(address))<0)
  {
    fprintf(stderr,"Bind failed\n");
    close(sfd);
    BAD_EXIT;
  }

  if(listen(sfd,5)<0)
  {
    fprintf(stderr,"Listen Failed\n");
    close(sfd);
    BAD_EXIT;
  }


  while(true)
  {
    printf("Waiting for new Connection\n");

    if((cfd = accept(sfd,SOCK_ADDR,(socklen_t*)&addr_len)) < 0)
    {
      fprintf(stderr,"Connection Failed");
      BAD_EXIT;

    }
    //spawn a thread that does this work

    printf("Connection accepted\n");

    memset(buff,0,BUFF_SIZE);

    int bytes_read = read(cfd,buff,BUFF_SIZE - 1);

    if(bytes_read>0)
    {
      printf("Received HTTP Request:\n\n%s\n",buff);
    }

    write(cfd,http_response,strlen(http_response));

    printf("Response sent to client\n");


    close(cfd);//closing the connection
    printf("Connection closed\n");

  }

  close(sfd);
  return 0;











    
  }


