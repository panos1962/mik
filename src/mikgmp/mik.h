#include <stdlib.h>
#include <stdio.h>
#include <gmp.h>

#define EXIT_USAGE 1
#define EXIT_OVERFLOW 2

#define MAX 10000

extern char *progname;

extern int debug;
extern unsigned long long mikPartCallCount;
extern unsigned long long mikPartExecCount;

extern int main(int, char *[]);
extern void mikAll(mpz_t, int);
