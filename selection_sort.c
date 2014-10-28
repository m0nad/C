#include <stdio.h>

void
selection_sort(int *v, int n)
{
	int i, j, min;
	for (i = 0; i < n - 1; i++) {
		min = i;
		for (j = i + 1; j < n; j++)
			if (v[j] < v[min])
				min = j;
		if (min != i) {
			v[min]	^= v[i];
			v[i]	^= v[min];
			v[min]	^= v[i];
		}
	}
}

#define N 6
int
main(void)
{
	int i, v[N] = {8, 2, 4, 9, 3, 6};
	for (i = 0; i < N; i++)
		printf("%d ", v[i]);
	puts("");
	selection_sort(v, N);
	for (i = 0; i < N; i++)
		printf("%d ", v[i]);
	puts("");
	return 0;
}

