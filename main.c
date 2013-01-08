#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include "race_condition.h"

#define NUM_THREADS 2

volatile counter_t in = 0;

counter_t get_number(const char* str) {
  counter_t result;
  char* endptr;
  // errno is set by strtoul in case something bad happens
  errno = 0;
  result = strtoul(str, &endptr, 10);
  // endptr points to the beginning of the string if no conversion occurred
  if (errno != 0 || endptr == str) {
    // zero is useless enough to be an error code in our case
    result = 0;
  }
  return result;
}

int main(int argc, const char** argv) {
  // check cli parameters
  if (argc < 2) {
    printf("No argument given.\n");
    printf("Usage: race_condition NUMBER_OF_ITERATIONS\n");
    return EXIT_FAILURE;
  }
  
  // convert the command line argument and check for conversion errors
  counter_t count_max = get_number(argv[1]);
  if (count_max == 0) {
    printf("Invalid argument given.\n");
    return EXIT_FAILURE;
  }
  
  pthread_t threads[NUM_THREADS];
  // pass count max as a pointer so its pointee is still valid after exiting
  // create_threads
  int err = create_threads(threads, NUM_THREADS, &count_max);
  if (err != 0) {
    printf("Could not create threads.\n");
    return EXIT_FAILURE;
  }
  
  // wait for all threads to finish
  join_threads(threads, NUM_THREADS);
  
  printf("All threads done. Variable in is now %lu.\n", in);
    
  pthread_exit(NULL);
}