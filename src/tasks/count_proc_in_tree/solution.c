#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int count_all_children(const int pid) {
  char *ch_f = malloc(BUFSIZ);
  sprintf(ch_f, "/proc/%d/task/%d/children", pid, pid);
  int fd = open(ch_f, 0);
  memset(ch_f, 0, BUFSIZ);
  if (!read(fd, ch_f, BUFSIZ)) {
    free(ch_f);
    return 0;
  }
  int res = 0;
  int temp;
  const char *p = ch_f;
  while (sscanf(p, "%d", &temp) == 1) {
    res += count_all_children(temp) + 1;
    p = strchr(p, ' ') + 1;
  }
  free(ch_f);
  return res;
}

int main(int argc, char *argv[]) {
  printf("%d\n", count_all_children(atoi(argv[1])) + 1);
  return 0;
}
