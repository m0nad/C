#include <stdio.h>

void
_bubble_sort(int *v, int n)
{
	int i, swaped;
	for (swaped = 1; swaped; n--) {
		swaped = 0;
		for (i = 1; i < n; i++) {
			if (v[i-1] > v[i]) {
				v[i-1]	^= v[i];
				v[i]	^= v[i-1];
				v[i-1]	^= v[i];
				swaped = 1;
			}
		}
	}
}

void
bubble_sort(int *v, int n)
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
	_bubble_sort(v, N);
	for (i = 0; i < N; i++)
		printf("%d ", v[i]);
	puts("");
	return 0;
}
