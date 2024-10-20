#include <stdio.h>
void blue () {
  printf("\033[1;34m");
}

void green() {
  printf("\033[1;32m");
}

void reset () {
  printf("\033[0m");
}

int main () {
  blue();
  printf("Hello ");
  green();
  printf("world\n");
  reset();
  return 0;
}