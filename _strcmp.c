/*
implemantation of strcmp
m0nad /at/ email.com
*/

#include <stdio.h>
#define LEN 256

int 
_strcmp (const char *s1, const char *s2)
{
 while (*s1 == *s2++)
  if (*s1++ == 0) return 0;
 return (unsigned)*s1 < (unsigned)*--s2 ? -1 : 1;
}

int
main ()
{
  char str1 [LEN], str2 [LEN];
  printf ("string 1: ");
  fgets (str1, LEN, stdin);
  printf ("string 2: ");
  fgets (str2, LEN, stdin);
  if (_strcmp (str1, str2) == 0)
    puts ("equal");
  else
    puts ("not equal");
  return 0;
}
