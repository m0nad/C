// ceasar cipher in C - m0nad
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
void
rot(unsigned int c, char * str)
{
  unsigned int i;
  for (i = 0; i < strlen(str); i++) {
    if (!isalpha(str[i]))
      continue;
    str[i] = (((tolower(str[i]) - 'a') + c) % 26) + 'a';
  }
}

int
main(int argc, char ** argv)
{
  int key;
  if (argc < 3)
    printf("Usage: %s <key> <msg>\n", argv[0]), exit(1);
  key = atoi(argv[1]);
  if (key < 0) key += 26;
  rot(key, argv[2]);
  printf("%s\n", argv[2]);
  return 0;
}
  
