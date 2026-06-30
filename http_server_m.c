#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdbool.h>
#include <pthread.h>

#define PORT 8080
#define BUFF_SIZE 1024
#define CONN_LIM 5

#define SOCK_ADDR (struct sockaddr *)&address
#define BAD_EXIT exit(EXIT_FAILURE)

// HTTP Response we send to browser
char *http_response =
    "HTTP/1.1 200 OK\r\n"
    "Content-Type: text/html\r\n"
    "Content-Length: 53\r\n"
    "Connection: close\r\n"
    "\r\n"
    "<html><body><h1>Hello From Backend</h1></body></html>";

void *worker(void *arg)
{
  char buff[BUFF_SIZE];

  int cfd = *(int *)arg;
  free(arg);//avoids eventual mem leak

  memset(buff, 0, sizeof(buff));

  int bytes_read = read(cfd, buff, BUFF_SIZE - 1);

  if (bytes_read < 0)
  {
    perror("read");
    close(cfd);
    return NULL;
  }

  if (bytes_read > 0)
  {
    printf("Received HTTP Request:\n\n%s\n", buff);
  }

  if (write(cfd, http_response, strlen(http_response)) < 0)
  {
    perror("write");
  }

  printf("Response sent to client\n");

  close(cfd);
  printf("Connection closed\n");

  return NULL;
}

int main()
{
  int sfd, cfd;

  struct sockaddr_in address;
  socklen_t addr_len = sizeof(address);

  sfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sfd == -1)
  {
    perror("socket");
    BAD_EXIT;
  }

  int opt = 1;
  if (setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
  {
    perror("setsockopt");
    close(sfd);
    BAD_EXIT;
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  if (bind(sfd, SOCK_ADDR, sizeof(address)) < 0)
  {
    perror("bind");
    close(sfd);
    BAD_EXIT;
  }

  if (listen(sfd, CONN_LIM) < 0)
  {
    perror("listen");
    close(sfd);
    BAD_EXIT;
  }

  while (true)
  {
    printf("Waiting for new Connection\n");

    cfd = accept(sfd, SOCK_ADDR, &addr_len);

    if (cfd < 0)
    {
      perror("accept");
      continue;
    }

    printf("Connection accepted\n");

    int *pcfd = malloc(sizeof(int));
    if (pcfd == NULL)
    {
      perror("malloc");
      close(cfd);
      continue;
    }

    *pcfd = cfd;

    pthread_t tid;

    if (pthread_create(&tid, NULL, worker, pcfd) != 0)
    {
      perror("pthread_create");
      free(pcfd);
      close(cfd);
      continue;
    }

    pthread_detach(tid);//free all resources of that thread(i.e. kill thread)
  }

  close(sfd);
  return 0;
}