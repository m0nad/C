/*
implementation of merge sort algorithim 
m0nad /at/ email.com
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 20


void
merge (int ini, int meio, int fim, int * v)
{
  int i, j, k = 0, *aux;
  i = ini;
  j = meio;
  aux = (int *) malloc ((fim-ini) * sizeof (int));
  while (i < meio && j < fim) {
    if (v[i] <= v[j]) aux[k++] = v[i++];
    else aux[k++] =  v[j++];
  }
  while (i < meio) aux[k++] = v[i++];
  while (j < fim) aux[k++] = v[j++];
  for (i = ini; i < fim ; i++)
    v[i] = aux[i-ini];
  free (aux);
}

void
mergesort (int ini, int fim, int * v)
{
  int meio;
  if (ini < fim - 1) {
    meio = (ini + fim) / 2;
    mergesort (ini, meio, v);
    mergesort (meio, fim, v);
    merge (ini, meio, fim, v);
  }
}

int
main ()
{
  int * lista, i;
  int inicio = 0, fim = MAX;
  lista = (int *) malloc (MAX * sizeof (int));
  for (i = 0; i < MAX; i++)
    scanf ("%i", &lista[i]);
  mergesort (inicio, fim, lista);
  for (i = 0; i < MAX; i++)
    printf ("%d ", lista[i]);
  puts ("");
  free(lista);
  return 0;
}
