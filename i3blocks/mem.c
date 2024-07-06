#include <stdio.h>
#include <stdlib.h>
#include <sys/sysinfo.h>
#include <time.h>

int main(void)
{
  char *envvar   = NULL;
  int critical   = (envvar = getenv("critical")) ? atoi(envvar) : 95;
  int warning    = (envvar = getenv("warning"))  ? atoi(envvar) : 70;
  float interval = 0.5;
  char *color_warning  = (envvar = getenv("color_warning"))  ? envvar : "#F77";
  char *color_critical = (envvar = getenv("color_critical")) ? envvar : "#FA0";
  struct timespec tm = {
    .tv_sec  = interval,
    .tv_nsec = ((int)(interval*1000)%1000)*1000000
  };
  struct sysinfo info;

  while (1) {
    sysinfo(&info);

    float percent = 100*((double)(info.totalram-info.freeram-info.bufferram-
                        info.sharedram)/info.totalram);

    printf("<span color='%s'>%.0f%%</span>\n",
        (percent > critical) ? color_critical :
        (percent > warning ) ? color_warning  : "#FFF", percent);
//printf("%.2fG (%.0f%%)</span>\n", usage/1073741824, percent);

    fflush(stdout);

    nanosleep(&tm, 0);
  }
}
