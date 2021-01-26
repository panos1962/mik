#include "mik.h"

// Η function "mikPart" δέχεται δύο θετικούς ακεραίους N και k με k ≤ N, και
// υπολογίζει το [N:k], δηλαδή το πλήθος όλων των ΜΙΚ των N πραγμάτων σε k
// ομάδες. Η function μετέρχεται memoization καθώς πολλές φορές το πρόγραμμα
// υπολογίζει ξανά και ξανά τους ίδιους ακριβώς συνδυασμούς.

static char mikMmzSet[MAX + 1][MAX + 1];
static mpz_t mikMmzVal[MAX + 1][MAX + 1];

static void mikPart(int n, int k) {
	// Αν το ζητούμενο έχει ήδη υπολογιστεί, τότε δεν προβαίνουμε σε
	// καμία περαιτέρω ενέργεια.

	if (mikMmzSet[n][k])
	return;

	mpz_init(mikMmzVal[n][k]);

	if (k == 1)
	mpz_set_ui(mikMmzVal[n][k], 1);

	else if (k == n)
	mpz_set_ui(mikMmzVal[n][k], 1);

	else {
		int m = n - k;
		int i = (m < k ? m : k);

		for (mpz_set_ui(mikMmzVal[n][k], 0); i > 0; i--) {
			if (!mikMmzSet[m][i])
			mikPart(m, i);

			mpz_add(mikMmzVal[n][k], mikMmzVal[n][k],
				mikMmzVal[m][i]);
		}
	}

	mikMmzSet[n][k] = 1;
}

// Ακολουθεί η βασική function "mikAll" που δέχεται έναν θετικό ακέραιο N και
// υπολογίζει το [N], τουτέστιν το πλήθος όλων των μη ισοδυνάμων καταμερισμών
// (ΜΙΚ) των N πραγμάτων. Η μέθοδος που ακολουθείται στο παρόν είναι η εξής:
// Για κάθε αριθμό k από το 1 έως και το N, υπολογίζονται όλοι οι ΜΙΚ των N
// στοιχείων σε k ομάδες με τη function "mikPart". Το άθροισμα όλων αυτών
// των συνδυασμών είναι προφανώς το ζητούμενο όλων των ΜΙΚ των Ν πραγμάτων
// σε k ομάδες με 1 ≤ k ≤ N.

void mikAll(mpz_t count, int n) {
	mpz_set_ui(count, 0);

	for (int k = 1; k <= n; k++) {
		mikPart(n, k);
		mpz_add(count, count, mikMmzVal[n][k]);
	}
}
