#include "mik.h"

#define MIK_PART_ADD(count, n, k) { \
	if (debug) \
	mikPartCallCount++; \
\
	if (!mikMmzSet[n][k]) \
	mikPart(n, k); \
\
	mpz_add(count, count, mikMmzVal[n][k]); \
}

unsigned long long mikPartCallCount = 0;
unsigned long long mikPartExecCount = 0;

// Η function "mikPart" δέχεται δύο θετικούς ακεραίους N και k με k ≤ N, και
// υπολογίζει το [N:k], δηλαδή το πλήθος όλων των ΜΙΚ των N πραγμάτων σε k
// ομάδες. Η function μετέρχεται memoization καθώς πολλές φορές το πρόγραμμα
// υπολογίζει ξανά και ξανά τους ίδιους ακριβώς συνδυασμούς.

static char mikMmzSet[MAX + 1][MAX + 1];
static mpz_t mikMmzVal[MAX + 1][MAX + 1];

// Η function "mikPart" καλείται όποτε παραστεί ανάγκη να υπολογίσει το
// πλήθος [N:k] για πρώτη φορά. Το αποτέλεσμα κρατείται ώστε την επόμενη
// φορά να χρησιμοποιηθεί απευθείας· ο συγκεκριμένος έλεγχος γίνεται εκτός
// της function, ενώ κανονικά θα έπρεπε να γίνεται εντός της function, καθώς
// υπάρχει σημαντική διαφορά στην απόδοση.

static void mikPart(int n, int k) {
	if (debug)
	mikPartExecCount++;

	mpz_init(mikMmzVal[n][k]);

	// Στην περίπτωση που ζητάμε χωρισμό σε μία (1) ομάδα, τότε
	// προφανώς αυτό γίνεται με έναν μόνο τρόπο.

	if (k == 1) {
		mpz_set_ui(mikMmzVal[n][k], 1);
		goto MEMOIZE;
	}

	// Επίσης, στην περίπτωση που ζητάμε χωρισμό σε τόσες ομάδες
	// όσες είναι και το πλήθος των στοιχείων, αυτό γίνεται πάλι
	// με έναν μόνο τρόπο. Το ίδιο ισχύει και στην περίπτωση που
	// «περισσεύει» ένα μόνο στοιχείο.

	int m = n - k;

	if (m < 2) {
		mpz_set_ui(mikMmzVal[n][k], 1);
		goto MEMOIZE;
	}

	// Ακολουθεί κώδικας για μη τετριμμένες περιπτώσεις. Πιο
	// συγκεκριμένα, τοποθετούμε από ένα στοιχείο στην κάθε
	// ομάδα και κατόπιν δημιουργούμε όλους τους ΜΙΚ για τα
	// στοιχεία που περισσεύουν, σε ομάδες μέχρι του πλήθους
	// των ομάδων ή του πλήθους των στοιχείων αυτών, ό,τι
	// είναι μικρότερο.

	mpz_set_ui(mikMmzVal[n][k], 0);

	for (int i = (m < k ? m : k); i > 0; i--)
	MIK_PART_ADD(mikMmzVal[n][k], m, i);

MEMOIZE:
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

	for (int k = 1; k <= n; k++)
	MIK_PART_ADD(count, n, k);
}

void printDebug(void) {
	fprintf(stderr, "Calls: %llu\nExecs: %llu",
		mikPartCallCount, mikPartExecCount);

	if (mikPartCallCount)
	fprintf(stderr, " (%.2lf%%)",
		(100.0 * mikPartExecCount) / mikPartCallCount);

	putc('\n', stderr);

	for (int i = 1; i <= MAX; i++) {
		for (int j = 1; j <= MAX; j++) {
			if (!mpz_cmp_ui(mikMmzVal[i][j], 0))
			continue;

			fprintf(stderr, "[%d:%d] = ", i, j);
			mpz_out_str(stderr, 10, mikMmzVal[i][j]);
			putc('\n', stderr);
		}
	}
}
