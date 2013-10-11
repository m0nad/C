/*
implementation of quicksort
m0nad /at/ email.com
*/

#include <stdio.h>
#include <stdlib.h>
#define MAX 5 

void
quicksort (int * v, int inicio, int fim)
{
  int i = inicio, j = fim, aux, meio, x;
  meio = (inicio + fim) / 2;
  x = v[meio];
  while (i <= j) {
    if (v[i] < x) i++;
    else if (v[j] > x) j--;
    else {
      aux = v[i];
      v[i++] = v[j];
      v[j--] = aux;
    }
  }
  if (inicio < j)
    quicksort (v, inicio, j);
  if (fim > i)
    quicksort (v, i , fim);
}

int
main ()
{
  int * lista, i;
  int inicio = 0, fim = MAX-1;
  
  lista = (int *) malloc (MAX * sizeof (int));
  for(i = 0; i < MAX; i++)
    scanf("%d", &lista[i]);
  quicksort(lista , inicio, fim);
  for(i = 0; i < MAX; i++)
    printf("%d ", lista[i]);
  puts("");
  free(lista);
  return 0;
}
