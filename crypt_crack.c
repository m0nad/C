// dictionary attack on crypt() - m0nad
#define _XOPEN_SOURCE
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int
main(int argc, char ** argv)
{

  FILE * fp;
  char * line = NULL;
  char * hash = NULL;
  size_t len = 0;

  if (argc < 3)
    printf("Usage: %s <dict> <hash>\n", argv[0]), exit(1);

  fp = fopen(argv[1], "r");
  if (fp == NULL)
    perror("fopen"), exit(1);
  puts("Cracking...");
  while (getline(&line, &len, fp) != -1) {
    line[strlen(line)-1] = 0;
    hash = crypt(line, argv[2]);
    if (strcmp(hash, argv[2]) == 0) {
      printf("%s\t-> %s == %s  <--- PASSWORD FOUND!\n", line, hash, argv[2]);
      goto clean;
    }
    printf("%s\t-> %s != %s\n", line, hash, argv[2]);
  }
  puts("Password not found :(");

clean:
  fclose(fp);
  if (line)
    free(line);
  return 0;
}
