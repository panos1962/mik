#include "mik.h"

// Η function "mikAll" δέχεται έναν θετικό ακέραιο N και υπλογίζει το [N],
// δηλαδή το πλήθος όλων των μη ισοδυνάμων καταμερισμών (ΜΙΚ) των N πραγμάτων.
// Η μέθοδος που ακολουθείται στο παρόν είναι η εξής: Για κάθε αριθμό k από το
// 1 έως και το N, υπολογίζονται όλοι οι ΜΙΚ των N στοιχείων σε k ομάδες με τη
// function "mikPart". Το άθροισμα όλων αυτών των συνδυασμών είναι προφανώς το
// ζητούμενο.

void mikAll(int n, mpz_t count) {
	int k;

	mpz_t t;
	mpz_init(t);

	for (mpz_set_ui(count, 0), k = 1; k <= n; k++) {
		mikPart(n, k, t);
		mpz_add(count, count, t);
	}

	mpz_clear(t);
}

// Ακολουθεί η function "mikPart" που δέχεται έναν θετικό ακέραιο N και ένα
// πλήθος k <= N, και υπολογίζει το [N:k], δηλαδή το πλήθος όλων των ΜΙΚ των
// N πραγμάτων σε k ομάδες. Η function μετέρχεται memoization καθώς πολλές
// φορές το πρόγραμμα υπολογίζει ξανά και ξανά τους ίδιους ακριβώς συδυασμούς.

static char mikMmzSet[MAX + 1][MAX + 1];
static mpz_t mikMmzVal[MAX + 1][MAX + 1];

void mikPart(int n, int k, mpz_t x) {
	if (mikMmzSet[n][k])
	return mpz_set(x, mikMmzVal[n][k]);

	if (k == 1)
	return mpz_set_ui(x, 1);

	if (k == n)
	return mpz_set_ui(x, 1);

	int m = n - k;
	int i = (m < k ? m : k);

	mpz_t t;
	mpz_init(t);
	mpz_init(mikMmzVal[n][k]);

	for (mpz_set_ui(x, 0); i > 0; i--) {
		mikPart(m, i, t);
		mpz_add(x, x, t);
	}

	mpz_set(mikMmzVal[n][k], x);
	mikMmzSet[n][k] = 1;
}
