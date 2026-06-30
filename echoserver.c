#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <pthread.h>
#include <sys/epoll.h>

#define MAX_CLIENT 5

int main()
{

  int sfd = socket(AF_INET, SOCK_STREAM, 0); // sfd(server file descriptor)

  struct sockaddr_in server;
  memset(&server, 0, sizeof(server));
  server.sin_family = AF_INET;
  server.sin_port = htons(8080);
  server.sin_addr.s_addr = INADDR_ANY; // accept connecctions from any network interface(ethernet,bluetooth,wifi)

  bind(sfd, (struct sockaddr *)&server, sizeof(server));
  listen(sfd, MAX_CLIENT);

  int cfd[MAX_CLIENT];
  int cntr = 0;

  // using epoll
  int epfd = epoll_create1(0);

  struct epoll_event ev, events[MAX_CLIENT];
  ev.events = EPOLLIN;
  ev.data.fd = sfd;

  epoll_ctl(epfd, EPOLL_CTL_ADD, sfd, &ev); // giving kernel sfd to kernel to watch upon

  char buffer[256];
  while (true)
  {
    int n = epoll_wait(epfd, events, MAX_CLIENT, -1); // returns no of ready events

    for (int i = 0; i < n; i++)
    {
      int fd = events[i].data.fd;

      // new connection
      if (fd == sfd)
      {
        int cfd = accept(sfd, NULL, NULL);
        ev.events = EPOLLIN;
        ev.data.fd = cfd;
        epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev); // add it to watch list

        printf("New client %d\n", cfd);

      } // client sends data
      else
      {
        // read(fd,buffer,sizeof(buffer)) instead of recv can also be used
        int bytes = recv(fd, buffer, sizeof(buffer) - 1, 0);

        if (bytes <= 0)
        {
          epoll_ctl(epfd, EPOLL_CTL_DEL, fd, NULL);
          close(fd);
        }
        else
        {
          buffer[bytes] = '\0';
          printf("Client %d: %s\n", fd, buffer);
        }

      }
    }
  }
}