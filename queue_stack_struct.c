/*
queue and stack implementation 
por
m0nad /at/ email.com 
*/
#include <stdio.h>
#include <stdlib.h>

struct dados {
  int * v;
  int sp;
};


void
push (struct dados * s, int max)
{

  if (s->sp + 1 < max) {
    printf ("number to push: ");
    scanf ("%d", &s->v[++s->sp]);
  }
  else
   puts ("stack is full");

}
void
shift (struct dados * s)
{
  int num, i;
  if (s->sp >= 0)
  {
    num = s->v[0];
    for (i = 0; i < s->sp; i++) 
      s->v[i] = s->v[i+1];
    s->sp--;
    printf ("shifted number: %d\n", num);
  }
  else
    puts ("queue is empty"); 
}
void
pop (struct dados * s)
{

  if (s->sp >= 0) {
    printf ("poped number: %d\n", s->v[s->sp--]);
  }
  else
    puts ("stack is empty");

}  
void
unshift (struct dados * s, int max)
{
  int i;
  if (s->sp+1 < max) {    
    for (i = ++s->sp; i > 0; i--) 
      s->v[i] = s->v[i-1];
    printf ("number to unshift: ");
    scanf ("%d", s->v);
  }
  else
    puts ("queue is full"); 
}

int
main ()
{
  int op, n;
  struct dados s;
  printf ("size of the vector: ");
  scanf ("%d", &n);
  s.v = (int *) malloc (n * sizeof (int));
  if (s.v == NULL) {
    perror ("malloc");
    exit (1);
  }  
  s.sp = -1;
  do {
    puts ("1 - push");
    puts ("2 - pop");
    puts ("3 - shift");
    puts ("4 - unshift");
    puts ("5 - exit");
    scanf ("%d", &op);
    switch (op) {
       case 1:
         push(&s, n);
         break;
       case 2:
         pop(&s);
         break;
       case 3: 
         shift(&s);
         break;
       case 4:
         unshift(&s, n);
         break;
    }
  } while (op != 5);
  return 0;
}
