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
//
// By default το πρόγραμμα χρησιμοποιεί memoization προκειμένου να κρατά
// στη μνήμη στοιχεία μερικών υπολογισμών [N:k]. Μπορούμε, όμως, να τρέξουμε
// το πρόγραμμα χωρίς memoization με την option -m· αυτός ο τρόπος υπολογισμού
// λέγεται straight και έχει νόημα πάλι σε περιπτώσεις ελέγχου απόδοσης κλπ.
//
// Προκειμένου να διευρύνουμε το εύρος των υπολογισμών, καταφεύγουμε σε long
// double data types για στοιχεία του προγράμματος που μπορεί να πάρουν πολύ
// μεγάλες τιμές. Ωστόσο, υπάρχει κάποιο όριο που θέτει το πρόγραμμα ώστε να
// αποφευχθούν εξωτικές καταστάσεις και παραπλανητικά αποτελέσματα. Το όριο
// αυτό σήμερα είναι της τάξης του 10000.
//
// XXX
// Για N > 416 οι τιμές που δίνει το πρόγραμμα είναι μάλλον προσεγγιστικές.

static void usage(void) {
	fprintf(stderr, "usage: %s [-m] [-v] [-s] number [number]\n",
		progname);
	exit(EXIT_USAGE);
}

int main(int argc, char *argv[]) {
	progname = strrchr(argv[0], '/');

	if (!progname)
	progname = argv[0];

	int opt;
	int verbose = 0;
	int silent = 0;
	int errs = 0;

	while ((opt = getopt(argc, argv, ":mvs")) != EOF) {
		switch (opt) {

		// By default το πρόγραμμα χρησιμοποιεί memoization. Με την
		// option -m ακυρώνουμε το memoization.
		case 'm':
			mikPart = mikPartStraight;
			break;

		// By default το πρόγραμμα εκτυπώνει το [N]. Με την option -v
		// (verbose) εκτυπώνεται το N και το [N].
		case 'v':
			verbose = 1;
			break;

		// Με την option -s ακυρώνουμε οποιοδήποτε output. Προφανώς
		// αυτό είναι κάτι που μπορεί να χρειαστεί μόνο σε μετρήσεις
		// απόδοσης.
		case 's':
			silent = 1;
			break;

		default:
			fprintf(stderr, "%s: %c: invalid option\n",
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

	// XXX
	// Υπάρχει κάποιο όριο της τάξης του 10000, αλλά το πρόγραμμα βγάζει
	// ακριβή αποτελέσματα μέχρι και τον αριθμό 416. Για μεγαλύτερους
	// αριθμούς το πρόγραμμα υπολογίζει προσεγγιστικά αποτελέσματα.

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

	for (int i = min; n >= 0; i += step, n--) {
		long double mik = mikAll(i);

		if (silent)
		continue;

		if (verbose)
		printf("%d ", i);

		printf("%.0Lf\n", mik);
	}

	exit(0);
}
