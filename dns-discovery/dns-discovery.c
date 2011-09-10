/*
Author	: m0nad
aka 	: Victor Ramos Mello
email	: m0nad /at/ email.com
github	: https://github.com/m0nad/
blog	: http://m0nadcoder.wordpress.com/
copyfree: beer license, if you like this, buy me a beer
	
$ gcc -o dns-discovery dns-discovery.c -Wall -Wextra -lpthread -O3
$ ./dns-discovery google.com wordlist.wl 5
   ___  _  ______    ___  _                              
  / _ \/ |/ / __/___/ _ \(_)__ _______ _  _____ ______ __
 / // /    /\ \/___/ // / (_-</ __/ _ \ |/ / -_) __/ // /
/____/_/|_/___/   /____/_/___/\__/\___/___/\__/_/  \_, / 
                                                  /___/  
	  by m0nad /at/ email.com

academico.google.com
IPv4 address: 74.125.229.81
IPv4 address: 74.125.229.80
IPv4 address: 74.125.229.84
IPv4 address: 74.125.229.83
IPv4 address: 74.125.229.82

accounts.google.com
IPv4 address: 74.125.45.84

ads.google.com
IPv4 address: 74.125.45.112

alerts.google.com
IPv4 address: 74.125.229.68
IPv4 address: 74.125.229.69
IPv4 address: 74.125.229.70
IPv4 address: 74.125.229.71
IPv4 address: 74.125.229.72
IPv4 address: 74.125.229.73
IPv4 address: 74.125.229.74
IPv4 address: 74.125.229.75
IPv4 address: 74.125.229.76
IPv4 address: 74.125.229.77
IPv4 address: 74.125.229.78
IPv4 address: 74.125.229.79
IPv4 address: 74.125.229.64
IPv4 address: 74.125.229.65
IPv4 address: 74.125.229.66
IPv4 address: 74.125.229.67

ipv6.google.com
IPv6 address: 2001:4860:8006::67

...

*/
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <pthread.h>
#include <string.h>

#define TAM 256
#define MAX 512
#define SAY puts

struct dd_threads_args {
  FILE * file;
  char * domain;
};

void
erro (const char * msg)
{
  perror (msg);
  exit (1);
}

FILE *
ck_fopen (char * path, const char * mode)
{
  FILE * file = fopen (path, mode);
  if (file == NULL) 
    erro ("fopen ");
   
  return file;
}

void *
ck_malloc (size_t size)
{
  void * ptr = malloc (size);
  if (ptr == NULL) 
    erro ("malloc ");
  return ptr;
}

void
chomp (char * str)
{
  while (*str) {
    if (*str == '\n' || *str == '\r') {
      *str = 0;
      return;
    }
    str++;
  }
}

void
banner ()
{
  SAY (
"   ___  _  ______    ___  _                              \n"
"  / _ \\/ |/ / __/___/ _ \\(_)__ _______ _  _____ ______ __\n"
" / // /    /\\ \\/___/ // / (_-</ __/ _ \\ |/ / -_) __/ // /\n"
"/____/_/|_/___/   /____/_/___/\\__/\\___/___/\\__/_/  \\_, / \n"
"                                                  /___/  \n"
"\t  by m0nad /at/ email.com\n");
}

int
usage ()
{
  SAY (" usage\n ./dns-discovery domain wordlist.wl [threads]\n");
  exit (1);
}

void 
dns_discovery (FILE * file, const char * domain)
{
  int err, ipv;
  char line [TAM];
  char hostname [MAX];
  char addrstr [TAM];
  void * ptr;
  struct addrinfo * res, hints;

  memset (&hints, 0, sizeof hints);
  hints.ai_family = PF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags |= AI_CANONNAME;


  while (fgets (line, sizeof line, file) != NULL) {
    chomp (line);
    snprintf (hostname, sizeof hostname, "%s.%s", line, domain);
    err = getaddrinfo (hostname, NULL, &hints, &res);
//lock ?
    if (err == 0) {
      SAY (hostname);
      while (res) {
	inet_ntop (res->ai_family, res->ai_addr->sa_data, addrstr, TAM);
        switch (res->ai_family) {
	  case AF_INET:
	    ipv = 4;
	    ptr = &((struct sockaddr_in *) res->ai_addr)->sin_addr;
	    break;
          case AF_INET6:
	    ipv = 6;
            ptr = &((struct sockaddr_in6 *) res->ai_addr)->sin6_addr;
            break;
        }
	inet_ntop (res->ai_family, ptr, addrstr, TAM);
	printf ("IPv%d address: %s\n", ipv, addrstr);
	res = res->ai_next;
      }
      SAY("");
      freeaddrinfo (res);
    } 
//unlock ?
  }
}

void *
dns_discovery_thread (void * args)
{
  struct dd_threads_args * dns_discovery_args = (struct dd_threads_args *) args;
  dns_discovery (dns_discovery_args->file, dns_discovery_args->domain);
  return NULL;	
}

int
main (int argc, char ** argv) 
{
  int nthreads = 1, i, err;
  pthread_t * threads;
  struct dd_threads_args dns_discovery_args;

  banner();
  if (argc < 3 || argc > 4) 
    usage();
  else if (argc == 4)
    nthreads = atoi (argv[3]);

  threads = (pthread_t *) ck_malloc (nthreads * sizeof (pthread_t)); 
 
  dns_discovery_args.file = ck_fopen (argv[2], "r");
  dns_discovery_args.domain = argv[1];
  for (i = 0; i < nthreads; i++) {
    err = pthread_create (&threads[i], NULL, dns_discovery_thread, (void *)&dns_discovery_args);
    if (err != 0)
      erro ("pthread ");
  }
  for (i = 0; i < nthreads; i++) {
    pthread_join (threads[i], NULL);
  }

  free (threads);
  fclose (dns_discovery_args.file);
  return 0;
}
