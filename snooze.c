/*
 * snooze.c
 *
 * 编写一个 sleep 的包装函数，叫做 snooze，带有下面的接口
 *
 * unsigned int snooze(unsigned int secs);
 */

#include <stdio.h>

#include <unistd.h>

unsigned int snooze(unsigned int secs)
{
  unsigned sleep_secs;

  sleep_secs = sleep(secs);

  printf("Slept for %u of %u secs\n", secs - sleep_secs, secs);
  return sleep_secs;
}

int main(void)
{
  snooze(3);
  return 0;
}

/* snooze.c ends here */
