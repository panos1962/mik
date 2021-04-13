#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

#define EXIT_USAGE 1
#define EXIT_OVERFLOW 2

#define MODE_VERBOSE 1
#define MODE_SILENT 2
#define MODE_REVERSE 4
#define MODE_DEBUG_CALLS 8
#define MODE_DEBUG_PARTS 16

#define MAX 16384

extern char *progname;
extern unsigned progopts;

extern int main(int, char *[]);
extern void mikAll(mpz_t, int);
extern void printDebug(void);
