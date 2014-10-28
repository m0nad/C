//https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher - m0nad
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LEN 26
int
main(int argc, char ** argv)
{
  unsigned int i;
  const char * key, * msg;
  if (argc < 3)
    printf("Usage: %s <key> <msg>\n", argv[0]), exit(1);
  key = argv[1];
  msg = argv[2];
  for (i = 0; i < strlen(msg); i++) {
    if (!isalpha(msg[i]))
      continue;
    printf("%c", ((tolower(msg[i]) - 'a' + tolower(key[i % strlen(key)]) - 'a') % 26) + 'a');
  }

  puts("");
  return 0;
}
