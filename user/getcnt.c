#include "../kernel/types.h"
#include "user.h"

int
main(int argc, char *argv[])
{
  int num = atoi(argv[1]);

  int cnt = getcnt(num);

  if (cnt == -1) {
    printf("syscall %d not valid\n", num);
  }
  else if (cnt == 1) {
    printf("syscall %d has been called 1 time\n", num);
  }
  else {
    printf("syscall %d has been called %d times\n", num, cnt);
  }

  exit(0);
}