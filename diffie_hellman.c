#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int
main()
{
  int i;
  long double p = 17, g = 5;//public
  long double a = 6, b = 15;//private
  long double bob_msg = 0, alice_msg = 0, alice_secret, bob_secret;

  srand(time(NULL)^(int)&i);

  a = rand() % 16;
  printf("Alice and Bob agree to use a prime number p=%Lf and base g=%Lf.\n", p, g);
  printf("Alice chooses a secret integer a=%Lf, then sends Bob alice_msg = g ^ a mod p\n", a);
  printf("alice_msg = %Lf ^ %Lf mod %Lf\n", g, a, p);
  alice_msg = fmod(pow(g, a), p);
  printf("alice_msg: %Lf\n", alice_msg);

  b = rand() % 16;
  printf("Bob chooses a secret integer b=%Lf, then sends Alice bob_msg = g ^ b mod p\n", b);
  printf("bob_msg = %Lf ^ %Lf mod %Lf\n", g, b, p);
  bob_msg = fmod(pow(g, b), p);
  printf("bob_msg: %Lf\n", bob_msg);

  printf("Alice computes s = bob_msg ^ a mod p\n");
  alice_secret = fmod(pow(bob_msg, a), p);
  printf("Alice secret: %Lf\n", alice_secret);
  printf("Bob computes s = alice_msg ^ b mod p\n");
  bob_secret = fmod(pow(alice_msg, b), p);
  printf("Bob secret: %Lf\n", bob_secret);

  return 0;
}
