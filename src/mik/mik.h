#include <stdlib.h>
#include <stdio.h>

#define EXIT_USAGE 1
#define EXIT_OVERFLOW 2

#define MAX 10000

extern char *progname;
extern double (*mikPart)(int, int);

extern int main(int, char *[]);
extern double mikAll(int);
extern double mikPartMemoize(int, int);
extern double mikPartStraight(int, int);
