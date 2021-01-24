#include "mik.h"

double mikAll(int n) {
	double count;
	int k;

	for (count = 0, k = 1; k <= n; k++)
	count += mikPart(n, k);

	return count;
}

static double mikMmz[MAX + 1][MAX + 1];

double mikPartMemoize(int n, int k) {
	if (k == 1)
	return 1;

	if (k == n)
	return 1;

	if (mikMmz[n][k])
	return mikMmz[n][k];

	int m = n - k;
	int min = (m < k ? m : k);

	for (mikMmz[n][k] = 0; min > 0; min--)
	mikMmz[n][k] += mikPart(m, min);

	return mikMmz[n][k];
}

double mikPartStraight(int n, int k) {
	if (k == 1)
	return 1;

	if (k == n)
	return 1;

	int m = n - k;
	int min = (m < k ? m : k);

	double count;

	for (count = 0; min > 0; min--)
	count += mikPart(m, min);

	return count;
}
