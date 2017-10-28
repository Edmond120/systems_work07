#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "random.h"

int errsv;

char genrand(int bytes) {
  errno = 0;
  int randfd = open("/dev/random", O_RDONLY);
  errsv = errno;
  if (errsv) {
    printf("Error %d: %s\n", errsv, strerror(errsv));
  }

  char buf[bytes];
  errno = 0;
  read(randfd, buf, bytes);
  if (errsv) {
    errsv = errno;
    printf("Error %d: %s\n", errsv, strerror(errsv));
  }

  errno = 0;
  if (close(randfd) == -1) {
    errsv = errno;
    printf("Error %d: %s\n", errsv, strerror(errsv));
  }

  return *buf;
}

