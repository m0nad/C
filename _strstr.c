/*
strstr implementation
m0nad /at/ email.com

*/

#include <stdio.h>
#define LEN 256

char *
_strstr (const char * s1, const char * s2)
{
  int i, j, k;
  for (i = 0; s1[i]; i++)
    for (j = i, k = 0; s1[j] == s2[k]; j++, k++)
      if (s2[k+1] == 0)
        return (char *) (s1 + i);
  return NULL;
}

