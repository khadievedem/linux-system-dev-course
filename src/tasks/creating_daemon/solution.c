#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  printf("%d", getpid());

  daemon(0, 0);
  while (1) {
  }

  return 0;
}
