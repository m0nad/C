/* insertion sort */
#include <stdio.h>

void
insertion_sort(int *v, int n)
{
	int i, j, key;
	for (i = 1; i < n; i++) {
		key = v[i];
		for (j = i - 1; (j >= 0) && (key < v[j]); j--) {
			v[j+1] = v[j];
		}
		v[j+1] = key;
	}
}
void
_insertion_sort(int *v, int n)
{
	int i, j, k, key;
	for (i = 1; i < n; i++) {
		for (j = 0; j < i; j++) {
			if (v[j] > v[i]) {
				key = v[i];
				for (k = i; k > j; k--) {
					v[k] = v[k-1];
				}
				v[j] = key;
			}
				
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
	insertion_sort(v, N);
	for (i = 0; i < N; i++)
		printf("%d ", v[i]);
	puts("");
	return 0;
}
