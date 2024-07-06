// Licensed under the terms of the GNU GPL v3, or any later version.
// Copyright 2019 Nolan Leake <nolan@sigbus.net>
// Loosely based on bandwidth2 (originally by Guillaume Coré <fridim@onfi.re>)

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

#define RED "#F77"
#define ORANGE "#FA0"

size_t get_usage(long *used_jiffies)
{
  FILE *fd;
  if (!(fd = fopen("/proc/stat", "r"))) perror("fopen /proc/stat: "), exit(1);
  long user, nice, sys, idle, iowait, irq, sirq, steal, guest, nguest;
  if (fscanf(fd, "cpu %ld %ld %ld %ld %ld %ld %ld %ld %ld %ld", &user, &nice,
      &sys, &idle, &iowait, &irq, &sirq, &steal, &guest, &nguest) != 10)
        perror("No read /proc/stat:"), exit(1);
  fclose(fd);

  *used_jiffies = user + nice + sys + irq + sirq + steal + guest + nguest;
  return *used_jiffies + idle + iowait;
}

int main()
{
  long old_total, old_used, used, total;

  old_total = get_usage(&old_used);

  while (1) {
    sleep(1);
    total = get_usage(&used);

    printf(" %02.0f%%\n", 100.0 * (used - old_used) / (total - old_total));
    fflush(stdout);

    old_total = total;
    old_used = used;
  }
}
