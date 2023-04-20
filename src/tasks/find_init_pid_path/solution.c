#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int get_t_ID(int cur_pid, char _t) {
  int ans_id;
  char *f_p = malloc(BUFSIZ + 1);

  sprintf(f_p, "/proc/%d/status", cur_pid);
  int fd = open(f_p, 0);
  read(fd, f_p, BUFSIZ);
  switch (_t) {
  case 'g':
    sscanf(f_p, "%*s %*s %*s %*s %*s %*s %*s %*s %d", &ans_id);
    break;
  case 'p':
    sscanf(f_p, "%*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %*s %d",
           &ans_id);
    break;
  default:
    ans_id = -1;
    goto exit_label;
  }
exit_label:
  close(fd);
  free(f_p);
  return ans_id;
}

int main(int argc, char *argv[]) /* get PID as a 2nd argument */
{
  int cur_pid = atoi(argv[1]);
  int prev_pid = -1;
  int prev_tgid = -1;
  while (cur_pid != 1) {
    if (prev_pid != cur_pid && cur_pid != prev_tgid)
      printf("%d\n", cur_pid);
    int Tgid = get_t_ID(cur_pid, 'g');
    int PPid = get_t_ID(cur_pid, 'p');
    if (Tgid != PPid && Tgid != prev_tgid && cur_pid != Tgid) {
      printf("%d\n", Tgid);
    }
    prev_tgid = Tgid;
    prev_pid = cur_pid;
    cur_pid = PPid;
  }
  printf("1\n");

  return 0;
}
