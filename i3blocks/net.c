#include <fcntl.h>
#include <time.h>
#include <unistd.h>

int main(void)
{
  // /proc/net/wireless header size: 162 bytes
  char buf[163];
  int fd = open("/proc/net/wireless", O_RDONLY);
  struct timespec tm = {.tv_sec = 0, .tv_nsec = 500000000};
  while (1) {
    write(1, read(fd, buf, 163) > 162 ? "🌐\n" : "🛩\n", 5);
    lseek(fd, 0, SEEK_SET);
    nanosleep(&tm, 0);
  }
}
