#!/usr/bin/env awk

BEGIN {
	mikPart = "mikPart" (straight ? "Straight" : "Memoize")
}

{
	if (verbose)
	printf $1 " "

	print mikAll($1)
}

function mikAll(n,			count, k) {
	for (k = 1; k <= n; k++)
	count += @mikPart(n, k)

	return count
}

BEGIN {
	mikMmz[1][1] = 1
}

function mikPartMemoize(n, k,			m, min, count) {
	if (mikMmz[n][k])
	return mikMmz[n][k]

	if (k == 1)
	return 1

	if (k == n)
	return 1

	m = n - k
	min = (m < k ? m : k)

	for (count = 0; min > 0; min--)
	count += @mikPart(m, min)

	return (mikMmz[n][k] = count)
}

function mikPartStraight(n, k,			m, min, count) {
	if (k == 1)
	return 1

	if (k == n)
	return 1

	m = n - k
	min = (m < k ? m : k)

	for (count = 0; min > 0; min--)
	count += @mikPart(m, min)

	return count
}
