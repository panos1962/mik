#include "mik.h"

char *progname = "mik";
double (*mikPart)(int, int) = mikPartMemoize;
