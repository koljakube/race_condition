#include <pthread.h>

// #define DO_YIELD

typedef unsigned long int counter_t;

volatile counter_t in;

int create_threads(pthread_t* threads, size_t thread_count, counter_t count_max);
void join_threads(pthread_t* threads, size_t thread_count);
