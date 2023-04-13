#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  char *f_p = malloc(100);
  sprintf(f_p, "/proc/%d/stat", getpid());
  FILE *stat_file = fopen(f_p, "r");

  int ppid;
  fscanf(stat_file, "%*d %*s %*c %d", &ppid);

  printf("%d\n", ppid);

  free(f_p);
  return 0;
}
