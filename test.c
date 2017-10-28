#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "random.h"

#define NUMS 10
#define NUMSIZE sizeof(char)
#define FILENAME "numbers.txt"

int errsv;

int main() {
  int i;

  printf("Generating numbers.\n");
  char *numbers = calloc(NUMS, NUMSIZE);
  for (i = 0; i < NUMS; i++) {
    numbers[i] = genrand(NUMSIZE);
    printf("numbers[%d]: %d\n", i, numbers[i]);
  }

  printf("Writing numbers to %s.\n", FILENAME);
  errno = 0;
  int filefd = open(FILENAME, O_CREAT | O_WRONLY | O_TRUNC, 0600);
  errsv = errno;
  if (errno) {
    printf("Error %d: %s\n", errsv, strerror(errsv));
  }

  errno = 0;
  write(filefd, numbers, NUMS * NUMSIZE);
  if (errno) {
    errsv = errno;
    printf("Error %d: %s\n", errsv, strerror(errsv));
  }
  free(numbers);

  errno = 0;
  if (close(filefd) == -1) {
    errsv = errno;
    printf("Error %d: %s\n", errsv, strerror(errsv));
  }

  //

  printf("Reading numbers from file.\n");
  errno = 0;
  filefd = open(FILENAME, O_RDONLY);
  errsv = errno;
  if (errno) {
    printf("Error %d: %s\n", errsv, strerror(errsv));
  }

  numbers = calloc(NUMS, NUMSIZE);
  errno = 0;
  read(filefd, numbers, NUMS * NUMSIZE);
  if (errno) {
    errsv = errno;
    printf("Error %d: %s\n", errsv, strerror(errsv));
  }

  for (i = 0; i < NUMS; i++) {
    printf("numbers[%d]: %d\n", i, numbers[i]);
  }
  free(numbers);

  errno = 0;
  if (close(filefd) == -1) {
    errsv = errno;
    printf("Error %d: %s\n", errsv, strerror(errsv));
  }

  return 0;
}

