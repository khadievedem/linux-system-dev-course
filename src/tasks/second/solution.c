#include <dlfcn.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

int (*func_prototype)(int);

bool init_library(const char *lib_name, const char *func_name) {
  void *hdl = dlopen(lib_name, RTLD_LAZY);
  if (NULL == hdl) {
    return false;
  }
  func_prototype = (int (*)(int))dlsym(hdl, func_name);
  if (NULL == func_prototype) {
    return false;
  }
  return true;
}

int main(int argc, char *argv[]) {
  if (init_library(argv[1], argv[2])) {
    int arg;
    sscanf(argv[3], "%d", &arg);
    printf("%d\n", func_prototype(arg));
  }
  return 0;
}
