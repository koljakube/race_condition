#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "race_condition.h"

#define NUM_THREADS 2

volatile counter_t in = 0;

counter_t get_number(const char* str) {
  counter_t result;
  char* endptr;
  errno = 0;
  result = strtoul(str, &endptr, 10);
  if (errno != 0 || endptr == str) {
    result = 0;
  }
  return result;
}

int main(int argc, const char** argv) {
  if (argc < 2) {
    printf("No argument given.\n");
    return EXIT_FAILURE;
  }
  
  counter_t count_max = get_number(argv[1]);
  if (count_max == 0) {
    printf("Invalid argument given.\n");
    return EXIT_FAILURE;
  }
  
  pthread_t threads[NUM_THREADS];
  int err = create_threads(threads, NUM_THREADS, count_max);
  if (err != 0) {
    printf("Could not create threads.\n");
  }
  
  join_threads(threads, NUM_THREADS);
  
  printf("All threads done. Variable in is now %lu.\n", in);
    
  pthread_exit(NULL);
}