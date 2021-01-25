#include "mik.h"

char *progname = "mik";
long double (*mikPart)(int, int) = mikPartMemoize;
