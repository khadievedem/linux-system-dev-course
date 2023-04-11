/* #include "hello.h" */
#include <dlfcn.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

void (*print_msg)(const char *);

bool init_library() {
  void *hdl = dlopen("lib/libhello.so", RTLD_LAZY);
  if (NULL == hdl) {
    return false;
  }
  print_msg = (void (*)(const char *))dlsym(hdl, "print_msg");
  if (NULL == print_msg) {
    return false;
  }
  return true;
}

int main() {
  if (init_library())
    print_msg("hello world!");
  else
    printf("Library was not found!\n");
  return 0;
}
