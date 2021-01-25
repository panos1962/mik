#include "mik.h"

// Η function "mikAll" δέχεται έναν θετικό ακέραιο N και υπλογίζει το [N],
// δηλαδή το πλήθος όλων των μη ισοδυνάμων καταμερισμών (ΜΙΚ) των N πραγμάτων.
// Η μέθοδος που ακολουθείται στο παρόν είναι η εξής: Για κάθε αριθμό k από το
// 1 έως και το N, υπολογίζονται όλοι οι ΜΙΚ των N στοιχείων σε k ομάδες με τη
// function "mikPart". Το άθροισμα όλων αυτών των συνδυασμών είναι προφανώς το
// ζητούμενο. Η "mikPart" μπορεί να είναι είτε η function "mikPartMemoize" που
// χρησιμοποιεί memoization για την επιτάχυνση των διαδικασιών, είτε η function
// "mikPartStraight" που δεν χρησιμοποιεί memoization και υπολογίζει κάθε φορά
// εκ νέου αποτελέσματα που ίσως έχουν ήδη υπολογιστεί.

long double mikAll(int n) {
	long double count;
	int k;

	for (count = 0, k = 1; k <= n; k++)
	count += mikPart(n, k);

	return count;
}

// Ακολουθεί η function "mikPartMemoize" που δέχεται έναν θετικό ακέραιο N
// και ένα πλήθος k <= N, και υπολογίζει το [N:k], δηλαδή το πλήθος όλων των
// ΜΙΚ των N πραγμάτων σε k ομάδες. Η function μετέρχεται memoization καθώς
// πολλές φορές το πρόγραμμα υπολογίζει ξανά και ξανά τους ίδιους ακριβώς
// συδυασμούς.

static long double mikMmz[MAX + 1][MAX + 1];

long double mikPartMemoize(int n, int k) {
	if (mikMmz[n][k])
	return mikMmz[n][k];

	if (k == 1)
	return 1;

	if (k == n)
	return 1;

	int m = n - k;
	int i = (m < k ? m : k);

	for (mikMmz[n][k] = 0; i > 0; i--)
	mikMmz[n][k] += mikPart(m, i);

	return mikMmz[n][k];
}

// Η function "mikPartStraight" επιτελεί τις ίδιες ακριβώς διεργασίες που
// επιτελεί και η "mikPartMemoize" χωρίς όμως να μετέρχεται memoization,
// γεγονός που την καθιστά πολύ πιο αργή από την "mikPartMemoize". Ο μόνος
// λόγος που παρέχεται ως εναλλακτική function υπολογισμού είναι για τον
// έλεγχο της διαφοράς στην απόδοση.

long double mikPartStraight(int n, int k) {
	if (k == 1)
	return 1;

	if (k == n)
	return 1;

	int m = n - k;
	int i = (m < k ? m : k);

	long double count;

	for (count = 0; i > 0; i--)
	count += mikPart(m, i);

	return count;
}
