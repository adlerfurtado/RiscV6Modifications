#include "../kernel/types.h"
#include "../kernel/syscall.h"
#include "user.h"

void
assert_count(char *name, int syscall_num, int before, int after, int expected)
{
  if(after == before + expected)
    printf("PASS: %s count changed from %d to %d\n", name, before, after);
  else
    printf("FAIL: %s expected %d -> %d, but got %d -> %d\n",
           name, before, before + expected, before, after);
}

int
main(void)
{
  int before, after;
  int pid;

  printf("=== Exact syscall count test ===\n");

  // ------------------------
  // getpid: exactly 1 call
  // ------------------------
  before = getcnt(SYS_getpid);
  getpid();
  after = getcnt(SYS_getpid);
  assert_count("getpid", SYS_getpid, before, after, 1);

  // ------------------------
  // sbrk: exactly 1 call
  // ------------------------
  before = getcnt(SYS_sbrk);
  sbrk(1);
  after = getcnt(SYS_sbrk);
  assert_count("sbrk", SYS_sbrk, before, after, 1);

  // ------------------------
  // fork: exactly 1 call
  // ------------------------
  before = getcnt(SYS_fork);
  pid = fork();
  if(pid == 0){
    exit(0);
  }
  wait(0);
  after = getcnt(SYS_fork);
  assert_count("fork", SYS_fork, before, after, 1);

  // ------------------------
  // wait: exactly 1 call
  // ------------------------
  pid = fork();
  if(pid == 0){
    exit(0);
  }

  before = getcnt(SYS_wait);
  wait(0);
  after = getcnt(SYS_wait);
  assert_count("wait", SYS_wait, before, after, 1);

  // ------------------------
  // getcnt: exactly 1 call
  // ------------------------
  before = getcnt(SYS_getcnt);
  after = getcnt(SYS_getcnt);
  assert_count("getcnt", SYS_getcnt, before, after, 1);

  printf("=== Test finished ===\n");
  exit(0);
}