#include "mik.h"
#include <unistd.h>
#include <string.h>

// Το πρόγραμμα δέχεται έναν ή δύο αριθμούς ως παραμέτρους. Αν δοθεί ένας
// αριθμός N, τότε υπολογίζει το [N]. Αν δοθούν δύο αριθμοί N και Μ, τότε
// υπολογίζει όλα [i] απο i = N έως i = M.
//
// By default το πρόγραμμα εκτυπώνει το πλήθος όλων των μη ισδυνάμων
// καταμερισμών για κάθε έναν αριθμό που υπολογίζει. Με την option -v
// εκτυπώνεται και ο αριθμός των στοιείων. Ωστόσο, με την option -s το
// πρόγραμμα δεν εκτυπώνει τίποτα απολύτως, απλώς κάνει τους υπολογισμούς·
// αυτή η option μπορεί να φανεί χρήσιμη κατά τις δοκιμές για να ελέγξουμε
// χρόνους εκτέλεσης κλπ.

static void usage(void) {
	fprintf(stderr, "usage: %s [-v] [-s] [-D mode] number [number]\n" \
		"mode 1: function calls\n" \
		"mode 2: print parts\n",
		progname);
	exit(EXIT_USAGE);
}

int main(int argc, char *argv[]) {
	progname = strrchr(argv[0], '/');

	if (!progname)
	progname = argv[0];

	int opt;
	int errs = 0;

	while ((opt = getopt(argc, argv, ":vsrD:")) != EOF) {
		switch (opt) {

		// By default το πρόγραμμα εκτυπώνει το [N]. Με την option -v
		// (verbose) εκτυπώνεται το N και το [N].
		case 'v':
			progopts |= MODE_VERBOSE;
			break;

		// Με την option -s ακυρώνουμε οποιοδήποτε output. Προφανώς
		// αυτό είναι κάτι που μπορεί να χρειαστεί μόνο σε μετρήσεις
		// απόδοσης.
		case 's':
			progopts |= MODE_SILENT;
			break;

		// Με την option -r αντιστρέφουμε τη σειρά των υπολογισμών.
		case 'r':
			progopts |= MODE_REVERSE;
			break;

		case 'D':
			progopts |= (atoi(optarg) << 3);
			break;

		default:
			fprintf(stderr, "%s: -%c: invalid option\n",
				progname, optopt);
			errs++;
		}
	}

	if (errs)
	usage();

	int min;
	int max;

	argc -= optind;
	argv += optind;

	// Το πρόγραμμα μπορεί να δεχθεί ως παραμέτρους έναν ή δύο θετικούς
	// ακεραίους.

	switch (argc) {

	// Αν δοθεί ένας μόνο αριθμός N, τότε το πρόγραμμα θα υπολογίσει
	// το [N].
	case 1:
		min = atoi(argv[0]);
		max = min;
		break;

	// Αν δοθούν δύο αριθμοί N και M, τότε το πρόγραμμα θα εκτυπώσει
	// όλα τα [i] με το i να λαμβάνει τιμές από το N έως και το M.
	case 2:
		min = atoi(argv[0]);
		max = atoi(argv[1]);
		break;

	default:
		usage();
	}

	// Υπάρχει κάποιο όριο της τάξης του 10000, αλλά το πρόγραμμα θα
	// μπορούσε να υπολογίζει ακριβή αποτελέσματα και για μεγαλύτερους
	// αριθμούς.

	if (max > MAX) {
		fprintf(stderr, "%s: %d: max number overflow\n",
			progname, max);
		exit(EXIT_OVERFLOW);
	}

	int n;
	int step;

	if (min <= max) {
		n = max - min;
		step = 1;
	}

	// Σε περίπτωση που το M είναι μικρότερο από το N γίνονται οι
	// υπολογισμοί με αντίστροφη σειρά.

	else {
		n = min - max;
		step = -1;
	}

	if (progopts & MODE_REVERSE) {
		int t = min;

		min = max;
		max = t;
		step = -step;
	}

	mpz_t mik;
	mpz_init(mik);

	for (int i = min; n >= 0; i += step, n--) {
		mikAll(mik, i);

		if (progopts & MODE_SILENT)
		continue;

		if (progopts & MODE_VERBOSE)
		printf("%d ", i);

		mpz_out_str(stdout, 10, mik);
		putchar('\n');
	}

	mpz_clear(mik);
	printDebug();
	exit(0);
}
