char notevil[] = "\x23\x69\x6e\x63\x6c\x75\x64\x65\x20\x3c\x73\x74\x64\x69\x6f\x2e\x68\x3e\x0a\x69\x6e\x74\x0a\x6d\x61\x69\x6e\x20\x28\x29\x0a\x7b\x0a\x20\x20\x69\x6e\x74\x20\x69\x20\x3d\x20\x30\x20\x3b\x0a\x20\x20\x70\x72\x69\x6e\x74\x66\x20\x28\x22\x63\x68\x61\x72\x20\x6e\x6f\x74\x65\x76\x69\x6c\x5b\x5d\x20\x3d\x20\x5c\x22\x22\x29\x3b\x0a\x20\x20\x77\x68\x69\x6c\x65\x20\x28\x6e\x6f\x74\x65\x76\x69\x6c\x5b\x69\x5d\x29\x20\x7b\x0a\x20\x20\x20\x20\x70\x72\x69\x6e\x74\x66\x20\x28\x22\x5c\x5c\x78\x25\x30\x32\x78\x22\x2c\x20\x6e\x6f\x74\x65\x76\x69\x6c\x5b\x69\x2b\x2b\x5d\x29\x3b\x0a\x20\x20\x7d\x0a\x20\x20\x70\x72\x69\x6e\x74\x66\x20\x28\x22\x5c\x22\x3b\x5c\x6e\x25\x73\x22\x2c\x20\x6e\x6f\x74\x65\x76\x69\x6c\x29\x3b\x0a\x20\x20\x72\x65\x74\x75\x72\x6e\x20\x30\x3b\x0a\x7d\x0a";
#include <stdio.h>
int
main ()
{
  int i = 0 ;
  printf ("char notevil[] = \"");
  while (notevil[i]) {
    printf ("\\x%02x", notevil[i++]);
  }
  printf ("\";\n%s", notevil);
  return 0;
}