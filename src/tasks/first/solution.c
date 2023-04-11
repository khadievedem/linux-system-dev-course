#include "solution.h"
#include <stddef.h>
#include <stdio.h>

int stringStat(const char *string, size_t multiplier, int *count) {
  int res = 0;
  for (; *string; res++, string++)
    ;
  count++;
  return res * multiplier;
}
