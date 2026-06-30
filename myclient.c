#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

int main()
{
  int cfd = socket(AF_INET, SOCK_STREAM, 0);

  struct sockaddr_in server;
  memset(&server, 0, sizeof(server)); // good practise not needed

  server.sin_family = AF_INET;
  server.sin_port = htons(8080);
  inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

  connect(cfd, (struct sockaddr *)&server, sizeof(server));

  char buffer[128];

  while (true)
  {


    fgets(buffer, sizeof(buffer), stdin);//puts \n till end
    int len = strlen(buffer);
    if (buffer[len - 1] == '\n')
    {
      buffer[len - 1] = '\0';
      len--;
    }

    send(cfd, buffer, len, 0);
  }

  close(cfd);
}