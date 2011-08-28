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
accounts.google.com
ads.google.com
alerts.google.com
ap.google.com
apps.google.com
asia.google.com
...

*/
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <pthread.h>

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
  int errcode;
  char line [TAM];
  char hostname [MAX];
  struct addrinfo * res;
  while (fgets (line, sizeof line, file) != NULL) {
    chomp (line);
    snprintf (hostname, sizeof hostname, "%s.%s", line, domain);
    errcode = getaddrinfo (hostname, NULL, NULL, &res);
    if (errcode == 0) {
      SAY (hostname);
      freeaddrinfo (res);
    } 
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
  int nthreads = 1, i;
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
    pthread_create (&threads[i], NULL, dns_discovery_thread, (void *)&dns_discovery_args);
  }
  for (i = 0; i < nthreads; i++) {
    pthread_join (threads[i], NULL);
  }

  free (threads);
  fclose (dns_discovery_args.file);
  return 0;
}
