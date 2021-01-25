#include <stdlib.h>
#include <stdio.h>

#define EXIT_USAGE 1
#define EXIT_OVERFLOW 2

#define MAX 10000

extern char *progname;
extern long double (*mikPart)(int, int);

extern int main(int, char *[]);
extern long double mikAll(int);
extern long double mikPartMemoize(int, int);
extern long double mikPartStraight(int, int);
