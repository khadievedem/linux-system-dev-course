#include <ctype.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static char procdirn[] = "/proc/";
static char genenv[] = "genenv";

int filter(const struct dirent *dir) {
  int i; /* the checker using C89 */
  for (i = 0; dir->d_name[i] != '\0'; i++) {
    if (!isdigit(dir->d_name[i]))
      return 0;
  }

  char *pathname;
  pathname = malloc(sizeof(*pathname) * strlen(procdirn));
  pathname[0] = '\0';
  strcat(pathname, procdirn);
  strcat(pathname, dir->d_name);
  strcat(pathname, "/stat");

  char *buf = malloc(64);
  int fd = open(pathname, 0);
  char *ret;

  free(pathname);

  read(fd, buf, 62);
  buf[63] = '\0';
  ret = strstr(buf, genenv);
  close(fd);

  return ret ? 1 : 0;
}

int main() {
  struct dirent **namelist;
  printf("%d\n", scandir(procdirn, &namelist, &filter, NULL));

  return 0;
}
