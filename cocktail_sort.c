#include <stdio.h>

void
cocktail_sort(int *v, int n)
{
	int i, swaped;
	do {
		swaped = 0;
		for (i = 1; i < n; i++)
			if (v[i-1] > v[i]) {
				v[i]	^= v[i-1];
				v[i-1]	^= v[i];
				v[i]	^= v[i-1];
				swaped = 1;
			}
		if (!swaped)
			break;
		for (i = i - 1; i > 0; i--)
			if (v[i-1] > v[i]) {
				v[i]	^= v[i-1];
				v[i-1]	^= v[i];
				v[i]	^= v[i-1];
				swaped = 1;
			}
		n--;
	} while (swaped);
}

#define N 6
int
main(void)
{
	int i, v[N] = {8, 2, 4, 9, 3, 6};
	for (i = 0; i < N; i++)
		printf("%d ", v[i]);
	puts("");
	cocktail_sort(v, N);
	for (i = 0; i < N; i++)
		printf("%d ", v[i]);
	puts("");
	return 0;
}
