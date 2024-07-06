#include <stdio.h>
#include <time.h>
#include <unistd.h>
int main(void)
{
  char buf[40];
  time_t now = time(0);
  while (1) {
    strftime(buf, 40, "%a %b %d %T", localtime(&now));
    puts(buf);
    fflush(stdout);
    sleep(1);
    now = time(0);
  }
}

